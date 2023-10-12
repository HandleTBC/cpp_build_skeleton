#include <vector>
#include <array>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include <algorithm>

#include "bounding_box.h"

struct CellData {
    size_t n_occupied;
    size_t n_allocated;
};

template<typename T_datatype>
class SpatialHashing {
    void set_data(const std::vector<std::array<double, 3>>& points, const std::vector<T_datatype>& data, double cell_length) {
        assert(points.size() >= 1);
        assert(points.size() == data.size());

        _cell_length = cell_length;

        size_t n_points = points.size();

        _bounds = get_points_bounds(points);

        // +1 guarantees there is a cell for the case where point is at upper bound.
        _n_x_cells = (_bounds.components.max_x - _bounds.components.min_x) / _cell_length + 1;
        _n_y_cells = (_bounds.components.max_y - _bounds.components.min_y) / _cell_length + 1;
        _n_z_cells = (_bounds.components.max_z - _bounds.components.min_z) / _cell_length + 1;






        // Allocate
        
        // Insert
        

    }

    void lookup_by_point() {

    }
    
    void lookup_by_point_distance() {

    }


private:
    size_t reserve_size = 5;

    size_t _n_total_cells;
    size_t _n_x_cells;
    size_t _n_y_cells;
    size_t _n_z_cells;
    double _x_length;
    double _y_length;
    double _z_length;
    BoundingBox _bounds;
    double _cell_length;
    

    std::vector<CellData> _cells_data;
    std::vector<std::vector<T_datatype>> _hash_map;

    // size_t hash(double x_coord, double y_coord, double z_coord) {
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

    //     size_t x_cell_id = (x_coord - _x_l_bound) / _x_cell_length;
    //     size_t y_cell_id = (y_coord - _y_l_bound) / _y_cell_length;
    //     size_t z_cell_id = (z_coord - _z_l_bound) / _z_cell_length;

    //     return x_cell_id + 
    //            y_cell_id * _n_y_cells +
    //            z_cell_id * (_n_x_cells * _n_y_cells);
    // }

    void allocate_hash_map() {
        
    }

    // Utils

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