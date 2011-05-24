/*
 * camera.hpp
 *
 *  Created on: Sep 22, 2008
 *      Author: mikosz
 */

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <vector.hpp>
#include <string>
#include <frustum.hpp>

namespace coconutengine {
namespace graphics {
namespace terrain {
class Terrain;
} // namespace terrain
} // namespace graphics

template <class> class Settings;
class Terrain;

class Camera
{
public:

    Camera(const graphics::terrain::Terrain& terrain, const Settings<std::string>& settings,
            const std::string& prefix);

    Vec3D& position() { return position_; }

    const Vec3D& position() const { return position_; }

    Vec3D& rotation() { return rotation_; }

    const Vec3D& rotation() const { return rotation_; }

    const float fov() const { return fov_; }

    const float nearPlane() const { return nearPlane_; }

    const float farPlane() const { return farPlane_; }

    void setupPerspective(float aspectRatio) const;

    void setupOrthographic(float width, float height) const;

    Frustum frustum() const;

    void moveRelative(const Vec3D& direction);

private:

    const graphics::terrain::Terrain& terrain_;

    float fov_;

    float nearPlane_;

    float farPlane_;

    Vec3D position_;

    Vec3D rotation_;

};

}

#endif /* CAMERA_HPP_ */
