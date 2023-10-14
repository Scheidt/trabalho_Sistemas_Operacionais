#include "objects.hpp"

// Abstract class definition
class RectangleObject {
public:
    int x;
    int y;
    int width;
    int height;

    // Constructor
    RectangleObject(int initialX, int initialY, int initialWidth, int initialHeight)
        : x(initialX), y(initialY), width(initialWidth), height(initialHeight) {}

};

// Concrete class that derives from RectangleObject
class ObjectChoppa : public RectangleObject {
public:
    ObjectChoppa()
        : RectangleObject(200, 100, choppa_width, choppa_height) {}
    char* source = "assets/choppa.png";

    // Implementation of the spawn method
    void move(int newX, int newY, bool right) {
        x = newX;
        y = newY;
    }
};

class ObjectCannon : public RectangleObject {
public:
    int ammo = max_ammo;
    float reload_time = reload_time;
    ObjectCannon()
        : RectangleObject(0, 0, cannon_width, cannon_height) {}
    char* source = "assets/cannon.png";

    // Implementation of the spawn method
    void move(int newX, int newY) {
        x = newX;
        y = newY;
    }
};

class ObjectBomb : public RectangleObject {
public:
    ObjectBomb(int x, int y)
        : RectangleObject(x, y, bomb_width, bomb_height) {}
    char* source = "assets/bomb.png";

    // Implementation of the spawn method
    void move(int newX, int newY) {
        x = newX;
        y = newY;
    }
};

class ObjectRuin : public RectangleObject {
public:
    ObjectRuin()
        : RectangleObject(ruinX, buildingY, building_width, building_height) {}
    char* source = "assets/burnt building.png";

    // Implementation of the spawn method
    void spawn() {
        render_object(display, )
    }
};

class ObjectHospital : public RectangleObject {
public:
    ObjectHospital()
        : RectangleObject(hospitalX, buildingY, building_width, building_height) {}
    char* source = "assets/hospital.png";

    // Implementation of the spawn method
    void spawn() {
    }
};

class ObjectRoad : public RectangleObject {
public:
    ObjectRoad()
        : RectangleObject(roadX, roadY, road_width, road_heigth) {}
    char* source = "assets/road.png";

    // Implementation of the spawn method
    void spawn() {
    }
};

class ObjectBackground : public RectangleObject {
public:
    ObjectBackground()
        : RectangleObject(backgroundX, backgroundY, background_width, background_height) {}
    char* source = "assets/bkground.png";
    // Implementation of the spawn method
    void spawn() {

    }
};



//road
//background