#pragma once

#ifndef CR_PLATFORM_GLFW
#error "GLFW-only header included, but CR_PLATFORM_GLFW is not set."
#endif

#include "crean/core/types.hpp"

#include <GLFW/glfw3.h>

namespace crean
{
    // Singleton wrapper over GLFW to ensure it is initialized first and then
    // only terminated once.
    class Glfw
    {
    public:
        static Glfw & get();

        Glfw(const Glfw &other) = delete;
        Glfw & operator=(const Glfw &other) = delete;
        Glfw(Glfw &&other) = delete;
        Glfw & operator=(Glfw &&other) = delete;

        GLFWwindow * create_window(uvec2 size, const string &title);
        void destroy_window(GLFWwindow *window_ptr);
        void poll_events();
        string version() const;
        void window_hint(i32 hint, i32 value);
        bool window_should_close(GLFWwindow *window_ptr) const;

    private:
        Glfw();
        ~Glfw();
    };
}
