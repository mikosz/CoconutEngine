#include "font.hpp"

#include <fstream>
#include <stdexcept>
#include <sstream>
#include <algorithm>

#include <GL/gl.h>

#include "settings.hpp"
#include "bitmap.hpp"
#include "log.hpp"

using namespace coconutengine;

namespace {

void setupBounds(std::map<char, Rectangle<Vec2D> >& bounds, Vec2D& maxBounds,
        const Settings<std::string>& settings, const std::string& prefix, size_t textureHeight) {
    bool teleType = getSetting<bool>(settings, prefix + ".teleType");
    std::string descFile = getSetting<std::string>(settings, prefix + ".description");
    std::ifstream fontDesc(descFile.c_str());
    std::string line;

    if (teleType) {
        maxBounds.x() = getSetting<float>(settings, prefix + ".width");
        maxBounds.y() = getSetting<float>(settings, prefix + ".height");
    } else {
        maxBounds.x() = 0.0f;
        maxBounds.y() = 0.0f;
    }

    Rectangle<Vec2D> bound(Vec2D(0.0f, textureHeight - maxBounds.y()), Vec2D(maxBounds.x(), textureHeight));

    while (std::getline(fontDesc, line)) {
        std::istringstream desc(line);
        char c;

        while (desc) {
            desc >> c;
            if (!teleType) {
                desc >> bound.bottomLeft.x() >> bound.bottomLeft.y() >> bound.topRight.x()
                        >> bound.topRight.y();
                maxBounds.x() = std::max(maxBounds.x(), bound.topRight.x() - bound.bottomLeft.x());
                maxBounds.y() = std::max(maxBounds.y(), bound.topRight.y() - bound.bottomLeft.y());
            }

            if (!desc) {
                break;
            }

            bounds[c] = bound;

            if (teleType) {
                bound.bottomLeft.x() += maxBounds.x();
                bound.topRight.x() += maxBounds.x();
            }
        }

        if (!desc.eof()) {
            throw std::runtime_error("Failed to read " + descFile + ", line: " + line);
        }

        if (teleType) {
            bound.bottomLeft.x() = 0.0f;
            bound.bottomLeft.y() -= maxBounds.y();
            bound.topRight.x() = maxBounds.x();
            bound.topRight.y() -= maxBounds.y();
        }
    }
    if (!fontDesc.eof()) {
        throw std::runtime_error("Failed to read " + descFile + ", last line read: " + line);
    }
}

} // anonymous namespace

Font::Font(const Settings<std::string>& settings, const std::string& prefix) {
    Bitmap texture(getSetting<std::string>(settings, prefix + ".texture"));
    texture.transparentColour(Colour::BLACK);
    setupBounds(charBounds_, maxBounds_, settings, prefix, texture.height());
    texture_.load(texture);
    textureSize_ = Vec2D(texture.width(), texture.height());
}

void Font::print(const std::string& s, const Rectangle<Vec2D>& bounds, const Colour& colour) const {
    texture_.enable();
    texture_.bind();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor3fv(colour.toRGBA());

    Vec2D pos(bounds.bottomLeft.x(), bounds.topRight.y() - maxBounds_.y());

    for (size_t i = 0; i < s.length(); ++i) {
        if (s[i] == ' ') {
            pos.x() += maxBounds_.x();
        } else if (s[i] == '\n') {
            pos.x() = bounds.bottomLeft.x();
            pos.y() -= maxBounds_.y();
        } else {
            const Rectangle<Vec2D>& letterBounds = charBounds_.at(s[i]);
            float letterWidth = letterBounds.topRight.x() - letterBounds.bottomLeft.x();
            float letterHeight = letterBounds.topRight.y() - letterBounds.bottomLeft.y();

            glBegin(GL_QUADS);
            glTexCoord2f(letterBounds.bottomLeft.x() / textureSize_.x(), letterBounds.bottomLeft.y() / textureSize_.y());
            glVertex2f(pos.x(), pos.y());
            glTexCoord2f(letterBounds.topRight.x() / textureSize_.x(), letterBounds.bottomLeft.y() / textureSize_.y());
            glVertex2f(pos.x() + letterWidth, pos.y());
            glTexCoord2f(letterBounds.topRight.x() / textureSize_.x(), letterBounds.topRight.y() / textureSize_.y());
            glVertex2f(pos.x() + letterWidth, pos.y() + letterHeight);
            glTexCoord2f(letterBounds.bottomLeft.x() / textureSize_.x(), letterBounds.topRight.y() / textureSize_.y());
            glVertex2f(pos.x(), pos.y() + letterHeight);
            glEnd();

            pos.x() += letterWidth;
        }
    }

    texture_.disable();

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}
