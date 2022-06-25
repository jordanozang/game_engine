cmake_minimum_required(VERSION 3.10)
include(FetchContent)
project(game_engine)



#Download all the project dependencies
FetchContent_Declare(
    sdl2-devel-vc 
    URL "https://www.libsdl.org/release/SDL2-devel-2.0.22-VC.zip" 
)

FetchContent_Declare(
    glew-win32
    URL "https://sourceforge.net/projects/glew/files/latest/download"
)

FetchContent_Declare(
    glm-header-only
    GIT_REPOSITORY https://github.com/g-truc/glm.git
)

file(DOWNLOAD "https://raw.githubusercontent.com/nothings/stb/master/stb_image.h" ${CMAKE_CURRENT_BINARY_DIR}/_deps/stb_image/stb_image.h)

file(DOWNLOAD "https://raw.githubusercontent.com/tinyobjloader/tinyobjloader/master/tiny_obj_loader.h" ${CMAKE_CURRENT_BINARY_DIR}/_deps/tinyobjloader/tiny_obj_loader.h)




#os-specific setup
#windows specific libraries
if (WIN32) #Check if it's ok to reuse the build directory for different targets
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/windows/)
add_compile_definitions(BUILDDIR="bin/windows/game.exe")
#add_compile_options(mwindows -Dmain=SDL_main)

FetchContent_MakeAvailable(sdl2-devel-vc glew-win32)
include_directories(${PROJECT_SOURCE_DIR}/build/_deps/sdl2-devel-vc-src/include ${PROJECT_SOURCE_DIR}/build/_deps/glew-win32-src/include)
link_directories(${PROJECT_SOURCE_DIR}/build/_deps/sdl2-devel-vc-src/lib/x64 ${PROJECT_SOURCE_DIR}/build/_deps/glew-win32-src/lib/Release/x64 ${PROJECT_SOURCE_DIR}/build/x64-Release/_deps/glew-win32-src/bin/Release/x64)
endif ()

#linux specific libraries (currently only tested on Linux, have to get a mac vm running and compile there
if(UNIX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/linux/)
add_compile_definitions(BUILDDIR="bin/linux/game")
endif ()



#include directories for all targets
#include project source directory
include_directories(${PROJECT_SOURCE_DIR}/src)
#include library header files
include_directories(${CMAKE_CURRENT_BINARY_DIR}/_deps/stb_image/ ${CMAKE_CURRENT_BINARY_DIR}/_deps/tinyobjloader ${CMAKE_CURRENT_BINARY_DIR}/_deps/glm-header-only-src)



#add executable
add_executable(game src/main.cpp)

#platform-specific linker instructions
if (WIN32)
target_link_libraries(game SDL2 glew32 opengl32 winmm)
endif ()
if(UNIX)
target_link_libraries(game SDL2 GLEW GL)
add_compile_options(lSDL2 I/usr/include/SDL2 D_REENTRANT)
endif ()
