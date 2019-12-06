#pragma once

// stlib
#include <fstream> // stdout, stderr..

// glfw
#define NOMINMAX
#include <gl3w.h>
#include <GLFW/glfw3.h>

// Simple utility macros to avoid mistyping directory name, name has to be a string literal
// audio_path("audio.ogg") -> data/audio/audio.ogg
// Get defintion of PROJECT_SOURCE_DIR from:
#include "project_path.hpp"

#define shader_path(name) PROJECT_SOURCE_DIR "/shaders/" name

#define data_path PROJECT_SOURCE_DIR "/data"
#define textures_path(name)  data_path "/textures/" name
#define audio_path(name) data_path  "/audio/" name
#define mesh_path(name) data_path  "/meshes/" name

// Not much math is needed and there are already way too many libraries linked (:
// If you want to do some overloads..
struct vec2 { float x, y; };
struct vec3 { float x, y, z; };
struct vec4 {float a, b, c, d;};
struct mat3 { vec3 c0, c1, c2; };
struct mat4 { vec4 c0, c1, c2, c3; };

// Utility functions
float dot(vec2 l, vec2 r);
float dot(vec3 l, vec3 r);
float dot(vec4 l, vec4 r);
mat3 mul(const mat3& l, const mat3& r);
mat4 mul(const mat4& l, const mat4& r);
vec2 mul(vec2 a, float b);
vec2 mul(vec2 a, vec2 b);
vec3 mul(mat3 m, vec3 v);
vec2 normalize(vec2 v);
vec2 add(vec2 a, vec2 b);
vec2 sub(vec2 a, vec2 b);
vec2 to_vec2(vec3 v);
float sq_len(vec2 a);
float len(vec2 a);



// OpenGL utilities
// cleans error buffer
void gl_flush_errors();
bool gl_has_errors();

// Single Vertex Buffer element for non-textured meshes (coloured.vs.glsl & salmon.vs.glsl)
struct Vertex
{
	vec3 position;
	vec3 color;
};

// Single Vertex Buffer element for textured sprites (textured.vs.glsl)
struct TexturedVertex
{
	vec3 position;
	vec2 texcoord;
};

// Texture wrapper
struct Texture
{
	Texture();
	~Texture();

	GLuint id = 0;
	GLuint depth_render_buffer_id;
	int width;
	int height;
	
	// Loads texture from file specified by path
	bool load_from_file(const char* path);
	bool is_valid()const; // True if texture is valid
	bool create_from_screen(GLFWwindow const * const window); // Screen texture
};

// https://stackoverflow.com/questions/207976/how-to-easily-map-c-enums-to-strings
template<typename T> struct map_init_helper
{
    T& data;
    map_init_helper(T& d) : data(d) {}
    map_init_helper& operator() (typename T::key_type const& key, typename T::mapped_type const& value)
    {
        data[key] = value;
        return *this;
    }
};

template<typename T> map_init_helper<T> map_init(T& item)
{
    return map_init_helper<T>(item);
}
