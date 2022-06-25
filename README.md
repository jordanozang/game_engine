# game\_engine

## Demo Controls
* Navigation in space is with usual wasd controls and mouse to look
* Press esc to exit
## Features
* Built to be fully cross-platform.The only runtime dependencies are SDL and OpenGL. The game folder is also fully portable within the filesystem.
* Support for loading *.obj and *.mtl files, with per-face materials, rapidly thanks to tinyobjloader.
## Coming Soon
* An importer for models that aren't in the game's native format
* Rigid body dynamics, celestial mechanics, parellelization of physics on the gpu
* A scene editor and a human-readable format for storing scene data
* Continuous integration checking
* Phong shading with support for multiple light sources soon and ray tracing later
## Libraries Used
* GLEW
* SDL2
* stb_image
* tinyobjloader
## Running
* There are precompiled binaries for Windows and GNU/Linux in bin/windows and bin/linux respectively. The Windows binary is standalone except for your graphics driver, but the linux binary links to SDL dynamically. To get it working, you will need SDL2 installed (e.g. apt-get install libsdl2-dev on Debian-based distributions).
## Building from source
### Linux
You'll need to install the SDL2 development library. Next, clone the repository and navigate to the project's base directory. Then enter these commands:

    mkdir build; cd build
    cmake ..
    make

If all went well, you will be told that the binary has been created in bin/linux, where you may access it.
### Windows
All of the configuration for building in Visual Studio with MSVC is done, so all you'll have to do is clone the project, navigate to the project directory in Visual Studio, and build target game_release with startup item game.exe.

