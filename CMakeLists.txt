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

FetchContent_MakeAvailable(sdl2-devel-vc)
FetchContent_MakeAvailable(glew-win32)

if (WIN32)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/windows/)
add_compile_definitions(BUILDDIR="bin/windows/game.exe")
include_directories(lib/windows src include include/windows ${PROJECT_SOURCE_DIR}/out/build/x64-Release/_deps/sdl2-devel-vc-src/include ${PROJECT_SOURCE_DIR}/out/build/x64-Release/_deps/glew-win32-src/include)
link_directories(lib/windows src include include/windows ${PROJECT_SOURCE_DIR}/out/build/x64-Release/_deps/sdl2-devel-vc-src/lib/x64 ${PROJECT_SOURCE_DIR}/out/build/x64-Release/_deps/glew-win32-src/lib/Release/x64 ${PROJECT_SOURCE_DIR}/out/build/x64-Release/_deps/glew-win32-src/bin/Release/x64)
endif ()

if(UNIX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/linux/)
add_compile_definitions(BUILDDIR="bin/linux/game")
include_directories(src include)
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

