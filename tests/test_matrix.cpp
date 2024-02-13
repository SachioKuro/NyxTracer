#include <gtest/gtest.h>
#include "../src/matrix.hpp"

TEST(Matrix, Init) {
    Nyx::Matrix m = Nyx::Matrix<4>{
        1.f, 2.f, 3.f, 4.f,
        5.5f, 6.5f, 7.5f, 8.5f,
        9.f, 10.f, 11.f, 12.f,
        13.5f, 14.5f, 15.5f, 16.5f
    };
    EXPECT_FLOAT_EQ(m(0, 0), 1.f);
    EXPECT_FLOAT_EQ(m(0, 3), 4.f);
    EXPECT_FLOAT_EQ(m(1, 0), 5.5f);
    EXPECT_FLOAT_EQ(m(1, 2), 7.5f);
    EXPECT_FLOAT_EQ(m(2, 2), 11.f);
    EXPECT_FLOAT_EQ(m(3, 0), 13.5f);
    EXPECT_FLOAT_EQ(m(3, 2), 15.5f);

    Nyx::Matrix m2 = Nyx::Matrix<2>{
        -3.f, 5.f,
        1.f, -2.f
    };
    EXPECT_FLOAT_EQ(m2(0, 0), -3.f);
    EXPECT_FLOAT_EQ(m2(0, 1), 5.f);

    Nyx::Matrix m3 = Nyx::Matrix<3>{
        -3.f, 5.f, 0.f,
        1.f, -2.f, -7.f,
        0.f, 1.f, 1.f
    };
    EXPECT_FLOAT_EQ(m3(0, 0), -3.f);
    EXPECT_FLOAT_EQ(m3(1, 1), -2.f);
    EXPECT_FLOAT_EQ(m3(2, 2), 1.f);
}

TEST(Matrix, Init2) {
    Nyx::Matrix m = Nyx::Matrix<3>(2.3f);
    for (int i = 0; i < 9; i++) {
        EXPECT_FLOAT_EQ(m.data[i], 2.3f);
    }
}

TEST(Matrix, Init3) {
    Nyx::Matrix m = Nyx::Matrix<5>();
    for (int i = 0; i < 25; i++) {
        EXPECT_FLOAT_EQ(m.data[i], 0.f);
    }
}

TEST(Matrix, CopyAssign) {
    Nyx::Matrix m = Nyx::Matrix<4>{
        1.f, 2.f, 3.f, 4.f,
        5.5f, 6.5f, 7.5f, 8.5f,
        9.f, 10.f, 11.f, 12.f,
        13.5f, 14.5f, 15.5f, 16.5f
    };
    Nyx::Matrix m2 = m;
    for (int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(m2.data[i], m.data[i]);
    }
}

TEST(Matrix, MoveAssign) {
    Nyx::Matrix m = Nyx::Matrix<4>{
        1.f, 2.f, 3.f, 4.f,
        5.5f, 6.5f, 7.5f, 8.5f,
        9.f, 10.f, 11.f, 12.f,
        13.5f, 14.5f, 15.5f, 16.5f
    };
    Nyx::Matrix m_copy = m;
    Nyx::Matrix m2 = std::move(m);
    for (int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(m2.data[i], m_copy.data[i]);
    }
}

TEST(Matrix, CopyConstructor) {
    Nyx::Matrix m = Nyx::Matrix<4>{
        1.f, 2.f, 3.f, 4.f,
        5.5f, 6.5f, 7.5f, 8.5f,
        9.f, 10.f, 11.f, 12.f,
        13.5f, 14.5f, 15.5f, 16.5f
    };
    Nyx::Matrix m2(m);
    for (int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(m2.data[i], m.data[i]);
    }
}

TEST(Matrix, MoveConstructor) {
    Nyx::Matrix m = Nyx::Matrix<4>{
        1.f, 2.f, 3.f, 4.f,
        5.5f, 6.5f, 7.5f, 8.5f,
        9.f, 10.f, 11.f, 12.f,
        13.5f, 14.5f, 15.5f, 16.5f
    };
    Nyx::Matrix m_copy = m;
    Nyx::Matrix m2(std::move(m));
    for (int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(m2.data[i], m_copy.data[i]);
    }
}

