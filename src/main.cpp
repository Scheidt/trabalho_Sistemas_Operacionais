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

        if(redraw && al_is_event_queue_empty(queue)){ // Render stuff
            // Dealing with user input
            if(pressed_keys[ALLEGRO_KEY_DOWN]){
                choppa.move(0, 5);
            }
            if(pressed_keys[ALLEGRO_KEY_UP]){
                choppa.move(0, -5);
            }
            if(pressed_keys[ALLEGRO_KEY_LEFT]){
                choppa.move(-5, 0);
            }
            if(pressed_keys[ALLEGRO_KEY_RIGHT]){
                choppa.move(5, 0);
            }

            // Clean buffer
            
            background.render();
            hospital.render();
            ruin.render();
            road.render();

            // Render Objects
            choppa.render();
            cannon0.render();
            cannon1.render();

            al_flip_display(); // Flip the display to show the rendered image
            if (choppa.isColided(road) || choppa.isColided(cannon0) || choppa.isColided(cannon1) || choppa.isColided(hospital) || choppa.isColided(ruin)){
                break;
            }


            //restart counting
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