#ifndef SHADER
#define SHADER
#include <glm//glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class shader{
    public:
        unsigned int shader_program;//this shouldn't stay public, methinks
        shader(const char* vertex_shader, const char* fragment_shader){
            shader_program = glCreateProgram();
            unsigned int v = load_shader(vertex_shader, GL_VERTEX_SHADER);
            unsigned int f = load_shader(fragment_shader, GL_FRAGMENT_SHADER);
            glLinkProgram(shader_program);
            glDeleteShader(v);
            glDeleteShader(f);
        }
        void setb(const std::string &name, bool value){
            glUniform1i(glGetUniformLocation(shader_program, name.c_str()), (int)value);
        }
        void seti(const std::string &name, int value){
            glUniform1i(glGetUniformLocation(shader_program, name.c_str()), value);
        }
        void setf(const std::string &name, float value){
            glUniform1f(glGetUniformLocation(shader_program, name.c_str()), value);
        }
        void setmat4(const std::string &name, float *matrix){
            glUniformMatrix4fv(glGetUniformLocation(shader_program, name.c_str()), 1, GL_FALSE, matrix);
        }
        void set3f(const std::string &name, float f1, float f2, float f3){
            glUniform3f(glGetUniformLocation(shader_program, name.c_str()), f1, f2, f3);
        }
        unsigned int load_shader(const char* filename, GLenum shader_type){
            std::string code;
            std::ifstream file;
            file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            
            try{
                file.open(filename);
                std::stringstream shader_stream;
                shader_stream << file.rdbuf();
                file.close();
                code = shader_stream.str();
            }
            catch(std::ifstream::failure& e){
                std::cout<<"Failed to read shader file at "<<filename<<std::endl;
            }
            const char* shader_code = code.c_str();

            unsigned int shader = glCreateShader(shader_type);
            glShaderSource(shader, 1, &shader_code, NULL);
            int success;
            char compile_log[512];
            glCompileShader(shader);
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success){
                glGetShaderInfoLog(shader, 512, NULL, compile_log);
                std::cout<<"Failed to compile shader at "<<filename<<"\n";
                std::cout<<compile_log<<std::endl;
                return false;
            }
            glAttachShader(shader_program, shader);
            return shader;
        }
        void use(){
            glUseProgram(shader_program);
        }
};
#endif
