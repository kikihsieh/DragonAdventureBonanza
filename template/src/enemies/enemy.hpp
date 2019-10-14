#ifndef DAB_ENEMY_HPP
#define DAB_ENEMY_HPP

#include <common.hpp>

class Enemy : public Entity {

public:
    enum Type {
        // TODO
        WALKING,
        FLYING
    };

    Enemy(Type type) {
        m_type = type;
    }

    virtual void update(float elapsed_ms) = 0;

    Type get_type() const {
        return m_type;
    }

protected:
    Type m_type;
};

#endif //DAB_ENEMY_HPP
