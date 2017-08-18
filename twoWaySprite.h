#ifndef TWOWAYSPRITE__H
#define TWOWAYSPRITE__H

#include <string>
#include <vector>
#include "drawable.h"
#include "frameFactory.h"

class twoWaySprite : public Drawable {
public:
  twoWaySprite(const std::string&, const std::vector<Frame*>&, const std::vector<Frame*>&);
  twoWaySprite( const std::string& name );
  virtual ~twoWaySprite() { } 

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }

protected:
  const std::vector<Frame *> frames;
  const std::vector<Frame *> framesLeft;
  int worldWidth;
  int worldHeight;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;

  void advanceFrame(Uint32 ticks);
  twoWaySprite(const twoWaySprite&);
  twoWaySprite& operator=(const twoWaySprite&);
};
#endif
