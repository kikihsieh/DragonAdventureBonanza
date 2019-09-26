// Header
#include "player.hpp"

// stlib
#include <string>
#include <algorithm>

bool Player::init()
{
	// Clearing errors
	gl_flush_errors();

	// Loading shaders
//	if (!effect.load_from_file(shader_path("player.vs.glsl"), shader_path("player.fs.glsl")))
//		return false;
	
	// Setting initial values
	motion.position = { 50.f, 100.f };
	motion.speed = 200.f;

	physics.scale = { -35.f, 35.f };

	m_is_alive = true;

	return true;
}

// Releases all graphics resources
void Player::destroy()
{
	glDeleteShader(effect.vertex);
	glDeleteShader(effect.fragment);
	glDeleteShader(effect.program);
}

// Called on each frame by World::update()
void Player::update(float ms)
{
	float step = motion.speed * (ms / 1000);
	if (m_is_alive)
	{
	}
	else
	{
	}
}

void Player::draw(const mat3& projection)
{
	transform.begin();

	transform.translate({ 100.0f, 100.0f });
	transform.scale(physics.scale);
	transform.end();

	// Setting shaders
	glUseProgram(effect.program);

	// Enabling alpha channel for textures
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

	// Getting uniform locations
	GLint transform_uloc = glGetUniformLocation(effect.program, "transform");
	GLint color_uloc = glGetUniformLocation(effect.program, "fcolor");
	GLint projection_uloc = glGetUniformLocation(effect.program, "projection");
	GLint light_up_uloc = glGetUniformLocation(effect.program, "light_up");

	// Setting vertices and indices
	glBindVertexArray(mesh.vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);

	// Input data location as in the vertex buffer
	GLint in_position_loc = glGetAttribLocation(effect.program, "in_position");
	GLint in_color_loc = glGetAttribLocation(effect.program, "in_color");
	glEnableVertexAttribArray(in_position_loc);
	glEnableVertexAttribArray(in_color_loc);
	glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(in_color_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(vec3));

	// Setting uniform values to the currently bound program
	glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float*)&transform.out);

	// !!! Player Color
	float color[] = { 1.f, 1.f, 1.f };
	glUniform3fv(color_uloc, 1, color);
	glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float*)&projection);


	int light_up = 0;
	glUniform1iv(light_up_uloc, 1, &light_up);

	// Get number of infices from buffer,
	// we know our vbo contains both colour and position information, so...
	GLint size = 0;
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	GLsizei num_indices = size / sizeof(uint16_t);

	// Drawing!
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_SHORT, nullptr);
}



// Simple bounding box collision check
// This is a SUPER APPROXIMATE check that puts a circle around the bounding boxes and sees
// if the center point of either object is inside the other's bounding-box-circle. You don't
// need to try to use this technique.
//bool Player::collides_with(const Turtle& turtle)
//{
//	float dx = motion.position.x - turtle.get_position().x;
//	float dy = motion.position.y - turtle.get_position().y;
//	float d_sq = dx * dx + dy * dy;
//	float other_r = std::max(turtle.get_bounding_box().x, turtle.get_bounding_box().y);
//	float my_r = std::max(physics.scale.x, physics.scale.y);
//	float r = std::max(other_r, my_r);
//	r *= 0.6f;
//	if (d_sq < r * r)
//		return true;
//	return false;
//}



vec2 Player::get_position() const
{
	return motion.position;
}

void Player::move(vec2 off)
{
	motion.position.x += off.x; 
	motion.position.y += off.y; 
}

bool Player::is_alive() const
{
	return m_is_alive;
}

// Called when the player collides with a turtle
void Player::kill()
{
	m_is_alive = false;
}
