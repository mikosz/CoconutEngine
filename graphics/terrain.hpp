/*
 * terrain.hpp
 *
 *  Created on: Dec 1, 2008
 *      Author: mikosz
 */

#ifndef TERRAIN_HPP_
#define TERRAIN_HPP_

#include <bitmap.hpp>
#include <string>
#include <vector.hpp>
#include <ntree.hpp>
#include <rectangle.hpp>
#include <auto_ptr.h>
#include <boost/scoped_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>

namespace ublas = boost::numeric::ublas;

namespace CoconutEngine {

template<class > class Settings;
class Camera;

class Terrain {
public:

    static std::auto_ptr<Terrain> create(const Settings<std::string>& settings, const std::string& prefix);

    void render(const Camera& camera) const;

private:

    struct HeightMapVertex {

        float height;

        Vec3D normal;

    };

    typedef ublas::matrix<HeightMapVertex> HeightMap;

    Terrain(const Bitmap* heightMapImage, const Settings<std::string>& settings, const std::string& prefix);

    struct QuadTreeEntry {
        Rectangle<Vec3D> boundingBox;

        Rectangle<Vector3D<size_t> > area;
    };

    QuadTree<QuadTreeEntry> quadTree_;

    HeightMap heightMap_;

    float waterLevel_;

    float renderingStep_;

    void setupHeightMap(const Bitmap* heightMapImage, float heightScalingFactor);

    QuadTreeEntry setupQuadTree(unsigned short level, Rectangle<Vector3D<size_t> > area, size_t node);

    void render(const Camera& camera, size_t node) const;

};

} // namespace CoconutEngine

#endif /* TERRAIN_HPP_ */
