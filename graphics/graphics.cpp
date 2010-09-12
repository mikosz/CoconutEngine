/*
 * graphics.cpp
 *
 *  Created on: Nov 26, 2008
 *      Author: mikosz
 */

#include <graphics.hpp>

#include <GL/gl.h>

using namespace CoconutEngine;

Graphics* Graphics::instance_ = 0;

Graphics& Graphics::instance() {
    if (!instance_) {
        instance_ = new Graphics();
    }
    return *instance_;
}

Graphics::Graphics() {
}

void Graphics::initEngine() {
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

void Graphics::beginScene() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Graphics::endScene() {

}

void Graphics::drawWireframe() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
