//
// Created by arden on 10/15/2019.
//

#ifndef DAB_BUTTON_H
#define DAB_BUTTON_H

#include "common.hpp"


class Button : public Entity {
public:
    Button();
    ~Button();

    // Creates all the associated render resources and default transform
    bool init(vec2 pos, const char* path);

    // Releases all associated resources
    void destroy();

    // Renders the background
    void draw(const mat3& projection)override;

    void update(float ms);
protected:
    Texture* m_texture;
private:
    TexturedVertex vertices[4];
};


#endif //DAB_BUTTON_H
