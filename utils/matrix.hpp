#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <cassert>
#include <utility>

#include <boost/multi_array.hpp>
#include <boost/operators.hpp>

#include "vector.hpp"

namespace coconutengine {
namespace detail {

template <class MatrixType, class PointerType, class ReferenceType, class ViewType>
class Iterator :
    public boost::random_access_iterator_helper<
        Iterator<MatrixType, PointerType, ReferenceType, ViewType> ,
        typename MatrixType::Value,
        ptrdiff_t,
        PointerType,
        ReferenceType>,
    // XXX: make sure additive2 wont allow pair +/- iterator
    public boost::additive2<
        Iterator<MatrixType, PointerType, ReferenceType, ViewType>,
        std::pair<ptrdiff_t, ptrdiff_t> > {
public:

    typedef MatrixType Matrix;

    typedef typename Matrix::Value Value;

    typedef typename Matrix::Range Range;

    typedef ReferenceType Reference;

    typedef PointerType Pointer;

    Iterator() :
        matrix_(0),
        view_(mockMultiArray_[boost::indices[Range(0, 0)][Range(0, 0)]]),
        row_(0),
        column_(0) {
    }

    Iterator(Matrix& matrix) :
        matrix_(&matrix),
        view_(matrix.data_[boost::indices[Range(0, matrix.height_)][Range(0, matrix.width_)]]),
        row_(0),
        column_(0) {
    }

    Iterator(Matrix& matrix, const Range& rowRange, const Range& columnRange) :
        matrix_(&matrix),
        view_(matrix.data_[boost::indices[rowRange][columnRange]]),
        row_(0),
        column_(0) {
    }

    Reference operator*() const {
        assert(matrix_);
        return view_[row_][column_];
    }

    Iterator& operator++() {
        assert(!atEnd());
        ++column_;
        if (column_ == width()) {
            ++row_;
            column_ = 0;
        }
        return *this;
    }

    Iterator& operator--() {
        assert(row_ || column_);
        if (column_) {
            --column_;
        } else {
            --row_;
            column_ = width() - 1;
        }
        return *this;
    }

    Iterator& operator+=(const std::pair<ptrdiff_t, ptrdiff_t>& vec) {
        assert(vec.first <= 0 || row_ + vec.first < height());
        assert(vec.second <= 0 || column_ + vec.second < width());
        assert(vec.first >= 0 || static_cast<size_t>(-vec.first) <= row_);
        assert(vec.second >= 0 || static_cast<size_t>(-vec.second) <= column_);
        row_ += vec.first;
        column_ += vec.second;
        return *this;
    }

    Iterator& operator-=(const std::pair<ptrdiff_t, ptrdiff_t>& vec) {
        assert(vec.first >= 0 || row_ + -vec.first < height());
        assert(vec.second >= 0 || column_ + -vec.second < width());
        assert(vec.first <= 0 || vec.first <= row_);
        assert(vec.second <= 0 || vec.second <= column_);
        row_ -= vec.first;
        column_ -= vec.second;
        return *this;
    }

    size_t row() const {
        return row_;
    }

    size_t column() const {
        return column_;
    }

    friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
        return (lhs.atEnd() && rhs.atEnd()) || ((lhs.matrix_ == rhs.matrix_) && (&*lhs == &*rhs));
    }

    friend bool operator<(const Iterator& lhs, const Iterator& rhs) {
        if (!rhs.matrix_) {
            if (lhs.matrix_) {
                return true;
            } else {
                return false;
            }
        } else if (!lhs.matrix_) {
            return false;
        }

        assert(sameView(lhs, rhs));

        return lhs.row_ < rhs.row_ || (lhs.row_ == rhs.row_ && lhs.column_ < rhs.column_);
    }

    friend ptrdiff_t operator-(const Iterator& lhs, const Iterator& rhs) {
        assert(lhs.matrix_ && sameView(lhs, rhs));

        return ((lhs.row_ - rhs.row_) * lhs.width_) + (lhs.column_ - rhs.column_);
    }

private:

    typedef ViewType View;

    static typename Matrix::Data mockMultiArray_;

    Matrix* matrix_;

    mutable View view_;

    size_t row_, column_;

    static bool sameView(const Iterator& lhs, const Iterator& rhs) {
        if (!lhs.matrix_) {
            if (!rhs.matrix_) {
                return true;
            } else {
                return false;
            }
        }

        return lhs.matrix_ == rhs.matrix_ && lhs.width() == rhs.width() && lhs.height() == rhs.height() && (lhs.width()
                == 0 || lhs.height() == 0 || (lhs.view_.origin() == &rhs.view_.origin()));
    }

    bool atEnd() const {
        return !matrix_ || row_ == height();
    }

    size_t height() const {
        assert(matrix_);
        return view_.size();
    }

    size_t width() const {
        assert(matrix_);
        return height() ? view_[0].size() : 0;
    }

    // XXX: find a way to implement operator=
    Iterator& operator=(const Iterator& rhs);

};

template<class MatrixType, class PointerType, class ReferenceType, class ViewType>
typename Iterator<MatrixType, PointerType, ReferenceType, ViewType>::Matrix::Data Iterator<MatrixType,
        PointerType, ReferenceType, ViewType>::mockMultiArray_(boost::extents[0][0]);

} // namespace detail

template <class T>
class Matrix {

    typedef boost::multi_array<T, 2> Data;

public:

    typedef Matrix<T> Self;

    typedef typename boost::multi_array<T, 2>::index_range Range;

    typedef T Value;

    typedef detail::Iterator<Self, T*, T&, typename Data::template array_view<2>::type> Iterator;

    typedef detail::Iterator<const Self, const T*, const T&, typename Data::template const_array_view<2>::type>
            ConstIterator;

    Matrix() :
        height_(0), width_(0) {
    }

    Matrix(size_t height, size_t width) :
        data_(boost::extents[height][width]), height_(height), width_(width) {
    }

    Iterator begin() {
        return Iterator(*this);
    }

    ConstIterator begin() const {
        return ConstIterator(*this);
    }

    Iterator end() {
        return Iterator();
    }

    ConstIterator end() const {
        return ConstIterator();
    }

    std::pair<Iterator, Iterator> range(size_t row1, size_t column1, size_t row2, size_t column2) {
        assert(row1 <= row2);
        assert(column1 <= column2);
        assert(row2 <= height());
        assert(column2 <= width());
        return std::make_pair(Iterator(*this, Range(row1, row2), Range(column1, column2)), Iterator());
    }

    std::pair<ConstIterator, ConstIterator> range(
            size_t row1, size_t column1, size_t row2, size_t column2) const {
        assert(row1 <= row2);
        assert(column1 <= column2);
        assert(row2 <= height());
        assert(column2 <= width());
        return std::make_pair(ConstIterator(*this, Range(row1, row2), Range(column1, column2)),
                ConstIterator());
    }

    void resize(size_t height, size_t width) {
        height_ = height;
        width_ = width;
        data_.resize(boost::extents[height][width]);
    }

    void swap(Matrix& rhs) {
        data_.swap(rhs);
    }

    size_t height() const {
        return height_;
    }

    size_t width() const {
        return width_;
    }


    T& operator()(size_t row, size_t column) {
        return data_[row][column];
    }

    const T& operator()(size_t row, size_t column) const {
        return data_[row][column];
    }

private:

    Data data_;

    size_t height_, width_;

    template <class MatrixType, class PointerType, class ReferenceType> friend class detail::Iterator;

};

} // namespace coconutengine

#endif /* MATRIX_HPP_ */
