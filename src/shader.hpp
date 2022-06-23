/* a simple shader class */
#ifndef SHADER
#define SHADER
#include <string>

class shader{
    public:
        unsigned int shader_program; 

        void set3f(std::string name, float f1, float f2, float f3){
            glUniform3f(glGetUniformLocation(shader_program, name.c_str()), f1, f2, f3);
        }
        void setf(std::string name, float f1){
            glUniform1f(glGetUniformLocation(shader_program, name.c_str()), f1);
        }
        void set1i(std::string name, int i1){
            glUniform1i(glGetUniformLocation(shader_program, name.c_str()), i1);
        }

        void use(){
            glUseProgram(shader_program);
        }

        shader(std::string vertex_path, std::string fragment_path){
            std::string vertex_source;
            std::string fragment_source;
            std::ifstream vertex_file;
            std::ifstream fragment_file;

            vertex_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fragment_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            try{
                vertex_file.open(vertex_path);
                fragment_file.open(fragment_path);
                std::stringstream vertex_stream, fragment_stream;
                vertex_stream << vertex_file.rdbuf();
                fragment_stream << fragment_file.rdbuf();
                vertex_file.close();
                fragment_file.close();
                vertex_source = vertex_stream.str();
                fragment_source = fragment_stream.str();
            }
            catch (std::ifstream::failure& e){
                std::cout<<"ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
            }
            const char* vertex_code = vertex_source.c_str();
            const char* fragment_code = fragment_source.c_str();

            unsigned int vertex_shader, fragment_shader;
            vertex_shader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex_shader, 1, &vertex_code, NULL);
            glCompileShader(vertex_shader);
            check_compile_errors(vertex_shader, "VERTEX");

            fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment_shader, 1, &fragment_code, NULL);
            glCompileShader(fragment_shader);
            check_compile_errors(fragment_shader, "FRAGMENT");

            shader_program = glCreateProgram();
            glAttachShader(shader_program, vertex_shader);
            glAttachShader(shader_program, fragment_shader);
            glLinkProgram(shader_program);
            check_compile_errors(shader_program, "PROGRAM");

            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);
        }

    private:

        void check_compile_errors(unsigned int shader_id, std::string type){
            int success;
            char info_log[1024];
            if (type != "PROGRAM"){
                glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
                if (!success){
                    glGetShaderInfoLog(shader_id, 1024, NULL, info_log);
                    std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << info_log << std::endl;
                }
            }
            else{
                glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
                if (!success){
                    glGetProgramInfoLog(shader_id, 1024, NULL, info_log);
                    std::cout<<"ERROR::PROGRAM_LINKING_ERROR of type: "<< type << "\n" << info_log << "\n";
                }
            }
        }
};
#endif
