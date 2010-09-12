/*
 * vector.hpp
 *
 *  Created on: Nov 24, 2008
 *      Author: mikosz
 */

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <string>
#include <boost/operators.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include <settings.hpp>

namespace ublas = boost::numeric::ublas;

namespace CoconutEngine {

/**
 * General fixed-size (D dimensions) vector type, with elements of type T.
 */
template<size_t D, class T = float>
class Vector : public ublas::bounded_vector<T, D> {
private:

    typedef ublas::bounded_vector<T, D> Super;

public:

    typedef typename Super::size_type size_type;

    Vector<D, T>() : Super(D) {
    }

    Vector<D, T>(const Vector<D, T>& v) : Super(v) {
    }

    template<class ExpressionType>
    Vector<D, T>(const ublas::vector_expression<ExpressionType>& expression) :
    Super(expression) {
    }

    /**
     * Lexical order.
     */
    bool operator <(const Vector<D, T>& v) const {
        for (size_type i = 0; i < D; ++i) {
            if (get(i) < v.get(i)) {
                return true;
            } else if (v.get(i) < get(i)) {
                return false;
            }
        }
        return false;
    }

    bool operator ==(const Vector<D, T>& v) const {
        for (size_type i = 0; i < D; ++i) {
            if (get(i) != v.get(i)) {
                return false;
            }
        }
        return true;
    }

    /**
     * Returns the length of the vector (in the Euclidean space sense, not the dimensionality).
     */
    T length() const {
        T result = 0;
        for (size_type i = 0; i < D; ++i) {
            result += get(i) * get(i);
        }
        return sqrt(result);
    }

    /**
     * Returns a normalised copy of this vector.
     */
    Vector<D, T> normalised() const {
        return Vector<D, T> (*this).normalise();
    }

    /**
     * Normalises this vector and returns it.
     */
    Vector<D, T>& normalise() {
        T l = length();
        if (l) {
            this->operator /=(l);
        }
        return *this;
    }

protected:

    T& get(size_type i) {
        return this->operator [](i);
    }

    const T& get(size_type i) const {
        return this->operator [](i);
    }

};

/**
 * 3D version of the Vector. Extends the base type by the cross product function, and
 * named accessors for elements (x, y and z).
 */
template<class T = float>
class Vector3D : public Vector<3, T> {
public:

    Vector3D() {
    }

    Vector3D(T x, T y, T z) {
        this->get(0) = x;
        this->get(1) = y;
        this->get(2) = z;
    }

    Vector3D(const Settings<std::string>& settings, const std::string& prefix) {
        this->get(0) = getSetting<T>(settings, prefix + ".x");
        this->get(1) = getSetting<T>(settings, prefix + ".y");
        this->get(2) = getSetting<T>(settings, prefix + ".z");
    }

    Vector3D(const Vector3D& v) : Vector<3, T>(v) {
    }

    template<class ExpressionType>
    Vector3D(const ublas::vector_expression<ExpressionType>& expression) : Vector<3, T>(expression) {
    }

    T& x() {
        return this->get(0);
    }

    const T& x() const {
        return this->get(0);
    }

    T& y() {
        return this->get(1);
    }

    const T& y() const {
        return this->get(1);
    }

    T& z() {
        return this->get(2);
    }

    const T& z() const {
        return this->get(2);
    }

    Vector3D crossProduct(const Vector3D& rhs) const {
        return Vector3D(y() * rhs.z() - z() * rhs.y(), z() * rhs.x() - x() * rhs.z(), x() * rhs.y() - y() * rhs.x());
    }

};

/**
 * Convenience typedef - short name for a three-dimensional float vector.
 */
typedef Vector3D<float> Vec3D;

/**
 * 2D version of the Vector. Extends the base type by named accessors for elements (x and y).
 */
template<class T = float>
class Vector2D : public Vector<2, T> {
public:

    Vector2D() {
    }

    Vector2D<T>(T x, T y) {
        this->get(0) = x;
        this->get(1) = y;
    }

    Vector2D(const Settings<std::string>& settings, const std::string& prefix) {
        this->get(0) = getSetting<T>(settings, prefix + ".x");
        this->get(1) = getSetting<T>(settings, prefix + ".y");
    }

    Vector2D(const Vector2D& v) : Vector<2, T>(v) {
    }

    template<class ExpressionType>
    Vector2D(const ublas::vector_expression<ExpressionType>& expression) : Vector<2, T>(expression) {
    }

    T& x() {
        return this->get(0);
    }

    const T& x() const {
        return this->get(0);
    }

    T& y() {
        return this->get(1);
    }

    const T& y() const {
        return this->get(1);
    }

};

/**
 * Convenience typedef - short name for a two-dimensional float vector.
 */
typedef Vector2D<float> Vec2D;

} // namespace CoconutEngine

#endif /* VECTOR_HPP_ */
