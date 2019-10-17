//
// Created by arden on 10/15/2019.
//

#include "button.hpp"

Button::Button() : m_texture(new Texture()) {
}

Button::~Button() {
    delete m_texture;
}

bool Button::init(vec2 pos, const char* path) {
//    if (!m_texture) {
//        m_texture = new Texture();
//    }
//    // Load shared texture
//    if (!m_texture->is_valid())
//    {
//        if (!m_texture->load_from_file(path))
//        {
//            fprintf(stderr, "Failed to load button texture!");
//            return false;
//        }
//    }
//    // The position corresponds to the center of the texture
//    float wr = m_texture->width * 0.5f;
//    float hr = m_texture->height * 0.5f;
//
//    vertices[0].position = { -wr, +hr, -0.02f };
//    vertices[0].texcoord = { 0.f, 1.f };
//    vertices[1].position = { +wr, +hr, -0.02f };
//    vertices[1].texcoord = { 1.f, 1.f };
//    vertices[2].position = { +wr, -hr, -0.02f };
//    vertices[2].texcoord = { 1.f, 0.f };
//    vertices[3].position = { -wr, -hr, -0.02f };
//    vertices[3].texcoord = { 0.f, 0.f };
//
//    // Counterclockwise as it's the default opengl front winding direction
//    uint16_t indices[] = { 0, 3, 1, 1, 3, 2 };
//
//    // Clearing errors
//    gl_flush_errors();
//
//    // Vertex Buffer creation
//    glGenBuffers(1, &mesh.vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(TexturedVertex) * 4, vertices, GL_STATIC_DRAW);
//
//    // Index Buffer creation
//    glGenBuffers(1, &mesh.ibo);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 6, indices, GL_STATIC_DRAW);
//
//    // Vertex Array (Container for Vertex + Index buffer)
//    glGenVertexArrays(1, &mesh.vao);
//    if (gl_has_errors())
//        return false;
//
//    // Loading shaders
//    if (!effect.load_from_file(shader_path("textured.vs.glsl"), shader_path("textured.fs.glsl")))
//        return false;
//
//    motion.position = pos;
    return true;
}

void Button::destroy() {
    delete m_texture;
    m_texture = nullptr;
}

void Button::draw(const mat3& projection) {
//    // Transformation code, see Rendering and Transformation in the template specification for more info
//    // Incrementally updates transformation matrix, thus ORDER IS IMPORTANT
//    transform.begin();
//    transform.translate(motion.position);
//    transform.end();
//
//    // Enabling alpha channel for textures
//    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glDisable(GL_DEPTH_TEST);
//
//    // Setting shaders
//    glUseProgram(effect.program);
//
//    // Getting uniform locations for glUniform* calls
//    GLint transform_uloc = glGetUniformLocation(effect.program, "transform");
//    GLint color_uloc = glGetUniformLocation(effect.program, "fcolor");
//    GLint projection_uloc = glGetUniformLocation(effect.program, "projection");
//
//    // Setting vertices and indices
//    glBindVertexArray(mesh.vao);
//    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
//
//    // Input data location as in the vertex buffer
//    GLint in_position_loc = glGetAttribLocation(effect.program, "in_position");
//    GLint in_texcoord_loc = glGetAttribLocation(effect.program, "in_texcoord");
//    glEnableVertexAttribArray(in_position_loc);
//    glEnableVertexAttribArray(in_texcoord_loc);
//    glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void*)0);
//    glVertexAttribPointer(in_texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void*)sizeof(vec3));
//
//    // Enabling and binding texture to slot 0
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, m_texture->id);
//
//    // Setting uniform values to the currently bound program
//    glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float*)&transform.out);
//    float color[] = { 1.f, 1.f, 1.f };
//    glUniform3fv(color_uloc, 1, color);
//    glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float*)&projection);
//
//    // Drawing!
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
}

void Button::update(float ms) {

}