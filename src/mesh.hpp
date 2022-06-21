#ifndef MESH
#define MESH
struct vertex{
    float pos_x;
    float pos_y;
    float pos_z;
    float norm_x;
    float norm_y;
    float norm_z;
    float tex_x;
    float tex_y;
    bool operator==(const vertex &p) const{
        return pos_x == p.pos_x && pos_y == p.pos_y && pos_z == p.pos_z &&
               norm_x == p.norm_x && norm_y == p.norm_y && norm_z == p.norm_z &&
               tex_x == p.tex_x && tex_y == p.tex_y;
    }
};

//using bitwise or may not be the best option
struct vertex_hash_fn{
    std::size_t operator()(const vertex &vert) const{
        return std::hash<float>()(vert.pos_x) ^ 
               std::hash<float>()(vert.pos_y) ^ 
               std::hash<float>()(vert.pos_z) ^ 
               std::hash<float>()(vert.norm_x) ^ 
               std::hash<float>()(vert.norm_y) ^ 
               std::hash<float>()(vert.norm_z) ^ 
               std::hash<float>()(vert.tex_x) ^ 
               std::hash<float>()(vert.tex_y);  
    }
};
class mesh{
    public:
    std::string model_name;
    std::unordered_map<struct vertex, unsigned int, vertex_hash_fn> vertex_indices;
    std::vector<vertex> vertices;//it makes sense to keep this data around for physics calculations and such
    std::vector<unsigned int> indices;

    //OpenGL buffers
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    //Material data
    //OpenGL is guaranteed to support at least 16 texture units
    //supported out of the box with obj
    tinyobj::material_t m_material;
    unsigned int texture_ambient;
    unsigned int texture_diffuse;
    unsigned int texture_specular;
    unsigned int texture_specular_highlight;
    unsigned int texture_bump;
    unsigned int texture_displacement;
    unsigned int texture_alpha;
    unsigned int texture_reflection;
    //PBR extension
    unsigned int texture_roughness;
    unsigned int texture_metallic;
    unsigned int texture_sheen;
    unsigned int texture_emissive;
    unsigned int texture_normal;

    mesh(tinyobj::material_t mat, std::string name_of_the_model){
        this->m_material = mat;
        this->model_name = name_of_the_model;
        generate_buffers();
        load_textures();
    }

        //assume the uniforms have been set for the texture units
        void draw(){
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture_diffuse);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture_diffuse);

            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
        void write_vbo(){
            //now write the vbo to the gpu
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vertex), &vertices[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        }

    private:

        //check if texture type is tinyobj::TEXTURE_TYPE_NONE
        //TODO: implement a method to reuse textures that are shared across materials (possibly even different models, but I don't think that would make nearly as much of a difference in memory utilization
        //I could write a script to generate this
        void load_textures(){
            if(m_material.ambient_texopt.type != tinyobj::TEXTURE_TYPE_NONE){
                texture_ambient = load_texture("assets/models/" + model_name + "/textures/" + m_material.ambient_texname, texture_unit_ambient);
            }
            if(m_material.diffuse_texname != ""){
                texture_diffuse = load_texture("assets/models/" + model_name + "/textures/" + m_material.diffuse_texname, texture_unit_diffuse);
            }
            if(m_material.specular_texopt.type != tinyobj::TEXTURE_TYPE_NONE){
                texture_specular = load_texture("assets/models/" + model_name + "/textures/" + m_material.specular_texname, texture_unit_specular);
            }
            if(m_material.specular_highlight_texopt.type != tinyobj::TEXTURE_TYPE_NONE){
                texture_specular_highlight = load_texture("assets/models/" + model_name + "/textures/" + m_material.specular_highlight_texname, texture_unit_specular_highlight);
            }
            if(m_material.bump_texopt.type != tinyobj::TEXTURE_TYPE_NONE){
                texture_bump = load_texture("assets/models/" + model_name + "/textures/" + m_material.bump_texname, texture_unit_bump);
            }
            if(m_material.displacement_texopt.type != tinyobj::TEXTURE_TYPE_NONE){
                texture_displacement = load_texture("assets/models/" + model_name + "/textures/" + m_material.displacement_texname, texture_unit_displacement);
            }
            if(m_material.alpha_texopt.type != tinyobj::TEXTURE_TYPE_NONE){
                texture_alpha = load_texture("assets/models/" + model_name + "/textures/" + m_material.alpha_texname, texture_unit_alpha);
            }
            if(m_material.reflection_texopt.type != tinyobj::TEXTURE_TYPE_NONE){
                texture_reflection = load_texture("assets/models/" + model_name + "/textures/" + m_material.reflection_texname, texture_unit_reflection);
            }
            if(m_material.roughness_texopt.type != tinyobj::TEXTURE_TYPE_NONE){
                texture_roughness = load_texture("assets/models/" + model_name + "/textures/" + m_material.roughness_texname, texture_unit_roughness);
            }
            if(m_material.metallic_texopt.type != tinyobj::TEXTURE_TYPE_NONE){
                texture_metallic = load_texture("assets/models/" + model_name + "/textures/" + m_material.metallic_texname, texture_unit_metallic);
            }
            if(m_material.sheen_texopt.type != tinyobj::TEXTURE_TYPE_NONE){
                texture_sheen = load_texture("assets/models/" + model_name + "/textures/" + m_material.sheen_texname, texture_unit_sheen);
            }
            if(m_material.emissive_texopt.type != tinyobj::TEXTURE_TYPE_NONE){
                texture_emissive = load_texture("assets/models/" + model_name + "/textures/" + m_material.emissive_texname, texture_unit_emissive);
            }
            if(m_material.normal_texopt.type != tinyobj::TEXTURE_TYPE_NONE){
                texture_normal = load_texture("assets/models/" + model_name + "/textures/" + m_material.normal_texname, texture_unit_normal);
            }
        }

        void generate_buffers(){
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ebo);

            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void *>(0));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void *>(3*sizeof(float)));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void *>(6*sizeof(float)));

            glBindVertexArray(0);
        }
};
#endif
