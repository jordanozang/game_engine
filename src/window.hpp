/* this boring class just creates and sets up the sdl window */
#ifndef WINDOW
#define WINDOW
#include <camera.hpp>
#include <shader.hpp>
#include <map>
#include <exception>

class window{
    public:
        SDL_Window* gwindow = 0;
        int width, height;
        window(const char* title, int flags){

            if (SDL_Init(SDL_INIT_EVERYTHING) >= 0){
                SDL_DisplayMode display_mode;
                if (SDL_GetDesktopDisplayMode(0, &display_mode) != 0){
                    SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
                    height = default_window_height;
                    width = default_window_width;
                }
                else{
                    width = display_mode.w;
                    height = display_mode.h;
                }
                gwindow = SDL_CreateWindow(title, 0, 0, width, height, flags);
                if (gwindow != 0){
                    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
                    gcontext = SDL_GL_CreateContext(gwindow);
                    if (gcontext != NULL){
                        if (SDL_GL_SetSwapInterval(1)<0){
                            std::cout<<"Warning: Unable to set VSync! SDL Error:"<<SDL_GetError()<<"\n";
                        }
                        //GLEW stuff
                        try{
                            GLenum err = glewInit();
                            if (err != GLEW_OK){
                            std::cout<<"GLEW failed to initialize\n";
                            }
                        if (!GLEW_VERSION_2_1){
                            std::cout<<"GLEW Version 2.1 not found\n";
                        }
                        //OpenGL stuff
                        glViewport(0, 0, width, height);
                        glEnable(GL_DEPTH_TEST);
                        }
                        catch(std::runtime_error& e){
                            printf("Runtime Error: %s\n", e.what());
                        }
                    }
                    else{
                        throw std::runtime_error("Failed to create OpenGL context");
                    }
                }
                else{
                    throw std::runtime_error("Failed to create SDL window");
                }
            }
            else{
                throw std::runtime_error("SDL failed to initialize");
            }
        }
        ~window(){
            SDL_GL_DeleteContext(gcontext);
            SDL_DestroyWindow(gwindow);
            SDL_Quit();
        }
    private:
        static constexpr int default_window_width = 640;
        static constexpr int default_window_height = 480;
        SDL_GLContext gcontext;
};
#endif
