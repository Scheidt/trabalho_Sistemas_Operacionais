#include "main.hpp"

int main(){
    hello();

    ALLEGRO_DISPLAY *display = NULL;

    if (!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro!\n");
        return -1;
    }

    if (!al_init_image_addon()) {
        fprintf(stderr, "Failed to initialize Allegro Image addon!\n");
        return -1;
    }

    display = al_create_display(800, 600);
    if (!display) {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }

    al_clear_to_color(al_map_rgb(0, 0, 0)); // Clear the screen to black

    #ifdef OS_WINDOWS
        ALLEGRO_BITMAP *image = al_load_bitmap("assets\image.jpg"); // Load your image file
    #endif
    #ifdef OS_LINUX
        ALLEGRO_BITMAP *image = al_load_bitmap("assets/image.jpg"); // Load your image file
    #endif

    if (!image) {
        fprintf(stderr, "Failed to load image!\n");
        return -1;
    }
    
    al_draw_bitmap(image, 0, 0, 0); // Draw the image at position (0,0)

    al_flip_display(); // Flip the display to show the image
    al_rest(5.0); // Display the image for 5 seconds
    al_destroy_bitmap(image);
    al_destroy_display(display);

    return 0;
}