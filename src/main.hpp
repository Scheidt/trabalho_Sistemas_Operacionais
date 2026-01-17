#ifndef MAIN_HPP
#define MAIN_HPP

#define OS_WINDOWS
//define OS_LINUX

// Standart libraries
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
// Allegro includes
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

// Project File
#include "physics/physics.hpp"
#include "cannonLogic/cannon.hpp"
#include "heliLogic/heli.hpp"
#include "Fuse/Fuse.hpp"

#define WIDTH 800
#define HEIGHT 600

#endif