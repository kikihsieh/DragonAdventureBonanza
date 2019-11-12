struct Flyable {
	Flyable() :
        t(0.f),
        speed(3),
        center_c({0,0}),
        initial_pos1({0,0}),
        final_pos2({0,0}),
        mid_p({0,0}),
        boundary_x0(0.f),
        boundary_x1(0.f),
        flag(true),
        angle_c(0.f),
        rotate_speed(3.f),
        velocity_c({1,0}),
        radius(50.f),
        fly_mode(1),
		flyable_enemy(false) {
	}

	bool flyable_enemy;
    float t;
    int speed;
    
    vec2 center_c;// = entity.position;
    vec2 initial_pos1; //= entity.position;
    vec2 final_pos2;// = {entity.position.x+100,entity.position.y};
    vec2 mid_p;// ={entity.position.x+5,entity.position.y +100};
    float boundary_x0;// = entity.position.x +100;
    float boundary_x1;
    bool flag;
    float angle_c;
    float rotate_speed;
    vec2 velocity_c;
    float radius;
    int fly_mode;
};
