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
    bool* pressed_keys;
    bool right;

    HeliObject(
        int xa,
        int ya,
        int w,
        int h,
        sem_t* sem0a,
        sem_t* sem1a,
        bool* gameLoopa,
        bool pressed_keysA [277]
    );
    void loop();
    void render();
};

typedef struct choppaArgs {
    bool right;
    int direction;
} choppaArgs;