TEST(Matrix, Multiplication) {
    Nyx::Matrix m1 = Nyx::Matrix<4>{
        1.f, 2.f, 3.f, 4.f,
        5.f, 6.f, 7.f, 8.f,
        9.f, 8.f, 7.f, 6.f,
        5.f, 4.f, 3.f, 2.f
    };
    Nyx::Matrix m2 = Nyx::Matrix<4>{
        -2.f, 1.f, 2.f, 3.f,
        3.f, 2.f, 1.f, -1.f,
        4.f, 3.f, 6.f, 5.f,
        1.f, 2.f, 7.f, 8.f
    };
    Nyx::Matrix m3 = m1 * m2;
    Nyx::Matrix m4 = Nyx::Matrix<4>{
        20.f, 22.f, 50.f, 48.f,
        44.f, 54.f, 114.f, 108.f,
        40.f, 58.f, 110.f, 102.f,
        16.f, 26.f, 46.f, 42.f
    };
    EXPECT_EQ(m3, m4);
}

TEST(Matrix, Multiplication2) {
    Nyx::Matrix m1 = Nyx::Matrix<4>{
        1.f, 2.f, 3.f, 4.f,
        2.f, 4.f, 4.f, 2.f,
        8.f, 6.f, 4.f, 1.f,
        0.f, 0.f, 0.f, 1.f
    };
    Nyx::Tuple v = Nyx::Tuple{1.f, 2.f, 3.f, 1.f};
    Nyx::Tuple v2 = m1 * v;
    Nyx::Tuple v3 = Nyx::Tuple{18.f, 24.f, 33.f, 1.f};
    EXPECT_EQ(v2, v3);
}

TEST(Matrix, Identity) {
    Nyx::Matrix m = Nyx::Matrix<4>::identity();
    Nyx::Matrix m2 = Nyx::Matrix<4>{
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    };
    EXPECT_EQ(m, m2);
}

TEST(Matrix, IdentityMultiplication) {
    Nyx::Matrix m = Nyx::Matrix<4>{
        1.f, 2.f, 3.f, 4.f,
        5.f, 6.f, 7.f, 8.f,
        9.f, 8.f, 7.f, 6.f,
        5.f, 4.f, 3.f, 2.f
    };
    Nyx::Matrix m2 = m * Nyx::Matrix<4>::identity();
    EXPECT_EQ(m, m2);
    Nyx::Matrix m3 = Nyx::Matrix<4>::identity() * m;
    EXPECT_EQ(m, m3);
}

TEST(Matrix, Transpose) {
    Nyx::Matrix m = Nyx::Matrix<4>{
        0.f, 9.f, 3.f, 0.f,
        9.f, 8.f, 0.f, 8.f,
        1.f, 8.f, 5.f, 3.f,
        0.f, 0.f, 5.f, 8.f
    };
    Nyx::Matrix m2 = Nyx::Matrix<4>{
        0.f, 9.f, 1.f, 0.f,
        9.f, 8.f, 8.f, 0.f,
        3.f, 0.f, 5.f, 5.f,
        0.f, 8.f, 3.f, 8.f
    };
    EXPECT_EQ(m.transpose(), m2);
}

TEST(Matrix, TransposeIdentity) {
    Nyx::Matrix m = Nyx::Matrix<4>::identity();
    Nyx::Matrix m2 = m.transpose();
    EXPECT_EQ(m, m2);
}

TEST(Matrix, DeterminantN2) {
    Nyx::Matrix m = Nyx::Matrix<2>{
        1.f, 5.f,
        -3.f, 2.f
    };
    EXPECT_FLOAT_EQ(m.determinant(), 17.f);
}

TEST(Matrix, Submatrix) {
    Nyx::Matrix m = Nyx::Matrix<3>{
        1.f, 5.f, 0.f,
        -3.f, 2.f, 7.f,
        0.f, 6.f, -3.f
    };
    Nyx::Matrix m2 = Nyx::Matrix<2>{
        -3.f, 2.f,
        0.f, 6.f
    };
    EXPECT_EQ(m.submatrix(0, 2), m2);
}

