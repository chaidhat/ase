#include "asepch.hpp"
#include "ase/graphics/graphics.hpp"

#include "ase/debug/log.hpp"

#include <glew.h>

namespace ase
{
    // static variable intialisations
    unsigned int Graphics::shaderProgram = 0;
    unsigned int Graphics::VAO = 0;
    unsigned int Graphics::VBO = 0;
    unsigned int Graphics::EBO = 0;

    Texture* Graphics::s_texture = nullptr;

    XPLMWindowID Graphics::myWindow = 0;

    int Graphics::DrawCallbackXp (XPLMDrawingPhase     inPhase,
                                   int                  inIsBefore,
                                   void *               inRefcon)
    {
        //TODO: add try/catch statement
        Graphics::Render();
        return 1;
    }

    Texture::Texture()
    {
        XPLMGenerateTextureNumbers(&m_textNum, 1);

        XPLMBindTexture2d(m_textNum, 0);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,windowWidth,windowHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &textureZone);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    Texture::~Texture()
    {
        //TODO: check this for memory leaks
        XPLMBindTexture2d(m_textNum, 0);
        GLuint t = static_cast<GLuint>(m_textNum);
        glDeleteTextures(1, &t);
    }

    void Graphics::Init()
    {
        //TODO: add try/catch statement here too
        XPLMRegisterDrawCallback(DrawCallbackXp, xplm_Phase_Gauges, 0, NULL);
        Debug::Log("Graphics: Initialising context");
        InitContext();
        Debug::Log("Graphics: Initialising textures");
        s_texture = new Texture();

        textureColor colour;
        colour.red = 255;
        colour.green = 128;
        colour.blue = 128;
        colour.alpha = 255; 
        s_texture->textureZone.fill(colour);
        s_texture->m_fHasToUpdate = true;

        Debug::Log("Graphics: Finished initialisation");

    }

    void Graphics::Render()
    {
        int wW(0),wH(0);/*screenL(0),screenR(0),screenT(0),screenB(0);
         XPLMGetWindowGeometry(myWindow,&screenL,&screenT,&screenR,&screenB);*/
        int screenL, screenT, screenR, screenB;
        if (XPLMWindowIsInVR(myWindow)){
            /*
            XPLMGetWindowGeometryVR(Graphics::myWindow,&wW,&wH);
            if (wW!=windowWidth||wH!=windowHeight){
                windowWidth=wW;
                windowHeight=wH;
            }
            */
        }
        else {
            XPLMGetWindowGeometry(myWindow,&screenL,&screenT,&screenR,&screenB);
           wW=screenR-screenL;
           wH=screenT-screenB;
           glPushAttrib(GL_VIEWPORT_BIT);
           glViewport(screenL,screenB,wW,wH);
        }

        XPLMSetGraphicsState(
            0,   // No fog, equivalent to glDisable(GL_FOG);
            0,   // No texture
            0,   // No lighting, equivalent to glDisable(GL_LIGHT0);
            0,   // No alpha testing, e.g glDisable(GL_ALPHA_TEST);
            1,   // Use alpha blending, e.g. glEnable(GL_BLEND);
            1,   // No depth read, e.g. glDisable(GL_DEPTH_TEST);
            0);
        XPLMBindTexture2d(s_texture->m_textNum,0);
        if (s_texture->m_fHasToUpdate){
            glTexSubImage2D(GL_TEXTURE_2D,
                        0,  // mipmap level
                        0,  // x-offset
                        0,  // y-offset
                        s_texture->windowWidth,
                        s_texture->windowHeight,
                        GL_RGBA8,           // color bytes of data we are sending
                        GL_UNSIGNED_BYTE,  // encoding of data we are sending
                        &s_texture->textureZone);
            s_texture->m_fHasToUpdate=false;
        }


        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glBindVertexArray(0);
        glUseProgram(0);
        if (!XPLMWindowIsInVR(myWindow)) glPopAttrib();
    }

    void Graphics::InitContext()
    {
        //TODO: put a try/catch around the init
        glewInit();

        //shader sources
        const char *vertexShaderSource = "#version 330 core\n"
           "layout (location = 0) in vec2 aPos;\n"
           "layout (location = 1) in vec2 aTexCoord;\n\n"
           "out vec2 TexCoord;\n"
           "void main()\n"
           "{\n"
           "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
           "   TexCoord = vec2(aTexCoord.x,aTexCoord.y);\n"
           "}\0";

        const char *fragmentShaderSource = "#version 330 core\n"
           "out vec4 FragColor;\n"
           "in vec2 TexCoord;\n"
           "uniform sampler2D texture1;\n"
           "void main()\n"
           "{\n"
           "   FragColor = texture(texture1, TexCoord);\n"
           "}\n\0";

        // vertex shader compile
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);
        CheckCompileErrors(vertexShader, "VERTEX");

        //fragment shader compile
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);
        CheckCompileErrors(fragmentShader, "FRAGMENT");

        // merge shaders in Program
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        CheckCompileErrors(shaderProgram, "PROGRAM");

        // Make space
        glDetachShader(shaderProgram, vertexShader);
        glDetachShader(shaderProgram, fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        //generate Vertex data
        float vertices[] = {
                     //1.0f,  1.0f, 1.0f, 1.0f,  // right top
                     1.0f,  0.0f, 1.0f, 1.0f,  // right top
                     1.0f, -1.0f, 1.0f, 0.0f,  // right bottom
                    -1.0f, -1.0f, 0.0f, 0.0f,  // left bottom
                    -1.0f,  1.0f, 0.0f, 1.0f  // left top
        };
        unsigned int indices[] = {
                      0, 1, 3,  // first Triangle
                      1, 2, 3   // second Triangle
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        //Prime uniform for use of texture unit 0
        glUseProgram(shaderProgram);
        glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);

        //hopefully this it not needed but don't want anybody to mess with my VAO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    void Graphics::CheckCompileErrors(unsigned int shader, std::string type)
    {
        // should be done only in debug builds!
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        else
            glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (success)
            Debug::Log("Graphics: Shader " + type + " compiled OK");
        else
        {
            Debug::Log("Graphics: Shader " + type + " compiled FAIL");

            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::string ilog=infoLog;
            Debug::Log("ERROR::SHADER_COMPILATION_ERROR of type: "+ilog); 
            //TODO: throw error
        }
    }
}
