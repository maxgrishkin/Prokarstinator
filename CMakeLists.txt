cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

set(PROJECT_NAME OpenGL_Game)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
add_executable(${PROJECT_NAME} main.cpp
        Render/ShaderProgram.cpp
        Render/ShaderProgram.h
        GLinclude.h
        Resource/ResourceManager.cpp
        Resource/ResourceManager.h)
add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glad ${OPENGL_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)