#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <stdio.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>

typedef struct Sprite{
    ALLEGRO_BITMAP* image;
    int width;
    int height;
} Sprite;

class RectangleObject{
    public:
        float x;
        float y;
        float width;
        float height;
        Sprite sprite;

        RectangleObject(float xa, float ya, float w, float h, const char* path);
        void render();
        void move(float xa, float ya);
        void setPosition(float x, float y);
        bool isColided(RectangleObject& another);
};

#endif