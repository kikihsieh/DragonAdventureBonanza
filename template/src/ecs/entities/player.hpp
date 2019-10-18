#include "entity.hpp"

struct Player : public Entity {
    Player() {
        scale = {0.16f, 0.16f};
        position = { 100.f, 450.f };

        physics = new Physics();
        physics->gravity = 10.f;
        physics->walk_speed = 250.f;
        physics->jump_speed = -500.f;
        physics->velocity = { physics->walk_speed, 0.f };
        physics->acceleration = { 0.f, physics->gravity };

        drawable = new Drawable();
        drawable->texture_path = textures_path("player.png");
        drawable->fs_shader = shader_path("textured.fs.glsl");
        drawable->vs_shader = shader_path("textured.vs.glsl");

        collider = new Collider();
		input = new Input();
	}
};
