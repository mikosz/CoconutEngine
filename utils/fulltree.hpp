/*
 * ntree.hpp
 *
 *  Created on: 2010-01-28
 *      Author: mikosz
 */

#ifndef NTREE_HPP_
#define NTREE_HPP_

#include <vector>
#include <cmath>
#include <boost/function.hpp>
#include <boost/call_traits.hpp>

template<unsigned char N, class ElementType>
class FullTree {
public:

    explicit FullTree(unsigned char depth) :
        depth_(depth), tree_((std::pow(N, depth + 1) - 1) / (N - 1)) {
    }

    std::vector<ElementType>& tree() {
        return tree_;
    }

    const std::vector<ElementType>& tree() const {
        return tree_;
    }

    size_t getLeftChild(size_t parent) const {
        return parent * N + 1;
    }

    bool hasChildren(size_t parent) const {
        return parent * N + 1 < tree_.size();
    }

    const unsigned char depth() const {
        return depth_;
    }

private:

    unsigned char depth_;

    std::vector<ElementType> tree_;

};

template<class ElementType>
class FullTree<1, ElementType> {
private:

    FullTree();

};

template<class ElementType>
class FullTree<0, ElementType> {
private:

    FullTree();

};

#endif /* NTREE_HPP_ */
