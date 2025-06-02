#include <crean/platform/platform.hpp>

using namespace crean;

int main()
{
    Platform platform;

    const auto window_ptr = platform.create_window({200, 200}, "Window 1");
    const auto window2_ptr = platform.create_window({100, 250}, "Window 2");

    while (!window_ptr->should_close() && !window2_ptr->should_close())
    {
        platform.process_events();
    }

    return 0;
}
