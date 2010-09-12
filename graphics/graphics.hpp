/*
 * graphics.hpp
 *
 *  Created on: Oct 14, 2008
 *      Author: mikosz
 */

#ifndef GRAPHICS_HPP_
#define GRAPHICS_HPP_

#include <GL/gl.h>
#include <colour.hpp>
#include <boost/noncopyable.hpp>

namespace CoconutEngine
{

class Graphics : boost::noncopyable
{
public:

    static Graphics& instance();

    void initEngine();

    void beginScene();

    void endScene();

    void drawWireframe();

private:

    static Graphics* instance_;

    Graphics();

};

} // namespace CoconutEngine

#endif /* GRAPHICS_HPP_ */
