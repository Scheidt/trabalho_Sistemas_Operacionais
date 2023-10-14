#include "main.hpp"

int main() {
    // Random number seed
    srand((unsigned int)time(NULL));
    const int width = WIDTH;
    const int height = HEIGHT;

    // Inicialize allegro lib
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
    /*if(!init_allegro()){
        return -1;
    }*/

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

    //Allegro - registering event sources
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    //User input variables
    bool pressed_keys[ALLEGRO_KEY_MAX] = {false};

    // Loop variables
    al_start_timer(timer);

    bool redraw = true;
    bool loop = true;

    while (loop){
        // Waiting for any event to happen (timer, keyboard, mouse, ext...)
        al_wait_for_event(queue, &event);

        // Processing diferent event types
        switch (event.type){
        case ALLEGRO_EVENT_DISPLAY_CLOSE: // apertou o x do display
            loop = false;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            pressed_keys[event.keyboard.keycode] = true;
            if(pressed_keys[ALLEGRO_KEY_ESCAPE]){
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
        // as setas são left, right, up, down
        // Executed each time event when as the last event
        if(redraw && al_is_event_queue_empty(queue)){
            // Dealing with pressed keys
            if(pressed_keys[ALLEGRO_KEY_DOWN]){
                
            }
            if(pressed_keys[ALLEGRO_KEY_UP]){
                
            }
            if(pressed_keys[ALLEGRO_KEY_LEFT]){
                
            }
            if(pressed_keys[ALLEGRO_KEY_RIGHT]){
                
            }

            // Clean buffer
            
            render_background(display);

            // Render Objects
            render_choppa(display, 200, 100.0, false); // Render the helicopter at (100, 100)
            render_cannon(display, 200, 500);
            render_bomb(display, 400, 300);
            render_ruin(display);
            render_hospital(display);
            render_road(display);

            al_flip_display(); // Flip the display to show the rendered image
            
            //restar counting
            redraw = false;
        }
    }

   //Destroing allegro events
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}