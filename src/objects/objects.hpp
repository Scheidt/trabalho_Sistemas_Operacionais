#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <stdio.h>
#include <allegro5/allegro.h>

void spawn_test(ALLEGRO_DISPLAY *display, float x, float y, float width, float height);
void spawn_choppa(ALLEGRO_DISPLAY *display, float x, float y, bool right);
void spawn_cannon(ALLEGRO_DISPLAY *display, float x, float y);
void spawn_bomb(ALLEGRO_DISPLAY *display, float x, float y);
void spawn_ruin(ALLEGRO_DISPLAY *display);
void spawn_hospital(ALLEGRO_DISPLAY *display);
void spawn_background(ALLEGRO_DISPLAY *display);
void spawn_road(ALLEGRO_DISPLAY *display);


#endif