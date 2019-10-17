// Header
#include "player.hpp"
#include "levels/tile.hpp"

// stlib
#include <algorithm>
#include <cmath>
#include <iostream>

Player::Player() {
    drawable = {};
    drawable->texture_path = textures_path("player.png");
    drawable->fs_shader = shader_path("textured.fs.glsl");
    drawable->vs_shader = shader_path("textured.vs.glsl");
}

bool Player::init(vec2 x_bounds, vec2 y_bounds)
{
    // walking_speed = 250.f;
    // jumping_speed = -500.f;
    // gravity = 10.f;

	// // Setting initial values
    // // motion.position = { 100.f, 450.f };
	// motion.speed.x = 0.f;
	// motion.speed.y = 0.f;
	// motion.acc.x = 0.f;
	// motion.acc.y = gravity;

	// physics.scale = { 0.16f, 0.16f };

	m_is_alive = true;
    m_on_ground = false;
	
    m_is_facing_forwards = true;
	kill_enemy = false;

	m_unlocked_double_jump = true;
	
	m_airdashing = false;
	
	m_airdash_duration = 500.f;
	m_airdash_timer = 0;
	
	m_jump_count = 10;

    m_x_world_bounds = x_bounds;
    m_y_world_bounds = y_bounds;
	
	return true;
}

// Releases all graphics resources
// void Player::destroy()
// {
// 	glDeleteBuffers(1, &mesh.vbo);
// 	glDeleteBuffers(1, &mesh.ibo);
// 	glDeleteBuffers(1, &mesh.vao);

// 	glDeleteShader(effect.vertex);
// 	glDeleteShader(effect.fragment);
// 	glDeleteShader(effect.program);
// }

// Called on each frame by World::update()
void Player::update(float ms)
{
//	if (m_is_alive) {

//		if (m_airdashing && abs(motion.speed.x) > 0) {
//			motion.speed.x -= (motion.speed.x / abs(motion.speed.x)) * 20;
//		} else {
//			m_airdashing = false;
//			gravity = 10;
//		}


//		float x_step = motion.speed.x * (ms / 1000);
//		/float y_step = motion.speed.y * (ms/ 1000);

//	    if ((x_step < 0 && motion.position.x < m_x_world_bounds.x) ||
//			  (x_step > 0 && motion.position.x > m_x_world_bounds.y)) {
//			  	x_step = 0;
//				m_airdashing = false;
//		}

		// Jumping
//		if (y_step < 0 && motion.position.y < m_y_world_bounds.x) {
//			y_step *= -1.f;
//			motion.speed.y = 0;
}

//		motion.speed.y += motion.acc.y;

		// Die when touching bottom of screen
//		if (y_step > 0 && motion.position.y > m_y_world_bounds.y) {
//			std::cout << "Player died" << std::endl;
//			m_is_alive = false;
//		}
	   
//		motion.speed.y += motion.acc.y;
//        move({x_step, y_step});
//	}
//	else {
//		float sink_step = 200.f * (ms / 1000);
//		move({ 0.f, sink_step });
//	}
//}

// void Player::draw(const mat3& projection)
// {
// 	// Transformation code, see Rendering and Transformation in the template specification for more info
// 	// Incrementally updates transformation matrix, thus ORDER IS IMPORTANT
// 	transform.begin();
// 	transform.translate(motion.position);
// 	transform.rotate(motion.radians);
// 	transform.scale(physics.scale);
// 	transform.end();

// 	// Enabling alpha channel for textures
// 	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
// 	glDisable(GL_DEPTH_TEST);

// 	// Setting shaders
// 	glUseProgram(effect.program);
		
// 	// Getting uniform locations for glUniform* calls
// 	GLint transform_uloc = glGetUniformLocation(effect.program, "transform");
// 	GLint color_uloc = glGetUniformLocation(effect.program, "fcolor");
// 	GLint projection_uloc = glGetUniformLocation(effect.program, "projection");

