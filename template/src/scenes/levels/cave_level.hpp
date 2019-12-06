#ifndef DAB_CAVE_LEVEL_HPP
#define DAB_CAVE_LEVEL_HPP

#include "level.hpp"

class CaveLevel: public Level {
public:
    explicit CaveLevel();

    const char * get_bg_texture_path() override {
        return textures_path("cave/background.png");
    }
    bool use_vertical_camera() override {
        return true;
    }

    bool init() override;
    void draw(const mat3& projection) override;
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
        
        {24, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 21, 24, 3, 3, 3, 3, 3, 25, 23, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 21, 24, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 25, 23, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 25, 23, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        
        { 25, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 23, 21, 24, 3, 3, 25, 17, 17, 2, 17, 17, 23, 25, 17, 2, 2, 17, 17, 17, 17, 2, 17, 23, 25, 17, 23, 3, 3, 3, 17, 17, 17, 17, 23, 3, 25, 23, 3, 25, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 23, 21, 24, 3, 3, 25, 17, 17, 17, 17, 17, 17, 17, 17, 23, 21, 24, 25, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 25, 23},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 2, 23, 25, 17, 18, 0, 0, 0, 0, 39, 14, 1, 38, 0, 0, 0, 0, 0, 0, 0, 0, 22, 18, 0, 0, 23, 3, 25, 0, 0, 0, 0, 19, 23, 21, 24, 3, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 3, 3, 21, 0, 0, 0, 0, 0, 0, 0, 39, 14, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21, 24},
        
        { 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22, 26, 0, 0, 0, 0, 0, 0, 0, 22, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22, 3, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 3, 3, 25, 8, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3},
        
        { 1, 0, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22, 17, 23, 25, 23, 21, 0, 35, 0, -2, 0, 0, 0, 0, 22, 23, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 39, 23, 3},
        
        { 21, 20, 27, 20, 27, 27, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -5, 0, 0, 0, 0, 0, 0, 15, 27, 27, 20, 20, 20, 27, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 21, 24, 3, 27, 20, 27, 20, 16, 0, 0, 0, 0, 24, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 3},
        
        { 3, 3, 3, 3, 3, 3, 21, 27, 16, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 27, 20, 27, 24, 3, 21, 24, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22, 25, 17, 17, 17, 23, 25, 26, 0, 0, 0, 0, 23, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3},
        
