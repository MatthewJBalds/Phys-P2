#pragma once 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../tiny_obj_loader.h"
#include "../stb_image.h"

class Model3D {
private:
    int img_width, img_height, colorChannels;
    unsigned char* tex_bytes;
    int img_width2, img_height2, colorChannels2;
    unsigned char* normal_bytes;

    GLuint texture;
    GLuint norm_tex;
    GLuint vertexShader;
    GLuint fragShader;
    GLuint shaderProg;
    GLuint colorAddress;

    glm::vec3 color;

    GLuint tex0Address;
    GLuint tex1Address;

    std::string path;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;

    tinyobj::attrib_t attributes;
    bool success;

    std::vector<GLuint> mesh_indices;
    std::vector<GLfloat> fullVertexData;

    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> bitangents;

    GLuint VAO, VBO;

    glm::mat4 identity_matrix4 = glm::mat4(1.0f);
    glm::mat4 transformation_matrix;

    glm::vec3 modelPosition;


public:
    Model3D(std::string obj);
    Model3D(std::string image, std::string obj);
    Model3D(std::string image, std::string normal_img, std::string obj);
    ~Model3D();

public:
    void setShaders(GLuint shaderProg) { this->shaderProg = shaderProg; }

private:
    void createTexture();
    void setVertAndTex();

public:
    void createModel();
    void updateTranslate(glm::vec3 position);
    void updateScale(glm::vec3 scale);
    void updateRotation(float rotate_x, float rotate_y, float rotate_z);
    void update();
    void renderTexture();
    void perform();

public:
    GLuint getShaderProg() { return this->shaderProg; }
    glm::vec3 getModelPos() { return this->modelPosition; }
    glm::vec3 getColor() { return this->color; }
    void setColor(glm::vec3 color) { this->color = color; }
};