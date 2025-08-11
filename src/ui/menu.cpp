// In your implementation file (e.g., my_menu_system.cpp)
#include "menu.h"
#include "../render/ui_context.h"

namespace nui
{
    MenuSystem g_menu_system;

    // Initialize menu items using the macro
    void InitializeMenuItems()
    {
        // File section items
        MY_MENU_ITEM("Open File", []() {
            // Handle file opening
            printf("Opening file...\n");
            }, "File");

        MY_MENU_ITEM("Save File", []() {
            // Handle file saving
            printf("Saving file...\n");
            }, "File");

        MY_MENU_ITEM("Save As...", []() {
            // Handle save as
            printf("Save as dialog...\n");
            }, "File");

        g_menu_system.AddSeparator(); // Add separator between sections

        // Edit section items
        MY_MENU_ITEM("Undo", []() {
            printf("Undo action\n");
            }, "Edit");

        MY_MENU_ITEM("Redo", []() {
            printf("Redo action\n");
            }, "Edit");

        g_menu_system.AddSeparator();

        // View section items
        MY_MENU_ITEM("Reset Layout", []() {
            nrender::UIContext::ResetLayout();
            }, "View");

        MY_MENU_ITEM("Toggle Properties", []() {
            printf("Toggle properties panel\n");
            }, "View");

        MY_MENU_ITEM("Toggle Scene View", []() {
            printf("Toggle scene view\n");
            }, "View");

        g_menu_system.AddSeparator();

        // Tools section items
        MY_MENU_ITEM("Mesh Editor", []() {
            printf("Open mesh editor\n");
            }, "Tools");

        MY_MENU_ITEM("Material Editor", []() {
            printf("Open material editor\n");
            }, "Tools");

        MY_MENU_ITEM("Animation Editor", []() {
            printf("Open animation editor\n");
            }, "Tools");
    }

    void MenuSystem::AddMenuItem(const std::string& name, const std::function<void()>& callback, const std::string& section)
    {
        m_items.emplace_back(name, callback, section);
    }

    void MenuSystem::AddSeparator()
    {
        m_items.emplace_back();
    }

    // Render the main menu bar at the top of the application
    void MenuSystem::renderMainMenuBar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open", "Ctrl+O")) { 
                    // Handle open
                    printf("Opening file...\n");
                }
                if (ImGui::MenuItem("Save", "Ctrl+S")) { 
                    // Handle save
                    printf("Saving file...\n");
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit", "Alt+F4")) { 
                    m_show_menu = false; 
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Reset Layout")) { 
                    nrender::UIContext::ResetLayout(); 
                }
                if (ImGui::MenuItem("Toggle Properties")) { 
                    printf("Toggle properties panel\n"); 
                }
                if (ImGui::MenuItem("Toggle Scene View")) { 
                    printf("Toggle scene view\n"); 
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Tools"))
            {
                if (ImGui::MenuItem("Mesh Editor")) { 
                    printf("Open mesh editor\n"); 
                }
                if (ImGui::MenuItem("Material Editor")) { 
                    printf("Open material editor\n"); 
                }
                if (ImGui::MenuItem("Animation Editor")) { 
                    printf("Open animation editor\n"); 
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

    void MenuSystem::render()
    {
        if (!m_show_menu)
            return;

        // Initialize menu items on first render (you could also do this in constructor)
        static bool initialized = false;
        if (!initialized) {
            InitializeMenuItems();
            initialized = true;
        }

        // Create a simple window (not docked) for additional menu content
        if (ImGui::Begin("Additional Menu Content", &m_show_menu))
        {
            // Section tabs using the macro
            ImGui::BeginChild("SectionTabs", ImVec2(0, 30), true);
            if (ImGui::Button("File")) {
                MY_SECTION_MARKER("File");
            }
            ImGui::SameLine();
            if (ImGui::Button("Edit")) {
                MY_SECTION_MARKER("Edit");
            }
            ImGui::SameLine();
            if (ImGui::Button("View")) {
                MY_SECTION_MARKER("View");
            }
            ImGui::SameLine();
            if (ImGui::Button("Tools")) {
                MY_SECTION_MARKER("Tools");
            }
            ImGui::EndChild();

            // Main content area
            ImGui::BeginChild("Content", ImVec2(0, 0), true);

            // Show current section name
            if (!m_active_section.empty()) {
                ImGui::Text("Current Section: %s", m_active_section.c_str());
                ImGui::Separator();
            }

            // Render items based on active section
            for (const auto& item : m_items)
            {
                if (item.is_separator)
                {
                    ImGui::Separator();
                    continue;
                }

                // Only show items for current section (or all if no section specified)
                if (item.section.empty() || item.section == m_active_section)
                {
                    if (ImGui::Button(item.name.c_str()))
                    {
                        if (item.callback)
                            item.callback();
                    }
                }
            }

            ImGui::EndChild();
        }
        ImGui::End();
    }

    void MenuSystem::SetActiveSection(const std::string& section)
    {
        m_active_section = section;
    }
}