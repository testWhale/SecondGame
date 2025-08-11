cmake_minimum_required(VERSION 3.10)

project(SecondGame VERSION 1.0 DESCRIPTION "3D ENGINE")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BULLET_USE_DEBUG_LIBS OFF CACHE BOOL "Disable debug suffix" FORCE)

# -------------------------------------------------------------------
# Gather source files
# -------------------------------------------------------------------
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h)
file(GLOB_RECURSE PROJECT_WINDOWS src/window/*.h src/window/*.cpp )
file(GLOB_RECURSE PROJECT_RENDER src/render/*.h src/render/*.cpp )
file(GLOB_RECURSE PROJECT_ELEMS src/elems/*.h src/elems/*.cpp )
file(GLOB_RECURSE PROJECT_ADDONS src/add-ons/*.h src/add-ons/*.cpp )
file(GLOB_RECURSE PROJECT_COMPONENTS SecondGame/Components/*.hpp)
file(GLOB_RECURSE PROJECT_ECS SecondGame/ECS/*.cpp)
file(GLOB_RECURSE PROJECT_SYSTEMS SecondGame/Systems/*.cpp
                                  SecondGame/Systems/*.hpp)
file(GLOB_RECURSE PROJECT_SHADERS 
    SecondGame/Shaders/*.comp
    SecondGame/Shaders/*.frag
    SecondGame/Shaders/*.geom
    SecondGame/Shaders/*.vert
    SecondGame/Shaders/*.fs
    SecondGame/Shaders/*.vs
    SecondGame/Shaders/*.shader

)
file(GLOB_RECURSE TEST_SHADERS 
    SecondGame/src/shader/*.h
    SecondGame/src/shader/*.cpp
)




# -------------------------------------------------------------------
# ImGui source files
# -------------------------------------------------------------------
set(IMGUI_SOURCES
    Third-Party/imgui/imgui.cpp
    Third-Party/imgui/imgui_demo.cpp
    Third-Party/imgui/imgui_draw.cpp
    Third-Party/imgui/imgui_tables.cpp
    Third-Party/imgui/imgui_widgets.cpp
    Third-Party/imgui/backends/imgui_impl_glfw.cpp
    Third-Party/imgui/backends/imgui_impl_opengl3.cpp
)

# -------------------------------------------------------------------
# Create executable
# -------------------------------------------------------------------
add_executable(SecondGame 
    ${SOURCES} 
    ${HEADERS}
    ${PROJECT_COMPONENTS}
    ${PROJECT_ECS}
    ${PROJECT_SHADERS}
    ${TEST_SHADERS}
    ${PROJECT_SYSTEMS}
    ${IMGUI_SOURCES}
    ${PROJECT_ADDONS}) 

# -------------------------------------------------------------------
# GLAD setup (add as static lib)
# -------------------------------------------------------------------
add_library(glad STATIC "Third-Party/glad/glad.c")
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/Third-Party)

# -------------------------------------------------------------------
# Add Assimp
# -------------------------------------------------------------------
add_subdirectory(Third-Party/assimp)

# -------------------------------------------------------------------
# Include directories
# -------------------------------------------------------------------
target_include_directories(SecondGame PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Third-Party
    ${CMAKE_SOURCE_DIR}/Third-Party/glad/include
    ${CMAKE_SOURCE_DIR}/Third-Party/imgui
    ${CMAKE_SOURCE_DIR}/Third-Party/GLFW
    ${CMAKE_SOURCE_DIR}/Third-Party/GLEW
    ${CMAKE_SOURCE_DIR}/Third-Party/KHR
    ${CMAKE_SOURCE_DIR}/Third-Party/stb
    ${CMAKE_SOURCE_DIR}/Third-Party/assimp/include
    ${CMAKE_SOURCE_DIR}/Third-Party/file

)


# -------------------------------------------------------------------
# Link libraries
# -------------------------------------------------------------------
find_package(OpenGL REQUIRED)

target_link_libraries(SecondGame PRIVATE 
    glad
    assimp
    ${OPENGL_LIBRARIES}
    "${CMAKE_SOURCE_DIR}/Third-Party/libs/glfw3.lib"        # Only if you're using precompiled GLFW
    "${CMAKE_SOURCE_DIR}/Third-Party/libs/assimp-vc143-mtd.lib"  # Only if you want this and also link `assimp` above
    "${CMAKE_SOURCE_DIR}/Third-Party/libs/glew/glew32s.lib"  # Only if you want this and also link `assimp` above
    "${CMAKE_SOURCE_DIR}/Third-Party/libs/glew/glew32.lib"  # Only if you want this and also link `assimp` above

)

# Optional: group files in IDEs
source_group("Components" FILES ${PROJECT_COMPONENTS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Test_shader" FILES ${TEST_SHADERS})

source_group("ECS" FILES ${PROJECT_ECS})
source_group("Systems" FILES ${PROJECT_SYSTEMS})
source_group("Elems" FILES ${PROJECT_ELEMS})
source_group("Renders" FILES ${PROJECT_RENDER})
source_group("Windows" FILES ${PROJECT_WINDOWS})
source_group("ImGui" FILES ${IMGUI_SOURCES})



message(STATUS "Source files: ${SOURCES}")

add_custom_command(TARGET SecondGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Shaders $<TARGET_FILE_DIR:SecondGame>/Shaders
)
add_custom_command(TARGET SecondGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:SecondGame>/assets
)
add_custom_command(TARGET SecondGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Textures $<TARGET_FILE_DIR:SecondGame>/Textures
)