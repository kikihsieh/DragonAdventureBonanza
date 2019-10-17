#include "background.hpp"

Background::Background() : background_texture(new Texture()) {
    scale = {1.f, 1.f};
    radians = 0.f;
    Drawable* d = new Drawable();
    d->fs_shader = shader_path("background.fs.glsl");
    d->vs_shader = shader_path("background.vs.glsl");
    drawable = d;
}

Background::~Background() {
    // TODO: !!!!! FREE MEMORY
     delete background_texture;
}

bool Background::init(const char* path) {
    drawable->texture_path = path;
 	scale = { 1.f, 1.f };
 	return true;
 }

 void Background::destroy() {
     delete background_texture;
     background_texture = nullptr;
 }
