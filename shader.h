//
// Created by 胡栋月 on 5/1/23.
//

#ifndef OPENGLSTUDY_SHADER_H
#define OPENGLSTUDY_SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader {
public:
    unsigned int ID;

    Shader(const char* vertexSourcePath, const char* fragmentSourcePath) {
        /// 1. retrieve the source code from source path
        std::string vertexSourceCode;
        std::string fragmentSourceCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // set the exceptions for ifstream
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            // open files
            vShaderFile.open(vertexSourcePath);
            fShaderFile.open(fragmentSourcePath);
            std::stringstream vShaderStream, fShaderStream;
            // read files
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file
            vShaderFile.close();
            fShaderFile.close();
            // convert to string
            vertexSourceCode = vShaderStream.str();
            fragmentSourceCode = fShaderStream.str();
        } catch (std::ifstream::failure e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << e.what() << std::endl;
        }

        const char* vertexSource = vertexSourceCode.c_str();
        const char* fragmentSource = fragmentSourceCode.c_str();

        /// 2. compile the shader
        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexSource, NULL);
        glCompileShader(vertex);

        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentSource, NULL);
        glCompileShader(fragment);

        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // shader program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);

        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // delete shader after linking
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void use() {
        glUseProgram(ID);
    }

    void setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void setInt(const std::string &name, int value) const {
        glUniform1i(glGetAttribLocation(ID, name.c_str()), value);
    }

    void setFloat(const std::string &name, float value) const {
        glUniform1f(glGetAttribLocation(ID, name.c_str()), value);
    }

    void setUnsignedInt(const std::string &name, unsigned int value) const {
        glUniform1i(glGetAttribLocation(ID, name.c_str()), value);
    }
};

#endif //OPENGLSTUDY_SHADER_H
