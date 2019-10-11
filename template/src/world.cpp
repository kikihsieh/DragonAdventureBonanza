// Header
#include "world.hpp"

// stlib
#include <string.h>
#include <cassert>
#include <sstream>
#include <iostream>
#include <ctime>

int rows = 17; //y values
int cols = 50; //x values

int level1[17][50] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,7,1,1,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,1,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,1,8,0,0,0,0,0,0,0,0,0,7,1,8,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,1,1,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,3,6,6,6,2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,3,6,6,6,6,6,2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
    {2,1,1,1,1,1,4,0,0,9,0,0,5,1,1,1,1,3,6,6,6,6,6,6,6,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
    {6,6,6,6,6,6,2,1,1,1,1,1,3,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
};

#include <ctime>
// Same as static in c, local to compilation unit
namespace
{
	const size_t NUM_SPIDER = 0;
	namespace
	{
		void glfw_err_cb(int error, const char* desc)
		{
			fprintf(stderr, "%d: %s", error, desc);
		}
	}
}


World::World()
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

	m_x_boundaries = {0.f, 2400.f};
	m_y_boundaries = {200.f, 700.f};

    return setTextures() && m_player.init(m_x_boundaries, m_y_boundaries) && m_platform.init() &&m_background.init() && m_ground.init() && /*init_enemies(m_screen_scale, fb_width, fb_height) &&*/ loadLevel(level1);
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
	
	auto spider_it = m_spiders.begin();
	while (spider_it != m_spiders.end())
	{
		if (m_player.is_alive() && m_player.collides_with(*spider_it))
		{
			if (m_player.kill_enemy) {
				spider_it = m_spiders.erase(spider_it);
				// Mix_PlayChannel(-1, m_salmon_eat_sound, 0);
				// ++m_points;
			}
			else if (!m_player.is_alive()) {
				//m_player.destroy();
				//Mix_PlayChannel(-1, m_salmon_dead_sound, 0);
				break;
			}
		}
		else
			++spider_it;
	}

	// check if player is on the ground
	m_player.update(elapsed_ms, m_platform);
	m_camera.update(m_player.get_position(), m_player.is_facing_forwards());

	m_ground.set_surface_y();
    m_player.land(m_ground, m_platform);

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
    for (auto& tile : m_tiles)
        tile.draw(projection_2D);
	for (auto& spider : m_spiders)
		spider.draw(projection_2D);
    m_platform.draw(projection_2D);
    m_player.draw(projection_2D);

	//////////////////
	// Presenting
	glfwSwapBuffers(m_window);
}

// Should the game be over ?
bool World::is_over() const
{
	return glfwWindowShouldClose(m_window);
}

bool World::loadLevel(int arr[17][50])
{
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            map[row][col] = arr[row][col];
        }
    }
    drawMap();
    return true;
}

bool World::drawMap()
{
    int type = 0;
    
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            type = map[row][col];
            if (type == 1) {
                Tile tile;
                tile.texture = &tile1_texture;
                if (tile.init()) {
                    tile.setPosition(col, row);
                    m_tiles.emplace_back(tile);
                }
            }
            else if (type == 2) {
                Tile tile;
                tile.texture = &tile1_left_texture;
                if (tile.init()) {
                    tile.setPosition(col, row);
                    m_tiles.emplace_back(tile);
                }
            }
            else if (type == 3) {
                Tile tile;
                tile.texture = &tile1_right_texture;
                if (tile.init()) {
                    tile.setPosition(col, row);
                    m_tiles.emplace_back(tile);
                }
            }
            else if (type == 4) {
                Tile tile;
                tile.texture = &tile1_left_corner_texture;
                if (tile.init()) {
                    tile.setPosition(col, row);
                    m_tiles.emplace_back(tile);
                }
            }
            else if (type == 5) {
                Tile tile;
                tile.texture = &tile1_right_corner_texture;
                if (tile.init()) {
                    tile.setPosition(col, row);
                    m_tiles.emplace_back(tile);
                }
            }
            else if (type == 6) {
                Tile tile;
                tile.texture = &tile2_texture;
                if (tile.init()) {
                    tile.setPosition(col, row);
                    m_tiles.emplace_back(tile);
                }
            }
            else if (type == 7) {
                Tile tile;
                tile.texture = &tile1_left_end_texture;
                if (tile.init()) {
                    tile.setPosition(col, row);
                    m_tiles.emplace_back(tile);
                }
            }
            else if (type == 8) {
                Tile tile;
                tile.texture = &tile1_right_end_texture;
                if (tile.init()) {
                    tile.setPosition(col, row);
                    m_tiles.emplace_back(tile);
                }
            }
            else if (type == 9) {
                init_enemies(col, row);
            }
        }
    }
    return true;
}

