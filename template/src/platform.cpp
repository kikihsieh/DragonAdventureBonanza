#include "platform.hpp"

#include <iostream>
#include <math.h>
#include <cmath>
#include <algorithm>
using namespace std;

bool Platform::init() {
    
    // Load shared texture
    if (!platform_med_texture.is_valid())
    {
        if (!platform_med_texture.load_from_file(textures_path("platform-med.png")))
        {
            fprintf(stderr, "Failed to load platform-med texture!");
            return false;
        }
    }
    
    // The position corresponds to the center of the texture
    float wr = platform_med_texture.width * 0.5f; //760 * 0.5
    float hr = platform_med_texture.height * 0.5f; //110 * 0.5
    
    //TexturedVertex vertices[4];
    vertices[0].position = { -wr, +hr, -0.02f };
    vertices[0].texcoord = { 0.f, 1.f };
    vertices[1].position = { +wr, +hr, -0.02f };
    vertices[1].texcoord = { 1.f, 1.f };
    vertices[2].position = { +wr, -hr, -0.02f };
    vertices[2].texcoord = { 1.f, 0.f };
    vertices[3].position = { -wr, -hr, -0.02f };
    vertices[3].texcoord = { 0.f, 0.f };
    
    // Counterclockwise as it's the default opengl front winding direction
    uint16_t indices[] = { 0, 3, 1, 1, 3, 2 };
    
    
    // Clearing errors
    gl_flush_errors();
    
    // Vertex Buffer creation
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexturedVertex) * 4, vertices, GL_STATIC_DRAW);
    
    // Index Buffer creation
    glGenBuffers(1, &mesh.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 6, indices, GL_STATIC_DRAW);
    
    // Vertex Array (Container for Vertex + Index buffer)
    glGenVertexArrays(1, &mesh.vao);
    if (gl_has_errors())
        return false;
    
    // Loading shaders
    if (!effect.load_from_file(shader_path("textured.vs.glsl"), shader_path("textured.fs.glsl")))
        return false;
    
    motion.position = {500.f, 400.f};
    physics.scale = { 0.3f, 0.3f };
    compute_world_coordinate();
    return true;
}

// Releases all graphics resources
void Platform::destroy() {
    glDeleteBuffers(1, &mesh.vbo);
    
    glDeleteShader(effect.vertex);
    glDeleteShader(effect.fragment);
    glDeleteShader(effect.program);
}

void Platform::draw(const mat3& projection) {
    
    transform.begin();
    transform.translate(motion.position);
    transform.scale(physics.scale);
    transform.end();
    
    // Enabling alpha channel for textures
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //    glEnable(GL_DEPTH_TEST);
    
    // Setting shaders
    glUseProgram(effect.program);
    
    // Getting uniform locations for glUniform* calls
    GLint transform_uloc = glGetUniformLocation(effect.program, "transform");
    GLint color_uloc = glGetUniformLocation(effect.program, "fcolor");
    GLint projection_uloc = glGetUniformLocation(effect.program, "projection");
    
    // Setting vertices and indices
    glBindVertexArray(mesh.vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
    
    // Input data location as in the vertex buffer
    GLint in_position_loc = glGetAttribLocation(effect.program, "in_position");
    GLint in_texcoord_loc = glGetAttribLocation(effect.program, "in_texcoord");
    glEnableVertexAttribArray(in_position_loc);
    glEnableVertexAttribArray(in_texcoord_loc);
    glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void*)0);
    glVertexAttribPointer(in_texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void*)sizeof(vec3));
    
    // Enabling and binding texture to slot 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, platform_med_texture.id);
    
    // Setting uniform values to the currently bound program
    glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float*)&transform.out);
    float color[] = { 1.f, 1.f, 1.f };
    glUniform3fv(color_uloc, 1, color);
    glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float*)&projection);
    
    // Drawing!
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
}

vec2 Platform::get_position() const
{
    return motion.position;
}

vec2 Platform::get_bounding_box() const
{
    // Returns the local bounding coordinates scaled by the current size of the turtle
    return { std::fabs(physics.scale.x) * platform_med_texture.width, std::fabs(physics.scale.y) * platform_med_texture.height };
}

void Platform::compute_world_coordinate()
{
    platform_world_coord.clear();
    transform.begin();
    transform.translate(motion.position);
    transform.scale(physics.scale);
    transform.end();
    
    for (auto& v : vertices) {
        vec3 transformed_vertex = mul(transform.out, vec3{ v.position.x, v.position.y, 1.f });
        platform_world_coord.push_back({ transformed_vertex.x, transformed_vertex.y });
    }
    
    top = platform_world_coord[2].y;
    bottom = platform_world_coord[0].y;
    left = platform_world_coord[0].x;
    right = platform_world_coord[2].x;
}
