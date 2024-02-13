#include <gtest/gtest.h>
#include "../src/color.hpp"
#include "../src/canvas.hpp"

TEST(Canvas, Init) {
    Nyx::Canvas can = Nyx::Canvas{10, 20};
    EXPECT_EQ(can.width, 10);
    EXPECT_EQ(can.height, 20);
    for (int i = 0; i < can.width; i++) {
        for (int j = 0; j < can.height; j++) {
            EXPECT_EQ(can(i, j), (Nyx::Color{0.f, 0.f, 0.f}));
        }
    }
}

TEST(Canvas, ReadWritePixel) {
    Nyx::Canvas can = Nyx::Canvas{10, 20};
    Nyx::Color red = Nyx::Color{1.f, 0.f, 0.f};
    Nyx::Color blue = Nyx::Color{0.f, 0.f, 1.f};

    can.write_pixel(2, 3, red);
    can.write_pixel(2, 4, blue);
    can(5, 3) = red;
    can(5, 4) = blue;

    for (int i = 0; i < can.width; i++) {
        for (int j = 0; j < can.height; j++) {
            if (i == 2 && j == 3) {
                EXPECT_EQ(can(i, j), red);
            } else if (i == 2 && j == 4) {
                EXPECT_EQ(can(i, j), blue);
            } else if (i == 5 && j == 3) {
                EXPECT_EQ(can(i, j), red);
            } else if (i == 5 && j == 4) {
                EXPECT_EQ(can(i, j), blue);
            } else {
                EXPECT_EQ(can(i, j), (Nyx::Color{0.f, 0.f, 0.f}));
            }
        }
    }

    EXPECT_EQ(can.pixel_at(2, 4), blue);
    EXPECT_EQ(can.pixel_at(2, 3), red);
}