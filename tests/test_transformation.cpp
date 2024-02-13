#include <gtest/gtest.h>
#include "../src/transformation.hpp"

#include "../src/matrix.hpp"
#include "../src/tuple.hpp"

TEST(Transformation, TranslationPoint) {
    Nyx::Matrix<4> transform = Nyx::Transformation::translation(5, -3, 2);
    Nyx::Tuple p = Nyx::Point(-3, 4, 5);
    Nyx::Tuple p2 = transform * p;
    EXPECT_EQ(p2, Nyx::Point(2, 1, 7));

    Nyx::Matrix<4> transformInv = transform.inverse();
    Nyx::Tuple p3 = transformInv * p;
    EXPECT_EQ(p3, Nyx::Point(-8, 7, 3));    
}

TEST(Transformation, TranslationIgnoreVector) {
    Nyx::Matrix<4> transform = Nyx::Transformation::translation(5, -3, 2);
    Nyx::Tuple v = Nyx::Vector(-3, 4, 5);
    Nyx::Tuple v2 = transform * v;
    EXPECT_EQ(v2, v);
}

TEST(Transformation, ScalingPoint) {
    Nyx::Matrix<4> transform = Nyx::Transformation::scaling(2, 3, 4);
    Nyx::Tuple p = Nyx::Point(-4, 6, 8);
    Nyx::Tuple p2 = transform * p;
    EXPECT_EQ(p2, Nyx::Point(-8, 18, 32));

    Nyx::Matrix<4> transformInv = transform.inverse();
    Nyx::Tuple p3 = transformInv * p;
    EXPECT_EQ(p3, Nyx::Point(-2, 2, 2));
}

TEST(Transformation, ScalingVector) {
    Nyx::Matrix<4> transform = Nyx::Transformation::scaling(2, 3, 4);
    Nyx::Tuple v = Nyx::Vector(-4, 6, 8);
    Nyx::Tuple v2 = transform * v;
    EXPECT_EQ(v2, Nyx::Vector(-8, 18, 32));
}

TEST(Transformation, ReflectionX) {
    Nyx::Matrix<4> transform = Nyx::Transformation::scaling(-1, 1, 1);
    Nyx::Tuple p = Nyx::Point(2, 3, 4);
    Nyx::Tuple p2 = transform * p;
    EXPECT_EQ(p2, Nyx::Point(-2, 3, 4));
}

TEST(Transformation, ReflectionY) {
    Nyx::Matrix<4> transform = Nyx::Transformation::scaling(1, -1, 1);
    Nyx::Tuple p = Nyx::Point(2, 3, 4);
    Nyx::Tuple p2 = transform * p;
    EXPECT_EQ(p2, Nyx::Point(2, -3, 4));
}

TEST(Transformation, ReflectionZ) {
    Nyx::Matrix<4> transform = Nyx::Transformation::scaling(1, 1, -1);
    Nyx::Tuple p = Nyx::Point(2, 3, 4);
    Nyx::Tuple p2 = transform * p;
    EXPECT_EQ(p2, Nyx::Point(2, 3, -4));
}

TEST(Transformation, RotationX) {
    Nyx::Tuple p = Nyx::Point(0, 1, 0);
    Nyx::Matrix<4> halfQuarter = Nyx::Transformation::rotationX(M_PI / 4);
    Nyx::Matrix<4> fullQuarter = Nyx::Transformation::rotationX(M_PI / 2);
    Nyx::Tuple p2 = halfQuarter * p;
    Nyx::Tuple p3 = fullQuarter * p;
    EXPECT_EQ(p2, Nyx::Point(0, std::sqrt(2) / 2, std::sqrt(2) / 2));
    EXPECT_EQ(p3, Nyx::Point(0, 0, 1));
}

TEST(Transformation, RotationXInverse) {
    Nyx::Tuple p = Nyx::Point(0, 1, 0);
    Nyx::Matrix<4> halfQuarter = Nyx::Transformation::rotationX(M_PI / 4);
    Nyx::Matrix<4> halfQuarterInv = halfQuarter.inverse();
    Nyx::Tuple p2 = halfQuarterInv * p;
    EXPECT_EQ(p2, Nyx::Point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2));
}

TEST(Transformation, RotationY) {
    Nyx::Tuple p = Nyx::Point(0, 0, 1);
    Nyx::Matrix<4> halfQuarter = Nyx::Transformation::rotationY(M_PI / 4);
    Nyx::Matrix<4> fullQuarter = Nyx::Transformation::rotationY(M_PI / 2);
    Nyx::Tuple p2 = halfQuarter * p;
    Nyx::Tuple p3 = fullQuarter * p;
    EXPECT_EQ(p2, Nyx::Point(std::sqrt(2) / 2, 0, std::sqrt(2) / 2));
    EXPECT_EQ(p3, Nyx::Point(1, 0, 0));
}

TEST(Transformation, RotationZ) {
    Nyx::Tuple p = Nyx::Point(0, 1, 0);
    Nyx::Matrix<4> halfQuarter = Nyx::Transformation::rotationZ(M_PI / 4);
    Nyx::Matrix<4> fullQuarter = Nyx::Transformation::rotationZ(M_PI / 2);
    Nyx::Tuple p2 = halfQuarter * p;
    Nyx::Tuple p3 = fullQuarter * p;
    EXPECT_EQ(p2, Nyx::Point(-std::sqrt(2) / 2, std::sqrt(2) / 2, 0));
    EXPECT_EQ(p3, Nyx::Point(-1, 0, 0));
}

