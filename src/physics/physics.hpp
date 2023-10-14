#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <stdio.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>

typedef struct Sprite{
    ALLEGRO_BITMAP *image;
    int width;
    int height;
} Sprite;

class retangleObject{
    public:
        float x;
        float y;
        float width;
        float height;
        Sprite sprite;

        retangleObject(float xa, float ya, float w, float h, char* path);
        void render();
        bool isColided(retangleObject& another);
};

#endif