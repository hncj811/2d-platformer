#include "playerSprite.h"
#include "twoWaySprite.h"
#include "explodingSprite.h"
#include <cmath>
PlayerSprite::PlayerSprite( const std::string& name ) :
  twoWaySprite(name),
  explosion(NULL),
  framesJump( ),
  //framesJumpLeft( FrameFactory::getInstance().getFrames(name +"JumpLeft") ),
  name(name),
  numberOfJumpFrames( Gamedata::getInstance().getXmlInt(name+"Jump/frames") ),
  jumpFrameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ) 
  , health(100), 
  iceCubes("iceCube")
{ 
  X( 100);
  velocityX(0.1);
  Y(Gamedata::getInstance().getXmlInt("world/groundLevel") - 100 );
  framesJump.push_back( FrameFactory::getInstance().getFrame(name +"Jump1") );     // jump right is ndx 0
  framesJump.push_back( FrameFactory::getInstance().getFrame(name +"Jump1Left") ); //jump Left is ndx 1
  framesJump.push_back( FrameFactory::getInstance().getFrame(name +"Land1") );     // land right is ndx 2
  framesJump.push_back( FrameFactory::getInstance().getFrame(name +"Land1Left") ); // land left is ndx 3

}

PlayerSprite::PlayerSprite( const PlayerSprite& s ):
  twoWaySprite(s.name),
  explosion(NULL),
  framesJump( ),
  //framesJumpLeft( FrameFactory::getInstance().getFrames(s.name +"JumpLeft") ),
  name(s.name),
  numberOfJumpFrames( Gamedata::getInstance().getXmlInt(s.name+"Jump/frames") ),
  jumpFrameInterval( Gamedata::getInstance().getXmlInt(s.name+"/frameInterval") ) 
  , health(100), 
  iceCubes("iceCube")
{ 
  Y(Gamedata::getInstance().getXmlInt("world/groundLevel") - 100 );
  framesJump.push_back( FrameFactory::getInstance().getFrame(name +"Jump1") );     // jump right is ndx 0
  framesJump.push_back( FrameFactory::getInstance().getFrame(name +"Jump1Left") );  // jump left is ndx 1
  framesJump.push_back( FrameFactory::getInstance().getFrame(name +"Land1") );     // land right is ndx 2
  framesJump.push_back( FrameFactory::getInstance().getFrame(name +"Land1Left") );  // land left is dnx3
}


void PlayerSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	  if (timeSinceLastFrame > frameInterval) {
        currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	  }
	/*******************
	  else{ 
	 *********** if (timeSinceLastFrame > jumpFrameInterval) {
        currentFrame = (currentFrame+1) % numberOfJumpFrames;
		timeSinceLastFrame = 0;
	  }  *******
  	  //std::cout << "made it to else in advanceFrame. CurrFrame is\t" <<currentFrame <<std::endl;
	  if( velocityY() < 0){
		currentFrame = 2;
		//std::cout << "made it to else in advanceFrame. CurrFrame is\t" <<currentFrame <<std::endl;
      }
	  else
	    currentFrame = 	2;	  
	}*/
}


void PlayerSprite::draw() const { 
  iceCubes.draw();
  if (explosion) {
    explosion->draw();
    return;
  }
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  if( velocityX() >=0.001 ){
	/*if(Y() >=  Gamedata::getInstance().getXmlInt("world/groundLevel") - 100 )
	  frames[currentFrame]->draw(x, y);
    else
      framesJump[currentFrame]->draw(x, y); ***/
      if(velocityY() == 0) frames[currentFrame]->draw(x, y);
      else if(velocityY() < 0)
        framesJump[0]->draw(x, y);
      else 
        framesJump[2]->draw(x, y);
  }
  if ( velocityX() <= 0) {  //left 
    /*if(Y() >=  Gamedata::getInstance().getXmlInt("world/groundLevel") - 100){
      std::cout << currentFrame <<std::endl;
      framesLeft[currentFrame]->draw(x, y);
    }  
	else  framesJumpLeft[2]->draw(x, y); *********/
    if(velocityY() == 0) framesLeft[currentFrame]->draw(x, y);
    else if(velocityY() < 0)
        framesJump[1]->draw(x, y);
    else 
        framesJump[3]->draw(x, y);
  }
}

