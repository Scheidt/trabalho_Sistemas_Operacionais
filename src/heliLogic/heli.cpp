#include "heli.hpp"


HeliObject::HeliObject(
    int xa,
    int ya,
    int w,
    int h,
    sem_t* sem0a,
    sem_t* sem1a,
    bool* gameLoopA

) : RectangleObject(xa, ya, w, h, "assets/helicopter.png"), sem0(sem0a), sem1(sem1a), gameLoop(gameLoopA){};

void HeliObject::loop(){
    while(*gameLoop) {
        move(velX, velY);
        sem_post(sem1);
    }
  

}