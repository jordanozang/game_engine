cmake_minimum_required(VERSION 3.10)

project(game_engine)

if (WIN32)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/windows/)
add_compile_definitions(BUILDDIR="bin/windows/game.exe")
include_directories(lib/windows src include include/windows)
link_directories(lib/windows src include include/windows )
endif ()

if(UNIX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/linux/)
add_compile_definitions(BUILDDIR="bin/linux/game")
include_directories(src include)
link_directories(src include)
add_compile_options('sdl2-config --libs --cflags)
endif ()




#executable
add_executable(game src/main.cpp)

if (WIN32)
target_link_libraries(game SDL2 glew32 opengl32 winmm)
endif ()

if(UNIX)
target_link_libraries(game SDL2 GLEW GL)
endif ()



#add_compile_options(`/home/jordano/Desktop/game/lib/SDL2-2.0.22/x86_64-w64-mingw32/bin/sdl2-config --libs --cflags`)
add_compile_options(mwindows -Dmain=SDL_main)

