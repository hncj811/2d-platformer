#ifndef BULLET__H
#define BULLET__H
#include <cstdlib>
#include <list>
#include <string>
#include "gamedata.h"
#include "sprite.h"
#include "vector2f.h"


class ExplodingSprite;
class Bullet : public Sprite{
public:
  Bullet( const std::string& n, const Vector2f& pos, const Vector2f& vel ):
    Sprite(n, pos, vel ), 
    life(true), 
    timeSinceShot(0), 
    explosion(NULL)
  {  }
  virtual void draw();
  bool lifeStatus() {return life; }
  void reset( const Vector2f& pos, const Vector2f& vel );
  virtual void update(Uint32 ticks);
  virtual bool collidedWith(const Drawable*); 
  bool explodeStatus() { if( explosion != NULL) { return true; } return false; }
  void explode();
private:
  bool life;
  int timeSinceShot;
  ExplodingSprite* explosion;
	
};

#endif
