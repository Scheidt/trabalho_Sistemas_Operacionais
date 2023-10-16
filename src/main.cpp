#include "main.hpp"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "Fuse/Fuse.hpp"


int hostages_onboard = 1;
int hostages_count = 9;

const int max_ammo_const = 3;
const float reload_time_const = 1/10;
int vel0X = 0;
int vel0Y = 0;
int vel1X = 0;
int vel1Y = 0;

ALLEGRO_BITMAP *explosion_image = nullptr;

void* cannonLoop(void* entrada){
    CannonObject* quaseArgs = (CannonObject*) entrada;
    srand((unsigned int)time(NULL)*(*((int*)(&entrada))));
    quaseArgs -> loop();
    return NULL;
}

void* bombLoop(void* entrada){
    BombObject* quaseArgs = (BombObject*) entrada;
    srand((unsigned int)time(NULL)*(*((int*)(&entrada))));
    quaseArgs -> loop();
    return NULL;
}



void render_info(ALLEGRO_DISPLAY *display, int hostages_count, int hostages_onboard) {
    ALLEGRO_FONT *font = al_create_builtin_font();
    al_draw_textf(font, al_map_rgb(255, 255, 255), 50, 70, ALLEGRO_ALIGN_LEFT, "Hostages remaining: %d", hostages_count);
    al_draw_textf(font, al_map_rgb(255, 255, 255), 50, 90, ALLEGRO_ALIGN_LEFT, "Hostages onboard: %d", hostages_onboard);
    al_destroy_font(font);
}

