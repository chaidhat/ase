#pragma once

// huge thank you to jrKok
// 
// https://forums.x-plane.org/index.php?/forums/topic/214939-implementing-modern-opengl/&tab=comments#comment-1939223
// https://github.com/jrKok/VR-Tools/blob/master/VR_Tools/drawlogic.h
// https://github.com/jrKok/VR-Tools/blob/master/VR_Tools/drawlogic.cpp

namespace ase
{
    struct textureColor
    {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        unsigned char alpha;
    };

    const int c_maxWWidth = 1400;
    const int c_maxWHeight = 1200;

    class Graphics;

    class Texture
    {
    friend Graphics;
    public:
        void Init();

    private:
        int m_textNum;
        int windowWidth, windowHeight;
        std::array<textureColor, c_maxWWidth*c_maxWHeight> textureZone;
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
        static bool hasToUpdate;
        static unsigned int shaderProgram, VAO, VBO, EBO;
    };
}
