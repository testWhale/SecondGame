#pragma once
#include "../pch.h"
#include "render_base.h"
#include "../window/window.h"

namespace nrender
{
    class UIContext : public RenderContext
    {
    public:
        bool init(nwindow::IWindow* window) override;
        void pre_render() override;
        void post_render() override;
        void end() override;
        
        // Add reset layout function
        static void ResetLayout();

    };
}