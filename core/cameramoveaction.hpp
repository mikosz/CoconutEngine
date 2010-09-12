/*
 * cameramoveaction.hpp
 *
 *  Created on: 2010-01-26
 *      Author: mikosz
 */

#ifndef CAMERAMOVEACTION_HPP_
#define CAMERAMOVEACTION_HPP_

#include <accelerationaction.hpp>
#include <vector.hpp>
#include <string>
#include <timemanager.hpp>

namespace CoconutEngine {

class Camera;
template <class> class Settings;

class CameraMoveAction: public AccelerationAction {
public:

    CameraMoveAction(Camera& camera, const Vec3D& direction, const Settings<std::string>& settings,
            const std::string& prefix);

    void update(Milliseconds delta);

    Vec3D& direction() {
        return direction_;
    }

    const Vec3D& direction() const {
        return direction_;
    }

private:

    Camera& camera_;

    Vec3D direction_;

};

}

#endif /* CAMERAMOVEACTION_HPP_ */
