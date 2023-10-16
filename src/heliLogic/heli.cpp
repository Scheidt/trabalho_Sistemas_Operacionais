#include "heli.hpp"


HeliObject::HeliObject(
    int xa,
    int ya,
    int w,
    int h,
    sem_t* sem0a,
    sem_t* sem1a,
    bool* gameLoopA,
    bool* pressed_keysA [277]

) : RectangleObject(xa, ya, w, h, "assets/helicopter.png"), sem0(sem0a), sem1(sem1a), gameLoop(gameLoopA), pressed_keys(pressed_keysA) {};

void HeliObject::loop(){
    while(*gameLoop) {
        move(velX, velY);
        sem_post(sem1);
    }
  

}