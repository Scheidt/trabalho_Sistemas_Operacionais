#include "main.hpp"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

const int hostages_count = 0;
int bomb_count = 5;
const int max_ammo_const = 3;
const float reload_time_const = 1/10;
int vel0X = 0;
int vel0Y = 0;
int vel1X = 0;
int vel1Y = 0;

ALLEGRO_BITMAP *explosion_image = nullptr;

void render_explosion(ALLEGRO_DISPLAY *display, float x, float y) {
    if (!explosion_image) {
        explosion_image = al_load_bitmap("assets/test square.png");
    }
    al_draw_bitmap(explosion_image, x, y, 0);
}

void render_bomb_count(ALLEGRO_DISPLAY *display, int bomb_count) {
    ALLEGRO_FONT *font = al_create_builtin_font();
    al_draw_textf(font, al_map_rgb(255, 255, 255), 50, 50, ALLEGRO_ALIGN_LEFT, "Bombs: %d", bomb_count);
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
    RectangleObject choppa(55, 55, 100, 50, "assets/helicopter.png");
    CannonObject cannon0(200, 500, 50, 50, max_ammo_const, reload_time_const);
    CannonObject cannon1(300, 500, 50, 50, max_ammo_const, reload_time_const);
    RectangleObject hospital(690, 210, 100, 350, "assets/hospital.png");
    RectangleObject ruin(0, 210, 100, 350, "assets/burnt building.png");
    RectangleObject background(0, 0, 800, 600, "assets/bkground.png");
    RectangleObject road(0, 550, 800, 50, "assets/road.png");
    RectangleObject bomba0(400, -100, 15, 15, "assets/bomb.png");
    RectangleObject bomba1(400, -100, 15, 15, "assets/bomb.png");
    RectangleObject ammo_storage(50, 500, 100, 50, "assets/ammo_storage.png");

    while (loop) {
    al_wait_for_event(queue, &event);

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

    if (redraw && al_is_event_queue_empty(queue)) {
        if (pressed_keys[ALLEGRO_KEY_DOWN]) {
            choppa.move(0, 5);
        }
        if (pressed_keys[ALLEGRO_KEY_UP]) {
            choppa.move(0, -5);
        }
        if (pressed_keys[ALLEGRO_KEY_LEFT]) {
            choppa.move(-5, 0);
        }
        if (pressed_keys[ALLEGRO_KEY_RIGHT]) {
            choppa.move(5, 0);
        }

        background.render();
        hospital.render();
        ruin.render();
        road.render();
        ammo_storage.render();

        choppa.render();

        // CANHÇAO 0
        std::pair<int, int> vel_vectors0 = cannon0.update();
        cannon0.render();

        // Access the individual values using .first and .second
        if ((bomba0.y >= 0) || (vel_vectors0.second == 0)) {
            // Se a bomba ainda está na tela ou se ela não receber uma velocidade Y
        } else if (bomba0.y < 0 && vel_vectors0.second != 0){ //Se a bomba está fora da tela e receber uma velocidade diferente de zero
            vel0X = vel_vectors0.first;
            vel0Y = vel_vectors0.second;
            fprintf(stderr, "boom!\n");
            bomba0.setPosition(((cannon0.x)+25), 450);
            cannon0.reduceAmmo();
        }
        bomba0.move(vel0X, vel0Y);
        bomba0.render();

        //CANHÃO 1
        std::pair<int, int> vel_vectors1 = cannon1.update();
        cannon1.render();

        // Access the individual values using .first and .second
        if ((bomba1.y >= 0) || (vel_vectors1.second == 0)) {
            // Se a bomba ainda está na tela ou se ela não receber uma velocidade Y
        } else if (bomba1.y < 0 && vel_vectors1.second != 0){ //Se a bomba está fora da tela e receber uma velocidade diferente de zero
            vel1X = vel_vectors1.first;
            vel1Y = vel_vectors1.second;
            fprintf(stderr, "boom!\n");
            bomba1.setPosition(((cannon1.x)+25), 450);
            cannon1.reduceAmmo();
        }
        bomba1.move(vel0X, vel0Y);
        bomba1.render();

       if (choppa.isColided(road) || choppa.isColided(cannon0) || choppa.isColided(cannon1) || choppa.isColided(hospital) || 
            choppa.isColided(ruin) || choppa.isColided(bomba0)|| choppa.isColided(ammo_storage))  {
            fprintf(stderr, "colided!\n");
            break;
        }


        render_bomb_count(display, cannon0.ammo);
        al_flip_display();

        redraw = false;
    }
}



    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_shutdown_font_addon();

    return 0;
}
