#pragma once

#ifndef CR_PLATFORM_GLFW
#error "GLFW-only header included, but CR_PLATFORM_GLFW is not set."
#endif

#include "crean/platform/platform.hpp"

namespace crean
{
    struct Platform::ImplData
    {

    };
}
