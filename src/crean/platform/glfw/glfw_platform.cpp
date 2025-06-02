#ifndef CR_PLATFORM_GLFW
#error "GLFW-only source compiled, but CR_PLATFORM_GLFW is not set."
#endif

#include "crean/platform/glfw/glfw_platform.hpp"

#include "crean/platform/glfw/glfw.hpp"

namespace crean
{
// public:
    Platform::Platform()
    {
        m_data_ptr = std::make_unique<ImplData>();

        Glfw::get();  // Initialize GLFW.
    }

    Platform::~Platform()
    {

    }

    std::shared_ptr<Window> Platform::create_window(const uvec2 size, const string &title)
    {
        return std::shared_ptr<Window>(new Window{size, title});
    }

    void Platform::process_events()
    {
        Glfw::get().poll_events();
    }
}
