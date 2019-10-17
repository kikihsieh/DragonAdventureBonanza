#include "render_system.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>

RenderSystem::RenderSystem(){
    //update this when adding sprites
    map_init(entity_textures)
            (PLAYER,"player.png")
            (FOREST_BACKGROUND, "background.png")
            (CAVE_BACKGROUND, "platform-lg.png")
            (START_MENU_BACKGROUND,"night.png");
    map_init(vs_shader_types)
            (PLAYER, "textured.vs.glsl")
            (FOREST_BACKGROUND, "background.vs.glsl")
            (CAVE_BACKGROUND, "background.vs.glsl")
            (START_MENU_BACKGROUND, "background.vs.glsl");
    map_init(fs_shader_types)
            (PLAYER, "textured.fs.glsl")
            (FOREST_BACKGROUND, "background.fs.glsl")
            (CAVE_BACKGROUND, "background.fs.glsl")
            (START_MENU_BACKGROUND, "background.fs.glsl");
}

RenderSystem::~RenderSystem() = default;

bool RenderSystem::init(const std::vector<Entity*>& entities) {

    for (auto & entity : entities){
        if (!entity->texture->is_valid())
	    {
		    if (!entity->texture->load_from_file(textures_path("player.png")))
		    {
			    fprintf(stderr, "Failed to load player texture!");
			    return false;
		    }
	    }
	
	// The position corresponds to the center of the texture
    	float wr = entity->texture->width * 0.5f;
    	float hr = entity->texture->height * 0.5f;

    	entity->vertices[0].position = { -wr, +hr, -0.02f };
    	entity->vertices[0].texcoord = { 0.f, 1.f };
    	entity->vertices[1].position = { +wr, +hr, -0.02f };
    	entity->vertices[1].texcoord = { 1.f, 1.f };
    	entity->vertices[2].position = { +wr, -hr, -0.02f };
    	entity->vertices[2].texcoord = { 1.f, 0.f };
    	entity->vertices[3].position = { -wr, -hr, -0.02f };
    	entity->vertices[3].texcoord = { 0.f, 0.f };
    
    	// Counterclockwise as it's the default opengl front winding direction
    	uint16_t indices[] = { 0, 3, 1, 1, 3, 2 };
    
    	// Clearing errors
    	gl_flush_errors();

    	// Vertex Buffer creation
    	glGenBuffers(1, &entity->vbo);
    	glBindBuffer(GL_ARRAY_BUFFER, entity->vbo);
    	glBufferData(GL_ARRAY_BUFFER, sizeof(TexturedVertex) * 4, entity->vertices, GL_STATIC_DRAW);

    	// Index Buffer creation
    	glGenBuffers(1, &entity->ibo);
    	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity->ibo);
    	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 6, indices, GL_STATIC_DRAW);
    
    	// Vertex Array (Container for Vertex + Index buffer)
    	glGenVertexArrays(1, &entity->vao);
    	if (gl_has_errors())
    		return false;

    	// Loading shaders
    	if (!entity->effect.load_from_file(shader_path("textured.vs.glsl"), shader_path("textured.fs.glsl")))
    		return false;
    };
}

void RenderSystem::destroy(const std::vector<Entity*>& entities) {
	for(auto & entity: entities){
        glDeleteBuffers(1, &entity->vbo);
	    glDeleteShader(entity->effect.vertex);
	    glDeleteShader(entity->effect.fragment);
	    glDeleteShader(entity->effect.program);
        delete entity->texture;
        entity->texture = nullptr;
    }
}

