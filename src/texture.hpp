/* this file defines constants and helper functions for textures and texture units */
#ifndef TEXTURE
#define TEXTURE
#include <iostream>

constexpr int texture_unit_ambient = 0;
constexpr int texture_unit_diffuse = 1;
constexpr int texture_unit_specular = 2;
constexpr int texture_unit_specular_highlight = 3;
constexpr int texture_unit_bump = 4;
constexpr int texture_unit_displacement = 5;
constexpr int texture_unit_alpha = 6;
constexpr int texture_unit_reflection = 7;
//PBR extension
constexpr int texture_unit_roughness = 8;
constexpr int texture_unit_metallic = 9;
constexpr int texture_unit_sheen = 10;
constexpr int texture_unit_emissive = 11;
constexpr int texture_unit_normal = 12;

unsigned int load_texture(std::string filename, int unit){

    unsigned int texture;
    glActiveTexture(unit);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout<<"Failed to load texture "<<filename<<"\n";
    }
    stbi_image_free(data);
    return texture;
}
#endif
