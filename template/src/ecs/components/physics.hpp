struct Physics {
    Physics() :
        gravity(750.f),
        acceleration({0.f, 0.f}),
        velocity({0.f, 0.f}),
        jump_speed(50.f),
        walk_speed(50.f),
        jump_count(0) {
    }

    float gravity;
    vec2 acceleration;
    vec2 velocity;
    float jump_speed;
    float walk_speed;
    int jump_count;
    bool grounded = false;
    float grounded_friction = 0;
    bool leaving_ice = false;
    bool off_screen = false;
};
