#ifndef FUSE_HPP
#define FUSE_HPP
#include <pthread.h>
#include <stdlib.h>


typedef struct {
    bool hasAmmo;
    bool bombOutOfBound;
    int cannonX;
    int cannonY;
    } cannonBombJunction;


#endif