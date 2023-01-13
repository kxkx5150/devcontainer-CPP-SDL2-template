cmake_minimum_required(VERSION 3.12)
project(cpp_app)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/exe)


set(USE_GLFW FALSE)


set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -s -DNDEBUG -march=native")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -Og -pg")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -s -DNDEBUG -march=native")

file(GLOB sourcefiles 
    "src/*.h" 
    "src/*.cpp"
    "src/gui/*.h" 
    "src/gui/*.cpp"
)

add_executable(${PROJECT_NAME} 
    ${sourcefiles}
)

# opengl
find_package(OpenGL)
include_directories(${OPENGL_INCLUDE_DIRS})
# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

if(USE_GLFW)
    message("Use GLFW")
    target_compile_definitions(cpp_app PUBLIC MODE_GLFW=1)
    # glfw
    find_package(glfw3 REQUIRED)
    include_directories(${GLFW_INCLUDE_DIRS})
else()
    message("Use SDL2")
    target_link_libraries(${PROJECT_NAME}
    SDL2_image SDL2_ttf SDL2 SDL2main)
endif()

target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARIES} 
    GLEW::GLEW
	glfw
)

