#include "Shader.h"

Shader::Shader()
{
    shaderID=0;
}
GLuint Shader::LoadShader(const char *shaderFile, GLenum type) {
    std::ifstream in(shaderFile);
    if (!in.is_open()) {
        throw std::runtime_error("Error: No se pudo abrir el archivo del shader: " + std::string(shaderFile));
    }

    std::string src = "", line;
    while (std::getline(in, line)) {
        src += line + "\n";
    }
    in.close();

    shaderID = glCreateShader(type);
    if (shaderID == 0) {
        throw std::runtime_error("Error: No se pudo crear el shader");
    }

    const char *source = src.c_str();
    glShaderSource(shaderID, 1, &source, NULL);
    glCompileShader(shaderID);

    GLint status;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        char *strInfoLog = new char[infoLogLength + 1];
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, strInfoLog);

        std::string errorMsg = "Error al compilar el shader:\n";
        errorMsg += strInfoLog;
        delete[] strInfoLog;

        glDeleteShader(shaderID);
        shaderID = 0;
        throw std::runtime_error(errorMsg);
    }

    return shaderID;
}

GLuint Shader::ReturnShaderID()
{
    return shaderID;
}
Shader::~Shader()
{
    //dtor
}
