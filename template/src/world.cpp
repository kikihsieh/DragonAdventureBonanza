// Header
#include "world.hpp"

// stlib
#include <sstream>

#include <scenes/levels/forest_level.hpp>
#include <scenes/levels/snow_mountain_level.hpp>
#include <scenes/start_menu.hpp>
#include <scenes/help_menu.hpp>
#include <iostream>


// Same as static in c, local to compilation unit
namespace
{
	namespace
	{
		void glfw_err_cb(int error, const char* desc)
		{
			fprintf(stderr, "%d: %s", error, desc);
		}
	}
}


World::World() {
    map_init(m_scenes)
            ("FOREST", new ForestLevel(true))
            ("SNOW_MOUNTAIN", new SnowMountainLeve(true))
			("MAIN_MENU", new StartMenu())
			("HELP", new HelpMenu());
}

World::~World() {}

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
	auto mouse_button_redirect = [](GLFWwindow* wnd,int _0, int _1, int _2) { ((World*)glfwGetWindowUserPointer(wnd))->on_mouse_click(wnd, _0, _1, _2); };
	glfwSetKeyCallback(m_window, key_redirect);
	glfwSetCursorPosCallback(m_window, cursor_pos_redirect);
	glfwSetMouseButtonCallback(m_window, mouse_button_redirect);

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

    m_save_path = "save.txt";

    //TODO: temporary settings, change to number of levels once determine
    int l = load();
    if (l < 0) {
        m_unlocked_levels.insert(std::pair<std::string, bool>("FOREST", true));
        m_unlocked_levels.insert(std::pair<std::string, bool>("CAVE", false));
        m_unlocked_levels.insert(std::pair<std::string, bool>("SNOW_MOUNTAIN", false));
        m_unlocked_levels.insert(std::pair<std::string, bool>("NIGHT_SKY", false));
        std::cout << "No existing save file" << std::endl;
    } else
        std::cout << "Loaded save!" << std::endl;

	return load_scene(m_scenes.at("MAIN_MENU"));
}

// Releases all the associated resources
void World::destroy() {
	glDeleteFramebuffers(1, &m_frame_buffer);
	glfwDestroyWindow(m_window);
    for (auto const &pair : m_scenes)
    {
        pair.second->destroy();
        delete pair.second;
    }
}

// Update our game world
bool World::update(float elapsed_ms)
{
    int w, h;
    glfwGetFramebufferSize(m_window, &w, &h);

    m_current_scene->update(elapsed_ms, {w / m_screen_scale, h / m_screen_scale});
  	return true;
}

// Render our game world
// http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/
void World::draw() {
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
	vec2 screen_size = {(right - left) , (bottom - top)};
	float tx = m_current_scene->get_translation_x(screen_size);
	float ty = m_current_scene->get_translation_y(screen_size);
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

    m_current_scene->draw(projection_2D);

	//////////////////
	// Presenting
	glfwSwapBuffers(m_window);
}

// Should the game be over ?
bool World::is_over() const {
	return glfwWindowShouldClose(m_window);
}

bool World::load_scene(Scene* scene) {
    if (m_current_scene) {
        m_current_scene->destroy();
    }

    m_current_scene = scene;
    m_current_scene->init();
	return true;
}

// On key callback
void World::on_key(GLFWwindow* window, int key, int, int action, int mod) {
    if (key == GLFW_KEY_1 && action == GLFW_RELEASE) {
        if (m_unlocked_levels["FOREST"])
            load_scene(m_scenes.at("FOREST"));
        return;
    }

    if (key == GLFW_KEY_2 && action == GLFW_RELEASE) {
        if (m_unlocked_levels["SNOW_MOUNTAIN"])
            load_scene(m_scenes.at("SNOW_MOUNTAIN"));
        return;
    }

	if (key == GLFW_KEY_H && action == GLFW_RELEASE) {
		m_current_scene->drawHelp = !m_current_scene->drawHelp;
		m_current_scene->paused = !m_current_scene->paused;
		return;
	}
	if (key == GLFW_KEY_P && action == GLFW_RELEASE) {
		if (!m_current_scene->drawHelp)
			m_current_scene->paused = !m_current_scene->paused;
		return;
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
		load_scene(m_scenes.at("MAIN_MENU"));
		return;
	}

    if (key == GLFW_KEY_O && action == GLFW_RELEASE) {
        int s = save();
        if (s < 0)
            std::cout << "Error saving game" << std::endl;
        else
            std::cout << "Saved game!" << std::endl;
        return;
    }
    m_current_scene->on_key(key, action);
}

void World::on_mouse_click(GLFWwindow* window, int key, int action, int mod) {
	double xposition, yposition;
    glfwGetCursorPos(window, &xposition, &yposition);
	Button* b = m_current_scene->on_mouse(key,action, xposition, yposition);
	if (b != nullptr) {
		Button btn = *b;
		if (btn.function == "level")
			load_scene(m_scenes.at(btn.scenes[btn.scene_index]));
		else if (btn.function == "close")
            glfwSetWindowShouldClose(m_window, true);
	}
}

void World::on_mouse_move(GLFWwindow* window, double xpos, double ypos)
{
	
}


int World::save() {
    int count = 0;
    if (m_unlocked_levels.empty())
        return -1;

    FILE *fp = fopen(m_save_path.c_str(), "w");
    if (!fp)
        return -errno;

    for(auto & it : m_unlocked_levels) {
        fprintf(fp, "%s=%s\n", it.first.c_str(), std::to_string(it.second).c_str());
        count++;
    }

    fclose(fp);
    return count;
}


int World::load() {
    int count = 0;

    FILE *fp = fopen(m_save_path.c_str(), "r");
    if (!fp)
        return -errno;

    m_unlocked_levels.clear();

    std::ifstream save;
    save.open(m_save_path);
    std::string s;
    if (save.is_open()) {
        while (!save.eof()) {

            getline(save, s);
            s += "\n";

            int n = s.length();
            char char_array[n + 1];
            strcpy(char_array, s.c_str());

            char *nl = strchr(char_array, '\n');
            if (nl == NULL)
                continue;
            *nl = 0;

            char *sep = strchr(char_array, '=');
            if (sep == NULL)
                continue;
            *sep = 0;
            sep++;


            std::string s1 = (const char *) char_array;
            bool s2 = *sep == '1';

            (m_unlocked_levels)[s1] = s2;
            count++;
        }
    }

    fclose(fp);
    return count;
}
