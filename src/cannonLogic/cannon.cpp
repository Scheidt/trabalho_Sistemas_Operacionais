#include "cannon.hpp"


CannonObject::CannonObject(
    int xa,
    int ya,
    int w,
    int h,
    int max_ammo,
    float reload_time,
    sem_t* sem0A,
    sem_t* sem1A,
    BombObject* bombA,
    bool* gameLoopA,
    cannonBombJunction* fuseOldA,
    cannonBombJunction* fuseNewA,
    pthread_mutex_t* bridge_lockA,
    bool* bridge_occupiedA

) : RectangleObject(xa, ya, w, h, "assets/cannon.png"), max_ammo(max_ammo), reload_time(reload_time), ammo(max_ammo), 
    sem0(sem0A), sem1(sem1A), bomb(bombA), gameLoop(gameLoopA), fuseOld(fuseOldA), fuseNew(fuseNewA), bridge_lock(bridge_lockA),
    bridge_occupied(bridge_occupiedA){};


void CannonObject::update() {
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
    if ((x + width) > 125 && x < 200) { // se está na ponte
        if (!*bridge_occupied && !am_in_bridge){
            pthread_mutex_lock(bridge_lock); // https://en.wikipedia.org/wiki/Double-checked_locking
            if (!*bridge_occupied){
                *bridge_occupied = true;
                am_in_bridge = true;
            }
            pthread_mutex_unlock(bridge_lock);
        }
        if (!am_in_bridge){
            if (x < 125) {// está na esquerda da ponte
                x = 75;
            } else {
                x = 200;
            }
        }
    } else if (am_in_bridge){
        am_in_bridge = false;
        pthread_mutex_lock(bridge_lock);
        *bridge_occupied = false;
        pthread_mutex_unlock(bridge_lock);
    }
}


void CannonObject::render_bomb_count(ALLEGRO_DISPLAY* display) {
    ALLEGRO_FONT *font = al_create_builtin_font();
    al_draw_textf(font, al_map_rgb(255, 255, 255), x, y+60, ALLEGRO_ALIGN_LEFT, "Bombs: %d", ammo);
    al_destroy_font(font);
}

void CannonObject::loop(){
    while(*gameLoop) {
        sem_wait(sem0);
        update();
        if (ammo > 0){
            fuseNew->hasAmmo = true;
            fuseNew->cannonX = x;
            fuseNew->cannonY = y;
        } else {
            fuseNew->hasAmmo = false;
        }
        if (fuseOld->hasAmmo && fuseOld->bombOutOfBound){
            ammo --;
        }
        sem_post(sem1);
    }
}
//reduceAmmo()