bool World::init_enemies(int x, int y)
{
    srand( time(0));
    
    int min_waitTime = 5;
    int max_waitTime = 10;
    int randomTime;
    
    Spider spider;
    spider.texture = &spider_texture;
    if (spider.init()) {
        srand( time(0));
        //TODO fix these hard coded values, but 24 pixels is half a tile, a tile is 48x48
        spider.set_init_position_and_max_xy({x*48.f - 24.f, y*48.f+24.f});
        randomTime = (rand()%(max_waitTime - min_waitTime + 1) + min_waitTime);
        spider.set_randomT();
        m_spiders.emplace_back(spider);
    }
    else {
        fprintf(stderr, "Failed to initialize spider");
        return false;
    }
    return true;
}

//assigns all tile variables a texture
bool World::setTextures()
{
    if (!tile1_texture.is_valid())
    {
        if (!tile1_texture.load_from_file(textures_path("tile1.png")))
        {
            fprintf(stderr, "Failed to load tile texture!");
            return false;
        }
    }
    if (!tile1_left_texture.is_valid())
    {
        if (!tile1_left_texture.load_from_file(textures_path("tile1_left.png")))
        {
            fprintf(stderr, "Failed to load tile texture!");
            return false;
        }
    }
    if (!tile1_right_texture.is_valid())
    {
        if (!tile1_right_texture.load_from_file(textures_path("tile1_right.png")))
        {
            fprintf(stderr, "Failed to load tile texture!");
            return false;
        }
    }
    if (!tile1_left_corner_texture.is_valid())
    {
        if (!tile1_left_corner_texture.load_from_file(textures_path("tile1_left_corner.png")))
        {
            fprintf(stderr, "Failed to load tile texture!");
            return false;
        }
    }
    if (!tile1_right_corner_texture.is_valid())
    {
        if (!tile1_right_corner_texture.load_from_file(textures_path("tile1_right_corner.png")))
        {
            fprintf(stderr, "Failed to load tile texture!");
            return false;
        }
    }
    if (!tile2_texture.is_valid())
    {
        if (!tile2_texture.load_from_file(textures_path("tile2.png")))
        {
            fprintf(stderr, "Failed to load tile texture!");
            return false;
        }
    }
    if (!tile1_left_end_texture.is_valid())
    {
        if (!tile1_left_end_texture.load_from_file(textures_path("tile1_left_end.png")))
        {
            fprintf(stderr, "Failed to load tile texture!");
            return false;
        }
    }
    if (!tile1_right_end_texture.is_valid())
    {
        if (!tile1_right_end_texture.load_from_file(textures_path("tile1_right_end.png")))
        {
            fprintf(stderr, "Failed to load tile texture!");
            return false;
        }
    }
    if (!spider_texture.is_valid())
    {
        if (!spider_texture.load_from_file(textures_path("spider.png")))
        {
            fprintf(stderr, "Failed to load spider texture!");
            return false;
        }
    }
    return true;
}

// On key callback
void World::on_key(GLFWwindow* window, int key, int, int action, int mod)
{
    if (m_player.can_jump() && (key == GLFW_KEY_UP || key == GLFW_KEY_W)) {
        if (action == GLFW_PRESS) {
            m_player.jump();
        }
    } 
	if (m_player.can_airdash() && (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT)) {
		if (action == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_LEFT) || glfwGetKey(window, GLFW_KEY_A))
				m_player.air_dash(false);
			else
				m_player.air_dash(true);
		}
	} 
	
	if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A) {
        if (action == GLFW_PRESS && !m_player.is_airdashing()) {
            m_player.walk(false);
        } else if (action == GLFW_RELEASE && !m_player.is_airdashing()) {
            m_player.stop();
        }
    } 
	
	if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) {
        if (action == GLFW_PRESS && !m_player.is_airdashing()) {
            m_player.walk(true);
        } else if (action == GLFW_RELEASE && !m_player.is_airdashing()) {
            m_player.stop();
        }
    } 
}

void World::on_mouse_move(GLFWwindow* window, double xpos, double ypos)
{

}
