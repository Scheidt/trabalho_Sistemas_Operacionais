#include "main.hpp"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

int hostages_count = 0;
int bomb_count = 5;

struct Bomb {
    float x;
    float y;
    float vy;  // vertical velocity
    bool active;  // is the bomb currently moving?
} bomb;

struct Explosion {
    float x;
    float y;
    bool active;
} explosion;

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
    // Random number seed
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

    bomb = {200, 500, -5.0f, true};
    explosion = {0, 0, false};

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
    RectangleObject cannon0(200, 500, 50, 50, "assets/cannon.png");
    RectangleObject cannon1(300, 500, 50, 50, "assets/cannon.png");
    RectangleObject hospital(690, 210, 100, 350, "assets/hospital.png");
    RectangleObject ruin(0, 210, 100, 350, "assets/burnt building.png");
    RectangleObject background(0, 0, 800, 600, "assets/bkground.png");
    RectangleObject road(0, 550, 800, 50, "assets/road.png");
    RectangleObject bomba(200, 500, 15, 15, "assets/bomb.png");

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

        if (bomb.active) {
            bomba.move(0, bomb.vy);
            bomb.y += bomb.vy;

            if (bomb.y <= 0 || choppa.isColided(bomba)) {
                bomb_count--;

                bomb.active = false;
                explosion.active = true;
                explosion.x = bomb.x;
                explosion.y = bomb.y;
                last_explosion_time = al_get_time();
            }
        }

        if (!bomb.active && !explosion.active && bomb_count > 0) {
            bomb = {200, 500, -5.0f, true};
            bomba.setPosition(bomb.x, bomb.y);  // Ensure bomba's position is reset
        }

        if (explosion.active && al_get_time() - last_explosion_time >= 1.0) {
            explosion.active = false;
        }

        background.render();
        hospital.render();
        ruin.render();
        road.render();

        choppa.render();
        cannon0.render();
        cannon1.render();

        if (bomb.active) {
            bomba.render();
        }
        if (explosion.active) {
            render_explosion(display, explosion.x, explosion.y);
        }

        render_bomb_count(display, bomb_count);

        al_flip_display();

        if (choppa.isColided(road) || choppa.isColided(cannon0) || choppa.isColided(cannon1) || choppa.isColided(hospital) || choppa.isColided(ruin) || choppa.isColided(bomba))  {
            break;
        }

        redraw = false;
    }
}


    if (explosion_image) {
        al_destroy_bitmap(explosion_image);
    }
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_shutdown_font_addon();

    return 0;
}
