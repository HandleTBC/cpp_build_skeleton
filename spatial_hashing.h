#include <vector>
#include <array>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include <algorithm>

#include "bounding_box.h"

struct CellData {
    int n_occupied;
    int n_allocated;
};

template<typename T_datatype>
class SpatialHashing {
    void add_data(const std::vector<std::array<double, 3>>& points, const std::vector<T_datatype>& data, double cell_length) {
        assert(points.size() >= 1);
        assert(points.size() == data.size());

        int n_points = points.size();

        _bounds = get_points_bounds(points);

        // _x_cell_length = cell_length;
        // _y_cell_length = cell_length;
        // _z_cell_length = cell_length;

        // // +1 guarantees there is a cell for the case where point is at upper bound.
        // _n_x_cells = (_x_u_bound - _x_l_bound) / _x_cell_length + 1;
        // _n_y_cells = (_y_u_bound - _y_l_bound) / _y_cell_length + 1;
        // _n_z_cells = (_z_u_bound - _z_l_bound) / _z_cell_length + 1;






        // Allocate
        
        // Insert
        

    }

    void lookup_by_point() {

    }
    
    void lookup_by_point_distance() {

    }


private:
    int reserve_size = 5;

    int _n_total_cells;
    int _n_x_cells;
    int _n_y_cells;
    int _n_z_cells;
    double _x_length;
    double _y_length;
    double _z_length;
    BoundingBox _bounds;
    double _x_cell_length;
    double _y_cell_length;
    double _z_cell_length;

    std::vector<CellData> _cells_data;
    std::vector<std::vector<T_datatype>> _hash_map;

    // int hash(double x_coord, double y_coord, double z_coord) {
    //     if (
    //         x_coord < _x_l_bound ||
    //         x_coord > _x_u_bound ||
    //         y_coord < _y_l_bound ||
    //         y_coord > _y_u_bound ||
    //         z_coord < _z_l_bound ||
    //         z_coord > _z_u_bound
    //     ) {
    //         throw std::runtime_error(
    //             "ERROR: point to be hashed is outside of bounds!"
    //         );
    //     }

    //     int x_cell_id = (x_coord - _x_l_bound) / _x_cell_length;
    //     int y_cell_id = (y_coord - _y_l_bound) / _y_cell_length;
    //     int z_cell_id = (z_coord - _z_l_bound) / _z_cell_length;

    //     return x_cell_id + 
    //            y_cell_id * _n_y_cells +
    //            z_cell_id * (_n_x_cells * _n_y_cells);
    // }

    void allocate_hash_map() {
        
    }

    // Utils

    double get_min_points_component(
        std::vector<std::array<double, 3>> points,
        size_t component
    ) {
        assert(component >=0 && component <= 2);

        size_t n_points = points.size();

        std::vector<double> points_component(n_points);
        for (size_t ii = 0; ii < n_points; ++ii) {
            points_component[ii] = points[ii][component];
        }

        auto min_it = std::min_element(
            points_component.begin(),
            points_component.end()
        );
        
        return *min_it;
    }

    BoundingBox get_points_bounds(
        const std::vector<std::array<double, 3>>& points
    ) {
        BoundingBox bounds;
        bounds.points.min = points[0];
        bounds.points.max = points[0];

        if (points.size() == 1) {
            return bounds;
        } else {
            for (size_t ii = 1; ii < points.size(); ++ii) {
                // min
                if (points[ii][0] < bounds.components.min_x) {
                    bounds.components.min_x = points[ii][0];
                }
                if (points[ii][1] < bounds.components.min_y) {
                    bounds.components.min_y = points[ii][1];
                }
                if (points[ii][2] < bounds.components.min_z) {
                    bounds.components.min_z = points[ii][2];
                }

                // max
                if (points[ii][0] > bounds.components.max_x) {
                    bounds.components.max_x = points[ii][0];
                }
                if (points[ii][1] > bounds.components.max_y) {
                    bounds.components.max_y = points[ii][1];
                }
                if (points[ii][2] > bounds.components.max_z) {
                    bounds.components.max_z = points[ii][2];
                }

            }

            return bounds;
        }
    }

};