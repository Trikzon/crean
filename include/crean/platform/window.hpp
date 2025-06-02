#pragma once

#include "crean/core/types.hpp"

#include <memory>

namespace crean
{
    class Window
    {
    public:
        ~Window();
        Window(const Window &other) = delete;
        Window & operator=(const Window &other) = delete;
        Window(Window &&other) = delete;
        Window & operator=(Window &&other) = delete;

        bool should_close() const;

    private:
        friend class Platform;
        struct ImplData;

        std::unique_ptr<ImplData> m_data_ptr;

        Window(uvec2 size, const string &title);
    };
}
