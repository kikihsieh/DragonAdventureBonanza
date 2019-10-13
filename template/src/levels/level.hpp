#ifndef DAB_LEVEL_HPP
#define DAB_LEVEL_HPP

#include <common.hpp>
#include <vector>
#include <tile.hpp>

class Level {
public:
    Level();
    ~Level();

    virtual void init();
    virtual void update();
    virtual void draw(const mat3& projection);
    virtual bool draw_map();

    const char * getMBgTexturePath() const {
        return m_bg_texture_path;
    }

protected:
    //Load tiles
    bool loadLevel(int arr[17][50]);
    bool drawMap();
    int map[17][50];

    virtual void setTextures();
    std::vector<Tile> m_tiles;

    const char* m_bg_texture_path;

    bool m_unlocked;

    vec2 m_x_boundaries;
    vec2 m_y_boundaries;

    // Game entities
    std::vector<Entity> m_enemies;
};

#endif //DAB_LEVEL_HPP
