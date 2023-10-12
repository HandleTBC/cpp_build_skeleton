#include <vector>
#include <array>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include <algorithm>

#include "bounding_box.h"

void print_point(const std::array<double, 3>& point) {
    std::cout << "x: " << point[0]
              << ", y: " << point[0]
              << ", z: " << point[0]
              << std::endl;
}

struct CellData {
    size_t n_occupied;
    size_t n_allocated;
};

template<typename T_datatype>
class SpatialHashing {
public:
    SpatialHashing(const size_t cell_reserve_size)
    : _cell_reserve_size(cell_reserve_size)
    {}

    void set_data(
        const std::vector<std::array<double, 3>>& points,
        const std::vector<T_datatype>& values,
        const double cell_length
    ) {
        assert(points.size() >= 1);
        assert(points.size() == values.size());

        _cell_length = cell_length;

        size_t n_points = points.size();

        _bounds = get_points_bounds(points);

        // +1 guarantees there is a cell for the case where point is at upper bound.
        _n_x_cells = (_bounds.components.max_x - _bounds.components.min_x) / _cell_length + 1;
        _n_y_cells = (_bounds.components.max_y - _bounds.components.min_y) / _cell_length + 1;
        _n_z_cells = (_bounds.components.max_z - _bounds.components.min_z) / _cell_length + 1;

        // Allocate
        _n_cells = _n_x_cells * _n_y_cells * _n_z_cells;
        allocate_hash_map(_n_cells);
        
        // Insert
        for (size_t ii = 0; ii < n_points; ++ii) {
            insert_data_risky(
                points[ii][0],
                points[ii][1],
                points[ii][2],
                values[ii]
            );
        }
    }

    std::vector<T_datatype> lookup_by_point_risky(
        const std::array<double, 3> point
    ) {
        size_t cell_id = hash_risky(
            point[0],
            point[1],
            point[2]
        );

        std::vector<T_datatype> values;
        values.reserve(_cell_counts[cell_id]);
        std::vector<T_datatype>& cell = _map[cell_id];
        values.insert(
            values.end(),
            cell.begin(),
            cell.begin() + _cell_counts[cell_id]
        );

        return values;
    }
    
    std::vector<T_datatype> lookup_by_point_distance_risky(
        const std::array<double, 3> point,
        const double distance
    ) {
        std::array<double, 3> max_point = {
            point[0] + distance,
            point[1] + distance,
            point[1] + distance
        };
        std::cout << "max_point: ";
        print_point(max_point);
        std::cout << std::endl;

        if (max_point[0] > _bounds.components.max_x) {
            max_point[0] = _bounds.components.max_x;
        }
        if (max_point[1] > _bounds.components.max_y) {
            max_point[1] = _bounds.components.max_y;
        }
        if (max_point[2] > _bounds.components.max_z) {
            max_point[2] = _bounds.components.max_z;
        }
        std::cout << "max_point: ";
        print_point(max_point);
        std::cout << std::endl;

        std::array<double, 3> min_point = {
            point[0] - distance,
            point[1] - distance,
            point[1] - distance,
        };
        std::cout << "min_point: ";
        print_point(min_point);
        std::cout << std::endl;

        if (min_point[0] < _bounds.components.min_x) {
            min_point[0] = _bounds.components.min_x;
        }
        if (min_point[1] < _bounds.components.min_y) {
            min_point[1] = _bounds.components.min_y;
        }
        if (min_point[2] < _bounds.components.min_z) {
            min_point[2] = _bounds.components.min_z;
        }
        std::cout << "min_point: ";
        print_point(min_point);
        std::cout << std::endl;

        std::array<size_t, 3> max_xyz = hash_to_xyz_risky(
            max_point[0],
            max_point[1],
            max_point[2]
        );

        std::array<size_t, 3> min_xyz = hash_to_xyz_risky(
            min_point[0],
            min_point[1],
            min_point[2]
        );

        // There is probably a more efficient way to do this.
        size_t n_values = 0;
        size_t cell_id;
        for (size_t zz = min_xyz[2]; zz <= max_xyz[2]; ++zz) {
            for (size_t yy = min_xyz[1]; yy <= max_xyz[2]; ++yy) {
                for (size_t xx = min_xyz[0]; xx <= max_xyz[0]; ++ xx) {
                    cell_id = xx + 
                              yy * _n_y_cells +
                              zz * (_n_x_cells * _n_y_cells);
                    n_values += _cell_counts[cell_id];
                }
            }
        }

        std::vector<T_datatype> values;
        values.reserve(n_values);

        for (size_t zz = min_xyz[2]; zz <= max_xyz[2]; ++zz) {
            for (size_t yy = min_xyz[1]; yy <= max_xyz[2]; ++yy) {
                for (size_t xx = min_xyz[0]; xx <= max_xyz[0]; ++ xx) {
                    cell_id = xx + 
                              yy * _n_y_cells +
                              zz * (_n_x_cells * _n_y_cells);

                    std::vector<T_datatype>& cell = _map[cell_id];
                    
                    values.insert(
                        values.end(),
                        cell.begin(),
                        cell.begin() + _cell_counts[cell_id]
                    );
                }
            }
        }

        return values;
    }


private:
    size_t _cell_reserve_size;

