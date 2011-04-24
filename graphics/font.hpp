#ifndef COCONUTENGINE_FONT_HPP_
#define COCONUTENGINE_FONT_HPP_

#include <string>
#include <map>

#include "texture.hpp"
#include "colour.hpp"
#include "vector.hpp"
#include "rectangle.hpp"

namespace coconutengine {

template <class Key> class Settings;

class Font {
public:

    Font(const Settings<std::string>& settings, const std::string& prefix);

    void print(const std::string& s, const Rectangle<Vec2D>& bounds, const Colour& colour) const;

private:

    Vec2D textureSize_;

    Texture texture_;

    std::map<char, Rectangle<Vec2D> > charBounds_;

    Vec2D maxBounds_;

};

} // namespace coconutengine

#endif /* COCONUTENGINE_FONT_HPP_ */
