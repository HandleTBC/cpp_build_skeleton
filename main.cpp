#include <iostream>

#include "spatial_hashing.h"

int main() {
    std::cout << "Hi from Spatial Accelerator test code." << std::endl;

    double x_length = 3.0;
    double x_cell_length = 1.0;

    int cell_id = 0;

    cell_id = 0.0 / x_cell_length;
    std::cout << "In: 0.0, result cell id: " << cell_id << std::endl;
    cell_id = 0.5 / x_cell_length;
    std::cout << "In: 0.5, result cell id: " << cell_id << std::endl;
    cell_id = 2.7 / x_cell_length;
    std::cout << "In: 2.7, result cell id: " << cell_id << std::endl;
    cell_id = 3.0 / x_cell_length;
    std::cout << "In: 3.0, result cell id: " << cell_id << std::endl;


    BoundingBox bounds;
    bounds.points.min = {1, 1, 1};
    bounds.points.max = {2, 2, 2};
    std::cout << "bounds.components.min_y: " << bounds.components.min_y << std::endl;
    std::cout << "bounds.components.max_y: " << bounds.components.max_y << std::endl;


    return 0;
}