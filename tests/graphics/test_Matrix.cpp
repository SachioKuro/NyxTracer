#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <ctime>
#include <limits>
#include <tuple>

#include "utils/Util.hpp"
#include "graphics/Matrix.hpp"

TEST_CASE("Matrix") {
	srand((unsigned)time(0));

	SECTION("Initialize") {
		SECTION("creating a matrix") {
			for (int test_i = 0; test_i < 100; test_i++) {
				int rows = randomInt(2, 10);
				int cols = randomInt(2, 10);
				Matrix m(rows, cols);
		
				for (int i = 0; i < rows; i++) {
					for (int j = 0; j < cols; j++) {
						REQUIRE(m(i, j) == 0);
					}
				}
			}
		}
	}

	SECTION("isEqual") {
		SECTION("if values are the same it is equal (different objects)") {
			int rows = randomInt(2, 10);
			int cols = randomInt(2, 10);
			Matrix m1(rows, cols);
			for (int i = 0; i < 1000; ++i)
				m1(randomInt(0, rows), randomInt(0, cols)) = randomFloat();
			Matrix m2(rows, cols);
			for (int r = 0; r < rows; ++r)
				for (int c = 0; c < cols; ++c)
					m2(r, c) = m1(r, c);

			REQUIRE(m1 == m2);
		}

		SECTION("if values are the same it is equal (same objects)") {
			int rows = randomInt(2, 10);
			int cols = randomInt(2, 10);
			Matrix m1(rows, cols);
			for (int i = 0; i < 100; ++i)
				m1(randomInt(0, rows), randomInt(0, cols)) = randomFloat();
			Matrix m2 = m1;

			REQUIRE(m1 == m2);
		}

		SECTION("if coordinate values are different it is not equal") {
			int rows = randomInt(10, 20);
			int cols = randomInt(10, 20);
			Matrix m1(rows, cols);
			for (int i = 0; i < 1000; ++i)
				m1(randomInt(0, rows), randomInt(0, cols)) = randomFloat();


			rows = randomInt(10, 20);
			cols = randomInt(10, 20);
			Matrix m2(rows, cols);
			for (int i = 0; i < 1000; ++i)
				m2(randomInt(0, rows), randomInt(0, cols)) = randomFloat();

			REQUIRE(m1 != m2);
		}
	}
	
	SECTION("Matric-Multiplication-4x4") {
		Matrix m1(4, 4);
		Matrix m2(4, 4);
		Matrix m3(4, 4);

		m1(0, 0) = 1;
		m1(0, 1) = 2;
		m1(0, 2) = 3;
		m1(0, 3) = 4;
		m1(1, 0) = 5;
		m1(1, 1) = 6;
		m1(1, 2) = 7;
		m1(1, 3) = 8;
		m1(2, 0) = 9;
		m1(2, 1) = 10;
		m1(2, 2) = 11;
		m1(2, 3) = 12;
		m1(3, 0) = 13;
		m1(3, 1) = 14;
		m1(3, 2) = 15;
		m1(3, 3) = 16;
		
		m2(0, 0) = 17;
		m2(0, 1) = 18;
		m2(0, 2) = 19;
		m2(0, 3) = 20;
		m2(1, 0) = 21;
		m2(1, 1) = 22;
		m2(1, 2) = 23;
		m2(1, 3) = 24;
		m2(2, 0) = 25;
		m2(2, 1) = 26;
		m2(2, 2) = 27;
		m2(2, 3) = 28;
		m2(3, 0) = 29;
		m2(3, 1) = 30;
		m2(3, 2) = 31;
		m2(3, 3) = 32;
		
		m3(0, 0) = 250;
		m3(0, 1) = 260;
		m3(0, 2) = 270;
		m3(0, 3) = 280;
		m3(1, 0) = 618;
		m3(1, 1) = 644;
		m3(1, 2) = 670;
		m3(1, 3) = 696;
		m3(2, 0) = 986;
		m3(2, 1) = 1028;
		m3(2, 2) = 1070;
		m3(2, 3) = 1112;
		m3(3, 0) = 1354;
		m3(3, 1) = 1412;
		m3(3, 2) = 1470;
		m3(3, 3) = 1528;

		REQUIRE(m1 * m2 == m3);
	}

	SECTION("Identity") {
		Matrix m1 = randomMatrix4x4();

		Matrix identity = Matrix::Identity();

		REQUIRE(m1 * identity == m1);

		Matrix m2 = randomMatrix4x4();
		Matrix m3 = randomMatrix4x4();

		REQUIRE(isClose(m2 * m3 * Matrix::Identity(), m2 * m3));
	}

	SECTION("Transpose") {
		Matrix m1{
			MatrixRow4D( 1,  2,  3,  4),
			MatrixRow4D( 5,  6,  7,  8),
			MatrixRow4D( 9, 10, 11, 12),
			MatrixRow4D(13, 14, 15, 16),
		};

		Matrix m2{
			MatrixRow4D(1, 5,  9, 13),
			MatrixRow4D(2, 6, 10, 14),
			MatrixRow4D(3, 7, 11, 15),
			MatrixRow4D(4, 8, 12, 16),
		};

		REQUIRE(m1.transpose() == m2);

		REQUIRE(Matrix::Identity().transpose() == Matrix::Identity());
	}

	SECTION("Inverse") {
		SECTION("Finding 2x2 determinant") {
			Matrix m1(2, 2);
			m1(0, 0) = 1;
			m1(1, 0) = -3;
			m1(0, 1) = 5;
			m1(1, 1) = 2;

			REQUIRE(m1.determinant() == 17);
		}

		SECTION("Submatrix") {
			Matrix m1(3, 3);
			m1(0, 0) = 1;
			m1(0, 1) = 5;
			m1(0, 2) = 6;
			m1(1, 0) = -3;
			m1(1, 1) = 2;
			m1(1, 2) = 7;
			m1(2, 0) = 0;
			m1(2, 1) = 6;
			m1(2, 2) = -3;

			Matrix msub1(2, 2);
			msub1(0, 0) = -3;
			msub1(0, 1) = 2;
			msub1(1, 0) = 0;
			msub1(1, 1) = 6;

			REQUIRE(isClose(m1.submatrix(0, 2), msub1));

			Matrix m2{
				MatrixRow4D(-6, 1, 1, 6),
				MatrixRow4D(-8, 5, 8, 6),
				MatrixRow4D(-1, 0, 8, 2),
				MatrixRow4D(-7, 1,-1, 1),
			};

			Matrix msub2(3, 3);
			msub2(0, 0) = -6;
			msub2(0, 1) = 1;
			msub2(0, 2) = 6;
			msub2(1, 0) = -8;
			msub2(1, 1) = 8;
			msub2(1, 2) = 6;
			msub2(2, 0) = -7;
			msub2(2, 1) = -1;
			msub2(2, 2) = 1;

			REQUIRE(isClose(m2.submatrix(2, 1), msub2));
		}

		SECTION("Minor") {
			Matrix m1(3, 3);
			m1(0, 0) = 3;
			m1(0, 1) = 5;
			m1(0, 2) = 0;
			m1(1, 0) = 2;
			m1(1, 1) = -1;
			m1(1, 2) = -7;
			m1(2, 0) = 6;
			m1(2, 1) = -1;
			m1(2, 2) = 5;

			REQUIRE(isClose(m1.minor(0, 0), -12));
			REQUIRE(isClose(m1.minor(1, 0), 25));
		}

		SECTION("Cofactor") {
			Matrix m1(3, 3);
			m1(0, 0) = 3;
			m1(0, 1) = 5;
			m1(0, 2) = 0;
			m1(1, 0) = 2;
			m1(1, 1) = -1;
			m1(1, 2) = -7;
			m1(2, 0) = 6;
			m1(2, 1) = -1;
			m1(2, 2) = 5;

			REQUIRE(isClose(m1.cofactor(0, 0), -12));
			REQUIRE(isClose(m1.cofactor(1, 0), -25));
		}

		SECTION("Finding determinant of larger determinant") {
			Matrix m1(3, 3);
			m1(0, 0) = 1;
			m1(0, 1) = 2;
			m1(0, 2) = 6;
			m1(1, 0) = -5;
			m1(1, 1) = 8;
			m1(1, 2) = -4;
			m1(2, 0) = 2;
			m1(2, 1) = 6;
			m1(2, 2) = 4;

			REQUIRE(isClose(m1.cofactor(0, 0), 56));
			REQUIRE(isClose(m1.cofactor(0, 1), 12));
			REQUIRE(isClose(m1.cofactor(0, 2), -46));
			REQUIRE(isClose(m1.determinant(), -196));

			Matrix m2{
				MatrixRow4D(-2, -8, 3, 5),
				MatrixRow4D(-3, 1, 7, 3),
				MatrixRow4D(1, 2, -9, 6),
				MatrixRow4D(-6, 7, 7, -9)
			};

			REQUIRE(isClose(m2.cofactor(0, 0), 690));
			REQUIRE(isClose(m2.cofactor(0, 1), 447));
			REQUIRE(isClose(m2.cofactor(0, 2), 210));
			REQUIRE(isClose(m2.cofactor(0, 3), 51));
			REQUIRE(isClose(m2.determinant(), -4071));
		}

		SECTION("Is invertable") {
			Matrix m1{
				MatrixRow4D(6, 4, 4, 4),
				MatrixRow4D(5, 5, 7, 6),
				MatrixRow4D(4, -9, 3, -7),
				MatrixRow4D(9, 1, 7, -6)
			};

			REQUIRE(isClose(m1.determinant(), -2120));
			REQUIRE(m1.isInvertable());

			Matrix m2{
				MatrixRow4D(-4, 2, -2, -3),
				MatrixRow4D(9, 6, 2, 6),
				MatrixRow4D(0, -5, 1, -5),
				MatrixRow4D(0, 0, 0, 0)
			};

			REQUIRE(isClose(m2.determinant(), 0));
			REQUIRE(!m2.isInvertable());
		}

		SECTION("Invert") {
			Matrix m1{
				MatrixRow4D(-5, 2, 6, -8),
				MatrixRow4D(1, -5, 1, 8),
				MatrixRow4D(7, 7, -6, -7),
				MatrixRow4D(1, -3, 7, 4)
			};

			Matrix m2{
				MatrixRow4D(0.21805, 0.45113, 0.24060, -0.04511),
				MatrixRow4D(-0.80827, -1.45677, -0.44361, 0.52068),
				MatrixRow4D(-0.07895, -0.22368, -0.05263, 0.19737),
				MatrixRow4D(-0.52256, -0.81391, -0.30075, 0.30639)
			};

			Matrix inverse = m1.inverse();

			REQUIRE(isClose(m1.determinant(), 532));
			REQUIRE(isClose(m1.cofactor(2, 3), -160));
			REQUIRE(isClose(inverse(3, 2), -160./532.));
			REQUIRE(isClose(m1.cofactor(3, 2), 105));
			REQUIRE(isClose(inverse(2, 3), 105./532.));
			REQUIRE(isClose(inverse, m2));

			Matrix m3{
				MatrixRow4D(8, -5, 9, 2),
				MatrixRow4D(7, 5, 6, 1),
				MatrixRow4D(-6, 0, 9, 6),
				MatrixRow4D(-3, 0, -9, -4)
			};

			Matrix m4{
				MatrixRow4D(-0.15385, -0.15385, -0.28205, -0.53846),
				MatrixRow4D(-0.07692, 0.12308, 0.02564, 0.03077),
				MatrixRow4D(0.35897, 0.35897, 0.43590, 0.92308),
				MatrixRow4D(-0.69231, -0.69231, -0.76923, -1.92308)
			};

			Matrix inverse2 = m3.inverse();

			REQUIRE(isClose(inverse2, m4));

			Matrix m5{
				MatrixRow4D(9, 3, 0, 9),
				MatrixRow4D(-5, -2, -6, -3),
				MatrixRow4D(-4, 9, 6, 4),
				MatrixRow4D(-7, 6, 6, 2)
			};

			Matrix m6{
				MatrixRow4D(-0.04074, -0.07778, 0.14444, -0.22222),
				MatrixRow4D(-0.07778, 0.03333, 0.36667, -0.33333),
				MatrixRow4D(-0.02901, -0.14630, -0.10926, 0.12963),
				MatrixRow4D(0.17778, 0.06667, -0.26667, 0.33333)
			};

			Matrix inverse3 = m5.inverse();

			REQUIRE(isClose(inverse3, m6));

			Matrix m7{
				MatrixRow4D(3, -9, 7, 3),
				MatrixRow4D(3, -8, 2, -9),
				MatrixRow4D(-4, 4, 4, 1),
				MatrixRow4D(-6, 5, -1, 1)
			};

			Matrix m8{
				MatrixRow4D(8, 2, 2, 2),
				MatrixRow4D(3, -1, 7, 0),
				MatrixRow4D(7, 0, 5, 4),
				MatrixRow4D(6, -2, 0, 5)
			};

			REQUIRE(isClose(m7 * m8 * m8.inverse(), m7));
		}
	}
}