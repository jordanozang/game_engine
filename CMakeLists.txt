cmake_minimum_required(VERSION 3.10)
include(FetchContent)
project(game_engine)

FetchContent_Declare(
    sdl2-devel-vc 
    URL "https://www.libsdl.org/release/SDL2-devel-2.0.22-VC.zip" 
)

FetchContent_Declare(
    glew-win32
    URL "https://sourceforge.net/projects/glew/files/latest/download"
)

FetchContent_Declare(
    stb-image-header-only
    URL ""https://raw.githubusercontent.com/nothings/stb/master/stb_image.h""
    DOWNLOAD_NO_EXTRACT TRUE
)
FetchContent_Declare(
    tinyobjloader-header-only
    URL "https://raw.githubusercontent.com/tinyobjloader/tinyobjloader/master/tiny_obj_loader.h"
    DOWNLOAD_NO_EXTRACT TRUE
)
FetchContent_Declare(
    glm-header-only
    GIT_REPOSITORY https://github.com/g-truc/glm.git
)

FetchContent_MakeAvailable(sdl2-devel-vc glew-win32 stb-image-header-only tinyobjloader-header-only glm-header-only)

#Check if it's ok to reuse the build directory for different targets
if (WIN32)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/windows/)
add_compile_definitions(BUILDDIR="bin/windows/game.exe")
include_directories(src ${PROJECT_SOURCE_DIR}/build/_deps/glm-header-only-src/glm ${PROJECT_SOURCE_DIR}/build/_deps/tinyobjloader-header-only-src ${PROJECT_SOURCE_DIR}/build/_deps/stb-image-header-only-src ${PROJECT_SOURCE_DIR}/build/_deps/sdl2-devel-vc-src/include ${PROJECT_SOURCE_DIR}/build/_deps/glew-win32-src/include)
link_directories(${PROJECT_SOURCE_DIR}/build/_deps/sdl2-devel-vc-src/lib/x64 ${PROJECT_SOURCE_DIR}/build/_deps/glew-win32-src/lib/Release/x64 ${PROJECT_SOURCE_DIR}/build/x64-Release/_deps/glew-win32-src/bin/Release/x64)
endif ()

if(UNIX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/linux/)
add_compile_definitions(BUILDDIR="bin/linux/game")
include_directories(src include ${PROJECT_SOURCE_DIR}/build/_deps/stb-image-header-only-src ${PROJECT_SOURCE_DIR}/build/_deps/tinyobjloader-header-only-src ${PROJECT_SOURCE_DIR}/build/_deps/glm-header-only-src/glm)
link_directories(src include)
endif ()




#executable
add_executable(game src/main.cpp)

if (WIN32)
    include_directories(src include)
target_link_libraries(game SDL2 glew32 opengl32 winmm)
endif ()

if(UNIX)
target_link_libraries(game SDL2 GLEW GL)
add_compile_options(lSDL2 I/usr/include/SDL2 D_REENTRANT)
endif ()


add_compile_options(mwindows -Dmain=SDL_main)

