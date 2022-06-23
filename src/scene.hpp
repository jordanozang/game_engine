#ifndef SCENE
#define SCENE
class game_object{//maybe put this in a different file (and) make it a class
    model m_model; 
    string m_gtype;//consider using an enum for this, but I doubt it will make much of a difference
    //we'll have one vao per type
};
class scene_object{
    game_object *object;
    glm::vec3 position;//scene position
};

//game objects are scene-indepedent, but scene objects have stuff like their position in the scene
class scene{
    public:
        std::vector<scene_object> scene_objects;
        camera active_camera;//I could turn this into a hashmap and allow camera switching
        scene(glm::vec3 cam_pos, glm::vec3 cam_targ){
            active_camera = camera(cam_pos, cam_targ);
        }
        draw();
        //use the shader
        //bind the vao
};

            
#endif