        { 25, 17, 17, 17, 17, 17, 17, 17, 21, 20, 27, 20, 16, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 15, 20, 16, 0, 0, 0, 0, 0, 0, 14, 25, 23, 3, 3, 3, 3, 3, 3, 25, 23, 21, 20, 27, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4, 0, -2, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 23, 3},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 19, 17, 17, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 20, 27, 20, 20, 20, 16, 0, 0, 0, 0, 15, 20, 20, 27, 20, 27, 24, 3, 21, 20, 16, 0, 0, 0, 0, 14, 21, 24, 3, 3, 25, 23, 3, 3, 21, 24, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 20, 24, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 13, 28, 0, 0, 0, 0, 15, 27, 27, 16, 0, 0, 0, 0, 15, 27, 20, 27, 27, 20, 20, 24, 3},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 27, 20, 16, 0, 0, 0, 22, 23, 25, 23, 3, 3, 21, 16, 0, 0, 0, 14, 25, 23, 3, 3, 3, 3, 25, 23, 3, 21, 16, 0, 0, 0, 14, 3, 3, 3, 3, 21, 24, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 27, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 1, 0, 0, 0, 0, 14, 25, 23, 3, 3, 3, 3, 3, 3},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 27, 24, 25, 23, 1, 0, 0, 0, 0, 14, 21, 24, 3, 3, 3, 21, 20, 0, 0, 14, 21, 24, 3, 3, 3, 3, 21, 24, 3, 3, 1, 0, 0, 0, 22, 23, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 20, 3, 3, 25, 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 17, 23, 1, 0, 0, 0, 0, 14, 21, 24, 3, 3, 25, 23, 3, 3},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 20, 27, 24, 3, 3, 21, 24, 1, 0, 0, 0, 0, 19, 17, 17, 2, 23, 3, 3, 3, -2, 35, 14, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 18, 0, 0, 0, 0, 14, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, -1, 0, 0, 0, 0, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -5, 13, 28, 0, 0, 0, 15, 20, 20, 27, 27, 27, 20, 3, 3, 3, 21, 24, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4, 0, 0, 14, 1, 13, 28, 0, 0, 14, 3, 3, 3, 3, 21, 24, 3, 3},
        
        { 1, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 25, 23, 3, 3, 3, 3, 3, 21, 16, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 3, 20, 20, 24, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 14, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 21, 27, 20, 27, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 0, 0, 0, 0, 0, -4, 0, 0, 0, 0, 0, 0, 13, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 39, 14, 1, 0, 0, 0, 0, 19, 17, 17, 17, 17, 17, 17, 17, 17},
        
        { 21, 20, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 15, 20, 27, 27, 24, 21, 24, 3, 3, 3, 3, 25, 23, 3, 16, 0, 0, 0, 0, 0, 0, 14, 25, 23, 3, 3, 25, 23, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 13, 28, 0, 0, 0, 14, 3, 3, 3, 3, 3, 3, 25, 17, 17, 17, 23, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 25, 23, 21, 16, 0, 0, -3, 0, 0, 0, 0, 15, 27, 24, 3, 25, 23, 3, 3, 3, 25, 23, 3, 3, 21, 24, 3, 1, 0, -2, 35, 0, 0, 0, 14, 21, 24, 3, 3, 21, 24, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 14, 3, 25, 17, 17, 17, 17, 18, 0, 0, 0, 19, 17, 17, 17, 23, 3, 3, 27, 20, 27, 20, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 1, 0, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, G},
        
        { 21, 24, 3, 21, 16, 0, 0, 0, 0, 0, 15, 24, 3, 3, 3, 21, 24, 3, 3, 3, 21, 24, 3, 3, 3, 3, 3, 21, 20, 20, 16, 0, 0, 0, 19, 23, 3, 23, 25, 23, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 14, 3, 21, 8, 0, 0, 0, 0, 0, -4, 0, 0, 0, 0, 0, 14, 3, 25, 23, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 21, 27, 20, 20, 27, 20, 20, 27, 27, 27, 27, 27, 20, 20},
        
        { 3, 25, 23, 3, 21, 16, 0, 0, 0, 0, 19, 17, 2, 17, 2, 2, 2, 2, 17, 2, 2, 17, 17, 2, 17, 2, 2, 2, 17, 17, 18, 0, 0, 0, 0, 0, 0, 14, 21, 24, 3, 25, 17, 2, 2, 17, 17, 2, 17, 2, 17, 0, 0, 0, 0, 15, 24, 3, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 23, 21, 24, 3, 3, 3, 1, 38, 0, 0, 0, 0, 15, 20, 20, 20, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 28, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        
        { 3, 21, 24, 25, 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 3, 1, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 21, 0, -2, 0, 0, 15, 16, 0, 0, 0, 0, 0, 0, 39, 14, 3, 3, 3, 25, 23, 1, 0, 0, 0, 0, 0, 14, 3, 3, 25, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17},
        
        { 25, 23, 3, 21, 24, 21, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 14, 3, 3, 21, 20, 20, 27, 20, 24, 21, 20, 20, 16, 0, 0, 0, 0, 14, 25, 23, 3, 21, 24, 1, 0, 0, 0, 0, 0, 14, 25, 23, 21, 20, 27, 27, 20, 27, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 21, 24, 3, 3, 3, 3, 21, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 3, 1, -2, 0, 0, 0, 0, 0, 0, 15, 20, 20, 27, 20, 20, 24, 3, 3, 3, 3, 17, 17, 17, 17, 17, 2, 3, 1, 0, 0, 0, 0, 14, 21, 24, 3, 3, 3, 1, 0, 0, 0, 0, 0, 14, 21, 24, 3, 3, 3, 25, 23, 3, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 3, 17, 2, 17, 2, 17, 2, 18, 0, 0, 0, 13, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 3, 21, 20, 16, 0, 0, 0, 0, 0, 19, 17, 17, 2, 17, 17, 17, 17, 17, 2, 17, 0, 0, 0, 0, 0, 0, 22, 18, 0, 0, 0, 0, 14, 3, 3, 25, 23, 3, 1, 0, 0, 0, 0, 0, 14, 3, 3, 3, 3, 3, 21, 24, 3, 21, 20, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 2, 2, 23, 3, 3, 21, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 20, 24, 3, 3, 21, 24, 3, 21, 24, 0, 0, 0, 0, 22, 3, 3, 3, 25, 23, 3, 3, 3, 3, 3, 21, 20, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 23, 3, 3, 21, 16, 0, 0, 0, -2, 0, 0, -1, 0, 0, 0, -1, 0, 0, 0, 0, 0, 15, 16, 0, 0, 0, 0, 0, 0, 14, 25, 23, 3, 3, 3, 3, 25, 23, 3, 0, 0, 0, 0, 0, 19, 3, 3, 21, 24, 3, 3, 3, 3, 25, 23, 3, 21, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 3, 21, 20, 27, 20, 27, 27, 27, 27, 27, 20, 27, 27, 20, 27, 20, 27, 20, 24, 21, 0, 0, 0, 0, 0, 0, 14, 21, 24, 3, 3, 3, 3, 21, 24, 25, 0, 0, 0, 0, 0, 0, 22, 17, 17, 17, 17, 3, 3, 3, 21, 24, 3, 3, 25, 8, 0, 0, 0, 0, 0, 0, 0, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 38, 0, 0, -5, 0, 0, 0, 0, 15, 20, 20, 27, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 27, 27, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, -1, 0, 35, 15, 20, 24, 25, 23, 3, 25, 23, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 17, 17, 17, 17, 17, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 27, 24, 3, 25, 23, 21, 27, 20, 16, 0, 0, 0, -3, 0, 0, 15, 24, 3, 3, 21, 16, 0, 0, 0, 0, 0, 0, 0, 0, -4, 0, 0, 0, 14, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 20, 27, 20, 27, 3, 3, 3, 21, 24, 3, 21, 24, 3, 25, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 27, 20, 27, 20, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 23, 25, 23, 21, 24, 25, 23, 3, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 25, 23, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 17, 17, 17, 17, 17, 17, 17, 2, 17, 17, 2, 17, 17, 17, 17, 17, 17, 2, 17, 17, 17, 2, 2, 17, 2, 17, 17, 17, 17, 17, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 39, 14, 3, 3, 3, 3, 1, 0, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 0, 0, 27, 3, 21, 24, 3, 3, 21, 24, 3, 21, 27, 27, 0, 0, 0, 0, 23, 3, 3, 21, 24, 21, 27, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 17, 17, 17, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 17, 17, 17, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 0, 0, 23, 3, 25, 23, 3, 3, 3, 3, 25, 23, 3, 3, 0, 0, 0, 0, 19, 17, 3, 3, 3, 3, 3, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 27, 27, 20, 20, 27, 16, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 15, 27, 24, 3, 21, 24, 3, 3, 25, 23, 21, 24, 3, 25, 0, 0, 0, 0, 0, 0, 22, 3, 3, 3, 3, 25, 38, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 3, 3, 3, 3, 3, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35, -2, 0, 35, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 22, 2, 2, 17, 17, 2, 23, 3, 21, 24, 3, 3, 3, 21, 16, 0, 0, 0, 0, 0, 0, 19, 2, 3, 3, 1, 0, 0, 0, 0, 15, 27, 20, 27, 20, 27, 16, 0, 0, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 3, 3, 3, 3, 25, 0, 0, 0, 0, 0, 0, 0, 0, 15, 27, 20, 27, 16, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 17, 17, 2, 23, 3, 3, 3, 21, 27, 0, 0, 0, 0, 0, 0, 0, 22, 17, 18, 0, 0, 0, 0, 14, 3, 3, 25, 23, 3, 21, 27, 20, 27, 20, 20, 20, 27, 20, 27, 27, 27, 20, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 20, 20, 27, 0, 0, 0, 0, 15, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 17, 17, 17, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 24, 3, 25, 23, 1, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0, 0, 22, 23, 3, 3, 3, 25, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 17, 2, 2, 23, 3, 21, 24, 3, 3, 3, 3, 3, 3, 25, 23, 3, 3, 3, 21, 27, 27, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 23, 3, 3, 25, 0, 0, 0, 0, 14, 3, 20, 20, 16, 0, -2, 0, 0, -4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35, 0, 0, -1, 35, 3, 3, 21, 24, 1, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22, 3, 3, 3, 21, 24, 27, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 17, 2, 2, 2, 17, 17, 3, 3, 3, 21, 24, 3, 3, 3, 3, 3, 3, 21, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 20, 20, 24, 3, -1, 0, 0, 0, 0, 0, 14, 25, 23, 3, 3, 20, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 20, 20, 27, 27, 24, 3, 3, 3, 1, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 15, 27, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 2, 23, 3, 17, 2, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 17, 23, 3, 3, 3, 3, 25, 23, 3, 3, 3, 21, 16, 0, 0, 0, 0, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 25, 23, 3, 3, 3, 1, 0, 0, 0, 0, 14, 21, 24, 3, 25, 23, 3, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0}, 
        
        { 1, 0, 0, 14, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 2, 17, 2, 3, 21, 24, 3, 25, 23, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 21, 24, 25, 23, 3, 21, 0, 0, 0, 0, 14, 3, 3, 3, 21, 24, 3, 3, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 28, 0, 0, 19, 17, 17, 17, 17, 17, 17, 17, 17, 18, 0, 0, 0, 0, 0}, //tODO
        
        
        { 1, 0, 0, 14, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22, 23, 3, 3, 21, 24, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 28, 0, 0, 0, 0, -2, 0, 14, 3, 3, 21, 24, 3, 25, 0, 0, 0, 0, 14, 3, 3, 3, 3, 3, 3, 3, 21, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 14, 3, 1, 0, 0, 15, 16, 0, 0, 0, 0, 0, 0, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 20, 20, 27, 16, 0, 0, 0, 15, 27, 27, 0, -2, 0, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, 22, 23, 3, 3, 3, 3, 1, 38, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 20, 20, 20, 24, 3, 3, 3, 3, 3, 21, 0, 0, 0, 0, 22, 17, 23, 25, 23, 3, 3, 3, 3, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 14, 3, 1, 0, 0, 14, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 20, 20, 27, 24, 3, 25, 23, 1, 0, 0, 0, 14, 3, 3, 27, 27, 16, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 25, 23, 3, 1, 0, 0, 0, 13, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 25, 23, 3, 3, 3, 3, 3, 3, 3, 25, 0, 0, 0, 0, 0, 0, 0, 39, 22, 25, 23, 3, 3, 21, 27, 0, 0, 0, 0, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35, 0, 0, 0, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 14, 3, 1, 0, 0, 14, 1, 8, 0, 0, -4, 0, 0, 0, 0, 0, 0, 15, 27, 24, 25, 23, 3, 3, 3, 21, 24, 1, 0, 0, 0, 14, 25, 23, 3, 3, 3, 27, 20, 27, 20, 27, 27, 27, 20, 27, 16, 0, 0, 0, 0, 0, 3, 21, 24, 3, 1, 0, 0, 0, 0, 0, 0, 0, -4, 0, 0, 0, 0, 0, 0, 0, 0, 24, 21, 24, 3, 25, 23, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 25, 23, 3, 3, 20, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 20, 27, 20, 27, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 14, 25, 1, 0, 0, 14, 1, 0, 0, 0, 0, -2, 0, -1, 0, 0, 15, 24, 3, 3, 21, 24, 3, 3, 25, 23, 3, 1, 0, -5, 0, 14, 21, 24, 3, 3, 3, 3, 25, 23, 25, 23, 3, 3, 3, 17, 18, 0, 0, 0, 0, 39, 23, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 28, 0, 0, 0, 0, 0, 3, 3, 3, 3, 21, 24, 3, 3, 25, 23, 1, 0, 0, 0, 0, 0, 0, 0, -3, 35, 0, 0, 0, 24, 3, 3, 3, 25, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 25, 23, 3, 1, 38, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 14, 21, 1, 0, 0, 14, 21, 27, 27, 20, 27, 20, 27, 20, 20, 27, 24, 3, 3, 3, 3, 3, 3, 3, 21, 24, 3, 1, 0, 0, 0, 14, 3, 3, 3, 25, 23, 3, 21, 24, 21, 24, 3, 17, 2, 0, 0, 0, 0, 0, 0, 0, 24, 3, 25, 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 3, 25, 23, 3, 3, 3, 3, 21, 24, 21, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 21, 27, 27, 27, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 21, 24, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 14, 3, 1, 0, 0, 14, 25, 23, 3, 3, 25, 23, 3, 3, 3, 25, 23, 3, 3, 3, 25, 17, 17, 17, 17, 17, 17, 18, 0, 0, 0, 14, 3, 3, 3, 21, 24, 3, 3, 3, 3, 3, 2, 0, 0, 0, -5, 0, 0, 0, 0, 0, 23, 3, 21, 24, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 24, 3, 21, 24, 3, 3, 3, 3, 3, 3, 25, 0, 0, 0, 0, 14, 20, 16, 0, 0, -2, 0, 35, 23, 25, 23, 3, 3, 3, 25, 23, 1, 0, 0, 0, 0, 13, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 28, 0, 0, 0, 19, 17, 17, 17, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        //todo
        { 1, 0, 0, 14, 3, 1, 0, 0, 14, 21, 24, 3, 3, 21, 24, 3, 3, 3, 21, 24, 3, 3, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 3, 3, 3, 3, 3, 3, 3, 17, 0, 0, 0, 0, 0, 0, 0, 27, 27, 27, 24, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 27, 20, 27, 24, 3, 3, 3, 3, 3, 25, 23, 3, 3, 1, 13, 28, 0, 0, 14, 3, 21, 27, 27, 20, 27, 20, 24, 21, 24, 3, 3, 3, 21, 24, 1, 38, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 14, 3, 1, 0, 0, 14, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 25, 23, 3, 3, 25, 23, 3, 3, 18, 0, 0, 0, 0, 0, 0, -2, 0, 3, 3, 3, 3, 3, 3, 3, 18, 0, 0, 0, 0, 0, 0, 0, 13, 28, 0, 0, 0, 23, 3, 3, 3, 3, 3, 3, 25, 23, 3, 21, 24, 3, 3, 1, 0, 0, 0, 0, 14, 3, 25, 23, 3, 3, 3, 25, 23, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 14, 3, 1, 0, 0, 14, 3, 3, 3, 3, 3, 3, 25, 23, 3, 25, 17, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 39, 14, 21, 24, 3, 3, 21, 24, 3, 2, 38, 0, 0, 0, 0, 0, 0, 15, 27, 24, 3, 25, 23, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 25, 23, 3, 3, 21, 24, 3, 3, 3, 3, 25, 18, 0, 0, 0, 0, 14, 3, 21, 24, 3, 3, 3, 21, 24, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 14, 3, 1, 0, 0, 14, 3, 25, 23, 3, 3, 3, 21, 24, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4, 0, 0, 0, 0, 14, 3, 3, 3, 3, 3, 3, 17, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 21, 24, 3, 3, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 3, 3, 21, 24, 3, 3, 3, 3, 3, 3, 3, 3, 26, 0, 0, 0, 0, 0, 14, 3, 25, 23, 3, 3, 3, 3, 3, 3, 3, 3, 25, 23, 3, 3, 1, 0, 0, -2, 0, 0, 0, 0, 0, 0, 15, 20, 27, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 14, 3, 1, 0, 0, 14, 3, 21, 24, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 17, 3, 3, 3, 17, 18, 0, 0, 0, 0, 0, 0, 0, 15, 27, 24, 3, 17, 2, 2, 2, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 25, 23, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 14, 3, 21, 24, 25, 23, 3, 3, 25, 23, 3, 3, 21, 24, 3, 3, 21, 27, 20, 20, 16, 0, 0, 0, 0, 0, 24, 3, 3, 27, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 19, 2, 18, 0, 0, 19, 17, 2, 17, 2, 17, 2, 17, 17, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 2, 2, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 20, 24, 21, 24, 25, 23, 3, 3, 3, 3, 3, 3, 25, 26, 0, 0, 0, 0, 0, 0, 14, 3, 3, 3, 21, 24, 3, 3, 21, 24, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 23, 3, 3, 3, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -5, 0, 0, 0, 0, 0, 0, 0, 0, 23, 3, 3, 3, 3, 21, 24, 3, 3, 3, 25, 23, 3, 25, 0, 0, 0, 0, 0, 0, 0, 19, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 0, 0, 0, 0, 0, 14, 3, 3, 3, 25, 0, 13, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 0, 14, 3, 3, 3, 3, 3, 3, 3, 3, 3, 21, 24, 3, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 20, 24, 25, 23, 3, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 20, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 27, 27, 20, 27, 24, 3, 25, 23, 3, 3, 3, 3, 3, 3, 3, 25, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 21, 24, 3, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 20, 24, 3, 3, 3, 25, 23, 3, 21, 24, 3, 3, 3, 25, 23, 3, 25, 26, 0, 0, 0, 0, -4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -5, 0, 0, 14, 25, 23, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 21, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 3, 3, 25, 23, 3, 21, 24, 3, 3, 3, 25, 23, 3, 21, 24, 25, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 27, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 27, 24, 21, 24, 3, 3, 3, 1, 0, 0, 0, 0, 13, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 27, 24, 25, 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 27, 27, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 27, 24, 3, 3, 21, 24, 3, 3, 3, 3, 3, 3, 21, 24, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 23, 3, 21, 38, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 3, 3, 3, 3, 3, 3, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 21, 24, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 27, 24, 3, 3, 21, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 25, 23, 3, 3, 3, 3, 17, 17, 17, 17, 17, 3, 3, 3, 3, 3, 3, 1, 38, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, 15, 20, 27, 27, 24, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 25, 23, 3, 25, 23, 3, 25, 38, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 38, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 14, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, -1, 0, 0, 14, 21, 24, 3, 3, 25, 18, 0, 0, 0, 0, 0, 2, 23, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 25, 23, 3, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 20, 24, 21, 24, 3, 21, 24, 3, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 27, 20, 27, 27, 20, 27, 24, 3, 25, 23, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 27, 20, 24, 25, 23, 3, 3, 25, 23, 0, 0, 0, 0, 15, 20, 27, 20, 20, 24, 3, 3, 25, 2, 26, 0, 0, 0, 0, 0, 0, 0, 14, 3, 25, 23, 25, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 3, 3, 21, 24, 3, 21, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 25, 23, 3, 3, 25, 23, 3, 3, 21, 24, 3, 1, 0, 0, 0, 0, 0, 0, -4, 0, 0, 0, 0, 0, 0, 0, 14, 25, 23, 3, 21, 24, 3, 3, 21, 24, 0, 0, 0, 0, 14, 25, 23, 3, 25, 23, 3, 3, 1, 8, 0, 0, 0, 0, -5, 0, 0, 0, 14, 3, 21, 24, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 3, 3, 3, 3, 3, 3, 3, 20, 0, 0, 0, 0, 0, 0, 0, -1, 0, 27, 20, 3, 3, 25, 23, 3, 3, 3, 3, 3, 25, 0, 0, 0, 0, 0, 0, -4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 15, 16, 0, 0, 0, 0, 14, 21, 24, 3, 3, 21, 24, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 15, 27, 16, 0, 0, 0, -2, 0, 0, 14, 21, 24, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 14, 21, 24, 3, 21, 24, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 3, 3, 2, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 20, 20, 24, 3, 3, 3, 3, 25, 23, 3, 3, 20, 27, 16, 0, 0, 15, 20, 20, 27, 24, 3, 3, 3, 21, 24, 3, 25, 23, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 1, 0, 0, P, 0, 0, 0, 0, 0, 14, 1, 0, 0, 0, 0, 14, 3, 3, 3, 3, 3, 3, 3, 3, 3, 25, 23, 1, 0, 0, 0, 0, 0, 14, 3, 21, 27, 20, 20, 27, 20, 27, 24, 3, 3, 3, 3, 3, 3, 25, 23, 3, 0, 0, 0, 0, 14, 3, 3, 3, 3, 25, 23, 3, 1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 19, 17, 18, 0, 0, 0, 0, -4, 0, 0, 0, 0, 0, 0, 20, 24, 3, 3, 3, 3, 3, 3, 3, 21, 24, 3, 3, 3, 25, 18, 0, 0, 23, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 21, 24, 25, 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 21, 27, 20, 27, 27, 16, 0, 0, 0, 14, 1, 0, 0, 0, 0, 14, 3, 3, 3, 3, 3, 25, 23, 3, 3, 21, 24, 1, 0, 0, 0, 0, 0, 14, 25, 23, 3, 3, 3, 25, 23, 3, 3, 25, 23, 3, 3, 25, 23, 21, 24, 3, 0, 0, 0, 0, 14, 3, 3, 3, 3, 21, 24, 3, 3, 27, 20, 27, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 24, 25, 23, 3, 3, 25, 23, 3, 3, 3, 3, 3, 3, 3, 21, 0, 0, 0, 19, 17, 17, 23, 3, 3, 3, 3, 25, 23, 3, 3, 3, 21, 24, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 25, 23, 3, 25, 23, 1, 0, 0, 0, 14, 1, 0, 0, 0, 0, 14, 25, 23, 3, 3, 3, 21, 24, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 14, 21, 24, 3, 3, 3, 21, 24, 3, 3, 21, 24, 3, 3, 21, 24, 3, 3, 3, 0, 0, 0, 0, 14, 3, 3, 25, 17, 17, 17, 17, 17, 17, 17, 17, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 20, 24, 3, 21, 24, 3, 3, 21, 24, 3, 3, 3, 25, 23, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 21, 24, 3, 21, 24, 1, 0, 0, 0, 14, 1, 0, 0, 0, 0, 14, 21, 24, 3, 3, 3, 3, 3, 3, 3, 25, 23, 1, 0, 0, 0, 0, 0, 14, 3, 3, 3, 3, 3, 3, 25, 23, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 14, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 20, 20, 20, 24, 3, 3, 3, 25, 23, 3, 3, 3, 3, 3, 3, 21, 24, 3, 3, 3, 25, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 3, 3, 3, 3, 3, 1, 0, 0, 0, 14, 1, 0, 0, 0, 0, 14, 3, 3, 3, 3, 3, 3, 3, 3, 3, 21, 24, 1, 0, 0, 0, 0, 0, 14, 3, 3, 25, 23, 3, 3, 21, 24, 3, 3, 3, 3, 3, 3, 3, 25, 23, 3, 0, 0, 0, 0, 14, 3, 25, 38, 0, 0, 0, 0, 0, -4, 0, 0, 0, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 35, 0, 24, 3, 3, 3, 3, 25, 23, 3, 21, 24, 3, 3, 3, 3, 3, 3, 3, 25, 23, 3, 3, 21, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 3, 3, 25, 23, 3, 1, 0, 0, 0, 14, 1, 0, 0, 0, 0, 14, 3, 3, 25, 23, 3, 25, 23, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 14, 3, 3, 21, 24, 3, 3, 3, 3, 25, 23, 3, 3, 25, 23, 3, 21, 24, 3, 0, 0, 0, 0, 14, 3, 21, 0, 0, 0, 35, 0, 0, 0, 0, 0, 0, 0, 15, 27, 27, 16, 0, 0, -1, 0, 0, 15, 20, 20, 24, 25, 23, 3, 3, 21, 24, 3, 3, 3, 3, 3, 25, 23, 3, 3, 3, 21, 24, 3, 3, 3, 27, 20, 27, 20, 20, 24, 3, 3, 3, 3, 25, 23, 3, 3, 3, 3, 3, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        
        { 3, 3, 21, 24, 3, 1, 0, 0, 0, 14, 1, 0, 0, 0, 0, 14, 3, 3, 21, 24, 3, 21, 24, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 14, 3, 3, 3, 3, 25, 23, 3, 3, 21, 24, 3, 3, 21, 24, 3, 3, 3, 3, 0, 0, 0, 0, 14, 3, 3, 21, 20, 27, 27, 20, 27, 27, 27, 20, 27, 27, 24, 3, 3, 21, 27, 20, 27, 20, 27, 24, 3, 3, 3, 21, 24, 3, 3, 3, 3, 3, 3, 3, 3, 3, 21, 24, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 25, 23, 3, 3, 21, 24, 3, 3, 3, 3, 3, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    const TexturePathMapping m_texture_map = {
        { -7, textures_path("fire.png")},
        { -6, textures_path("cave/projectiles/ice.png")},
        { -5, textures_path("bat/bat_spritesheet1.png")},
        { -4, textures_path("bat/bat_spritesheet1.png")},
        { -3, textures_path("bat/bat_spritesheet1.png")},
        
        { -2, textures_path("cave/enemies/littleppl/blue_spritesheet.png")},
        { -1, textures_path("cave/enemies/littleppl/littleppl.png")},
        
        { 1, textures_path("cave/tiles/right_side.png")},
        { 2, textures_path("cave/tiles/bottom_l.png")},
        { 3, textures_path("cave/tiles/fill.png")},
        { 8, textures_path("cave/torch_empty.png")},
        { 13, textures_path("cave/tiles/rock_L.png")},
        { 14, textures_path("cave/tiles/left-wall.png")},
        { 15, textures_path("cave/tiles/floor_left.png")},
        { 16, textures_path("cave/tiles/floor_right.png")},
        
        { 17, textures_path("cave/tiles/bottom_r.png")},
        { 18, textures_path("cave/tiles/right_curve.png")},
        { 19, textures_path("cave/tiles/left_curve.png")},
        { 20, textures_path("cave/tiles/middle2.png")},
        { 21, textures_path("cave/tiles/corner_TR.png")},
        { 22, textures_path("cave/tiles/floor_BL.png")},
        { 23, textures_path("cave/tiles/corner_BL.png")},
        { 24, textures_path("cave/tiles/corner_TL.png")},
        { 25, textures_path("cave/tiles/corner_BR.png")},
        { 26, textures_path("cave/tiles/floor_BR.png")},
        { 27, textures_path("cave/tiles/middle_r.png")},
        { 28, textures_path("cave/tiles/rock_right.png")},
        { 35, textures_path("heart_spritesheet.png")},
        
        { 38, textures_path("cave/static_torch.png")},
        { 39, textures_path("cave/static_torch_R.png")}
        
    };
    
    const TilePropertyMapping m_property_map = {
        {8, std::make_shared<Properties>(Properties::Type::TORCH)},
        {38, std::make_shared<Properties>(Properties::Type::TORCH_LIT)},
        {39, std::make_shared<Properties>(Properties::Type::TORCH_LIT)},
        {35, std::make_shared<Properties>(Properties::Type::HEALTH)}
    };

    float offset;
};

#endif //DAB_FOREST_LEVEL_HPP
