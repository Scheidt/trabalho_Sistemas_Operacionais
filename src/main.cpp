#include "main.hpp"

int main() {
    if (!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro!\n");
        return -1;
    }

    ALLEGRO_DISPLAY *display = al_create_display(800, 600);

    if (!display) {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }

    al_clear_to_color(al_map_rgb(0, 0, 0)); // Clear the screen to black

    
    render_background(display);
    render_choppa(display, 200, 100.0, false); // Render the helicopter at (100, 100)
    render_cannon(display, 200, 500);
    render_bomb(display, 400, 300);
    render_ruin(display);
    render_hospital(display);
    /*
    struct {
        x = 125
        y = 550
        width = 75
        hight = 50
    } bridge_position
    */
    render_road(display);

    al_flip_display(); // Flip the display to show the rendered image

    al_rest(15.0); // Display the image for 5 seconds

    al_destroy_display(display);

    return 0;
}