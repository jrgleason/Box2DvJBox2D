#ifndef B2GLPOLYGONSHAPE_H_
#define B2GLPOLYGONSHAPE_H_

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <OpenBox/Collision/Shapes/b2GLPolygonShape.h>
#include <OpenBox/GLManager.h>
#include <GLES/gl.h>
#include <Box2D/JNIBox2DWorld.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Collision/Shapes/b2Shape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/android-log.h>

class b2GLPolygonShape 
{
public:
  void Draw();
  void Draw(b2PolygonShape* s, b2Body* b);
};
#endif
