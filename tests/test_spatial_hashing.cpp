#include <array>
#include <vector>

#include <gtest/gtest.h>

#include "spatial_hashing.h"

class SpatialHasherTest : public ::testing::Test {
protected:
    void SetUp() override {
        // set up points
        for (double ii = 0; ii < grid_size; ++ii) {
            for (double jj = 0; jj < grid_size; ++jj) {
                for (double kk = 0; kk < grid_size; ++kk) {
                    points.push_back({ii, jj, kk});
                }
            }
        }

        // set up indices
        indices.reserve(points.size());
            for (size_t ii = 0; ii < points.size(); ++ii) {
                indices.push_back(ii);
            }
    }

    size_t grid_size = 3;
    double cell_length = 1.0;
    std::vector<std::array<double, 3>> points;
    std::vector<size_t> indices;

};

TEST_F(SpatialHasherTest, lookup_by_point_risky) {
    SpatialHashing<size_t> map(2);
    map.set_data(
        points,
        indices,
        cell_length
    );

    std::vector<size_t> indices_returned;
    for (size_t ii = 0; ii < std::pow(grid_size, 3); ++ii) {
        indices_returned = map.lookup_by_point_risky(points[0]);
        EXPECT_EQ(indices_returned.size(), 1);
    }
}

TEST_F(SpatialHasherTest, lookup_by_point_distance_risky) {
    SpatialHashing<size_t> map(2);
    map.set_data(
        points,
        indices,
        cell_length
    );

    for (size_t ii = 0; ii < std::pow(grid_size, 3); ++ii) {
        std::vector<size_t> indices_returned = map.lookup_by_point_risky(points[0]);
        EXPECT_EQ(indices_returned.size(), 1);
    }

    std::vector<size_t> indices_returned;

    indices_returned = map.lookup_by_point_distance_risky(points[0], 0.9);
    EXPECT_EQ(indices_returned.size(), 1);

    indices_returned = map.lookup_by_point_distance_risky(points[0], 1.0);
    EXPECT_EQ(indices_returned.size(), 8);

    indices_returned = map.lookup_by_point_distance_risky(points[0], 2.0);
    EXPECT_EQ(indices_returned.size(), 27);

    indices_returned = map.lookup_by_point_distance_risky(points[0], 5.0);
    EXPECT_EQ(indices_returned.size(), 27);
}