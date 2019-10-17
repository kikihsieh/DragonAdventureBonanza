#include "background.hpp"

Background::Background()  {
    scale = {1.f, 1.f};
    radians = 0.f;
    drawable = new Drawable();
    drawable->fs_shader = shader_path("background.fs.glsl");
    drawable->vs_shader = shader_path("background.vs.glsl");
}

Background::~Background() {}

bool Background::init(const char* path) {
    drawable->texture_path = path;
 	scale = { 1.f, 1.f };
 	return true;
 }

 void Background::destroy() {

 }