TEST(Matrix, Submatrix2) {
    Nyx::Matrix m = Nyx::Matrix<4>{
        -6.f, 1.f, 1.f, 6.f,
        -8.f, 5.f, 8.f, 6.f,
        -1.f, 0.f, 8.f, 2.f,
        -7.f, 1.f, -1.f, 1.f
    };
    Nyx::Matrix m2 = Nyx::Matrix<3>{
        -6.f, 1.f, 6.f,
        -8.f, 8.f, 6.f,
        -7.f, -1.f, 1.f
    };
    EXPECT_EQ(m.submatrix(2, 1), m2);
}

TEST(Matrix, Minor) {
    Nyx::Matrix m = Nyx::Matrix<3>{
        3.f, 5.f, 0.f,
        2.f, -1.f, -7.f,
        6.f, -1.f, 5.f
    };
    Nyx::Matrix m2 = m.submatrix(1, 0);
    EXPECT_FLOAT_EQ(m2.determinant(), 25.f);
    EXPECT_FLOAT_EQ(m.minor(1, 0), 25.f);
}

TEST(Matrix, Cofactor) {
    Nyx::Matrix m = Nyx::Matrix<3>{
        3.f, 5.f, 0.f,
        2.f, -1.f, -7.f,
        6.f, -1.f, 5.f
    };
    EXPECT_FLOAT_EQ(m.minor(0, 0), -12.f);
    EXPECT_FLOAT_EQ(m.cofactor(0, 0), -12.f);
    EXPECT_FLOAT_EQ(m.minor(1, 0), 25.f);
    EXPECT_FLOAT_EQ(m.cofactor(1, 0), -25.f);
    EXPECT_FLOAT_EQ(m.minor(1, 1), 15.f);
    EXPECT_FLOAT_EQ(m.cofactor(1, 1), 15.f);
    EXPECT_FLOAT_EQ(m.minor(1, 2), -33.f);
    EXPECT_FLOAT_EQ(m.cofactor(1, 2), 33.f);
}

TEST(Matrix, DeterminantN3) {
    Nyx::Matrix m = Nyx::Matrix<3>{
        1.f, 2.f, 6.f,
        -5.f, 8.f, -4.f,
        2.f, 6.f, 4.f
    };
    EXPECT_FLOAT_EQ(m.cofactor(0, 0), 56.f);
    EXPECT_FLOAT_EQ(m.cofactor(0, 1), 12.f);
    EXPECT_FLOAT_EQ(m.cofactor(0, 2), -46.f);
    EXPECT_FLOAT_EQ(m.determinant(), -196.f);
}

TEST(Matrix, DeterminantN4) {
    Nyx::Matrix m = Nyx::Matrix<4>{
        -2.f, -8.f, 3.f, 5.f,
        -3.f, 1.f, 7.f, 3.f,
        1.f, 2.f, -9.f, 6.f,
        -6.f, 7.f, 7.f, -9.f
    };
    EXPECT_FLOAT_EQ(m.cofactor(0, 0), 690.f);
    EXPECT_FLOAT_EQ(m.cofactor(0, 1), 447.f);
    EXPECT_FLOAT_EQ(m.cofactor(0, 2), 210.f);
    EXPECT_FLOAT_EQ(m.cofactor(0, 3), 51.f);
    EXPECT_FLOAT_EQ(m.determinant(), -4071.f);
}

TEST(Matrix, Invertible) {
    Nyx::Matrix m = Nyx::Matrix<4>{
        6.f, 4.f, 4.f, 4.f,
        5.f, 5.f, 7.f, 6.f,
        4.f, -9.f, 3.f, -7.f,
        9.f, 1.f, 7.f, -6.f
    };
    EXPECT_FLOAT_EQ(m.determinant(), -2120.f);
    EXPECT_TRUE(m.isInvertible());
    EXPECT_TRUE(m.isInvertible(-2120.f));
}

TEST(Matrix, NotInvertible) {
    Nyx::Matrix m = Nyx::Matrix<4>{
        -4.f, 2.f, -2.f, -3.f,
        9.f, 6.f, 2.f, 6.f,
        0.f, -5.f, 1.f, -5.f,
        0.f, 0.f, 0.f, 0.f
    };
    EXPECT_FLOAT_EQ(m.determinant(), 0.f);
    EXPECT_FALSE(m.isInvertible());
    EXPECT_FALSE(m.isInvertible(0.f));
}

