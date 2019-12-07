#ifndef DAB_COLLISION_SYSTEM_HPP
#define DAB_COLLISION_SYSTEM_HPP

#include <ecs/entities/tile.hpp>
#include <map>
#include <list>
#include <functional>

class CollisionSystem {
public:
    enum Side {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        NONE
    };

    bool init(std::list<Entity> *entities, std::map<int, Tile*>* tiles);

    void update(float ms);

    bool is_goal_reached() const {
        return m_goal_reached;
    };

    void set_torches_to_light(int torches_to_light);
    int m_torches_to_light = 0;

private:
    void tile_collisions(Entity& entity, float ms); // Returns true if tile should be removed

    bool collide_with_tile(Entity& entity, Tile &tile, float ms);
    bool collide_with_entities(Entity& e);

    bool tile_property_updates(Entity& entity, Tile& tile, Side side, float ms); // Returns true if tile should be removed
    static bool entity_property_updates(Entity& entity, Tile &tile, Side side); // Returns true if tile should be removed
    void collider_updates(Entity& entity, Tile &tile, Side side);
    static void bounce_updates(Entity& entity, float bounce, Side side);
    static void friction_updates(Entity& entity, float friction, Side side, float ms);

    static Side detect_collision(Entity& e1, Entity &e2);

    static void land(Entity& entity);
    void grounded(Entity& entity);
    static void fall(Entity& entity);
    
    bool m_goal_reached;

    std::function<void(void)> m_torch_light_callback;

    std::list<Entity>* m_entities;
    std::map<int, Tile*>* m_tiles;
    float padding = 0.1;
};

#endif //DAB_COLLISION_SYSTEM_HPP
