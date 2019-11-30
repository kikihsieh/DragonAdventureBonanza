#ifndef DAB_DRAWABLE_HPP
#define DAB_DRAWABLE_HPP

#include <common.hpp>
#include <memory>
#include <glm/glm.hpp>

struct Drawable {

    Drawable() :
        texture(std::make_shared<Texture>()) {
    }

    ~Drawable() {}

    const char* texture_path;
    const char* vs_shader;
    const char* fs_shader;

    // A Mesh is a collection of a VertexBuffer and an IndexBuffer. A VAO
    // represents a Vertex Array Object and is the container for 1 or more Vertex Buffers and
    // an Index Buffer.
    GLuint vao;
    GLuint vbo;
    GLuint ibo;

    TexturedVertex vertices[4];
    std::shared_ptr<Texture> texture;
    glm::mat4 transform;

    // Effect component of Entity for Vertex and Fragment shader, which are then put(linked) together in a
    // single program that is then bound to the pipeline.
    struct Effect {
        GLuint vertex;
        GLuint fragment;
        GLuint program;
    } effect;
};

#endif //DAB_DRAWABLE_HPP
