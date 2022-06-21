/* define a model class with support for loading obj+mtl with tiny obj loader, which makes a lot more sense than using something monolithic (and comparatively slow) like assimp at runtime. I can always write a tool to convert files to the format expected by my engine. This makes things predictable and fast.*/
/* The model class corresponds to one obj file. Obj files have support for per-face materials. The approach taken here is to create a mesh for each material, so drawing the model takes as many draw calls as there are materials in the file and no more. */
/* Rigging would be done with an extra file pointing to the obj files and describing their relationship */
/* Asset structure: models consists of folders corresponding to the model name. These folders contain an obj, optional mtl, and a textures folder*/
/* Model loading could be done on another thread */
#ifndef MODEL
#define MODEL
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "mesh.hpp"

class model{
    public:
        std::vector<mesh> meshes;

        void draw(){
            for (int i = 0; i < meshes.size(); i++){
                meshes[i].draw();
            }
        }

        model(std::string model_name){
            tinyobj::attrib_t attrib;//this can go after loading into the vbo 
            std::vector<tinyobj::shape_t> shapes;//I could support by having something like a shape class with its own buffers
            std::vector<tinyobj::material_t> materials;//I can get rid of this too
            tinyobj::ObjReaderConfig reader_config;
            reader_config.mtl_search_path = "assets/models/"+model_name+"/"; // Path to material files
            reader_config.vertex_color = false;

            tinyobj::ObjReader reader;
            if (!reader.ParseFromFile("assets/models/"+model_name+"/"+model_name+".obj", reader_config)) {
              if (!reader.Error().empty()) {
                  std::cerr << "TinyObjReader: " << reader.Error();
              }
            }

            if (!reader.Warning().empty()) {
              std::cout << "TinyObjReader: " << reader.Warning();
            }

            attrib = reader.GetAttrib();
            shapes = reader.GetShapes();
            materials = reader.GetMaterials();//returns a vector of material_t

            for(tinyobj::material_t mat: materials)
                meshes.push_back(mesh(mat, model_name));
            //pack all the vertices into a buffer to put in the model vbo 
            // Loop over shapes
            for (size_t s = 0; s < shapes.size(); s++) {
              // Loop over faces(polygon)
              size_t index_offset = 0;
              for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
                size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

                // Loop over vertices in the face. I'm triangulating, so this isn't really necessary
                for (size_t v = 0; v < fv; v++) {
                  vertex vert;

                  // access to vertex
                  tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                  vert.pos_x = attrib.vertices[3*size_t(idx.vertex_index)+0];
                  vert.pos_y = attrib.vertices[3*size_t(idx.vertex_index)+1];
                  vert.pos_z = attrib.vertices[3*size_t(idx.vertex_index)+2];

                  // Check if `normal_index` is zero or positive. negative = no normal data
                  if (idx.normal_index >= 0) {
                    vert.norm_x = attrib.normals[3*size_t(idx.normal_index)+0];
                    vert.norm_y = attrib.normals[3*size_t(idx.normal_index)+1];
                    vert.norm_z = attrib.normals[3*size_t(idx.normal_index)+2];
                  }
                  else{
                      vert.norm_x = 0.0f;
                      vert.norm_y = 0.0f;
                      vert.norm_z = 0.0f;
                  }

                  // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                  if (idx.texcoord_index >= 0) {
                    vert.tex_x = attrib.texcoords[2*size_t(idx.texcoord_index)+0];
                    vert.tex_y = attrib.texcoords[2*size_t(idx.texcoord_index)+1];
                  }
                  else{
                      vert.tex_x = 0.0f;
                      vert.tex_y = 0.0f;
                  }

                  auto face_material = shapes[s].mesh.material_ids[f];
                  auto found = meshes[face_material].vertex_indices.find(vert); 
                  if(found == meshes[face_material].vertex_indices.end()){
                    meshes[face_material].vertices.push_back(vert);
                    meshes[face_material].indices.push_back(meshes[face_material].vertex_indices.size());
                    meshes[face_material].vertex_indices.insert(std::make_pair(vert, meshes[face_material].vertex_indices.size()));
                  }
                  else{
                      meshes[face_material].indices.push_back(found->second);
                  }
              }

                index_offset += fv;
            }
            for (int i = 0; i < meshes.size(); i++){
                meshes[i].write_vbo();
            }
            }

        }
};
#endif
