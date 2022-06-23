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

            unsigned int model_loc, view_loc, projection_loc;
            //coordinate space transformation matrices
            glm::mat4 view = r_camera->view_matrix();
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(r_window->width)/static_cast<float>(r_window->height), 0.1f, 100.0f);

            //find the uniforms for the transformation matrices for obj_shader on the gpu
            model_loc = glGetUniformLocation(obj_shader->shader_program, "model");
            view_loc = glGetUniformLocation(obj_shader->shader_program, "view");
            projection_loc = glGetUniformLocation(obj_shader->shader_program, "projection");

            //write the transformation matrices to the gpu
            glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection));

            //use the object shader
            obj_shader->use();

            //these draw calls will be go a loop over gameobjects in a scene
            testobj->draw();

            model = glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f,0.0f,0.0f)), static_cast<float>(-0.5f*M_PI), z_unit_vector), glm::vec3(10.0f,10.0f,10.0f)); 
            glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
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
            obj_shader->set1i("texture_diffuse", texture_unit_diffuse); 

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