TEST(Transformation, ShearingXY) {
    Nyx::Matrix<4> transform = Nyx::Transformation::shearing(1, 0, 0, 0, 0, 0);
    Nyx::Tuple p = Nyx::Point(2, 3, 4);
    Nyx::Tuple p2 = transform * p;
    EXPECT_EQ(p2, Nyx::Point(5, 3, 4));

    Nyx::Matrix<4> transform2 = Nyx::Transformation::shearing(2.5, 0, 0, 0, 0, 0);
    Nyx::Tuple p3 = transform2 * p;
    EXPECT_EQ(p3, Nyx::Point(9.5, 3, 4));
}

TEST(Transformation, ShearingXZ) {
    Nyx::Matrix<4> transform = Nyx::Transformation::shearing(0, 1, 0, 0, 0, 0);
    Nyx::Tuple p = Nyx::Point(2, 3, 4);
    Nyx::Tuple p2 = transform * p;
    EXPECT_EQ(p2, Nyx::Point(6, 3, 4));

    Nyx::Matrix<4> transform2 = Nyx::Transformation::shearing(0, 2.5, 0, 0, 0, 0);
    Nyx::Tuple p3 = transform2 * p;
    EXPECT_EQ(p3, Nyx::Point(12, 3, 4));
}

TEST(Transformation, ShearingYX) {
    Nyx::Matrix<4> transform = Nyx::Transformation::shearing(0, 0, 1, 0, 0, 0);
    Nyx::Tuple p = Nyx::Point(2, 3, 4);
    Nyx::Tuple p2 = transform * p;
    EXPECT_EQ(p2, Nyx::Point(2, 5, 4));

    Nyx::Matrix<4> transform2 = Nyx::Transformation::shearing(0, 0, 2.5, 0, 0, 0);
    Nyx::Tuple p3 = transform2 * p;
    EXPECT_EQ(p3, Nyx::Point(2, 8, 4));
}

TEST(Transformation, ShearingYZ) {
    Nyx::Matrix<4> transform = Nyx::Transformation::shearing(0, 0, 0, 1, 0, 0);
    Nyx::Tuple p = Nyx::Point(2, 3, 4);
    Nyx::Tuple p2 = transform * p;
    EXPECT_EQ(p2, Nyx::Point(2, 7, 4));

    Nyx::Matrix<4> transform2 = Nyx::Transformation::shearing(0, 0, 0, 2.5, 0, 0);
    Nyx::Tuple p3 = transform2 * p;
    EXPECT_EQ(p3, Nyx::Point(2, 13, 4));
}

TEST(Transformation, ShearingZX) {
    Nyx::Matrix<4> transform = Nyx::Transformation::shearing(0, 0, 0, 0, 1, 0);
    Nyx::Tuple p = Nyx::Point(2, 3, 4);
    Nyx::Tuple p2 = transform * p;
    EXPECT_EQ(p2, Nyx::Point(2, 3, 6));

    Nyx::Matrix<4> transform2 = Nyx::Transformation::shearing(0, 0, 0, 0, 2.5, 0);
    Nyx::Tuple p3 = transform2 * p;
    EXPECT_EQ(p3, Nyx::Point(2, 3, 9));
}

TEST(Transformation, ShearingZY) {
    Nyx::Matrix<4> transform = Nyx::Transformation::shearing(0, 0, 0, 0, 0, 1);
    Nyx::Tuple p = Nyx::Point(2, 3, 4);
    Nyx::Tuple p2 = transform * p;
    EXPECT_EQ(p2, Nyx::Point(2, 3, 7));

    Nyx::Matrix<4> transform2 = Nyx::Transformation::shearing(0, 0, 0, 0, 0, 2.5);
    Nyx::Tuple p3 = transform2 * p;
    EXPECT_EQ(p3, Nyx::Point(2, 3, 11.5));
}

TEST(Transformation, ShearingMix) {
    Nyx::Matrix<4> transform = Nyx::Transformation::shearing(1, 2, 3, 4, 5, 6);
    Nyx::Tuple p = Nyx::Point(2, 3, 4);
    Nyx::Tuple p2 = transform * p;
    EXPECT_EQ(p2, Nyx::Point(13, 25, 32));
}

TEST(Transformation, Sequence) {
    Nyx::Tuple p = Nyx::Point(1, 0, 1);
    Nyx::Matrix<4> A = Nyx::Transformation::rotationX(M_PI / 2);
    Nyx::Matrix<4> B = Nyx::Transformation::scaling(5, 5, 5);
    Nyx::Matrix<4> C = Nyx::Transformation::translation(10, 5, 7);

    Nyx::Tuple p2 = A * p;
    EXPECT_EQ(p2, Nyx::Point(1, -1, 0));

    Nyx::Tuple p3 = B * p2;
    EXPECT_EQ(p3, Nyx::Point(5, -5, 0));

    Nyx::Tuple p4 = C * p3;
    EXPECT_EQ(p4, Nyx::Point(15, 0, 7));
}

TEST(Transformation, Chained) {
    Nyx::Tuple p = Nyx::Point(1, 0, 1);
    Nyx::Matrix<4> A = Nyx::Transformation::rotationX(M_PI / 2);
    Nyx::Matrix<4> B = Nyx::Transformation::scaling(5, 5, 5);
    Nyx::Matrix<4> C = Nyx::Transformation::translation(10, 5, 7);

    Nyx::Matrix<4> T = C * B * A;
    Nyx::Tuple p2 = T * p;
    EXPECT_EQ(p2, Nyx::Point(15, 0, 7));
}

TEST(Transformation, Fluid) {
    Nyx::Tuple p = Nyx::Point(1, 0, 1);
    Nyx::Tuple p2 = Nyx::Transformation::identity()
        .rotateX(M_PI / 2).scale(5, 5, 5).translate(10, 5, 7) * p;
    EXPECT_EQ(p2, Nyx::Point(15, 0, 7));
}