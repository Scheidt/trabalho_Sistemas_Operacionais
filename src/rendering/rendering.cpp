#include "rendering.hpp"


ALLEGRO_DISPLAY *display = al_create_display(800, 600);

void render_object(ALLEGRO_DISPLAY *display, float x, float y, float width, float height, char* source) {
    ALLEGRO_BITMAP *image = al_load_bitmap(source);
    // Set the target bitmap to draw the image onto
    al_set_target_bitmap(al_get_backbuffer(display));

    al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
                          x, y, width, height, 0);
 
};

void render_test(ALLEGRO_DISPLAY *display, float x, float y, float width, float height) {
    ALLEGRO_BITMAP *image = al_load_bitmap("assets/test square.png");
    // Set the target bitmap to draw the image onto
    al_set_target_bitmap(al_get_backbuffer(display));

    al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
                          x, y, width, height, 0);
 
};

void render_choppa(ALLEGRO_DISPLAY *display, float x, float y, bool right) {
    ALLEGRO_BITMAP *image = al_load_bitmap("assets/helicopter.png");
    // Set the target bitmap to draw the image onto
    al_set_target_bitmap(al_get_backbuffer(display));

    if (right) {
    al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
                          x, y, 100, 50, 0);
    } else { 
    al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
                          x, y, -100, 50, 0);
    }
    al_destroy_bitmap(image);
};

void render_cannon(ALLEGRO_DISPLAY *display, float x, float y) {
    ALLEGRO_BITMAP *image = al_load_bitmap("assets/cannon.png");
    // Set the target bitmap to draw the image onto
    al_set_target_bitmap(al_get_backbuffer(display));


    al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
                          x, y, 50, 50, 0);

    al_destroy_bitmap(image);
};

void render_bomb(ALLEGRO_DISPLAY *display, float x, float y) {
    ALLEGRO_BITMAP *image = al_load_bitmap("assets/bomb.png");
    // Set the target bitmap to draw the image onto
    al_set_target_bitmap(al_get_backbuffer(display));


    al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
                          x, y, 15, 15, 0);

    al_destroy_bitmap(image);
};

void render_ruin(ALLEGRO_DISPLAY *display) {
    ALLEGRO_BITMAP *image = al_load_bitmap("assets/burnt building.png");
    // Set the target bitmap to draw the image onto
    al_set_target_bitmap(al_get_backbuffer(display));


    al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
                         0, 210, 100, 350, 0);

    al_destroy_bitmap(image);
};

void render_hospital(ALLEGRO_DISPLAY *display) {
    ALLEGRO_BITMAP *image = al_load_bitmap("assets/hospital.png");
    // Set the target bitmap to draw the image onto
    al_set_target_bitmap(al_get_backbuffer(display));


    al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
                         690, 210, 100, 350, 0);

    al_destroy_bitmap(image);
};

void render_road(ALLEGRO_DISPLAY *display) {
    ALLEGRO_BITMAP *image = al_load_bitmap("assets/road.png");
    // Set the target bitmap to draw the image onto
    al_set_target_bitmap(al_get_backbuffer(display));


    al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
                          1, 550, 800, 50, 0);

    al_destroy_bitmap(image);
};

void render_background(ALLEGRO_DISPLAY *display) { // PRONTO, VAMO Q VAMO
    ALLEGRO_BITMAP *image = al_load_bitmap("assets/bkground.png");
    // Set the target bitmap to draw the image onto
    al_set_target_bitmap(al_get_backbuffer(display));


    al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
                          0, 0, 800, 600, 0);

    al_destroy_bitmap(image);
};