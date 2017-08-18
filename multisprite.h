#ifndef MULTISPRITE__H
#define MULTISPRITE__H
#include <string>
#include <vector>
#include "drawable.h"
#include "frameFactory.h"
class MultiSprite : public Drawable {
public:
  MultiSprite(const std::string&, const std::vector<Frame*>&);
  MultiSprite( const std::string& name );
  virtual ~MultiSprite() { } 

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }

protected:
  const std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;

  void advanceFrame(Uint32 ticks);
  MultiSprite(const MultiSprite&);
  MultiSprite& operator=(const MultiSprite&);
};
#endif
