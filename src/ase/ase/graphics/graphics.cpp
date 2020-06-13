#include "asepch.hpp"
#include "ase/graphics/graphics.hpp"

#include "ase/debug/log.hpp"

#include <glew.h>

namespace ase
{
    void Graphics::Init()
    {
        Debug::Log("Graphics: Initialising Context");
        InitContext();
        Debug::Log("Graphics: Initialised Context");
    }

    void Graphics::InitContext()
    {
        glewInit();
    }
}
