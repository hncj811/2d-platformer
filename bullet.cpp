#include <cmath>
#include "bullet.h"
#include "explodingSprite.h"


bool Bullet::collidedWith(const Drawable* obj2) {

  float left1 = X();
  float left2 = obj2->X();
  float right1 = left1+ frameWidth;
  float right2 = left2+obj2->getFrame()->getWidth();
  if ( right1 < left2 ) return false;
  if ( left1 > right2 ) return false;
  float top1 = Y();
  float top2 = obj2->Y();
  float bottom1 = top1+ frameHeight;
  float bottom2 = top2+obj2->getFrame()->getHeight();
  if ( bottom1 < top2 ) return false;
  if ( bottom2 < top1 ) return false;
   
  explode();
  return true;
}

void Bullet::update(Uint32 ticks) 
{ 
  timeSinceShot += ticks;
  if ( timeSinceShot >= 3500) {
	  explode();
	  //life = false;
  }
  if ( explosion ) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 || timeSinceShot >=4500 ) {
      delete explosion;
      explosion = NULL;
      life= false;
    }
    return;
  }
  
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
  velocityY( velocityY() + 7);
  if ( Y() < 0) {
    velocityY( 0 ); life  = false;
  }
  if( Y() > Gamedata::getInstance().getXmlInt("world/groundLevel") )
	  explode();
  if ( Y() > worldHeight-frameHeight) {
    velocityY( 0 );  life = false;
  }

  if ( X() < 0) {
    velocityX( 0);  life = false;
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( 0  ); life = false;
  }  
}

void Bullet::reset(const Vector2f& pos, const Vector2f& vel ){
  setVelocity(vel);
  setPosition(pos);
  life = true;
  timeSinceShot = 0;
  explosion = NULL;
}

void Bullet::explode() { 
  if ( explosion ) return;
  Sprite sprite(getName(), getPosition(), getVelocity(), getFrame());
  explosion = new ExplodingSprite(sprite); 
  //std::cout << "called new explosion\n";
}

void Bullet::draw(){
  if (explosion) {
    explosion->draw();
    return;
  }
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y); 

}
