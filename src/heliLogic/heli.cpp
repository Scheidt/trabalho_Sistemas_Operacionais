#include "heli.hpp"


HeliObject::HeliObject(
    int xa,
    int ya,
    int w,
    int h,
    sem_t* sem0a,
    sem_t* sem1a,
    bool* gameLoopA,
    bool pressed_keysA [277]

) : RectangleObject(xa, ya, w, h, "assets/helicopter.png"), sem0(sem0a), sem1(sem1a), gameLoop(gameLoopA), pressed_keys(pressed_keysA) {};

void HeliObject::loop(){
    while(*gameLoop) {
        sem_wait(sem0);
        if (pressed_keys[ALLEGRO_KEY_DOWN]) { //baixo
            move(0, 5);
        }
        if (pressed_keys[ALLEGRO_KEY_UP]) { //cima
            move(0, -5);
        }
        if (pressed_keys[ALLEGRO_KEY_LEFT]) {
            move(-5, 0);
        }
        if (pressed_keys[ALLEGRO_KEY_RIGHT]) {
            move(5, 0);
        }
        sem_post(sem1);
    }
  

}