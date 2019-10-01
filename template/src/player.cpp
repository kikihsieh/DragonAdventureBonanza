// Header
#include "player.hpp"
#include "ground.hpp"

// stlib
#include <algorithm>

bool Player::init()
{
	// Load shared texture
	if (!player_texture.is_valid())
	{
		if (!player_texture.load_from_file(textures_path("player.png")))
		{
			fprintf(stderr, "Failed to load player texture!");
			return false;
		}
	}
	
	// The position corresponds to the center of the texture
	float wr = player_texture.width * 0.5f;
	float hr = player_texture.height * 0.5f;

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
	if (!effect.load_from_file(shader_path("player.vs.glsl"), shader_path("player.fs.glsl")))
		return false;

    walking_speed = 250.f;
    jumping_speed = -500.f;
    gravity = 10.f;

	// Setting initial values
	motion.position = { 100.f, 400.f };
	motion.speed.x = 0.f;
	motion.speed.y = 0.f;
	motion.acc.x = 0.f;
	motion.acc.y = gravity;

	physics.scale = { 0.25f, 0.25f };

	m_is_alive = true;
    m_on_ground = false;
    m_is_facing_forwards = true;

	return true;
}

// Releases all graphics resources
void Player::destroy()
{
	glDeleteBuffers(1, &mesh.vbo);
	glDeleteBuffers(1, &mesh.ibo);
	glDeleteBuffers(1, &mesh.vao);

	glDeleteShader(effect.vertex);
	glDeleteShader(effect.fragment);
	glDeleteShader(effect.program);
}

// Called on each frame by World::update()
void Player::update(float ms)
{
	float x_step = motion.speed.x * (ms / 1000);
	float y_step = motion.speed.y * (ms/ 1000);
	motion.speed.y += motion.acc.y;
	if (m_is_alive) {
        move({x_step, y_step});
    }
}

void Player::draw(const mat3& projection)
{
	// Transformation code, see Rendering and Transformation in the template specification for more info
	// Incrementally updates transformation matrix, thus ORDER IS IMPORTANT
	transform.begin();
	transform.translate(motion.position);
	transform.rotate(motion.radians);
	transform.scale(physics.scale);
	transform.end();

	// Enabling alpha channel for textures
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

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
	glBindTexture(GL_TEXTURE_2D, player_texture.id);

	// Setting uniform values to the currently bound program
	glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float*)&transform.out);
	float color[] = { 1.f, 1.f, 1.f };
	glUniform3fv(color_uloc, 1, color);
	glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float*)&projection);

	// Drawing!
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
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

void Player::walk(bool forward) {
    if (forward) {
        motion.speed.x = walking_speed;
        m_is_facing_forwards = true;
    } else {
        motion.speed.x = -walking_speed;
        m_is_facing_forwards = false;
    }
}

void Player::stop() {
    motion.speed.x = 0;
}

void Player::jump() {
    motion.speed.y = jumping_speed;
}

bool Player::can_jump() {
    // TODO double jump can be added here
    return m_on_ground;
}

void Player::land(const Ground& ground)
{
	compute_world_coordinate();
	for (vec2 pwc : player_world_coord) {
		if (pwc.y >= ground.surface_y) {
			m_on_ground = true;
		    motion.speed.y = 0;
		    motion.acc.y = 0;
			return;
		}
	}
	motion.acc.y = gravity;
	m_on_ground = false;
}

void Player::compute_world_coordinate()
{
	player_world_coord.clear();
	transform.begin();
	transform.translate(motion.position);
	transform.rotate(motion.radians);
	transform.scale(physics.scale);
	transform.end();

	for (auto& v : vertices) {
		vec3 transformed_vertex = mul(transform.out, vec3{ v.position.x, v.position.y, 1.f });
		player_world_coord.push_back({ transformed_vertex.x, transformed_vertex.y });
	}
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
