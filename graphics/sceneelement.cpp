#include "sceneelement.hpp"

#include <GL/gl.h>

using namespace coconutengine;

void SceneElement::render(const Camera& camera) const {
#warning if(renderBoundingBox) ?

    renderBoundingBox(camera);
    this->doRender(camera);
}

void SceneElement::renderBoundingBox(const Camera& camera) const {
    GLint lighting;
    glGetIntegerv(GL_LIGHTING, &lighting);
    glDisable(GL_LIGHTING);

    GLint polygonMode;
    glGetIntegerv(GL_POLYGON_MODE, &polygonMode);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);
    {
        // bottom
        glVertex3f(boundingBox_.bottomLeft.x(), boundingBox_.bottomLeft.y(), boundingBox_.bottomLeft.z());
        glVertex3f(boundingBox_.topRight.x(), boundingBox_.bottomLeft.y(), boundingBox_.bottomLeft.z());
        glVertex3f(boundingBox_.topRight.x(), boundingBox_.topRight.y(), boundingBox_.bottomLeft.z());
        glVertex3f(boundingBox_.bottomLeft.x(), boundingBox_.topRight.y(), boundingBox_.bottomLeft.z());

        // top
        glVertex3f(boundingBox_.bottomLeft.x(), boundingBox_.bottomLeft.y(), boundingBox_.topRight.z());
        glVertex3f(boundingBox_.topRight.x(), boundingBox_.bottomLeft.y(), boundingBox_.topRight.z());
        glVertex3f(boundingBox_.topRight.x(), boundingBox_.topRight.y(), boundingBox_.topRight.z());
        glVertex3f(boundingBox_.bottomLeft.x(), boundingBox_.topRight.y(), boundingBox_.topRight.z());

        // front
        glVertex3f(boundingBox_.bottomLeft.x(), boundingBox_.bottomLeft.y(), boundingBox_.bottomLeft.z());
        glVertex3f(boundingBox_.topRight.x(), boundingBox_.bottomLeft.y(), boundingBox_.bottomLeft.z());
        glVertex3f(boundingBox_.topRight.x(), boundingBox_.bottomLeft.y(), boundingBox_.topRight.z());
        glVertex3f(boundingBox_.bottomLeft.x(), boundingBox_.bottomLeft.y(), boundingBox_.topRight.z());

        // back
        glVertex3f(boundingBox_.bottomLeft.x(), boundingBox_.topRight.y(), boundingBox_.bottomLeft.z());
        glVertex3f(boundingBox_.topRight.x(), boundingBox_.topRight.y(), boundingBox_.bottomLeft.z());
        glVertex3f(boundingBox_.topRight.x(), boundingBox_.topRight.y(), boundingBox_.topRight.z());
        glVertex3f(boundingBox_.bottomLeft.x(), boundingBox_.topRight.y(), boundingBox_.topRight.z());

        // lines only, so no need for right and left faces
    }
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    if (lighting) {
        glEnable(GL_LIGHTING);
    }
}
