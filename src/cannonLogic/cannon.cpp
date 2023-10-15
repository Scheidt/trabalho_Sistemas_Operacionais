#include "cannon.hpp"


CannonObject::CannonObject(
    int xa,
    int ya,
    int w,
    int h,
    int max_ammo,
    float reload_time
) : RectangleObject(xa, ya, w, h, "assets/cannon.png"), max_ammo(max_ammo), reload_time(reload_time), ammo(max_ammo) {
        // Any additional initialization specific to CannonObject can go here
    };

int* CannonObject::update(){
    if ((ammo == 0) && (x == 50)){
        Sleep(reload_time);
        ammo = max_ammo;
    }
    if((ammo <= 0) && (x > 51)){
        move(-5, 0);
    } else {
        switch (rand()%3){
            case 0:
                if (x > 50){
                    move(-5, 0);
                };
                break;
            case 1:
                if (x < 750){
                    move(5, 0);
                };
                break;
            case 2:
                break;
            default:
                break;
        }
        int* arr = (int*)malloc(2 * sizeof(int));
        if (rand()%100 == 42){
            ammo --;
            int velX = (rand()%5) * ((rand()%2)*2 - 1);
            int velY = (rand()%5) * (-1);
            arr[0] = velX;
            arr[1] = velY;
            return arr;
        } else {
            arr[0] = 0;
            arr[1] = 0;
        }
    }
    
}
