#pragma once

#include <initializer_list>
#include <cmath>
#include <cstdint>
#include <vector>
#include "config.hpp"
#include "tuple.hpp"

namespace Nyx {
    template<uint8_t N>
    struct Matrix {
        constexpr static uint8_t SIZE = N * N;
        float *data;

        Matrix() {
            data = new float[SIZE];
            for (int i = 0; i < SIZE; i++) {
                data[i] = 0.f;
            }
        }

        Matrix(std::initializer_list<float> d) {
            data = new float[SIZE];
            std::copy(d.begin(), d.end(), data);
        }

        Matrix(float* d) {
            data = d;
        }

        Matrix(float d) {
            data = new float[SIZE];
            for (int i = 0; i < SIZE; i++) {
                data[i] = d;
            }
        }

        Matrix(const Matrix<N>& m) {
            data = new float[SIZE];
            for (int i = 0; i < SIZE; i++) {
                data[i] = m.data[i];
            }
        }

        Matrix(Matrix<N>&& m) noexcept : data(m.data) {
            m.data = nullptr;
        }

        Matrix<N>& operator=(const Matrix<N>& m) {
            if (this != &m) {
                delete[] data;
                data = new float[SIZE];
                for (int i = 0; i < SIZE; i++) {
                    data[i] = m.data[i];
                }
            }
            return *this;
        }

        Matrix<N>& operator=(Matrix<N>&& m) noexcept {
            if (this != &m) {
                delete[] data;
                data = m.data;
                m.data = nullptr;
            }
            return *this;
        }

        static Matrix identity() {
            Matrix m;
            for (int i = 0; i < N; i++) {
                m(i, i) = 1.f;
            }
            return std::move(m);
        }

        ~Matrix() {
            delete[] data;
        }

        bool operator==(const Matrix<N>& m) const {
            for (int i = 0; i < SIZE; i++) {
                if (std::abs(data[i] - m.data[i]) > EPSILON) {
                    return false;
                }
            }
            return true;
        }

        float& operator()(uint8_t r, uint8_t c) {
            return data[r * N + c];
        }

        Matrix operator*(const Matrix<N>& m) const {
            float* result_data = new float[SIZE];
            for (int r = 0; r < N; ++r) {
                for (int c = 0; c < N; ++c) {
                    size_t i = r * N + c;
                    float sum = 0.f;
                    for (int k = 0; k < N; ++k) {
                        sum += data[r * N + k] * m.data[k * N + c];
                    }
                    result_data[r * N + c] = sum;
                }
            }
            return std::move(Matrix<N>(std::move(result_data)));
        }

        Tuple operator*(const Tuple& v) const {
            static_assert(N == 4);
            
            float x = data[0] * v.x + data[1] * v.y + data[2] * v.z + data[3] * v.w;
            float y = data[4] * v.x + data[5] * v.y + data[6] * v.z + data[7] * v.w;
            float z = data[8] * v.x + data[9] * v.y + data[10] * v.z + data[11] * v.w;
            float w = data[12] * v.x + data[13] * v.y + data[14] * v.z + data[15] * v.w;

            return Tuple{x, y, z, w};
        }

        Vector operator*(const Vector& v) const {
            static_assert(N == 4);
            
            float x = data[0] * v.x + data[1] * v.y + data[2] * v.z + data[3] * v.w;
            float y = data[4] * v.x + data[5] * v.y + data[6] * v.z + data[7] * v.w;
            float z = data[8] * v.x + data[9] * v.y + data[10] * v.z + data[11] * v.w;
            float w = data[12] * v.x + data[13] * v.y + data[14] * v.z + data[15] * v.w;

            return Vector{x, y, z};
        }

        Point operator*(const Point& p) const {
            static_assert(N == 4);
            
            float x = data[0] * p.x + data[1] * p.y + data[2] * p.z + data[3] * p.w;
            float y = data[4] * p.x + data[5] * p.y + data[6] * p.z + data[7] * p.w;
            float z = data[8] * p.x + data[9] * p.y + data[10] * p.z + data[11] * p.w;
            float w = data[12] * p.x + data[13] * p.y + data[14] * p.z + data[15] * p.w;

            return Point{x, y, z};
        }

        Matrix transpose() const {
            float* result_data = new float[SIZE];
            for (int r = 0; r < N; ++r) {
                for (int c = 0; c < N; ++c) {
                    result_data[r * N + c] = data[c * N + r];
                }
            }
            return std::move(Matrix<N>(std::move(result_data)));
        }

        Matrix<N-1> submatrix(uint8_t rowToRemove, uint8_t colToRemove) const {
            float* result_data = new float[(N - 1) * (N - 1)];
            
            for (auto row = 0, dest_row = 0; row < N; ++row) {
                if (row == rowToRemove) {
                    continue;
                }
                for (auto col = 0, dest_col = 0; col < N; ++col) {
                    if (col == colToRemove) {
                        continue;
                    }
                    result_data[dest_row * (N - 1) + dest_col++] = data[row * N + col];
                }
                dest_row++;
            }

            return std::move(Matrix<N-1>(std::move(result_data)));
        }

        float determinant() const {
            static_assert(N >= 2);
            if constexpr(N == 2) {
                return data[0] * data[3] - data[1] * data[2];
            } else {
                float det = 0.f;
                for (auto col = 0; col < N; ++col) {
                    det += data[col] * this->cofactor(0, col);
                }
                return det;
            }
        }

        float minor(uint8_t row, uint8_t col) const {
            return this->submatrix(row, col).determinant();
        }

        float cofactor(uint8_t row, uint8_t col) const {
            return (1 - 2 * ((row + col) % 2)) * this->minor(row, col);
        }

        bool isInvertible() const {
            return std::abs(this->determinant()) > EPSILON;
        }

        bool isInvertible(float det) const {
            return std::abs(det) > EPSILON;
        }

        Matrix inverse() const {
            float det = this->determinant();
            assert(this->isInvertible(det));

            float* result_data = new float[SIZE];

            for (auto row = 0; row < N; ++row) {
                for (auto col = 0; col < N; ++col) {
                    result_data[col * N + row] = this->cofactor(row, col) / det;
                }
            }

            return std::move(Matrix<N>(std::move(result_data)));
        }
    };
}