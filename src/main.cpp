/* The program begins execution here. The core game instance is created and updated. */
#define STB_IMAGE_IMPLEMENTATION
#ifdef __linux__
#include <unistd.h>
#elif _WIN64
#include <windows.h>
#include <direct.h>
#endif
#include <string>
#include <fstream>
#include <sstream>

//OpenGl and SDL
#include "GL/glew.h"
#define SDL_MAIN_HANDLED
#ifdef __linux__
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#elif _WIN64
#include "SDL.h"
#include "SDL_opengl.h"
#endif

//utilities
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//classes
#include "game.hpp"


int main(int argc, char *argv[]){
//os-specific code to get to the project base directory independently of where the program was executed from or where it(i.e. the base folder) is stored in the filesystem.
//Some of this should probably be delegated to a compile-time script
#ifdef _WIN64
    char executable_directory[MAX_PATH];
    GetModuleFileName(nullptr, executable_directory, MAX_PATH);
#endif
#ifdef __linux__
    char executable_directory[PATH_MAX];
    readlink("/proc/self/exe", executable_directory, PATH_MAX);
#endif
    int i=0;
    for(i = strlen(executable_directory)-1; i >= 0 && executable_directory[i] != '/'; i--){};
    executable_directory[i+1] = '\0';
    chdir(executable_directory);

    auto build_directory = BUILDDIR;
    i = 0;
    while(build_directory[i] != '\0'){
        if(build_directory[i] == '/')
            chdir("..");
        i++;
    }
 

    game *game_main_instance = new game();

    while(game_main_instance->is_running()){
        game_main_instance->game_loop();
    }

    delete game_main_instance;
    return 0;
}
