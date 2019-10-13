#include "level.hpp"

void Level::init() {
    setTextures();
}

void Level::update() {
}

void Level::draw(const mat3 &projection) {
//    for (auto& tile : m_tiles)
//        tile.draw(projection_2D);
}

/*** Assigns all tile variables a texture
 *
 */
void Level::setTextures() {
    if (!m_tile1_texture.is_valid())
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

bool Level::loadLevel(int arr[17][50])
{
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            map[row][col] = arr[row][col];
        }
    }
    drawMap();
    return true;
}

bool Level::draw_map() {
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
