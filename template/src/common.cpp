#include "common.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../ext/stb_image/stb_image.h"

// stlib
#include <cmath>

void gl_flush_errors()
{
	while (glGetError() != GL_NO_ERROR);
}

bool gl_has_errors()
{
	GLenum error = glGetError();

	if (error == GL_NO_ERROR) return false;

	while (error != GL_NO_ERROR)
	{
		const char* error_str = "";
		switch (error)
		{
			case GL_INVALID_OPERATION:
			error_str = "INVALID_OPERATION";
			break;
			case GL_INVALID_ENUM:
			error_str = "INVALID_ENUM";
			break;
			case GL_INVALID_VALUE:
			error_str = "INVALID_VALUE";
			break;
			case GL_OUT_OF_MEMORY:
			error_str = "OUT_OF_MEMORY";
			break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
			error_str = "INVALID_FRAMEBUFFER_OPERATION";
			break;
		}

		fprintf(stderr, "OpenGL: %s", error_str);
		error = glGetError();
	}

	return true;
}

float dot(vec2 l, vec2 r)
{
	return l.x * r.x + l.y * r.y;
}

float dot(vec3 l, vec3 r)
{
	return l.x * r.x + l.y * r.y + l.z * r.z;
}

float dot(vec4 l, vec4 r)
{
	return l.a * r.a + l.b * r.b + l.c * r.c + l.d * r.d;
}

vec2 add(vec2 a, vec2 b) { return { a.x+b.x, a.y+b.y }; }
vec2 sub(vec2 a, vec2 b) { return { a.x-b.x, a.y-b.y }; }
vec2 mul(vec2 a, float b) { return { a.x*b, a.y*b }; }
vec2 mul(vec2 a, vec2 b) { return { a.x*b.x, a.y*b.y }; }
vec3 mul(mat3 m, vec3 v) { return {
  dot(vec3{m.c0.x, m.c1.x, m.c2.x}, v),
  dot(vec3{m.c0.y, m.c1.y, m.c2.y}, v),
  dot(vec3{m.c0.z, m.c1.z, m.c2.z}, v)
}; }
float sq_len(vec2 a) { return dot(a, a); }
float len(vec2 a) { return std::sqrt(sq_len(a)); }
vec2 to_vec2(vec3 v) { return { v.x, v.y }; }

mat3 mul(const mat3 & l, const mat3 & r)
{
	mat3 l_t = { { l.c0.x, l.c1.x, l.c2.x},
	{ l.c0.y, l.c1.y, l.c2.y } ,
	{ l.c0.z, l.c1.z, l.c2.z } };

	mat3 ret;
	ret.c0.x = dot(l_t.c0, r.c0);
	ret.c0.y = dot(l_t.c1, r.c0);
	ret.c0.z = dot(l_t.c2, r.c0);

	ret.c1.x = dot(l_t.c0, r.c1);
	ret.c1.y = dot(l_t.c1, r.c1);
	ret.c1.z = dot(l_t.c2, r.c1);

	ret.c2.x = dot(l_t.c0, r.c2);
	ret.c2.y = dot(l_t.c1, r.c2);
	ret.c2.z = dot(l_t.c2, r.c2);
	return ret;
}

mat4 mul(const mat4 & l, const mat4 & r)
{
	mat4 l_t = { { l.c0.a, l.c1.a, l.c2.a, l.c3.a},
				 { l.c0.b, l.c1.b, l.c2.b, l.c3.b},
				 { l.c0.c, l.c1.c, l.c2.c, l.c3.c},
				 { l.c0.d, l.c1.d, l.c2.d, l.c3.d}};

	mat4 ret;
	ret.c0.a = dot(l_t.c0, r.c0);
	ret.c0.b = dot(l_t.c1, r.c0);
	ret.c0.c = dot(l_t.c2, r.c0);
	ret.c0.d = dot(l_t.c3, r.c0);

	ret.c1.a = dot(l_t.c0, r.c1);
	ret.c1.b = dot(l_t.c1, r.c1);
	ret.c1.c = dot(l_t.c2, r.c1);
	ret.c1.d = dot(l_t.c3, r.c1);

	ret.c2.a = dot(l_t.c0, r.c2);
	ret.c2.b = dot(l_t.c1, r.c2);
	ret.c2.c = dot(l_t.c2, r.c2);
	ret.c2.d = dot(l_t.c3, r.c2);

	ret.c3.a = dot(l_t.c0, r.c3);
	ret.c3.b = dot(l_t.c1, r.c3);
	ret.c3.c = dot(l_t.c2, r.c3);
	ret.c3.d = dot(l_t.c3, r.c3);
	return ret;
}

vec2 normalize(vec2 v)
{
	float m = sqrtf(dot(v, v));
	return { v.x / m, v.y / m };
}

Texture::Texture()
{

}

Texture::~Texture()
{
	if (id != 0) glDeleteTextures(1, &id);
	if (depth_render_buffer_id != 0) glDeleteRenderbuffers(1, &depth_render_buffer_id);
}

bool Texture::load_from_file(const char* path)
{
	if (path == nullptr)
		return false;

	stbi_uc* data = stbi_load(path, &width, &height, NULL, 4);
	if (data == NULL)
		return false;

	gl_flush_errors();
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	stbi_image_free(data);
	return !gl_has_errors();
}

// http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/
bool Texture::create_from_screen(GLFWwindow const * const window) {
	gl_flush_errors();
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glfwGetFramebufferSize(const_cast<GLFWwindow *>(window), &width, &height);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Generate the render buffer with the depth buffer
	glGenRenderbuffers(1, &depth_render_buffer_id);
	glBindRenderbuffer(GL_RENDERBUFFER, depth_render_buffer_id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_render_buffer_id);

	// Set id as colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, id, 0);

	// Set the list of draw buffers
	GLenum draw_buffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, draw_buffers); // "1" is the size of DrawBuffers

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	return !gl_has_errors();
}

bool Texture::is_valid()const
{
	return id != 0;
}
