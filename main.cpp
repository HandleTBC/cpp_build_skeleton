#include <iostream>
#include <array>
#include <vector>

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


    std::cout << std::endl;
    std::cout << "Playing with the Spatial Hasher...." << std::endl;

    std::vector<std::array<double, 3>> points;
    size_t grid_size = 10;
    for (double ii = 0; ii < grid_size; ++ii) {
        for (double jj = 0; jj < grid_size; ++jj) {
            for (double kk = 0; kk < grid_size; ++kk) {
                points.push_back({ii, jj, kk});
            }
        }
    }

    std::vector<size_t> indices;
    indices.reserve(points.size());
    for (size_t ii = 0; ii < points.size(); ++ii) {
        indices.push_back(ii);
    }

    double cell_length = 2.0;


    SpatialHashing<size_t> map(2);
    map.set_data(
        points,
        indices,
        cell_length
    );

    std::vector<size_t> indices_returned = map.lookup_by_point_risky(points[0]);
    std::cout << "Size of indices_returned: " << indices_returned.size() << std::endl;



    indices_returned = map.lookup_by_point_distance_risky(points[0], 5.0);
    std::cout << "Size of indices_returned: " << indices_returned.size() << std::endl;


    return 0;
}