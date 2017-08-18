#include <string>
#include <vector>
#include "ioManager.h"
#include "frame.h"
#include "viewport.h"
#include "frameFactory.h"

class MultiWorld {
public:
  MultiWorld(const std::string& name, int fact);
  // ~MultiWorld() { ; } // The frame will be deleted by the FrameFactory
  void update(Uint32);
  void draw() const;
private:
  const IOManager& io;
  const std::vector<Frame*> frames;
  int factor;
  unsigned frameWidth;
  unsigned worldWidth;
  float viewX;
  float viewY;
  const Viewport & view;
  
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameHeight;
  void advanceFrame(Uint32 ticks);
  MultiWorld(const MultiWorld&);
  MultiWorld& operator=(const MultiWorld&);
};
