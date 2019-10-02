// Header
#include "spider.hpp"

#include <cmath>
#include <iostream>

Texture Spider::spider_texture;

bool Spider::init()
{
	// Load shared texture
	if (!spider_texture.is_valid())
	{
		if (!spider_texture.load_from_file(textures_path("spider.png")))
		{
			fprintf(stderr, "Failed to load spider texture!");
			return false;
		}
	}

	// The position corresponds to the center of the texture
	float wr = spider_texture.width * 0.5f;
	float hr = spider_texture.height * 0.5f;

	TexturedVertex vertices[4];
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
	if (!effect.load_from_file(shader_path("spider.vs.glsl"), shader_path("spider.fs.glsl")))
		return false;

	motion.radians = 0.f;

	// Setting initial values, scale is negative to make it face the opposite way
	// 1.0 would be as big as the original texture.
	
    physics.scale = { -0.4f, 0.4f };
    
    direction = true; // true = walking to right, false= left
    jumpNow = false;
    
	direction_y = true;
    randomBoo = false;
    
	return true;
}

// Releases all graphics resources
void Spider::destroy()
{
	glDeleteBuffers(1, &mesh.vbo);
	glDeleteBuffers(1, &mesh.ibo);
	glDeleteBuffers(1, &mesh.vao);

	glDeleteShader(effect.vertex);
	glDeleteShader(effect.fragment);
	glDeleteShader(effect.program);
}

void Spider::update(float ms)
{
    float step = -1.0 * motion.speed.x * (ms / 1000);
    
    if(randomBoo == false) {
		jumpNow = true;
        randomBoo =true;
    };

    y_axis_movement(step);
    x_axis_movement();
}

void Spider::set_init_position_and_max_xy(vec2 coord)
{
	motion.position = coord;
	distance = 20;
	max_position = motion.position.x + distance;
	min_position = motion.position.x - distance;
	inital_pos = motion.position.x;
	distance_y = 50;
	max_position_y = motion.position.y + distance_y;
	min_position_y = motion.position.y;
}

void Spider::draw(const mat3& projection)
{
	// Transformation code, see Rendering and Transformation in the template specification for more info
	// Incrementally updates transformation matrix, thus ORDER IS IMPORTANT
	transform.begin();
	transform.translate(motion.position);
	transform.rotate(motion.radians);
	transform.scale(physics.scale);
	transform.end();

	// Setting shaders
	glUseProgram(effect.program);

	// Enabling alpha channel for textures
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

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
	glBindTexture(GL_TEXTURE_2D, spider_texture.id);

	// Setting uniform values to the currently bound program
	glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float*)&transform.out);
	float color[] = { 1.f, 1.f, 1.f };
	glUniform3fv(color_uloc, 1, color);
	glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float*)&projection);

	// Drawing!
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
}

vec2 Spider::get_position()const
{
	return motion.position;
}

void Spider::x_axis_movement()
{
    // move towards the positive x-axis
    if(jumpNow==false){
        if (direction == true){
            if (motion.position.x < max_position){
                motion.position.x += 1;
            } else {
                direction = false;
                motion.position.x -= 1;
            }
            
        };
    // move towards negative x-axis
        if (direction == false){
            if (min_position < motion.position.x){
                motion.position.x -= 1;
            } else {
                direction = true;
                motion.position.x += 1;
            }
        }
    }
}

int Spider::jump_Time(float step){
    int min_waitTime = 5;
    int max_waitTime = 100;
    int num = (rand()%(max_waitTime - min_waitTime + 1) + min_waitTime);
    jumpT = num + step;
    currTime = step;
    return jumpT;
}

void Spider::y_axis_movement (float step){
    // move towards the positive x-axis
    if (jumpNow == true){
        if (direction_y == true){
            if(motion.position.y < max_position_y){
                motion.position.y += 1;
            } else {
                direction_y = false;
                motion.position.y -=1;
            }};
        if (direction_y == false){
            if (min_position_y < motion.position.y){
                motion.position.y -= 1;
            }
            if (min_position_y == motion.position.y){
                direction_y = true;
                jumpNow = false;
                
            }
        }
    }
}

vec2 Spider::get_bounding_box() const
{
	// Returns the local bounding coordinates scaled by the current size of the spider
	// fabs is to avoid negative scale due to the facing direction.
	return { std::fabs(physics.scale.x) * spider_texture.width, std::fabs(physics.scale.y) * spider_texture.height };
}
