#include "tile.hpp"

using namespace std;

Tile::Tile() {

}

Tile::~Tile() = default;

bool Tile::init() {
    
    //motion.position = { 33.5f, 33.5f};
    scale = { 0.75f, 0.75f };
//    compute_world_coordinate();
    return true;
}

void Tile::set_position(float x, float y)
{
//    motion.position.x = x * m_texture->width*physics.scale.x - m_texture->width*0.5f*physics.scale.x;
//    motion.position.y = y * m_texture->height*physics.scale.y + m_texture->height*0.5f*physics.scale.y;
}

//void Tile::compute_world_coordinate()
//{
//    for (auto& v : vertices) {
////        vec3 transformed_vertex = mul(transform.out, vec3{ v.position.x, v.position.y, 1.f });
////        platform_world_coord.push_back({ transformed_vertex.x, transformed_vertex.y });
//    }
//
//}
