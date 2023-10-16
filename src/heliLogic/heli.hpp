#include "../physics/physics.hpp"
#include <semaphore.h>
#include <utility>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>

class HeliObject : public RectangleObject {
public:
    int velX;
    int velY;
    sem_t* sem0;
    sem_t* sem1;
    bool* gameLoop;

    HeliObject(
        int xa,
        int ya,
        int w,
        int h,
        sem_t* sem0a,
        sem_t* sem1a,
        bool* gameLoopa
    );
    void loop();
};

typedef struct choppaArgs {
    bool right;
    int direction;
} choppaArgs;