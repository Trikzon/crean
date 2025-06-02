#pragma once

#include "crean/platform/window.hpp"

namespace crean
{
    class Platform
    {
    public:
        Platform();
        ~Platform();
        Platform(const Platform &other) = delete;
        Platform & operator=(const Platform &other) = delete;
        Platform(Platform &&other) = delete;
        Platform & operator=(Platform &&other) = delete;

        std::shared_ptr<Window> create_window(uvec2, const string &title);
        void process_events();

    private:
        struct ImplData;

        std::unique_ptr<ImplData> m_data_ptr;
    };
}
