#ifndef FUSE_HPP
#define FUSE_HPP
#include <pthread.h>
#include <stdlib.h>


typedef struct {
    bool hasAmmo;
    bool bombOutOfBound;
    float cannonX;
    float cannonY;
} cannonBombJunction;


#endif