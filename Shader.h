#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <fstream>
#include <stdexcept>

class Shader {
public:
    Shader();
    GLuint LoadShader(const char *shaderFile, GLenum type);
    GLuint ReturnShaderID();
    virtual ~Shader();

    // Variables de la cámara
    glm::mat4 viewMatrix; // Matriz de vista para las cámaras
    void SetCameraView(int cam, float tx, float ty, float tz, float gc, float altura, float d);

private:
    GLuint shaderID;
};

#endif // SHADER_H
