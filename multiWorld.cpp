#include "multiWorld.h"
#include "gamedata.h"
#include "frameFactory.h"


MultiWorld::MultiWorld(const std::string& name, int fact) : 
  io( IOManager::getInstance() ),
  frames(  FrameFactory::getInstance().getFrames(name) ) ,
  factor(fact),
  frameWidth( frames[0]->getWidth() ),
  worldWidth( Gamedata::getInstance().getXmlInt("world/width") ),
  viewX(0.0), viewY(0.0), 
  view(Viewport::getInstance()), 
    
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameHeight(frames[0]->getHeight()) 
{}


void MultiWorld::advanceFrame(Uint32 ticks){
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

void MultiWorld::update(Uint32 ticks){
  advanceFrame(ticks);
  viewX = static_cast<int>(view.X() / factor) % frameWidth;
  viewY = view.Y();
	
}

void MultiWorld::draw() const { 
  frames[currentFrame]->draw(viewX, viewY, 0, 0); 
  frames[currentFrame]->draw(0, viewY, frameWidth-viewX, 0); 
}

