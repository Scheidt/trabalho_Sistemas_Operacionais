#include "cannon.hpp"


CannonObject::CannonObject(
    int xa,
    int ya,
    int w,
    int h,
    int max_ammo,
    float reload_time
) : RectangleObject(xa, ya, w, h, "assets/cannon.png"), max_ammo(max_ammo), reload_time(reload_time), ammo(max_ammo) {};


std::pair<int, int> CannonObject::update() {
    int velX = 0;
    int velY = 0;

    if ((ammo <= 0) && (x == 50)) {
        Sleep(reload_time);
        ammo = max_ammo;
    }
    if ((ammo <= 0) && (x > 51)) {
        move(-5, 0);
    } else {
        switch (rand()%8){
            case 0:
                if (x > 50){
                    move(-7, 0);
                };
                break;
            case 1:
                if (x < 750){
                    move(7, 0);
                };
                break;
            case 2:
                if (x < 750){
                    move(7, 0);
                };
                break;
            default:
                break;
        }
    }
    if (rand() % 100 == 42) {
        velX = (rand() % 3) * ((rand() % 2) * 2 - 1); //0~3 * 50% de chance de ser positivo ou negativo
        velY = ((rand() % 5) + 2) * (-1);
    }

    return std::make_pair(velX, velY);
}

void CannonObject::reduceAmmo(){
    ammo --;
}