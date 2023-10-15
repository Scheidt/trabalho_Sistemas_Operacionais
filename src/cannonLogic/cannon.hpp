#ifndef CANNON_HPP
#define CANNON_HPP

#include <stdio.h>
#include "../physics/physics.hpp"
#include <windows.h>


class CannonObject : public RectangleObject {
public:
    int max_ammo;
    float reload_time;
    int ammo;

    // Constructor prototype for CannonObject
    CannonObject(
        int xa,
        int ya,
        int w,
        int h,
        int max_ammo,
        float reload_time
    );
    int* update();
};


#endif