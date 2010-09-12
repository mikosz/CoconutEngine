/*
 * matrix.hpp
 *
 *  Created on: 2010-09-12
 *      Author: mikosz
 */

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <vector>
#include <algorithm>

namespace CoconutEngine {
namespace detail {

template <class Matrix, class T>
class MatrixIterator : public std::iterator<std::input_iterator_tag, T> {
public:

    typedef MatrixIterator<Matrix, T> Self;

    MatrixIterator(Matrix& matrix) :
        startingColumn_(0), row_(0), column_(0), lastRow_(0), lastColumn_(0) {
    }

    MatrixIterator(Matrix& matrix, size_t lastRow, size_t lastColumn) :
        startingColumn_(0), row_(0), column_(0), lastRow_(lastRow), lastColumn_(lastColumn) {
    }

    MatrixIterator(Matrix& matrix, size_t row, size_t column, size_t lastRow, size_t lastColumn) :
        startingColumn_(column), row_(row), column_(column), lastRow_(lastRow), lastColumn_(lastColumn) {
    }

    bool operator==(const MatrixIterator& rhs) const {
        return row_ == rhs.row_ && column_ == rhs.column_;
    }

    bool operator!=(const MatrixIterator& rhs) const {
        return !(*this == rhs);
    }

    Self& operator++() {
        ++column_;
        if (column_ >= lastColumn_) {
            column_ = startingColumn_;
            ++row_;
        }
        return *this;
    }

    Self operator++(int) {
        return ++Self(*this);
    }

    Self& operator--() {
        --column_;
        if (column_ < startingColumn_) {
            column_ = lastColumn_ - 1;
            --row_;
        }
        return *this;
    }

    Self operator--(int) {
        return --Self(*this);
    }

    reference operator*() const {
        return matrix_[row_][column_];
    }

    pointer operator->() const {
        return &matrix_[row_][column_];
    }

private:

    Matrix& matrix_;

    size_t startingColumn_;

    size_t row_;

    size_t column_;

    size_t lastRow_;

    size_t lastColumn_;

};

} // namespace detail

template <class T>
class Matrix {

    class Row {
    public:

        Row() {
        }

        Row(size_t width) {
            row_.reserve(width);
            row_.resize(width);
        }

        T& operator[](size_t i) {
            return row_[i];
        }

        T& operator[](size_t i) const {
            return row_[i];
        }

        void resize(size_t width) {
            row_.reserve(width);
            row_.resize(width);
        }

    private:

        std::vector<T> row_;

    };

public:

    typedef Matrix<T> Self;

    typedef T Value;

    typedef T& Reference;

    typedef T* Pointer;

    typedef MatrixIterator<Self, Value> Iterator;

    typedef MatrixIterator<const Self, const Value> ConstIterator;

    Matrix() {
    }

    Matrix(size_t height, size_t width) :
        height_(height), width_(width) {
        rows_.resize(height);
        rows_.resize(height, width);
    }

    Row& operator[](size_t i) {
        return rows_[i];
    }

    const Row& operator[](size_t i) const {
        return rows_[i];
    }

    void resize(size_t height, size_t width) {
        height_ = height;
        width_ = width;
        rows_.reserve(height);
        rows_.resize(height);
        std::for_each(rows_.begin(), rows_.end(), std::mem_fun(&Row::resize));
    }

    size_t height() const {
        return height_;
    }

    size_t width() const {
        return width_;
    }

    Iterator begin() {
        return Iterator(*this, height_, width_);
    }

    ConstIterator begin() const {
        return ConstIterator(*this, height_, width_);
    }

    Iterator end() {
        return Iterator(*this, height_, width_, height_, width_);
    }

    ConstIterator end() const {
        return ConstIterator(*this, height_, width_, height_, width_);
    }

    std::pair<Iterator, Iterator> range(size_t row, size_t column, size_t lastRow, size_t lastColumn) {
        return std::pair<Iterator, Iterator>(Iterator(*this, row, column, lastRow, lastColumn),
                Iterator(*this, lastRow, lastColumn, lastRow, lastColumn));
    }

    std::pair<ConstIterator, ConstIterator> range(size_t row, size_t column, size_t lastRow, size_t lastColumn) {
        return std::pair<ConstIterator, ConstIterator>(ConstIterator(*this, row, column, lastRow, lastColumn),
                ConstIterator(*this, lastRow, lastColumn, lastRow, lastColumn));
    }

private:

    size_t height_;

    size_t width_;

    std::vector<Row> rows_;

};

} // namespace CoconutEngine

#endif /* MATRIX_HPP_ */
