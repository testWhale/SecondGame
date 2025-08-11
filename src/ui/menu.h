// In your header file (e.g., my_menu_system.h)
#pragma once
#include "imgui.h"
#include <string>
#include <vector>
#include <functional>

namespace nui
{
    // Menu item structure
    struct MenuItem
    {
        std::string name;
        std::string section;
        std::function<void()> callback;
        bool is_separator = false;

        MenuItem(const std::string& n, const std::function<void()>& cb, const std::string& s = "")
            : name(n), callback(cb), section(s) {
        }

        MenuItem() : is_separator(true) {} // Separator constructor
    };

    // Menu system class
    class MenuSystem
    {
    public:
        void AddMenuItem(const std::string& name, const std::function<void()>& callback, const std::string& section = "");
        void AddSeparator();
        void render();
        void renderMainMenuBar();  // Render main menu bar at top of application
        void SetActiveSection(const std::string& section);

    private:
        std::vector<MenuItem> m_items;
        std::string m_active_section;
        bool m_show_menu = true;
    };

    // Global instance
    extern MenuSystem g_menu_system;
}

// Macro for easy menu creation - moved outside namespace
#define MY_MENU_ITEM(name, callback, section) \
        nui::g_menu_system.AddMenuItem(name, callback, section)

// Macro for marking sections (similar to IMGUI_DEMO_MARKER) - moved outside namespace
#define MY_SECTION_MARKER(section) do { if (ImGui::IsItemClicked()) nui::g_menu_system.SetActiveSection(section); } while (0)

