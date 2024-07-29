#include  "Model3D.h"

/* Contructors */
Model3D::Model3D(std::string obj) {
    this->path = obj.c_str();
    this->success = tinyobj::LoadObj(
        &this->attributes,
        &this->shapes,
        &this->material,
        &this->warning,
        &this->error,
        this->path.c_str()
    );
}

Model3D::Model3D(std::string image, std::string obj) {
    stbi_set_flip_vertically_on_load(true);

    this->tex_bytes =
        stbi_load(image.c_str(),
            &this->img_width,
            &this->img_height,
            &this->colorChannels,
            0);

    this->path = obj.c_str();

    this->success = tinyobj::LoadObj(
        &this->attributes,
        &this->shapes,
        &this->material,
        &this->warning,
        &this->error,
        this->path.c_str()
    );
}

Model3D::Model3D(std::string image, std::string normal_img, std::string obj) {
    stbi_set_flip_vertically_on_load(true);

    this->tex_bytes =
        stbi_load(image.c_str(),
            &this->img_width,
            &this->img_height,
            &this->colorChannels,
            0);

    this->path = obj.c_str();

    this->success = tinyobj::LoadObj(
        &this->attributes,
        &this->shapes,
        &this->material,
        &this->warning,
        &this->error,
        this->path.c_str()
    );

    stbi_set_flip_vertically_on_load(true);

    this->normal_bytes =
        stbi_load(normal_img.c_str(),
            &this->img_width2,
            &this->img_height2,
            &this->colorChannels2,
            0);
}

/* Delete model */
Model3D::~Model3D() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
}


/* Create Texture */
void Model3D::createTexture() {
    glGenTextures(1, &this->texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture);

    if (this->colorChannels == 3) {
        glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGB,
            this->img_width,
            this->img_height,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            this->tex_bytes);
    }
    else {
        glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGBA,
            this->img_width,
            this->img_height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            this->tex_bytes);
    }

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(this->tex_bytes);
}

/* Set Vertex and Texture */
void Model3D::setVertAndTex() {
    for (int i = 0; i < this->shapes[0].mesh.indices.size(); i++) {
        this->mesh_indices.push_back(this->shapes[0].mesh.indices[i].vertex_index);
    }

    for (int i = 0; i < this->shapes[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData = this->shapes[0].mesh.indices[i];

        this->fullVertexData.push_back(this->attributes.vertices[(vData.vertex_index * 3)]);
        this->fullVertexData.push_back(this->attributes.vertices[(vData.vertex_index * 3) + 1]);
        this->fullVertexData.push_back(this->attributes.vertices[(vData.vertex_index * 3) + 2]);

        this->fullVertexData.push_back(this->attributes.normals[(vData.normal_index * 3)]);
        this->fullVertexData.push_back(this->attributes.normals[(vData.normal_index * 3) + 1]);
        this->fullVertexData.push_back(this->attributes.normals[(vData.normal_index * 3) + 2]);

        this->fullVertexData.push_back(this->attributes.texcoords[(vData.texcoord_index * 2)]);
        this->fullVertexData.push_back(this->attributes.texcoords[(vData.texcoord_index * 2) + 1]);
    }
}

/* Make Model */
void Model3D::createModel() {
    this->createTexture();
    this->setVertAndTex();

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GLfloat) * this->fullVertexData.size(),
        this->fullVertexData.data(),
        GL_DYNAMIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GLfloat),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    GLintptr normalPtr = 3 * sizeof(float);

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GLfloat),
        (void*)normalPtr
    );

    glEnableVertexAttribArray(1);

    GLintptr uvPtr = 6 * sizeof(float);

    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GLfloat),
        (void*)uvPtr
    );

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/* Update pos */
void Model3D::updateTranslate(glm::vec3 position) {
    this->transformation_matrix = glm::translate(this->identity_matrix4, glm::vec3(position.x, position.y, position.z));
    this->modelPosition = glm::vec3(this->transformation_matrix[3]);
}

/* Scale model */
void Model3D::updateScale(glm::vec3 scale) {
    this->transformation_matrix = glm::scale(this->transformation_matrix, glm::vec3(scale.x, scale.y, scale.z));
}

/* Rotate model */
void Model3D::updateRotation(float rotate_x, float rotate_y, float rotate_z) {
    this->transformation_matrix = glm::rotate(this->transformation_matrix, glm::radians(rotate_x), glm::normalize(glm::vec3(1.f, 0.f, 0.f))); //X
    this->transformation_matrix = glm::rotate(this->transformation_matrix, glm::radians(rotate_y), glm::normalize(glm::vec3(0.f, 1.f, 0.f))); //Y
    this->transformation_matrix = glm::rotate(this->transformation_matrix, glm::radians(rotate_z), glm::normalize(glm::vec3(0.f, 0.f, 1.f))); //Z
}

void Model3D::update() {
    unsigned int transformLoc = glGetUniformLocation(this->shaderProg, "transform");
    glUniformMatrix4fv(transformLoc,
        1,
        GL_FALSE,
        glm::value_ptr(this->transformation_matrix));
}

void Model3D::renderTexture() {
    glActiveTexture(GL_TEXTURE0);
    this->tex0Address = glGetUniformLocation(this->shaderProg, "tex0");
    glBindTexture(GL_TEXTURE_2D, this->texture);
    this->colorAddress = glGetUniformLocation(this->shaderProg, "color");
    glUniform3fv(this->colorAddress, 1, glm::value_ptr(this->color));
    glUniform1i(this->tex0Address, 0);
}

void Model3D::perform() {
    this->update();
    this->renderTexture();
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, this->fullVertexData.size() / 8);
}