// 	// Setting vertices and indices
// 	glBindVertexArray(mesh.vao);
// 	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);

// 	// Input data location as in the vertex buffer
// 	GLint in_position_loc = glGetAttribLocation(effect.program, "in_position");
// 	GLint in_texcoord_loc = glGetAttribLocation(effect.program, "in_texcoord");
// 	glEnableVertexAttribArray(in_position_loc);
// 	glEnableVertexAttribArray(in_texcoord_loc);
// 	glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void*)0);
// 	glVertexAttribPointer(in_texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void*)sizeof(vec3));

// 	// Enabling and binding texture to slot 0
// 	glActiveTexture(GL_TEXTURE0);
// 	glBindTexture(GL_TEXTURE_2D, player_texture.id);

// 	// Setting uniform values to the currently bound program
// 	glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float*)&transform.out);
// 	float color[] = { 1.f, 1.f, 1.f };
// 	glUniform3fv(color_uloc, 1, color);
// 	glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float*)&projection);

// 	// Drawing!
// 	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
// }

vec2 Player::get_position() const
{
//	return motion.position;
}

void Player::move(vec2 off)
{
//	motion.position.x += off.x;
//	motion.position.y += off.y;
}

void Player::walk(bool forward) {
    if (forward) {
//        motion.speed.x = walking_speed;
        m_is_facing_forwards = true;
    } else {
//        motion.speed.x = -walking_speed;
        m_is_facing_forwards = false;
    }
}

void Player::stop() {
//    motion.speed.x = 0;
}

void Player::jump() {
//    motion.speed.y = jumping_speed;
	m_jump_count ++;
}

void Player::air_dash(bool forward) {
//	motion.speed.x =  forward ? 1000.f : -1000.f;
//	motion.speed.y = 0;
//	gravity = 0;
	m_airdashing = true;
}

bool Player::can_jump() {
	return m_unlocked_double_jump ? m_jump_count < 2 : m_on_ground;
}

bool Player::can_airdash() {
	return !m_on_ground && !m_airdashing;
}

bool Player::is_airdashing() {
	return m_airdashing;
}

void Player::compute_world_coordinate()
{
	player_world_coord.clear();
//	transform.begin();
//	transform.translate(motion.position);
//	transform.rotate(motion.radians);
//	transform.scale(physics.scale);
//	transform.end();

//	for (auto& v : vertices) {
//		vec3 transformed_vertex = mul(transform.out, vec3{ v.position.x, v.position.y, 1.f });
//		player_world_coord.push_back({ transformed_vertex.x, transformed_vertex.y });
//	}

	top = player_world_coord[2].y;
	bottom = player_world_coord[0].y;
	left = player_world_coord[0].x;
	right = player_world_coord[2].x;

}

//bool Player::collides_with(Spider& spider)
//{
//	kill_enemy = false;
//	compute_world_coordinate();
//	spider.compute_world_coordinate();
//	// kills enemy
//
//	if ((left + 1.f) < spider.right &&
//		(right - 1.f) > spider.left &&
//		bottom >= spider.top-5.f &&
//		bottom <= spider.top+5.f) {
//		if (motion.speed.y > 0) {
//			motion.speed.y = 0.f;
//		}
//		std::cout << "killed one enemy" << std::endl;
//		motion.acc.y = 0.f;
//		m_jump_count = 1;
//		kill_enemy = true;
//		return true;
//	}
//	// bump into enemy
//	else if (top < spider.bottom && bottom > spider.top && left <spider.right && right > spider.left){
//
//		// TODO: check if player is still alive
//		// life-- if life > 0 else die
//		kill_enemy = false;
//		kill();
//		return true;
//	}
//
//	return false;
//}

bool Player::is_alive() const
{
	return m_is_alive;
}

// Called when the player collides with a turtle
void Player::kill()
{
	m_is_alive = false;
}
