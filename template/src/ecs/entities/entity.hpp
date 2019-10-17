#pragma once

#include "../components/physics.hpp"
#include "common.hpp"

struct Entity {
	//compied and omdified from common.hpp

	// pointers to all components go here
	Physics *physics = nullptr;
	
	// attributes that all or almost all of the entities will have
	float radians;
	vec2 position;
	vec2 scale;

	TexturedVertex vertices[4];
	Texture *texture;

	// A Mesh is a collection of a VertexBuffer and an IndexBuffer. A VAO
	// represents a Vertex Array Object and is the container for 1 or more Vertex Buffers and 
	// an Index Buffer.
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	// Effect component of Entity for Vertex and Fragment shader, which are then put(linked) together in a
	// single program that is then bound to the pipeline.
	struct Effect {
		GLuint vertex;
		GLuint fragment;
		GLuint program;

		bool load_from_file(const char* vs_path, const char* fs_path); // load shaders from files and link into program
		void release(); // release shaders and program
	} effect;

	// Transform component handles transformations passed to the Vertex shader.
	// gl Immediate mode equivalent, see the Rendering and Transformations section in the
	// specification pdf.
	struct Transform {
		mat3 out;

		void begin();
		void scale(vec2 scale);
		void rotate(float radians);
		void translate(vec2 offset);
		void end();
	} transform;
};