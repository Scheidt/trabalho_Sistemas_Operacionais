#ifndef CANNON_HPP
#define CANNON_HPP

#include <stdio.h>
#include "../physics/physics.hpp"
#include <windows.h>
#include <utility>
#include <iostream>


class CannonObject : public RectangleObject {
public:
    int max_ammo;
    float reload_time;
    int ammo;

    CannonObject(
        int xa,
        int ya,
        int w,
        int h,
        int max_ammo,
        float reload_time
    );
    std::pair<int, int> update();
    void reduceAmmo();
};


#endif