#pragma once
#ifndef DELFI_VECTOR_H
#define DELFI_VECTOR_H

#include "delfi/constants.h"
#include "delfi/Matrix.h"
#include <vector>
namespace delfi
{
    class Vector
    {
    public:
        enum class Orientation
        {
            ROW,
            COL
        };

    private:
        std::vector<Variable> _data;
        Orientation _orientation;

    public:
        Vector();
        Vector(size_t size, Orientation orientation = Orientation::ROW);
        Vector(const Vector &other);
        Vector(const Matrix &other);
        Vector(const std::vector<double> &other, Orientation orientation = Orientation::ROW);
        Vector(const std::vector<Variable> &other, Orientation orientation = Orientation::ROW);
        ~Vector();

        Vector &operator=(const Vector &other);
        Vector &operator=(const Matrix &other);
        Vector &operator=(const std::vector<double> &other);
        Vector &operator=(const std::vector<Variable> &other);

        Vector &operator+=(const Vector &other);
        Vector &operator-=(const Vector &other);

        Vector operator+(const Vector &other) const;
        Vector operator-(const Vector &other) const;
        Variable operator*(const Vector &other) const;

        Variable dot(const Vector &other) const;
        Vector cross(const Vector &other) const;
        static Variable dot(const Vector &a, const Vector &b);
        static Vector cross(const Vector &a, const Vector &b);

        Variable operator[](size_t index) const;
        Variable &operator[](size_t index);

        size_t size() const;
        Orientation orientation() const;
        void resize(size_t size, Orientation orientation = Orientation::ROW);
        void clear();

        void setOrientation(Orientation orientation);
        Vector toRow() const;
        Vector toCol() const;
        Vector transpose() const;
        Matrix toMatrix() const;
    };
}

#endif // DELFI_VECTOR_H