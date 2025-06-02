#ifndef CR_PLATFORM_GLFW
#error "GLFW-only source compiled, but CR_PLATFORM_GLFW is not set."
#endif

#include "crean/platform/glfw/glfw.hpp"

#include "crean/core/logger.hpp"

namespace crean
{
// public:
    Glfw & Glfw::get()
    {
        static Glfw instance;
        return instance;
    }

    GLFWwindow * Glfw::create_window(const uvec2 size, const string &title)
    {
        const auto window_ptr = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
        CR_ASSERT(window_ptr, "Failed to create window {} at size {}x{}.", title, size.x, size.y);
        CR_TRACE("Created window \"{}\" at size {}x{}.", title, size.x, size.y);
        return window_ptr;
    }

    void Glfw::destroy_window(GLFWwindow *window_ptr)
    {
        glfwDestroyWindow(window_ptr);
    }

    void Glfw::poll_events()
    {
        glfwPollEvents();
    }

    string Glfw::version() const
    {
        return glfwGetVersionString();
    }

    void Glfw::window_hint(const i32 hint, const i32 value)
    {
        glfwWindowHint(hint, value);
    }

    bool Glfw::window_should_close(GLFWwindow *window_ptr) const
    {
        return glfwWindowShouldClose(window_ptr);
    }

// private:
    Glfw::Glfw()
    {
        CR_ASSERT(glfwInit(), "Failed to initialize GLFW.");
        CR_TRACE("Initialized GLFW v{}.", version());
    }

    Glfw::~Glfw()
    {
        glfwTerminate();
    }
}
