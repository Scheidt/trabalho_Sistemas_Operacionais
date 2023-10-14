#ifndef RENDERING_HPP
#define RENDERING_HPP

// Allegro includes
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
// I/O includes
#include <cstdio> // Include the <cstdio> header for fprintf
#include <iostream> // Include <iostream> for std::cerr

void render_test(ALLEGRO_DISPLAY *display, float x, float y, float width, float height);
void render_choppa(ALLEGRO_DISPLAY *display, float x, float y, bool right);
void render_cannon(ALLEGRO_DISPLAY *display, float x, float y);
void render_bomb(ALLEGRO_DISPLAY *display, float x, float y);
void render_ruin(ALLEGRO_DISPLAY *display);
void render_hospital(ALLEGRO_DISPLAY *display);
void render_background(ALLEGRO_DISPLAY *display);
void render_road(ALLEGRO_DISPLAY *display);
void render_hostage_count(ALLEGRO_DISPLAY *display, int count);



#endif