TEST(Matrix, Inverse) {
    Nyx::Matrix m = Nyx::Matrix<4>{
        -5.f, 2.f, 6.f, -8.f,
        1.f, -5.f, 1.f, 8.f,
        7.f, 7.f, -6.f, -7.f,
        1.f, -3.f, 7.f, 4.f
    };
    Nyx::Matrix m2 = m.inverse();
    Nyx::Matrix m3 = Nyx::Matrix<4>{
        0.21805f, 0.45113f, 0.24060f, -0.04511f,
        -0.80827f, -1.45677f, -0.44361f, 0.52068f,
        -0.07895f, -0.22368f, -0.05263f, 0.19737f,
        -0.52256f, -0.81391f, -0.30075f, 0.30639f
    };
    EXPECT_EQ(m2, m3);

    Nyx::Matrix m4 = Nyx::Matrix<4>{
        8.f, -5.f, 9.f, 2.f,
        7.f, 5.f, 6.f, 1.f,
        -6.f, 0.f, 9.f, 6.f,
        -3.f, 0.f, -9.f, -4.f
    };
    Nyx::Matrix m5 = m4.inverse();
    Nyx::Matrix m6 = Nyx::Matrix<4>{
        -0.15385f, -0.15385f, -0.28205f, -0.53846f,
        -0.07692f, 0.12308f, 0.02564f, 0.03077f,
        0.35897f, 0.35897f, 0.43590f, 0.92308f,
        -0.69231f, -0.69231f, -0.76923f, -1.92308f
    };
    EXPECT_EQ(m5, m6);

    Nyx::Matrix m7 = Nyx::Matrix<4>{
        9.f, 3.f, 0.f, 9.f,
        -5.f, -2.f, -6.f, -3.f,
        -4.f, 9.f, 6.f, 4.f,
        -7.f, 6.f, 6.f, 2.f
    };
    Nyx::Matrix m8 = m7.inverse();
    Nyx::Matrix m9 = Nyx::Matrix<4>{
        -0.04074f, -0.07778f, 0.14444f, -0.22222f,
        -0.07778f, 0.03333f, 0.36667f, -0.33333f,
        -0.02901f, -0.14630f, -0.10926f, 0.12963f,
        0.17778f, 0.06667f, -0.26667f, 0.33333f
    };
}

TEST(Matrix, Inverse2Original) {
    Nyx::Matrix m = Nyx::Matrix<4>{
        3.f, -9.f, 7.f, 3.f,
        3.f, -8.f, 2.f, -9.f,
        -4.f, 4.f, 4.f, 1.f,
        -6.f, 5.f, -1.f, 1.f
    };
    Nyx::Matrix m2 = m.inverse();
    Nyx::Matrix m3 = m2.inverse();
    EXPECT_EQ(m, m3);
}

TEST(Matrix, Inverse2OriginalIdentity) {
    Nyx::Matrix m = Nyx::Matrix<4>{
        3.f, -9.f, 7.f, 3.f,
        3.f, -8.f, 2.f, -9.f,
        -4.f, 4.f, 4.f, 1.f,
        -6.f, 5.f, -1.f, 1.f
    };
    Nyx::Matrix m2 = m.inverse();
    Nyx::Matrix m3 = m * m2;
    EXPECT_EQ(m3, Nyx::Matrix<4>::identity());
}

TEST(Matrix, Inverse2OriginalMutliplication) {
    Nyx::Matrix m = Nyx::Matrix<4>{
        3.f, -9.f, 7.f, 3.f,
        3.f, -8.f, 2.f, -9.f,
        -4.f, 4.f, 4.f, 1.f,
        -6.f, 5.f, -1.f, 1.f
    };
    Nyx::Matrix m2 = Nyx::Matrix<4>{
        8.f, 2.f, 2.f, 2.f,
        3.f, -1.f, 7.f, 0.f,
        7.f, 0.f, 5.f, 4.f,
        6.f, -2.f, 0.f, 5.f
    };
    Nyx::Matrix m3 = m * m2;
    Nyx::Matrix m4 = m3 * m2.inverse();
    EXPECT_EQ(m4, m);

    Nyx::Matrix m5 = m2 * m;
    Nyx::Matrix m6 = m5 * m.inverse();
    EXPECT_EQ(m6, m2);

    Nyx::Matrix m7 = m * m2;
    Nyx::Matrix m8 = m.inverse() * m7;
    EXPECT_EQ(m8, m2);
}