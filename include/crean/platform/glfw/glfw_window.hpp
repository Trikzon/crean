#pragma once

#ifndef CR_PLATFORM_GLFW
#error "GLFW-only header included, but CR_PLATFORM_GLFW is not set."
#endif

#include "crean/platform/window.hpp"

#include <GLFW/glfw3.h>

namespace crean
{
    struct Window::ImplData
    {
        GLFWwindow *glfw_window_ptr;
    };
}
