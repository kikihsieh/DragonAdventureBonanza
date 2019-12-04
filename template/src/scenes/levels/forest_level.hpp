#ifndef DAB_FOREST_LEVEL_HPP
#define DAB_FOREST_LEVEL_HPP

#include "level.hpp"
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_mixer.h>

class ForestLevel: public Level {
public:
	explicit ForestLevel();

    const char * get_bg_texture_path() override {
        return textures_path("forest/background.png");
    }
    
    bool use_vertical_camera() override {
        return true;
    }

    bool init() override;
    bool init_player() override;
    void init_walking_enemy(std::shared_ptr<Texture> texture, vec2 pos) override;
    void init_throwing_enemy(std::shared_ptr<Texture> texture, vec2 pos) override;

private:
    const MapVector get_map() const override {
        return m_tile_vec;
    }

    const TexturePathMapping get_mapping() const override {
        return m_texture_map;
    }

    const TilePropertyMapping get_property_map() const override {
        return m_property_map;
    }
    
    const MapVector m_tile_vec = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 14, 9, 9, 9, 15, 1, 1, 1, 1, 14, 9, 9, 9, 9, 15, 1, 14, 9, 9, 9, 9, 9, 9, 15, 1, 14, 9, 9, 9, 15, 1, 1, 1, 1, 1, 14, 9, 9, 15, 1, 1, 14, 9, 9, 9, 9, 15, 1, 1, 1, 14, 9, 9, 9, 9, 9, 9, 15, 1, 1, 1, 1, 14, 9, 9, 9, 9, 9, 9, 15, 1, 1, 1, 1, 14, 9, 9, 9, 9, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 14, 9, 9, 9, 9, 9, 9, 9, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 14, 9, 9, 9, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 14, 9, 9, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 14, 9, 9, 9, 9, 9, 9, 9, 15, 1, 14, 9, 15, 1, 14, 9, 15, 14, 9, 9, 9, 9, 9, 15, 1, 1, 1, 1, 1, 1, 1, 14, 9, 9, 9, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 14, 9, 9, 9, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 14, 9, 9, 9, 9, 15, 1, 1, 1, 1, 1, 1, 1, 14, 9, 9, 9, 9, 15, 1, 14, 9, 9, 15},
        {1, 1, 1, 14, 11, 10, 15, 1, 1, 1, 1, 1, 1, 1, 14, 11, 0, 0, 0, 10, 9, 15, 14, 9, 11, 0, 0, 0, 0, 10, 15, 16, 7, 0, 0, 0, 0, 6, 17, 14, 11, 0, 0, 0, 10, 15, 1, 1, 1, 14, 11, 0, 0, 10, 15, 14, 11, 0, 0, 0, 0, 10, 15, 1, 14, 11, 0, 0, 0, 0, 0, 0, 10, 15, 1, 1, 14, 11, 0, 0, 0, 0, 0, 0, 10, 15, 1, 1, 14, 11, 0, 0, 0, 0, 10, 9, 9, 9, 9, 15, 1, 1, 1, 1, 1, 1, 14, 9, 15, 1, 1, 14, 9, 15, 16, 7, 0, 0, 0, 0, 0, 6, 17, 1, 1, 1, 1, 1, 1, 1, 1, 1, 14, 11, 0, 0, 0, 10, 9, 9, 9, 9, 9, 9, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 14, 9, 9, 9, 9, 9, 9, 9, 15, 1, 1, 1, 1, 1, 1, 1, 1, 14, 11, 0, 0, 10, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 14, 9, 11, 0, 0, 0, 0, 0, 0, 0, 10, 9, 11, 0, 10, 9, 11, 0, 13, 12, 0, 0, 0, 0, 0, 10, 9, 9, 9, 15, 1, 1, 14, 11, 0, 0, 0, 10, 15, 1, 1, 1, 1, 1, 1, 1, 1, 14, 11, 0, 0, 0, 10, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 14, 11, 0, 0, 0, 0, 10, 15, 1, 1, 1, 1, 1, 14, 11, 0, 0, 0, 0, 10, 9, 11, 0, 0, 13},
        {1, 1, 1, 12, 0, 0, 10, 15, 1, 1, 1, 1, 1, 14, 11, 0, 0, 0, 0, 0, 0, 10, 11, 0, 0, 0, 0, 0, 0, 0, 10, 15, 16, 7, -1, 0, 6, 17, 14, 11, 0, 0, 0, 0, 0, 10, 9, 9, 9, 11, 0, 0, 0, 0, 10, 11, 0, 0, 0, 0, 0, 0, 10, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 10, 15, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 1, 1, 14, 9, 11, 0, 13, 1, 1, 12, 0, 10, 15, 16, 7, 0, -2, 0, 6, 17, 14, 9, 11, 10, 15, 1, 1, 1, 1, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 9, 9, 15, 1, 14, 9, 9, 9, 9, 9, 15, 1, 14, 11, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 1, 1, 1, 1, 14, 9, 11, 0, 0, 0, 0, 10, 9, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 14, 9, 9, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 11, 0, 0, 0, 0, 0, 10, 9, 15, 14, 9, 9, 15, 1, 14, 11, 0, 0, 0, 0, 0, 10, 15, 1, 1, 1, 1, 1, 14, 9, 9, 15, 1, 1, 1, 14, 9, 15, 1, 1, 1, 14, 9, 9, 11, 0, 0, 0, -2, 0, 0, 10, 9, 9, 15, 1, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13},
        {1, 1, 14, 11, 0, 0, 0, 10, 15, 1, 1, 1, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 15, 16, 8, 8, 17, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 11, 0, 0, 0, 13, 1, 1, 12, 0, 0, 10, 15, 16, 8, 8, 8, 17, 14, 11, 0, 0, 0, 10, 15, 1, 1, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 15, 12, 0, 0, 0, 0, 0, 13, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 1, 1, 1, 1, 1, 14, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 15, 14, 9, 11, 0, 0, 10, 15, 1, 14, 11, 0, 10, 15, 1, 14, 11, 0, 0, 6, 8, 8, 8, 8, 8, 8, 7, 0, 0, 10, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13},
        {1, 1, 12, 0, 0, 0, 0, 0, 10, 9, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 15, 1, 1, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 12, 0, 0, 0, 10, 9, 15, 1, 14, 9, 11, 0, 0, 0, 0, 0, 10, 15, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 15, 7, 0, 0, 0, 6, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 1, 14, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 10, 9, 11, 0, 0, 0, 10, 9, 11, 0, 0, 0, 10, 9, 9, 9, 9, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13},
        {1, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 15, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 12, 0, 0, 0, 0, 0, 10, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 15, 7, 0, 6, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 13, 1, 12, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13},
        {14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 14, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 15, 8, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 17, 1, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10},
        {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 6, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 17, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 14, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 9, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0, 0, G},
        {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 13, 1, 12, 0, 0, 0, 10, 9, 15, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 17, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 15, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, -2, 13, 12, 0, 0, 0, 0, 0, 0, G},
        {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 17, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 10, 9, 15, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 17, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 8, 17, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 6, 8, 8, 7, 0, 0, 0, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 6, 8, 8, 7, 0, 0, 0, 6, 8, 17, 12, 0, 0, 0, 0, 0, 0, G},
        {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 8, 8, 8, 17, 1, 1, 12, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 6, 8, 8, 17, 12, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 15, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 17, 1, 1, 1, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 5, 0, 0, 0, 10, 15, 14, 11, 0, 0, 0, 0, 6, 8, 8, 7, 0, 0, 0, 0, 0, 10, 15, 14, 11, 0, 0, 0, 10, 9, 15, 16, 8, 8, 8, 8, 8, 8, 8},
        {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0, 10, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 1, 1, 1, 1, 1, 16, 8, 8, 8, 8, 8, 8, 7, 0, 0, 0, 0, 18, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 7, 0, 0, 0, 0, 0, 0, 0, 6, 8, 7, 0, 0, 0, 0, 0, 0, 0, 6, 8, 7, 0, 0, 0, 10, 15, 1, 1, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 5, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 1, 1, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11, 0, 0, 0, 0, 0, 10, 9, 9, 11, 0, 0, 0, 0, 0, 0, 10, 11, 0, 0, 0, 0, 0, 0, 10, 9, 9, 9, 9, 9, 9, 9, 15},
        {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 17, 1, 12, 0, 0, 0, 6, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 8, 8, 8, 8, 17, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 12, 0, 0, 0, 6, 8, 8, 17, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, -1, 0, 0, 0, 0, 5, 5, 5, 0, 0, -1, 0, 10, 9, 11, 0, -1, 0, 0, 0, -2, 0, 10, 9, 11, 0, -2, 0, 0, 0, -1, 0, 10, 9, 11, 0, -1, 0, 0, 13, 1, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 8, 7, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 6, 8, 17, 1, 1, 1, 1, 1, 1, 1, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 16, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13},
        {12, 0, 0, 0, 0, 0, 0, 0, 6, 8, 17, 14, 9, 9, 9, 15, 1, 14, 9, 9, 9, 9, 9, 9, 15, 1, 1, 14, 9, 9, 9, 9, 9, 9, 15, 1, 14, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 0, 0, 0, 10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 15, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 1, 1, 1, 1, 1, 1, 14, 9, 9, 9, 9, 9, 15, 1, 1, 1, 1, 1, 12, 0, 0, 0, 10, 15, 1, 1, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 7, 0, 0, 0, 6, 8, 7, 0, 6, 8, 7, 0, 0, 0, 6, 8, 7, 0, 6, 8, 7, 0, 0, 0, 6, 8, 7, 0, 13, 1, 1, 1, 14, 11, 0, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 0, 0, 10, 15, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 15, 14, 11, 0, 0, 0, 0, -2, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13},
        {12, 0, 5, 0, 0, 0, 0, 0, 10, 9, 9, 11, 0, 0, 0, 10, 9, 11, 0, 0, 0, 0, 0, 0, 10, 9, 9, 11, 0, 0, 0, 0, 0, 0, 10, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 16, 8, 7, 0, 0, 0, -2, 0, 0, 0, 0, 6, 8, 8, 8, 8, 17, 1, 1, 1, 1, 1, 1, 1, 1, 16, 7, 0, -1, 0, 6, 17, 1, 1, 1, 1, 1, 12, 0, 0, 0, 0, 13, 1, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 14, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 11, 0, 0, 0, 10, 9, 11, 0, 10, 9, 11, 0, 0, 0, 10, 9, 11, 0, 10, 9, 11, 0, 0, 0, 10, 9, 11, 0, 13, 1, 1, 1, 12, 0, 0, 13, 12, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 13, 12, 0, 0, 0, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11, 0, 0, 0, 0, 6, 8, 8, 17, 12, 0, 0, 0, 0, 0, 6, 8, 17, 1, 14, 9, 9, 9, 9, 9, 9, 9, 15, 1, 16, 8, 7, 0, 0, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13},
        {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 11, 0, 5, 0, 6, 8, 8, 7, 0, 10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 15, 16, 8, 8, 8, 17, 14, 9, 9, 9, 9, 9, 11, 5, 0, 0, 0, 13, 1, 1, 1, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 13, 12, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 14, 11, 0, 0, 13, 16, 7, 0, -2, 0, -2, 0, -2, 0, -2, 0, 6, 17, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 15, 1, 1, 12, 5, 0, 0, 0, 0, 13, 1, 1, 1, 16, 7, 0, 0, 0, 0, 0, 6, 17, 1, 1, 1, 12, 0, 0, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 1, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13},
        {16, 8, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 1, 14, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 17, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 12, 0, 0, 0, 13, 1, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 17, 1, 12, 0, -1, -1, 0, -1, -1, 0, 0, -1, 0, -1, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 12, 0, 0, 0, 0, 0, 13, 1, 14, 9, 15, 16, 7, 0, -2, 0, 6, 17, 14, 9, 15, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 1, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13},
        {1, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 6, 8, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 13, 1, 1, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 12, 0, -1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 16, 8, 8, 8, 17, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 0, 0, 0, 0, 6, 8, 17, 1, 1, 12, 0, 0, 0, 0, 5, 13, 1, 12, 0, 10, 15, 16, 8, 8, 8, 17, 14, 11, 0, 13, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 1, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13},
        {1, 1, 1, 1, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 17, 14, 9, 9, 11, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 0, 0, 0, 0, 0, 0, 13, 14, 9, 9, 15, 14, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 5, 0, 0, 0, 13, 14, 9, 9, 9, 11, 0, 0, 0, 0, 0, 13, 1, 12, 0, 0, 10, 9, 15, 1, 14, 9, 11, 0, 0, 13, 1, 12, 0, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 1, 12, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13},
        {14, 9, 9, 9, 9, 9, 15, 14, 9, 9, 9, 9, 9, 15, 14, 9, 9, 9, 9, 9, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 14, 9, 9, 9, 9, 9, 9, 9, 9, 9, 15, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 14, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 14, 9, 9, 9, 9, 9, 9, 15, 1, 16, 8, 7, 0, 0, 0, 0, 13, 12, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 5, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 10, 9, 11, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 16, 8, 8, 8, 8, 7, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13},
        {12, 0, 0, 0, 0, 0, 10, 11, 0, 0, 0, 0, 0, 10, 11, 0, 0, 0, 0, 0, 10, 9, 9, 15, 1, 1, 1, 1, 1, 1, 1, 1, 14, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 13, 14, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 13, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 14, 9, 11, 0, 0, 0, 0, 0, 0, 10, 9, 9, 9, 11, 0, 0, 0, 0, 13, 12, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 9, 9, 9, 15, 16, 8, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13},
        {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 15, 1, 1, 14, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 17, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 1, 1, 1, 1, 1, 14, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 13, 12, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 5, 13, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13},
        {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 16, 8, 8, 7, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 17, 12, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 1, 14, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 13, 12, -2, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 1, 12, 0, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 9, 9, 11, 0, 0, 0, 5, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13},
        {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 14, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 12, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 13, 12, 0, 0, 13, 16, 8, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 1, 12, 0, 0, 0, 0, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 8, 8, 7, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 13},
        {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 5, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 5, 0, 0, 10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 10, 9, 9, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 6, 8, 8, 8, 8, 17, 16, 8, 8, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 1, 16, 8, 8, 8, 8, 7, 0, 0, 0, 0, 0, 0, 13},
        {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 8, 17, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 6, 8, 7, 0, 0, 0, 0, 0, 6, 8, 7, 0, 0, 0, 0, 0, 0, 10, 9, 9, 15, 1, 1, 1, 1, 14, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 9, 9, 9, 9, 9, 9, 11, 0, 0, 0, 0, 0, -1, 13},
        {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 17, 1, 16, 7, 0, 0, 0, 0, 0, 0, 0, 13, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 11, 0, 0, 0, 0, 0, 10, 9, 11, 0, 0, 0, 5, 0, 0, 0, 0, 0, 10, 9, 15, 14, 9, 11, 0, 0, 0, 0, 0, 0, 0, 6, 8, 8, 8, 8, 8, 7, 0, 0, 0, 0, 0, 5, 0, 13, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 17},
        {12, 0, 0, 0, 0, 0, 0, 0, 6, 8, 8, 8, 8, 7, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 6, 8, 8, 8, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 17, 1, 1, 1, 16, 7, 0, 0, 0, 0, 0, 0, 13, 14, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 7, 0, 0, 0, 6, 8, 8, 8, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 8, 8, 8, 8, 7, 0, 0, 0, 13, 12, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 9, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 1},
        {12, 0, P, 0, 0, 0, 6, 8, 17, 1, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 6, 8, 7, 0, 0, 0, 0, 0, 10, 9, 15, 1, 14, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 10, 9, 9, 9, 9, 9, 11, 0, 0, 0, 0, -2, 0, 13, 12, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 10, 9, 11, 0, 0, 0, 10, 9, 15, 1, 14, 9, 11, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 10, 9, 15, 1, 14, 9, 11, 0, 0, 0, 13, 12, 0, 6, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 0, 13, 1, 1, 1, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 6, 8, 8, 17, 1, 1},
        {12, 0, 0, 0, 6, 8, 17, 1, 1, 1, 14, 9, 9, 11, 0, 0, 0, 0, 0, 0, 10, 9, 11, 0, 0, 0, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 6, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 17, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 0, 0, 6, 8, 8, 7, 0, 0, 0, 0, 0, -2, -2, 0, 0, 0, 0, 0, 6, 8, 8, 7, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 13, 12, 0, 10, 9, 15, 16, 8, 7, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 13, 1, 1, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 13, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 8, 17, 1, 1, 1, 1, 1},
        {16, 8, 8, 8, 17, 1, 1, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0, 0, 6, 7, 0, 0, 0, 6, 17, 1, 16, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 17, 16, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 0, 0, 10, 15, 14, 11, 0, 0, 0, 0, 6, 8, 8, 7, 0, 0, 0, 0, 10, 15, 14, 11, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 10, 9, 15, 16, 8, 7, 0, 0, 6, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 17, 12, 0, 13, 1, 1, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 6, 17, 16, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 6, 8, 8, 8, 8, 17, 1, 12, 0, 0, 0, -1, 0, 0, 0, 6, 8, 8, 8, 17, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 14, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 0, 6, 17, 16, 8, 8, 8, 8, 8, 8, 17, 16, 8, 8, 8, 17, 1, 1, 1, 16, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 7, 0, 0, 0, 0, 0, 0, 6, 17, 16, 7, 0, 0, 0, 0, 0, 6, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 6, 17, 1, 1, 16, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11, 0, 0, 0, 0, 0, 10, 9, 9, 11, 0, 0, 0, 0, 0, 10, 11, 0, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 10, 9, 9, 11, 0, 0, 10, 9, 15, 16, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0, 6, 8, 7, 0, 0, 0, 0, 0, 0, 6, 17, 16, 7, 0, 0, 0, 0, 0, 6, 8, 7, 0, 0, 0, 0, 13, 1, 1, 12, 0, 13, 1, 1, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 6, 17, 1, 1, 16, 7, 0, 0, 0, 0, 0, 0, 6, 8, 8, 8, 8, 8, 8, 8, 17, 1, 1, 1, 1, 1, 1, 16, 8, 8, 8, 8, 8, 8, 8, 17, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 0, 10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 17, 1, 16, 8, 8, 8, 8, 8, 8, 17, 1, 1, 16, 8, 8, 8, 8, 8, 17, 1, 16, 8, 8, 8, 8, 8, 8, 8, 8, 17, 1, 1, 1, 1, 16, 7, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 1, 12, 0, 0, 0, 0, 0, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 15, 16, 8, 7, 0, 0, 0, 6, 7, 0, 0, 0, 10, 11, 0, 0, 0, 6, 8, 17, 1, 16, 8, 8, 8, 8, 8, 8, 17, 1, 1, 16, 8, 8, 8, 8, 8, 17, 1, 16, 8, 8, 8, 8, 17, 1, 1, 12, 0, 13, 1, 1, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 6, 17, 1, 1, 1, 1, 16, 7, 0, 0, 0, 0, 0, 10, 15, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 14},
        {1, 1, 1, 1, 1, 1, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 11, 0, 0, 0, 0, 0, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 11, 0, 0, 0, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 0, 10, 1, 1, 1, 1, 1, 16, 8, 7, 0, 0, 0, 0, 10, 9, 9, 9, 9, 9, 9, 11, 0, 0, 0, 0, 0, 0, 10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11}
    };

    const TexturePathMapping m_texture_map = {
        {-7, textures_path("fire.png")},
        {-6, textures_path("forest/projectiles/ice.png")},
        {-5, textures_path("bat/bat_spritesheet1.png")},
        {-4, textures_path("bat/bat_spritesheet1.png")},
        {-3, textures_path("bat/bat_spritesheet1.png")},
        {-2, textures_path("forest/enemies/glob.png")},
        {-1, textures_path("forest/enemies/spider.png")},
        {1,  textures_path("forest/tiles2/tile_c_m.png")},
        {5,  textures_path("forest/tiles2/tile.png")},
        {6,  textures_path("forest/tiles2/tile_t_l.png")},
        {7,  textures_path("forest/tiles2/tile_t_r.png")},
        {8,  textures_path("forest/tiles2/tile_t_m.png")},
        {9,  textures_path("forest/tiles2/tile_e_m.png")},
        {10, textures_path("forest/tiles2/tile_e_l.png")},
        {11, textures_path("forest/tiles2/tile_e_r.png")},
        {12, textures_path("forest/tiles2/tile_s_r.png")},
        {13, textures_path("forest/tiles2/tile_s_l.png")},
        {14, textures_path("forest/tiles2/tile_i_r.png")},
        {15, textures_path("forest/tiles2/tile_i_l.png")},
        {16, textures_path("forest/tiles2/tile_m_r.png")},
        {17, textures_path("forest/tiles2/tile_m_l.png")},
        {18, textures_path("heart.png")}
    };

    const TilePropertyMapping m_property_map = {
        {18, std::make_shared<Properties>(Properties::Type::HEALTH)}
    };
};

#endif //DAB_FOREST_LEVEL_HPP