    size_t _n_cells;
    size_t _n_x_cells;
    size_t _n_y_cells;
    size_t _n_z_cells;
    BoundingBox _bounds;
    double _cell_length;
    

    std::vector<size_t> _cell_counts;
    std::vector<std::vector<T_datatype>> _map;

    
    /**
     * @brief Standard Hash. Checks that point is within the existing hash map.
     * 
     * @param x_coord 
     * @param y_coord 
     * @param z_coord 
     * @return size_t 
     */
    size_t hash(
        const double x_coord,
        const double y_coord, 
        const double z_coord
    ) {
        if (
            out_of_bounds(
                x_coord,
                y_coord,
                z_coord,
                _bounds
            )
        ) {
            throw std::runtime_error(
                "ERROR: point to be hashed is outside of bounds!"
            );
        }

        size_t x_cell_id = (x_coord - _bounds.components.min_x) / _cell_length;
        size_t y_cell_id = (y_coord - _bounds.components.min_y) / _cell_length;
        size_t z_cell_id = (z_coord - _bounds.components.min_z) / _cell_length;

        return x_cell_id + 
               y_cell_id * _n_y_cells +
               z_cell_id * (_n_x_cells * _n_y_cells);
    }

    /**
     * @brief Risky Hash. Does not check for point being within bounds of
     current map. User must guarantee point is within bounds.
     * 
     * @param x_coord 
     * @param y_coord 
     * @param z_coord 
     * @return size_t 
     */
    size_t hash_risky(
        const double x_coord,
        const double y_coord, 
        const double z_coord
    ) {
        size_t x_cell_id = (x_coord - _bounds.components.min_x) / _cell_length;
        size_t y_cell_id = (y_coord - _bounds.components.min_y) / _cell_length;
        size_t z_cell_id = (z_coord - _bounds.components.min_z) / _cell_length;

        return x_cell_id + 
               y_cell_id * _n_y_cells +
               z_cell_id * (_n_x_cells * _n_y_cells);
    }

    std::array<size_t, 3> hash_to_xyz_risky(
        const double x_coord,
        const double y_coord, 
        const double z_coord
    ) {
        return {
            (x_coord - _bounds.components.min_x) / _cell_length,
            (y_coord - _bounds.components.min_y) / _cell_length,
            (z_coord - _bounds.components.min_z) / _cell_length
        };
    }

    void allocate_hash_map(size_t n_cells) {
        _cell_counts = std::vector<size_t>(n_cells, 0);
        _map = std::vector<std::vector<T_datatype>>(n_cells, std::vector<T_datatype>(_cell_reserve_size));
    }

    /**
     * @brief Inserts value at a position into _map. Uses risky hash function.
     * 
     * @param x_coord 
     * @param y_coord 
     * @param z_coord 
     * @param value 
     */
    void insert_data_risky(
        const double x_coord,
        const double y_coord, 
        const double z_coord,
        const T_datatype& value
    ) {
        size_t cell_id = hash_risky(x_coord, y_coord, z_coord);
        std::cout << cell_id << std::endl;

        std::vector<T_datatype>& cell = _map[cell_id];

        if (cell.size() == cell.capacity()) {
            cell.reserve(2 * cell.capacity());
        }

        cell[_cell_counts[cell_id]] = value;
        _cell_counts[cell_id] += 1;
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

    bool out_of_bounds(
        const double x_coord,
        const double y_coord,
        const double z_coord,
        const BoundingBox& bounds
    ) {
        if (
            x_coord < bounds.components.min_x ||
            x_coord > bounds.components.max_x ||
            y_coord < bounds.components.min_y ||
            y_coord > bounds.components.max_y ||
            z_coord < bounds.components.min_z ||
            z_coord > bounds.components.max_z
        ) {
            return true;
        } else {
            return false;
        }
    }

};