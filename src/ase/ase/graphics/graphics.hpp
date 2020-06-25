#pragma once

// huge thank you to jrKok
// 
// https://forums.x-plane.org/index.php?/forums/topic/214939-implementing-modern-opengl/&tab=comments#comment-1939223
// https://github.com/jrKok/VR-Tools/blob/master/VR_Tools/drawlogic.h
// https://github.com/jrKok/VR-Tools/blob/master/VR_Tools/drawlogic.cpp

namespace ase
{
    typedef unsigned char color;
    struct textureColor
    {
        textureColor();
        textureColor(color red, color green, color blue, color alpha);
        ~textureColor();
        
        color red;
        color green;
        color blue;
        color alpha;
    };

    const int c_maxWWidth = 1024;
    const int c_maxWHeight = 1024;

    class Texture
    {
    public:
        Texture();
        ~Texture();

        void Load(const unsigned char* image, const int imageSizeX, const int imageSizeY);
        void Render();

        std::array<textureColor, c_maxWWidth*c_maxWHeight> textureZone;
    private:
        int m_textNum;
        bool m_fHasToUpdate;
        int windowWidth, windowHeight;

        void InitContext();
    };

    class Graphics
    {
    public:
        static int DrawCallbackXp(XPLMDrawingPhase     inPhase,
                                   int                  inIsBefore,
                                   void *               inRefcon);

        static void Init();
        static void Render();

    private:
        static void InitContext();
        static void CheckCompileErrors(unsigned int shader, std::string type);

        static Texture* s_texture;
        static XPLMWindowID myWindow;
        static unsigned int shaderProgram, VAO, VBO, EBO;
    };
}
