#ifndef PLAYERSPRITE__H
#define PLAYERSPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "twoWaySprite.h"
#include "frameFactory.h"
#include "gamedata.h"
#include "weaponPool.h"

class ExplodingSprite;
class PlayerSprite : public twoWaySprite{
public:
  PlayerSprite( const std::string& name);
  PlayerSprite( const PlayerSprite& s );
  virtual ~PlayerSprite() { }
  virtual void draw () const;
  virtual void update(Uint32 ticks);
  void moveLeft();
  void moveRight();
  void jump();
  void explode();
  void reset();
  void fire();
  bool shots(const Drawable*);
  virtual bool collidedWith(const Drawable*); 
  //bool shots(const Drawable*);
  float distance(float x1, float y1, float x2, float y2) const {
    float x = x1-x2, y = y1-y2;  return hypot(x, y);
  }
  void changeHealth(int hit) { health += hit; }
  int inUse() const { return iceCubes.inUseSize();  }
  int available() const { return iceCubes.availableSize();  }
  
private:
  ExplodingSprite* explosion;
  std::vector<Frame *> framesJump;  
  //const std::vector<Frame *> framesJumpLeft; 
  const std::string name;
  
  int numberOfJumpFrames;
  int jumpFrameInterval;
  int health;
  WeaponPool iceCubes;
  virtual void advanceFrame( Uint32 ticks);
  PlayerSprite& operator=(const PlayerSprite&);
};

#endif
