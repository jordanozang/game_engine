#ifndef WORLD
#define WORLD
struct entry{
    int instance_id;
    int object_id;
    const char* model_filename;
    const char* texture_filename;
};
class World{
    public:
        //there are so many things wrong with this code, but let's just get it running
        void instantiate(int obj_id, const char *model_filename, const char *texture_filename, glm::vec3){
            db[i].instance_id = i;
            db[i].object_id = obj_id;
            db[i].model_filename = model_filename;
            db[i].texture_filename = texture_filename;
            i++;
        }
        int i = 0;
        struct entry db[1000];
};

        //we store a lot of duplicate infor for objects that occur multiple times this way. We have to find the right tradeoff between memory and speed, with an emphasis on speed because this is a realtime application.
        //add an extra table for looking up the ids
    //The world is a database of objects
    //list of objects that can be look up against an object manager
    //functions like instantiate for objects
    //add db entry
    //add more members to this struct as we need more things associated with the object
    //we should probably tell the render when we've added a new object, so that it can load things onto the gpu
    //it might even be good to send out an alert about any changes to the database for the rest of the program to interact to. This would practically be an api. Very modular.
    //It might make more sense to use linked lists for our database, because we wouldn't need a counter or to count each time, plus we'd be able to respond to requests to delete objects very simply by changing a single pointer.
#endif
