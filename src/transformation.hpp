#pragma once

#include <cmath>

#include "config.hpp"
#include "tuple.hpp"
#include "matrix.hpp"

namespace Nyx {
    class Transformation {
    public:
        static Matrix<4> translation(float x, float y, float z) {
            Matrix<4> m = Matrix<4>::identity();
            m(0, 3) = x;
            m(1, 3) = y;
            m(2, 3) = z;
            return std::move(m);
        }

        static Matrix<4> scaling(float x, float y, float z) {
            Matrix<4> m = Matrix<4>::identity();
            m(0, 0) = x;
            m(1, 1) = y;
            m(2, 2) = z;
            return std::move(m);
        }

        static Matrix<4> rotationX(float r) {
            Matrix<4> m = Matrix<4>::identity();
            m(1, 1) = std::cos(r);
            m(1, 2) = -std::sin(r);
            m(2, 1) = std::sin(r);
            m(2, 2) = std::cos(r);
            return std::move(m);
        }

        static Matrix<4> rotationY(float r) {
            Matrix<4> m = Matrix<4>::identity();
            m(0, 0) = std::cos(r);
            m(0, 2) = std::sin(r);
            m(2, 0) = -std::sin(r);
            m(2, 2) = std::cos(r);
            return std::move(m);
        }

        static Matrix<4> rotationZ(float r) {
            Matrix<4> m = Matrix<4>::identity();
            m(0, 0) = std::cos(r);
            m(0, 1) = -std::sin(r);
            m(1, 0) = std::sin(r);
            m(1, 1) = std::cos(r);
            return std::move(m);
        }

        static Matrix<4> shearing(float xy, float xz, float yx, float yz, float zx, float zy) {
            Matrix<4> m = Matrix<4>::identity();
            m(0, 1) = xy;
            m(0, 2) = xz;
            m(1, 0) = yx;
            m(1, 2) = yz;
            m(2, 0) = zx;
            m(2, 1) = zy;
            return std::move(m);
        }

        Transformation() : transformationMatrix(Matrix<4>::identity()) {}
        Transformation(const Matrix<4>& m) : transformationMatrix(m) {}

        bool operator==(const Transformation& other) const {
            return this->transformationMatrix == other.transformationMatrix;
        }

        static Transformation identity() {
            return Transformation();
        }

        Matrix<4> matrix() const {
            return transformationMatrix;
        }

        Transformation translate(float x, float y, float z) {
            transformationMatrix = Transformation::translation(x, y, z) * transformationMatrix;
            return *this;
        }

        Transformation scale(float x, float y, float z) {
            transformationMatrix = Transformation::scaling(x, y, z) * transformationMatrix;
            return *this;
        }

        Transformation rotateX(float r) {
            transformationMatrix = Transformation::rotationX(r) * transformationMatrix;
            return *this;
        }

        Transformation rotateY(float r) {
            transformationMatrix = Transformation::rotationY(r) * transformationMatrix;
            return *this;
        }

        Transformation rotateZ(float r) {
            transformationMatrix = Transformation::rotationZ(r) * transformationMatrix;
            return *this;
        }

        Transformation shear(float xy, float xz, float yx, float yz, float zx, float zy) {
            transformationMatrix = Transformation::shearing(xy, xz, yx, yz, zx, zy) * transformationMatrix;
            return *this;
        }

        Matrix<4> operator*(const Matrix<4>& m) const {
            return transformationMatrix * m;
        }
    
        Tuple operator*(const Tuple& t) const {
            return transformationMatrix * t;
        }

        Vector operator*(const Vector& v) const {
            return transformationMatrix * v;
        }

        Point operator*(const Point& p) const {
            return transformationMatrix * p;
        }

        Transformation inverse() const {
            return {transformationMatrix.inverse()};
        }

        Transformation transpose() const {
            return {transformationMatrix.transpose()};
        }
    private:
        Matrix<4> transformationMatrix;
    };
}