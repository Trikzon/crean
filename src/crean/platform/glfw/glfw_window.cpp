#ifndef CR_PLATFORM_GLFW
#error "GLFW-only source compiled, but CR_PLATFORM_GLFW is not set."
#endif

#include "crean/platform/glfw/glfw_window.hpp"

#include "crean/platform/glfw/glfw.hpp"

namespace crean
{
// public:
    Window::~Window()
    {
        Glfw::get().destroy_window(m_data_ptr->glfw_window_ptr);
    }

    bool Window::should_close() const
    {
        return Glfw::get().window_should_close(m_data_ptr->glfw_window_ptr);
    }

// private:
    Window::Window(const uvec2 size, const string &title) : m_data_ptr(std::make_unique<ImplData>())
    {
        auto &glfw = Glfw::get();

        glfw.window_hint(GLFW_RESIZABLE, false);

        #ifdef CR_GRAPHICS_VULKAN
            glfw.window_hint(GLFW_CLIENT_API, GLFW_NO_API);
        #endif

        m_data_ptr->glfw_window_ptr = glfw.create_window(size, title);
    }
}
