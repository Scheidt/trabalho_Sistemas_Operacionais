#ifndef CANNON_HPP
#define CANNON_HPP

#include <stdio.h>
#include "../physics/physics.hpp"
#include <utility>
#include <semaphore.h>
#include <iostream>
#include "../bombLogic/bomb.hpp"
#include <allegro5/allegro_font.h>
#include "../Fuse/Fuse.hpp"
#include <unistd.h>



class CannonObject : public RectangleObject {
public:
    int ammo;
    unsigned int max_ammo;
    unsigned int reload_time;
    int framesTilReload = 0;
    sem_t* sem0;
    sem_t* sem1;
    BombObject* bomb;
    bool* gameLoop;
    cannonBombJunction* fuseOld;
    cannonBombJunction* fuseNew;
    pthread_mutex_t* bridge_lock;
    bool* bridge_occupied;
    bool am_in_bridge = false;

    CannonObject(
        int xa,
        int ya,
        int w,
        int h,
        unsigned int max_ammo,
        unsigned int reload_time,
        sem_t* sem0A,
        sem_t* sem1A,
        BombObject* bombA,
        bool* gameLoopA,
        cannonBombJunction* fuseOldA,
        cannonBombJunction* fuseNewA,
        pthread_mutex_t* bridge_lockA,
        bool* bridge_occupiedA
    );
    void update();
    void loop();
    void render_bomb_count(ALLEGRO_DISPLAY* display);
    void* sleepThread(void* arg);
};


#endif