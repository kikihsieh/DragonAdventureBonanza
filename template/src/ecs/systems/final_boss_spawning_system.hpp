//
// Created by Austin Kobayashi on 2019-11-18.
//

#ifndef DAB_FINAL_BOSS_SPAWNING_SYSTEM_HPP
#define DAB_FINAL_BOSS_SPAWNING_SYSTEM_HPP

#include <ecs/entities/entity.hpp>
#include <list>

class FinalBossSpawningSystem {
public:

    bool init(std::list<Entity> *entities, vec2 screen_bounds);

    bool spawn_final_boss();
    void spawn_cloud(int texture, vec2 position);
    void spawn_bomb(vec2 position);
    void explode_bomb(vec2 position);

private:

    bool init_entity(Entity& entity);
    bool load_from_file(Drawable::Effect& effect, const char* vs_path, const char* fs_path);
    void release(Drawable::Effect& effect);
    void destroy_entity(Entity& entity);

    std::map<const char*, Drawable::Effect> m_effects;

    vec2 m_screen_bounds;

    std::list<Entity>* m_entities;

    TextureMapping m_texture_mapping;
    const TexturePathMapping m_texture_map = {
            { 1, textures_path("night_sky/cloud1.png")},
            { 2, textures_path("night_sky/cloud2.png")},
            { 3, textures_path("night_sky/final_boss.png")},
            { 4, textures_path("night_sky/bomb.png")},
            { -7, textures_path("fire.png")}
    };
};

#endif //DAB_FINAL_BOSS_SPAWNING_SYSTEM_HPP
