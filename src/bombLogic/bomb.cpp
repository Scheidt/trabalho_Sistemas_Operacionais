#include "bomb.hpp"


BombObject::BombObject(
    int xa,
    int ya,
    int w,
    int h,
    int velXa,
    int velYa,
    sem_t* sem0a,
    sem_t* sem1a,
    cannonBombJunction* fuseNewa,
    cannonBombJunction* fuseOlda,
    bool* gameLoopa,
    pthread_mutex_t* bridge_lockA
) : RectangleObject(xa, ya, w, h, "assets/bomb.png"), velX(velXa), velY(velYa), sem0(sem0a), sem1(sem1a), fuseNew(fuseNewa), fuseOld(fuseOlda), gameLoop(gameLoopa),
        bridge_lock(bridge_lockA){};

void BombObject::loop(){
    while(*gameLoop){
        sem_wait(sem0);
        if (y < -10 && rand()%100 == 42){
            fuseNew->bombOutOfBound = true;
        } else {
            fuseNew->bombOutOfBound = false;
            move(velX, velY);
        }
        if (fuseOld->bombOutOfBound && fuseOld->hasAmmo){
            shoot();
            setPosition(fuseOld->cannonX+25, fuseOld->cannonY);
        } 
        sem_post(sem1);
    }
}

void BombObject::shoot(){
    velX = (rand() % 3) * ((rand() % 2) * 2 - 1); //0~3 * 50% de chance de ser positivo ou negativo
    velY = ((rand() % 5) + 2) * (-1);
}