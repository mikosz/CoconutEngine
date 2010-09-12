/*
 * camera.cpp
 *
 *  Created on: Sep 22, 2008
 *      Author: mikosz
 */

#include <camera.hpp>

#include <GL/gl.h>
#include <GL/glu.h>
#include <settings.hpp>
#include <utility.hpp>
#include <cmath>

using namespace CoconutEngine;

namespace
{

Plane extractPlane(GLfloat matrix[], short row)
{
    int scale = (row < 0) ? -1 : 1;
    row = abs(row) - 1;

    Plane result(
            matrix[3] + scale * matrix[row],
            matrix[7] + scale * matrix[row + 4],
            matrix[11] + scale * matrix[row + 8],
            matrix[15] + scale * matrix[row + 12]
    );

    // normalize the plane
    float length = sqrt(result.a * result.a + result.b * result.b + result.c * result.c);
    result.a /= length;
    result.b /= length;
    result.c /= length;
    result.d /= length;

    return result;
}

} // anonymous namespace

Camera::Camera(const Settings<std::string>& settings, const std::string& prefix) :
    fov_(getSetting<float>(settings, prefix + ".fov")),
    nearPlane_(getSetting<float>(settings, prefix + ".near_plane")),
    farPlane_(getSetting<float>(settings, prefix + ".far_plane")),
    position_(settings, prefix + ".position"),
    rotation_(settings, prefix + ".rotation")
{}

void Camera::setupOrthographic(float width, float height) const
{
    // TODO: Hard coded
    gluOrtho2D(0.0f, width, 0.0f, height);
}

void Camera::setupPerspective(float aspectRatio) const
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // TODO: Hard coded
    gluPerspective(fov_, aspectRatio, nearPlane_, farPlane_);

    glMatrixMode(GL_MODELVIEW);
    glRotatef(toDegrees(-rotation_.x()), 1.0f, 0.0f, 0.0f);
    glRotatef(toDegrees(-rotation_.y()), 0.0f, 1.0f, 0.0f);
    glRotatef(toDegrees(-rotation_.z()), 0.0f, 0.0f, 1.0f);
    glTranslatef(-position_.x(), -position_.y(), -position_.z());
}

Frustum Camera::frustum() const
{
    GLfloat projection[16];
    GLfloat modelview[16];

    glGetFloatv(GL_PROJECTION_MATRIX, projection);
    glGetFloatv(GL_MODELVIEW_MATRIX, modelview);

    glPushMatrix();
    glLoadMatrixf(projection);
    glMultMatrixf(modelview);
    glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
    glPopMatrix();

    return Frustum(
            extractPlane(modelview, 3),
            extractPlane(modelview, -3),
            extractPlane(modelview, -2),
            extractPlane(modelview, 2),
            extractPlane(modelview, 1),
            extractPlane(modelview, -1)
            );
}
