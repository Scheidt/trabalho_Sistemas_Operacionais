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
    
    if (!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro!\n");
        return -1;
    }

    if (!al_init_font_addon()) {
        fprintf(stderr, "Failed to initialize Allegro Font Addon!\n");
        return -1;
    }

    ALLEGRO_DISPLAY *display = al_create_display(800, 600);
    if (!display) {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }

    bomb = {200, 500, -5.0f, true};
    explosion = {0, 0, false};

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    double last_explosion_time = 0;

    al_install_mouse();

   while (true) {  
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            // Bomb movement logic
            if (bomb.active) {
                bomb.y += bomb.vy;

                // Bomb explosion logic
                if (bomb.y <= 0) {
                    bomb_count--;  // Decrease bomb count

                    bomb.active = false;
                    if (bomb_count > 0) {
                        explosion.active = true;
                        explosion.x = bomb.x;
                        explosion.y = bomb.y;
                        last_explosion_time = al_get_time();
                    }
                }
            }

            // Explosion timing logic
            if (explosion.active && al_get_time() - last_explosion_time >= 1.0) {
                explosion.active = false;
                if (bomb_count > 0) {
                    bomb.active = true;
                    bomb.x = 200;
                    bomb.y = 500;
                }
            }

            // Rendering logic
            al_clear_to_color(al_map_rgb(0, 0, 0));
            if (bomb.active) {
                render_bomb(display, bomb.x, bomb.y);
            }
            if (explosion.active) {
                render_explosion(display, explosion.x, explosion.y);
            }

            render_bomb_count(display, bomb_count);
            al_flip_display();
        }
    }


    // while (true) {  // Game loop
    //     ALLEGRO_EVENT ev;
    //     al_wait_for_event(event_queue, &ev);

    //   if (ev.type == ALLEGRO_EVENT_TIMER) {
    //     // std::cout << "Timer event fired at time: " << al_get_time() << std::endl;
    //         if (bomb.active) {
    //             bomb.y += bomb.vy;
    //             // std::cout << "Bomb Y Position: " << bomb.y << std::endl;
    //             //  std::cout << "Time: " << al_get_time() << " - Bomb Y Position: " << bomb.y << std::endl;

    //             if (bomb.y <= 0) {
    //                 bomb.active = false;
    //                 explosion.active = true;
    //                 explosion.x = bomb.x;
    //                 explosion.y = bomb.y;
    //                 last_explosion_time = al_get_time();
    //             }
    //         }

    //         if (explosion.active && al_get_time() - last_explosion_time >= 1.0) {
    //             explosion.active = false;
    //             bomb.active = true;  // Reactivate the bomb after the explosion ends
    //             bomb.x = 200;  // Reset the bomb's x position
    //             bomb.y = 500;  // Reset the bomb's y position
    //         }

    //         // Render everything
    //         al_clear_to_color(al_map_rgb(0, 0, 0));
    //         render_background(display);
    //         render_choppa(display, 200, 100.0, false);
    //         render_cannon(display, 200, 500);
    //         if (bomb.active) {
    //             render_bomb(display, bomb.x, bomb.y);
    //         }
    //        if (explosion.active) {
    //             render_explosion(display, explosion.x, explosion.y);
    //         }
    //         render_ruin(display);
    //         render_hospital(display);
    //         render_road(display);
    //         render_hostage_count(display, hostages_count);

    //         al_flip_display();
    //     }
    // }

    // Cleanup code
    if (explosion_image) {
        al_destroy_bitmap(explosion_image);
    }
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    al_shutdown_font_addon();

    

    return 0;
}


   
