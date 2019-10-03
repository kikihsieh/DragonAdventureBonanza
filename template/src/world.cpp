// Header
#include "world.hpp"

// stlib
#include <string.h>
#include <cassert>
#include <sstream>
#include <iostream>

// Same as static in c, local to compilation unit
namespace
{
	const size_t NUM_SPIDER = 5;
	namespace
	{
		void glfw_err_cb(int error, const char* desc)
		{
			fprintf(stderr, "%d: %s", error, desc);
		}
	}
}

World::World() :
m_next_spider_spawn(0.f)
{
	// Seeding rng with random device
	m_rng = std::default_random_engine(std::random_device()());
}

World::~World()
{

}

// World initialization
bool World::init(vec2 screen)
{
	//-------------------------------------------------------------------------
	// GLFW / OGL Initialization
	// Core Opengl 3.
	glfwSetErrorCallback(glfw_err_cb);
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW");
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
#if __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	glfwWindowHint(GLFW_RESIZABLE, 0);
	m_window = glfwCreateWindow((int)screen.x, (int)screen.y, "Dragon Adventure Bonanza", nullptr, nullptr);
	if (m_window == nullptr)
		return false;

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1); // vsync

	// Load OpenGL function pointers
	gl3w_init();

	// Setting callbacks to member functions (that's why the redirect is needed)
	// Input is handled using GLFW, for more info see
	// http://www.glfw.org/docs/latest/input_guide.html
	glfwSetWindowUserPointer(m_window, this);
	auto key_redirect = [](GLFWwindow* wnd, int _0, int _1, int _2, int _3) { ((World*)glfwGetWindowUserPointer(wnd))->on_key(wnd, _0, _1, _2, _3); };
	auto cursor_pos_redirect = [](GLFWwindow* wnd, double _0, double _1) { ((World*)glfwGetWindowUserPointer(wnd))->on_mouse_move(wnd, _0, _1); };
	glfwSetKeyCallback(m_window, key_redirect);
	glfwSetCursorPosCallback(m_window, cursor_pos_redirect);

	// Create a frame buffer
	m_frame_buffer = 0;
	glGenFramebuffers(1, &m_frame_buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer);

	// For some high DPI displays (ex. Retina Display on Macbooks)
	// https://stackoverflow.com/questions/36672935/why-retina-screen-coordinate-value-is-twice-the-value-of-pixel-value
	int fb_width, fb_height;
	glfwGetFramebufferSize(m_window, &fb_width, &fb_height);
	m_screen_scale = static_cast<float>(fb_width) / screen.x;

	// Initialize the screen texture
	m_screen_tex.create_from_screen(m_window);

	m_camera.init(screen);

	return m_player.init() && m_background.init() && m_ground.init() && init_enemies(m_screen_scale, fb_width, fb_height);
}

// Releases all the associated resources
void World::destroy()
{
	glDeleteFramebuffers(1, &m_frame_buffer);
	glfwDestroyWindow(m_window);
}

// Update our game world
bool World::update(float elapsed_ms)
{
	int w, h;
	glfwGetFramebufferSize(m_window, &w, &h);
	vec2 screen = { (float)w / m_screen_scale, (float)h / m_screen_scale };
	
	// check if player is on the ground
	m_player.update(elapsed_ms);

	m_camera.update(m_player.get_position(), m_player.is_facing_forwards());

	m_ground.set_surface_y();
    m_player.land(m_ground);
	for(auto& spider : m_spiders)
		spider.update(elapsed_ms);

	return true;
}

// Render our game world
// http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/
void World::draw()
{
	// Clearing error buffer
	gl_flush_errors();

	// Getting size of window
	int w, h;
	glfwGetFramebufferSize(m_window, &w, &h);

	/////////////////////////////////////
	// First render to the custom framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer);

	// Clearing backbuffer
	glViewport(0, 0, w, h);
	glDepthRange(0.00001, 10);
	const float clear_color[3] = { 0.3f, 0.3f, 0.8f };
	glClearColor(clear_color[0], clear_color[1], clear_color[2], 1.0);
	glClearDepth(1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Fake projection matrix, scales with respect to window coordinates
	// PS: 1.f / w in [1][1] is correct.. do you know why ? (:
	float left = 0.f;// *-0.5;
	float top = 0.f;// (float)h * -0.5;
	float right = (float)w / m_screen_scale;// *0.5;
	float bottom = (float)h / m_screen_scale;// *0.5;

	float sx = 2.f / (right - left);
	float sy = 2.f / (top - bottom);
	float tx = m_camera.compute_translation_x();
	float ty = -(top + bottom) / (top - bottom);
	mat3 projection_2D{ { sx, 0.f, 0.f },{ 0.f, sy, 0.f },{ tx, ty, 1.f } };

	/////////////////////
	// Truely render to the screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Clearing backbuffer
	glViewport(0, 0, w, h);
	glDepthRange(0, 10);
	glClearColor(0, 0, 0, 1.0);
	glClearDepth(1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_screen_tex.id);

	m_background.draw(projection_2D);
	m_ground.draw(projection_2D);
	m_player.draw(projection_2D);
	for (auto& spider : m_spiders)
		spider.draw(projection_2D);

	//////////////////
	// Presenting
	glfwSwapBuffers(m_window);
}

// Should the game be over ?
bool World::is_over() const
{
	return glfwWindowShouldClose(m_window);
}

bool World::init_enemies(float& screen_scale, int& w, int& h)
{
	vec2 screen = { (float)w / screen_scale, (float)h / screen_scale };
	for (int i = 0; i < NUM_SPIDER; i++) {
		Spider spider;
		if (spider.init()) {
			spider.set_init_position_and_max_xy(vec2{ 50 + m_dist(m_rng) * (screen.x - 50), m_dist(m_rng) * (screen.y - 150) });
			m_spiders.emplace_back(spider);
		}
		else {
			fprintf(stderr, "Failed to initialize spider");
			return false;
		}
	}
	return true;
}

// On key callback
void World::on_key(GLFWwindow*, int key, int, int action, int mod)
{
    if (m_player.can_jump() && (key == GLFW_KEY_UP || key == GLFW_KEY_W)) {
        if (action == GLFW_PRESS) {
            m_player.jump();
        }
    }

    //LEFT
    if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A) {
        if (action == GLFW_PRESS) {
            m_player.walk(false);
        } else if (action == GLFW_RELEASE) {
            m_player.stop();
        }
    }
    // RIGHT
    if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) {
        if (action == GLFW_PRESS) {
            m_player.walk(true);
        } else if (action == GLFW_RELEASE) {
            m_player.stop();
        }
    }
}

void World::on_mouse_move(GLFWwindow* window, double xpos, double ypos)
{

}