void RenderSystem::draw(const mat3 & projection, const std::vector<Entity*>& entities)
{
    for(auto & entity: entities){

        entity->transform.begin();
	    entity->transform.translate(entity->position);
	    entity->transform.rotate(entity->radians);
	    entity->transform.scale(entity->scale);
	    entity->transform.end();

	    // Enabling alpha channel for textures
	    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	    glDisable(GL_DEPTH_TEST);

	    // Setting shaders
	    glUseProgram(entity->effect.program);
    
	    // Getting uniform locations for glUniform* calls
	    GLint transform_uloc = glGetUniformLocation(entity->effect.program, "transform");
	    GLint color_uloc = glGetUniformLocation(entity->effect.program, "fcolor");
	    GLint projection_uloc = glGetUniformLocation(entity->effect.program, "projection");

	    // Setting vertices and indices
	    glBindVertexArray(entity->vao);
	    glBindBuffer(GL_ARRAY_BUFFER, entity->vbo);
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity->ibo);

	    // Input data location as in the vertex buffer
	    GLint in_position_loc = glGetAttribLocation(entity->effect.program, "in_position");
	    GLint in_texcoord_loc = glGetAttribLocation(entity->effect.program, "in_texcoord");
	    glEnableVertexAttribArray(in_position_loc);
	    glEnableVertexAttribArray(in_texcoord_loc);
	    glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void*)0);
	    glVertexAttribPointer(in_texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void*)sizeof(vec3));

	    // Enabling and binding texture to slot 0
	    glActiveTexture(GL_TEXTURE0);
	    glBindTexture(GL_TEXTURE_2D, entity->texture->id);

	    // Setting uniform values to the currently bound program
	    glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float*)&entity->transform.out);
	    float color[] = { 1.f, 1.f, 1.f };
	    glUniform3fv(color_uloc, 1, color);
	    glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float*)&projection);

	    // Drawing!
	    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
    };
}

namespace
{
	bool gl_compile_shader(GLuint shader)
	{
		glCompileShader(shader);
		GLint success = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLint log_len;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);
			std::vector<char> log(log_len);
			glGetShaderInfoLog(shader, log_len, &log_len, log.data());
			glDeleteShader(shader);

			fprintf(stderr, "GLSL: %s", log.data());
			return false;
		}

		return true;
	}
}

bool Entity::Effect::load_from_file(const char* vs_path, const char* fs_path) 
{
	gl_flush_errors();

	// Opening files
	std::ifstream vs_is(vs_path);
	std::ifstream fs_is(fs_path);

	if (!vs_is.good() || !fs_is.good())
	{
		fprintf(stderr, "Failed to load shader files %s, %s", vs_path, fs_path);
		return false;
	}

	// Reading sources
	std::stringstream vs_ss, fs_ss;
	vs_ss << vs_is.rdbuf();
	fs_ss << fs_is.rdbuf();
	std::string vs_str = vs_ss.str();
	std::string fs_str = fs_ss.str();
	const char* vs_src = vs_str.c_str();
	const char* fs_src = fs_str.c_str();
	GLsizei vs_len = (GLsizei)vs_str.size();
	GLsizei fs_len = (GLsizei)fs_str.size();

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vs_src, &vs_len);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fs_src, &fs_len);

	// Compiling
	// Shaders already delete if compilation fails
	if (!gl_compile_shader(vertex))
		return false;

	if (!gl_compile_shader(fragment))
	{
		glDeleteShader(vertex);
		return false;
	}

	// Linking
	program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	{
		GLint is_linked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &is_linked);
		if (is_linked == GL_FALSE)
		{
			GLint log_len;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);
			std::vector<char> log(log_len);
			glGetProgramInfoLog(program, log_len, &log_len, log.data());

			release();
			fprintf(stderr, "Link error: %s", log.data());
			return false;
		}
	}

	if (gl_has_errors())
	{
		release();
		fprintf(stderr, "OpenGL errors occured while compiling Effect");
		return false;
	}

	return true;
}

void Entity::Effect::release()
{
	glDeleteProgram(program);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Entity::Transform::begin()
{
	out = { { 1.f, 0.f, 0.f }, { 0.f, 1.f, 0.f}, { 0.f, 0.f, 1.f} };
}

void Entity::Transform::scale(vec2 scale)
{
	mat3 S = { { scale.x, 0.f, 0.f },{ 0.f, scale.y, 0.f },{ 0.f, 0.f, 1.f } };
	out = mul(out, S);
}

void Entity::Transform::rotate(float radians)
{
	float c = cosf(radians);
	float s = sinf(radians);
	mat3 R = { { c, s, 0.f },{ -s, c, 0.f },{ 0.f, 0.f, 1.f } };
	out = mul(out, R);
}

void Entity::Transform::translate(vec2 offset)
{
	mat3 T = { { 1.f, 0.f, 0.f },{ 0.f, 1.f, 0.f },{ offset.x, offset.y, 1.f } };
	out = mul(out, T);
}

void Entity::Transform::end()
{
	//
}
