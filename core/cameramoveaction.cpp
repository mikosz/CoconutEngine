/*
 * cameramoveaction.cpp
 *
 *  Created on: 2010-01-26
 *      Author: mikosz
 */

#include <cameramoveaction.hpp>
#include <camera.hpp>

using namespace coconutengine;

CameraMoveAction::CameraMoveAction(Camera& camera, const Vec3D& direction, const Settings<std::string>& settings,
        const std::string& prefix) :
    AccelerationAction(settings, prefix), camera_(camera), direction_(direction) {
}

void CameraMoveAction::update(Milliseconds delta) {
    AccelerationAction::update(delta);

    Vec3D& position = camera_.position();
    position += direction_.normalised() * velocity() * delta;
}
