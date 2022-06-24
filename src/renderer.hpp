/* this class takes a scene and churns it until it becomes pixels(really it just tells the gpu to) */
#ifndef RENDERER
#define RENDERER
#include <stdio.h>
#include <texture.hpp>
#include <window.hpp>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.hpp"
#include "model.hpp"
#include "texture.hpp"

class renderer{
    public:
        glm::vec3 light_pos;
        shader* obj_shader = nullptr;
        shader* light_cube_shader = nullptr;
        camera* r_camera = nullptr;
        model *testobj = nullptr;
        model *sphinx = nullptr;

        void render(window *r_window){
            //flush the screen buffer
            glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //coordinate space transformation matrices
            glm::mat4 view = r_camera->view_matrix();
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(r_window->width)/static_cast<float>(r_window->height), 0.1f, 100.0f);

            //write the transformation matrices to the gpu
            obj_shader->set_uniform("model", 1, GL_FALSE, model);
            obj_shader->set_uniform("view", 1, GL_FALSE, view);
            obj_shader->set_uniform("projection", 1, GL_FALSE, projection);


            //use the object shader
            obj_shader->use();

            //these draw calls will be go a loop over gameobjects in a scene
            testobj->draw();

            model = glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f,0.0f,0.0f)), static_cast<float>(-0.5f*M_PI), z_unit_vector), glm::vec3(10.0f,10.0f,10.0f)); 
            obj_shader->set_uniform("model", 1, GL_FALSE, model);
            sphinx->draw();

            SDL_GL_SwapWindow(r_window->gwindow);
            }

        renderer(){
            //Make the shaders
            obj_shader = new shader("assets/shaders/light.vert", "assets/shaders/light.frag");

            //Make the camera and set it to default position and target
            r_camera = new camera();

            obj_shader->use();
            //pass the texture unit setup to the shader
            obj_shader->set_uniform("texture_diffuse", texture_unit_diffuse); 

            testobj = new model("Trex"); 
            sphinx = new model("Sphynx");
            }
        ~renderer(){
            delete r_camera;
            delete testobj;
            delete sphinx;
        }
};
#endif