void PlayerSprite::explode() { 
  if ( explosion ) return;
  Sprite sprite(getName(), getPosition(), getVelocity(), getFrame());
  explosion = new ExplodingSprite(sprite); 
}


void PlayerSprite::update(Uint32 ticks) { 
  iceCubes.update(ticks);
  if(health <=0) explode();
  if (explosion) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 ) {
      delete explosion;
      explosion = NULL;
      reset();
    }
    
    return;
  }
  advanceFrame(ticks);
    Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  /*if ( Y() < 50) {
    velocityY( -10 );
  }
  if ( Y() > Gamedata::getInstance().getXmlInt("world/groundLevel") - 100) {
    velocityY(  0 );
    Y(Gamedata::getInstance().getXmlInt("world/groundLevel") - 100);
  }****************************/
  
  if( velocityY() !=0){
	  //Y(Y() +2 );
    if ( Y() >= Gamedata::getInstance().getXmlInt("world/groundLevel") - 100) {
      velocityY( 0 );
      Y(Gamedata::getInstance().getXmlInt("world/groundLevel") - 100);
    }
    else if(velocityY() < 55 )
	  velocityY( velocityY() + 9);
  }

  if ( X() < 2) {
    setPosition(Vector2f(10, Y()) );
    velocityX( std::abs( 0 ) );
  }
  if ( X()+ ( 4 + frameWidth) >= worldWidth ) {
    velocityX( 0.001);
    setPosition(Vector2f(worldWidth - frameWidth -10, Y()) );
  }  
}

void PlayerSprite::moveLeft(){
	
   if(velocityX() > -300)
            velocityX(velocityX()-20);
        else
         velocityX(-300);
}

void PlayerSprite::moveRight(){
	
   if(velocityX() < 300)
       velocityX(velocityX()+20);
   else
       velocityX(300);
}

void PlayerSprite::jump(){
	if(velocityY() != 0) return;
	//currentFrame =0;
	//Y(Y() - 170);
	velocityY(-300);
}

void PlayerSprite::reset(){
	X(Gamedata::getInstance().getXmlInt(name+"/startLoc/x") );
	velocityX(1);
	Y(Gamedata::getInstance().getXmlInt("world/groundLevel") - 100 );
	velocityY(0);
	currentFrame = 0;
	health = 100;
	if (explosion){
	  delete explosion;
	  explosion = NULL;
	}
 }

void PlayerSprite::fire(){
	Vector2f firePos= getPosition();
	Vector2f fireVel= getVelocity();
	if (velocityX() > 0 )
	{
		firePos[0] +=  200;
		fireVel[0] += 350;
	}
	else{
		fireVel[0] -= 350;
	}
	//fireVel[0] += Gamedata::getInstance().getXmlInt("iceCube/speedX") ; 
  iceCubes.getAttack(firePos, fireVel );
}


 bool PlayerSprite::collidedWith(const Drawable* obj2) {

 /* int COLLISION_DISTANCE = frameWidth/2 + obj2->getFrame()->getWidth()/2;
  float xobj1 = X()+              frameWidth/2;
  float yobj1 = Y()+ frameHeight/2;
  float xobj2 = obj2->X() + obj2->getFrame()->getWidth()/2;
  float yobj2 = obj2->Y() + obj2->getFrame()->getHeight()/2;
  return distance(xobj1, yobj1, xobj2, yobj2) < COLLISION_DISTANCE;
*/  ///mid dist 

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
  health =health - 15;
  return true;
}

bool PlayerSprite::shots( const Drawable* obj){
	return iceCubes.collisions(obj);
}