int main() {
    
    srand((unsigned int)time(NULL));


    const int width = WIDTH;
    const int height = HEIGHT;

    // Initialize allegro lib
    if (!al_init()){
        fprintf(stderr, "Failed to initialize Allegro!\n");
        return -1;
    };
    if(!al_init_image_addon()){
        fprintf(stderr, "Failed to initialize Allegro Image!\n");
        return -1;
    };
    if(!al_install_keyboard()){
        fprintf(stderr, "Failed to initialize Allegro Keyboard!\n");
        return -1;
    };
    if(!al_init_primitives_addon()){
        fprintf(stderr, "Failed to initialize Allegro Primitives!\n");
        return -1;
    };

    if (!al_init_font_addon()) {
        fprintf(stderr, "Failed to initialize Allegro Font Addon!\n");
        return -1;
    }

    // Allegro Variables
    ALLEGRO_DISPLAY* display = al_create_display(width, height);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_EVENT event;

    if (!display) {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }

    // Allegro - registering event sources
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));


    // User input variables
    bool pressed_keys[ALLEGRO_KEY_MAX] = {false};

    // Loop variables
    al_start_timer(timer);

    bool redraw = true;
    bool loop = true;
    double last_explosion_time = 0;

    int choppaX = 55;
    int choppaY = 55;
    bool right = true;

    bool bridge_full = false;
    pthread_mutex_t bridge_lock;
    pthread_mutex_init(&bridge_lock, NULL);
    //choppa initial info

    //GET THE CHOPPA
    RectangleObject choppa(choppaX, choppaY, 100, 50, "assets/helicopter.png");

    //cannon preparation
    cannonBombJunction fuseOld0 = {.hasAmmo = false, .bombOutOfBound = false, .cannonX = 0, .cannonY = 0};
    cannonBombJunction fuseNew0 = {.hasAmmo = false, .bombOutOfBound = false, .cannonX = 0, .cannonY = 0};

    cannonBombJunction fuseOld1 = {.hasAmmo = false, .bombOutOfBound = false, .cannonX = 0, .cannonY = 0} ;   
    cannonBombJunction fuseNew1 = {.hasAmmo = false, .bombOutOfBound = false, .cannonX = 0, .cannonY = 0};


    sem_t bomb0_sem0, bomb0_sem1;
    sem_t bomb1_sem0, bomb1_sem1;
    sem_init(&bomb0_sem0, 0, 0);
    sem_init(&bomb0_sem1, 0, 0);
    sem_init(&bomb1_sem0, 0, 0);
    sem_init(&bomb1_sem1, 0, 0);
    BombObject bomb0(400, -100, 15, 15, 0, 0, &bomb0_sem0, &bomb0_sem1, &fuseNew0, &fuseNew0, &loop, &bridge_lock);
    BombObject bomb1(400, -100, 15, 15, 0, 0, &bomb1_sem0, &bomb1_sem1, &fuseNew1, &fuseNew1, &loop, &bridge_lock);

    

    sem_t cannon0_sem0, cannon0_sem1;
    sem_init(&cannon0_sem0, 0, 0);
    sem_init(&cannon0_sem1, 0, 0);
    CannonObject cannon0(200, 500, 50, 50, max_ammo_const, reload_time_const, &cannon0_sem0, &cannon0_sem1, &bomb0, &loop, &fuseOld0, &fuseNew0, &bridge_lock, &bridge_full);
    

    sem_t cannon1_sem0, cannon1_sem1;
    sem_init(&cannon1_sem0, 0, 0);
    sem_init(&cannon1_sem1, 0, 0);
    CannonObject cannon1(300, 500, 50, 50, max_ammo_const, reload_time_const, &cannon1_sem0, &cannon1_sem1, &bomb1, &loop, &fuseOld1, &fuseNew1, &bridge_lock, &bridge_full);
    
    RectangleObject hospital(690, 210, 100, 350, "assets/hospital.png");
    RectangleObject ruin(0, 210, 100, 350, "assets/burnt building.png");
    RectangleObject background(0, 0, 800, 600, "assets/bkground.png");
    RectangleObject road(0, 550, 800, 50, "assets/road.png");
    RectangleObject ammo_storage(50, 500, 100, 50, "assets/ammo_storage.png");
    RectangleObject explosion(-200, -200, 150, 150, "assets/explosion.png");

    pthread_t cannon0_thread;
    pthread_create(&cannon0_thread, NULL, &cannonLoop, (void*) &cannon0);

    pthread_t cannon1_thread;
    pthread_create(&cannon1_thread, NULL, &cannonLoop, (void*) &cannon1);

    
    pthread_t bomb0_thread;
    pthread_create(&bomb0_thread, NULL, &bombLoop, (void*) &bomb0);
    
    pthread_t bomb1_thread;
    pthread_create(&bomb1_thread, NULL, &bombLoop, (void*) &bomb1);


    //GAME LOOP
    while (loop) {
    al_wait_for_event(queue, &event);
        if (pressed_keys[ALLEGRO_KEY_DOWN]) { //baixo
            choppa.move(0, 5);
        }
        if (pressed_keys[ALLEGRO_KEY_UP]) { //cima
            choppa.move(0, -5);
        }
        if (pressed_keys[ALLEGRO_KEY_LEFT]) {
            choppa.move(-5, 0);
        }
        if (pressed_keys[ALLEGRO_KEY_RIGHT]) {
            choppa.move(5, 0);
        }
    

    switch (event.type) {
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        loop = false;
        break;
    case ALLEGRO_EVENT_KEY_DOWN:
        pressed_keys[event.keyboard.keycode] = true;
        if (pressed_keys[ALLEGRO_KEY_ESCAPE]) {
            loop = false;
        }
        break;
    case ALLEGRO_EVENT_KEY_UP:
        pressed_keys[event.keyboard.keycode] = false;
        break;
    case ALLEGRO_EVENT_TIMER:
        redraw = true;
        break;
    }


    if ((choppa.x < ruin.x + ruin.width) && (choppa.y > ruin.y - 80) && hostages_onboard == 0 && hostages_count > 0) {
        hostages_onboard = 1;
        hostages_count--;  // Decrease the hostage count when a hostage is picked up
    }

    if ((choppa.x > hospital.x) && (choppa.y > hospital.y - 80) && hostages_onboard > 0) {
        hostages_onboard = 0;  // No hostages onboard after dropping off
    }


    if (redraw && al_is_event_queue_empty(queue)) {

        background.render();
        hospital.render();
        ruin.render();
        road.render();
        ammo_storage.render();
        render_info(display, hostages_count, hostages_onboard);
        choppa.render();


        sem_post(&cannon0_sem0);
        sem_post(&cannon1_sem0);
        sem_post(&bomb0_sem0);
        sem_post(&bomb1_sem0);


        sem_wait(&cannon0_sem1);
        sem_wait(&cannon1_sem1);
        sem_wait(&bomb0_sem1);
        sem_wait(&bomb1_sem1);
        
        //FLIPPING FUSES FROM CANNON 0 
        cannonBombJunction flipper {
            .hasAmmo = fuseOld0.hasAmmo,
            .bombOutOfBound = fuseOld0.bombOutOfBound,
            .cannonX = fuseOld0.cannonX,
            .cannonY = fuseOld0.cannonY
        };

        fuseOld0.hasAmmo = fuseNew0.hasAmmo;
        fuseOld0.bombOutOfBound = fuseNew0.bombOutOfBound;
        fuseOld0.cannonX = fuseNew0.cannonX;
        fuseOld0.cannonY = fuseNew0.cannonY;

        fuseNew0.hasAmmo = flipper.hasAmmo;
        fuseNew0.bombOutOfBound = flipper.bombOutOfBound;
        fuseNew0.cannonX = flipper.cannonX;
        fuseNew0.cannonY = flipper.cannonY;

        // FLIPPING FUSES FROM CANNON 1
        flipper.hasAmmo = fuseOld1.hasAmmo;
        flipper.bombOutOfBound = fuseOld1.bombOutOfBound;
        flipper.cannonX = fuseOld1.cannonX;
        flipper.cannonY = fuseOld1.cannonY;

        fuseOld1.hasAmmo = fuseNew1.hasAmmo;
        fuseOld1.bombOutOfBound = fuseNew1.bombOutOfBound;
        fuseOld1.cannonX = fuseNew1.cannonX;
        fuseOld1.cannonY = fuseNew1.cannonY;

        fuseNew1.hasAmmo = flipper.hasAmmo;
        fuseNew1.bombOutOfBound = flipper.bombOutOfBound;
        fuseNew1.cannonX = flipper.cannonX;
        fuseNew1.cannonY = flipper.cannonY;


        cannon0.render();
        cannon0.render_bomb_count(display);  // Adjusted the y coordinate
        bomb0.render();
        
        cannon1.render();
        cannon1.render_bomb_count(display);  // Adjusted the y coordinate
        bomb1.render();


        if (choppa.isColided(road) || choppa.isColided(cannon0) || choppa.isColided(cannon1) || choppa.isColided(hospital) || 
                choppa.isColided(ruin) || choppa.isColided(bomb0)|| choppa.isColided(bomb1) || choppa.isColided(ammo_storage)
                || choppa.y < 0) {
                explosion.setPosition(choppa.x-40, choppa.y-20);
                explosion.render();
                
                fprintf(stderr, "colided!\n");
        }

        
        al_flip_display();


        redraw = false;
    }
    //entre um frame e um ciclo de jogo
    
}

    sem_post(&cannon0_sem0);
    sem_post(&cannon1_sem0);
    sem_post(&bomb0_sem0);
    sem_post(&bomb1_sem0);
    pthread_join(cannon0_thread, NULL);
    pthread_join(cannon1_thread, NULL);
    pthread_join(bomb0_thread, NULL);
    pthread_join(bomb1_thread, NULL);
    pthread_mutex_destroy(&bridge_lock);
    sem_destroy(&cannon0_sem0);
    sem_destroy(&cannon0_sem1);
    sem_destroy(&cannon1_sem0);
    sem_destroy(&cannon1_sem1);
    sem_destroy(&bomb0_sem0);
    sem_destroy(&bomb0_sem1);
    sem_destroy(&bomb1_sem0);
    sem_destroy(&bomb1_sem1);


    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_shutdown_font_addon();


    return 0;
}
