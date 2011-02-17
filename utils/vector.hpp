/*
 * vector.hpp
 *
 *  Created on: Nov 24, 2008
 *      Author: mikosz
 */

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <iosfwd>
#include <string>
#include <cassert>

#include <boost/operators.hpp>

#include <settings.hpp>

namespace coconutengine {

/**
 * General fixed-size (D dimensions) vector type, with elements of type T.
 */
template<size_t D, class T = float>
class Vector: public boost::arithmetic<Vector<D, T> >,
        public boost::arithmetic<Vector<D, T> , T>,
        public boost::totally_ordered<Vector<D, T> > {
public:

    Vector() {
    }

    template<class T2>
    Vector(const Vector<D, T2>& rhs) {
        for (size_t i = 0; i < D; ++i) {
            data_[i] = rhs[i];
        }
    }

    template<class T2>
    Vector& operator=(const Vector<D, T2>& rhs) {
        for (size_t i = 0; i < D; ++i) {
            data_[i] = rhs[i];
        }
        return *this;
    }

    T& operator[](size_t i) {
        return get(i);
    }

    const T& operator[](size_t i) const {
        return get(i);
    }

    Vector operator-() const {
        Vector v(*this);
        v *= -1;
        return v;
    }

    Vector& operator+=(const Vector& v) {
        for (size_t i = 0; i < D; ++i) {
            get(i) += v.get(i);
        }
        return *this;
    }

    Vector& operator-=(const Vector& v) {
        for (size_t i = 0; i < D; ++i) {
            get(i) -= v.get(i);
        }
        return *this;
    }

    Vector& operator*=(const Vector& v) {
        for (size_t i = 0; i < D; ++i) {
            get(i) *= v.get(i);
        }
        return *this;
    }

    Vector& operator/=(const Vector& v) {
        for (size_t i = 0; i < D; ++i) {
            assert(v.get(i));
            get(i) /= v.get(i);
        }
        return *this;
    }

    Vector& operator+=(const T& v) {
        for (size_t i = 0; i < D; ++i) {
            get(i) += v;
        }
        return *this;
    }

    Vector& operator-=(const T& v) {
        for (size_t i = 0; i < D; ++i) {
            get(i) -= v;
        }
        return *this;
    }

    Vector& operator*=(const T& v) {
        for (size_t i = 0; i < D; ++i) {
            get(i) *= v;
        }
        return *this;
    }

    Vector& operator/=(const T& v) {
        assert(v);
        for (size_t i = 0; i < D; ++i) {
            get(i) /= v;
        }
        return *this;
    }

    /**
     * Lexical order.
     */
    bool operator<(const Vector<D, T>& v) const {
        for (size_t i = 0; i < D; ++i) {
            if (get(i) < v.get(i)) {
                return true;
            } else if (get(i) < get(i)) {
                return false;
            }
        }
        return false;
    }

    bool operator==(const Vector<D, T>& v) const {
        for (size_t i = 0; i < D; ++i) {
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
        for (size_t i = 0; i < D; ++i) {
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
            (*this) /= (l);
        }
        return *this;
    }

protected:

    T& get(size_t i) {
        assert(i < D);
        return data_[i];
    }

    const T& get(size_t i) const {
        assert(i < D);
        return data_[i];
    }

    T* data() {
        return data_;
    }

    const T* data() const {
        return data_;
    }

private:

    T data_[D];

};

template <size_t D, class T>
std::ostream& operator<<(std::ostream& os, const Vector<D, T>& vector) {
    os << '[';
    for (size_t i = 0; i < D; ++i) {
        if (i) {
            os << ", ";
        }
        os << vector[i];
    }
    os << ']';
    return os;
}

/**
 * 3D version of the Vector. Extends the base type by the cross product function, and
 * named accessors for elements (x, y and z).
 */
template<class T = float>
class Vector3D : public Vector<3, T> {
public:

    Vector3D() {
    }

    template<class T2, class T3, class T4>
    Vector3D(T2 x, T3 y, T4 z) {
        get(0) = x;
        get(1) = y;
        get(2) = z;
    }

    Vector3D(const Settings<std::string>& settings, const std::string& prefix) {
        get(0) = getSetting<T>(settings, prefix + ".x");
        get(1) = getSetting<T>(settings, prefix + ".y");
        get(2) = getSetting<T>(settings, prefix + ".z");
    }

    template <class T2>
    Vector3D(const Vector<3, T2>& rhs) : Vector<3, T>(rhs) {
    }

    T& x() {
        return get(0);
    }

    const T& x() const {
        return get(0);
    }

    T& y() {
        return get(1);
    }

    const T& y() const {
        return get(1);
    }

    T& z() {
        return get(2);
    }

    const T& z() const {
        return get(2);
    }

    Vector3D crossProduct(const Vector3D& rhs) const {
        return Vector3D(y() * rhs.z() - z() * rhs.y(), z() * rhs.x() - x() * rhs.z(), x() * rhs.y() - y()
                * rhs.x());
    }

    T* toXYZ() {
        return data();
    }

    const T* toXYZ() const {
        return data();
    }

protected:

    using Vector<3, T>::get;

    using Vector<3, T>::data;

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

    template<class T2, class T3>
    Vector2D(T2 x, T3 y) {
        get(0) = x;
        get(1) = y;
    }

    template<class T2, class T3>
    Vector2D(const std::pair<T2, T3>& p) {
        get(0) = p.first;
        get(1) = p.second;
    }

    Vector2D(const Settings<std::string>& settings, const std::string& prefix) {
        get(0) = getSetting<T>(settings, prefix + ".x");
        get(1) = getSetting<T>(settings, prefix + ".y");
    }

    template <class T2>
    Vector2D(const Vector<2, T2>& rhs) : Vector<2, T>(rhs) {
    }

    T& x() {
        return get(0);
    }

    const T& x() const {
        return get(0);
    }

    T& y() {
        return get(1);
    }

    const T& y() const {
        return get(1);
    }

    T* toXY() {
        return data();
    }

    const T* toXY() const {
        return data();
    }

protected:

    using Vector<2, T>::get;

    using Vector<2, T>::data;

};

/**
 * Convenience typedef - short name for a two-dimensional float vector.
 */
typedef Vector2D<float> Vec2D;

} // namespace coconutengine

#endif /* VECTOR_HPP_ */
