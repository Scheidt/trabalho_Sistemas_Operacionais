#include "physics.hpp"

retangleObject::retangleObject(
    float xa, 
    float ya, 
    float w, 
    float h, 
    char* path
):x(xa), y(ya), width(w), height(h){
    sprite.image = al_load_bitmap(path);
    if(!sprite.image){
        fprintf(stderr, "Failed to load image!\n");
        return;
    }

    sprite.width = al_get_bitmap_width(sprite.image);
    sprite.height = al_get_bitmap_height(sprite.image);
}

void retangleObject::render(){
    al_draw_scaled_bitmap(
        sprite.image, 
        0, 0, 
        (float)sprite.width, (float)sprite.height,
        x, y, 
        width, height, 0
    );
}

bool retangleObject::isColided(retangleObject& another){
    if(
        x < another.x + another.width &&
        x + width > another.x &&
        y < another.y + another.height &&
        y + height > another.y
    ){
        return true;
    }
    return false;
}