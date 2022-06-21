/* defines the camera class */
/* TODO: standardize camera speed across frame rates and computers by using a velocity in terms of SDLGetTicks time*/
#ifndef CAMERA
#define CAMERA
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

//These should go in some kind of constant header
static constexpr glm::vec3 x_unit_vector = glm::vec3(1.0f,0.0f,0.0f);
static constexpr glm::vec3 y_unit_vector = glm::vec3(0.0f,1.0f,0.0f);
static constexpr glm::vec3 z_unit_vector = glm::vec3(0.0f,0.0f,1.0f);

class camera{
    public:
        //these could inherit from some sort of game_object class, a vector of which would be stored by a scene
        glm::vec3 position = glm::vec3(0.0f,0.0f,10.0f);
        float pitch = 0.0f;
        float yaw = 0.0f;
        float roll = 0.0f;
        //float focal_length = 1.0f;
    private:
        float mouse_sensitivity = 0.001f;
        float movement_sensitivity = 0.5f;

    public:
        glm::mat4 view_matrix(){
            return glm::inverse(glm::rotate(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), position), roll, z_unit_vector), yaw, y_unit_vector), pitch, x_unit_vector));
        }
        void move_forward(){
            glm::vec3 direction;

            direction.x = -cos(pitch)*sin(yaw);
            direction.y = sin(pitch);
            direction.z = -cos(pitch)*cos(yaw);
            position = position + direction*movement_sensitivity; 
            
        }
        void move_backward(){
            glm::vec3 direction;

            direction.x = -cos(pitch)*sin(yaw);
            direction.y = sin(pitch);
            direction.z = -cos(pitch)*cos(yaw);
            position = position - direction*movement_sensitivity; 
        }

        void move_left(){
            glm::vec3 direction;

            direction.x = -cos(pitch)*sin(yaw);
            direction.y = sin(pitch);
            direction.z = -cos(pitch)*cos(yaw);

            direction = glm::cross(direction, y_unit_vector);
            position = position - direction*movement_sensitivity; 
        }
        void move_right(){
            glm::vec3 direction;

            direction.x = -cos(pitch)*sin(yaw);
            direction.y = sin(pitch);
            direction.z = -cos(pitch)*cos(yaw);

            direction = glm::cross(direction, y_unit_vector);
            position = position + direction*movement_sensitivity; 
        }

        void mouse_look(Sint32 xrel, Sint32 yrel){
            yaw -= mouse_sensitivity* xrel;
            pitch -= mouse_sensitivity* yrel;
        }


};

#endif
