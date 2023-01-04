cmake_minimum_required(VERSION 3.24)
project(OpenGLStudy)

set(CMAKE_CXX_STANDARD 11)

# 1. 加载glad项目

# 2. 包含头文件
include_directories(./glad/include)

# 3. 加载glfw  /opt/homebrew/Cellar/glfw/3.3.8
# brew 安装的 库都在：/opt/homebrew/Cellar
include_directories(/opt/homebrew/Cellar/glfw/3.3.8/include)

# 加载库文件 glfw库文件
link_directories(/opt/homebrew/Cellar/glfw/3.3.8/lib)


add_executable(OpenGLStudy
        ./glad/src/glad.c
        main.cpp)

# link库文件到项目
target_link_libraries(
        OpenGLStudy
        glfw
)