/*
 * octree.hpp
 *
 *  Created on: 2010-08-23
 *      Author: mikosz
 */

#ifndef OCTREE_HPP_
#define OCTREE_HPP_

#include "utils/rectangle.hpp"
#include "utils/vector.hpp"
#include "utils/fulltree.hpp"

namespace coconutengine {

template <class Element>
class Octree {
public:

    class Node {
    public:

        Node(const Rectangle<Vec3D>& boundingBox) :
            boundingBox_(boundingBox),
            divisionPoint_(calculateDivisionPoint(boundingBox)) {
        }

    private:

        Rectangle<Vec3D> boundingBox_;

        Vec3D divisionPoint_;

        std::list<Element> elements_;

        static Vec3D calculateDivisionPoint(const Rectangle<Vec3D>& boundingBox) {
            return (boundingBox.topRight - boundingBox.bottomLeft) / 2;
        }

    };

    typedef Element ElementType;

    Octree(size_t depth) :
        tree_(depth) {
    }

private:

    FullTree<8, Node> tree_;

};

} // namespace coconutengine

#endif /* OCTREE_HPP_ */
