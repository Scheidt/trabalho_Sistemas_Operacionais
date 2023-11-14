#include "../physics/physics.hpp"
#include <semaphore.h>
#include <utility>
#include "../Fuse/Fuse.hpp"
#include <stdlib.h>
#include <pthread.h>



class BombObject : public RectangleObject {
public:
    float velX;
    float velY;
    sem_t* sem0;
    sem_t* sem1;
    cannonBombJunction* fuseNew;
    cannonBombJunction* fuseOld;
    bool* gameLoop;
    pthread_mutex_t* bridge_lock;

    BombObject(
        float xa,
        float ya,
        float w,
        float h,
        float velXa,
        float velYa,
        sem_t* sem0a,
        sem_t* sem1a,
        cannonBombJunction* fuseNewa,
        cannonBombJunction* fuseOlda,
        bool* gameLoopa,
        pthread_mutex_t* bridge_lockA
    );
    void shoot();
    void loop();
};

void* bombLoop(void* entrada);