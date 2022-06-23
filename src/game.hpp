/* defines the game class */
#ifndef GAME 
#define GAME
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>
#include <functional>
#include <world.hpp>
#include <renderer.hpp>
#include <texture.hpp>
#include <model.hpp>

class game{
    public:
        void game_loop(){
            handle_window_events();
            g_renderer->render(g_window);
        }
        bool is_running(){
            return running;
        }

        game(){
            try{
                g_window = new window("Jordan's Game", SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL|SDL_WINDOW_FULLSCREEN);
                g_renderer = new renderer();
            }
            catch(std::runtime_error& e){
                printf("Runtime Error: %s\n", e.what());
            }
            SDL_SetRelativeMouseMode(SDL_TRUE);
            running = true;
        }
        ~game(){
            delete g_renderer;
            delete g_window;
        }
    private:
        window *g_window = nullptr;
        renderer *g_renderer = nullptr;

        bool running = false;
        //until I setup some config files

        void handle_window_events(){
            SDL_Event event;
            //I'll probably implement a callback system to handle input at some point
            while(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym){
                            case SDLK_ESCAPE:
                                running = false;
                                break;
                            case SDLK_w:
                                g_renderer->r_camera->move_forward();
                                break;
                            case SDLK_a:
                                g_renderer->r_camera->move_left();
                                break;
                            case SDLK_s:
                                g_renderer->r_camera->move_backward();
                                break;
                            case SDLK_d:
                                g_renderer->r_camera->move_right();
                                break;
                            default:
                                break;
                        }
                        break;
                    case SDL_WINDOWEVENT:
                        switch(event.window.event){
                            case SDL_WINDOWEVENT_CLOSE:
                                running = false;
                                break;
                            default:
                                break;
                        }
                        break;
                    case SDL_MOUSEMOTION:
                        g_renderer->r_camera->mouse_look(event.motion.xrel, event.motion.yrel);
                        break;
                    default:
                        break;
                        }
                }
        }

};
#endif
