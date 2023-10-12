#ifndef BOUDNING_BOX_H_
#define BOUDNING_BOX_H_

#include <array>

struct Points {
    std::array<double, 3> min;
    std::array<double, 3> max;
};

struct Components {
    double min_x;
    double min_y;
    double min_z;
    double max_x;
    double max_y;
    double max_z;
};

union BoundingBox {
    Points points;
    Components components;
};

#endif