#include <cmath>
#include "enemySprite.h"
#include "explodingSprite.h"
#include "weaponPool.h"

EnemySprite::EnemySprite(const std::string& n, const std::string& weapon):
  twoWaySprite(n),
  explosion(NULL),
  dir(-1),
  attack(weapon),
  range(500),
  health(100),
  home( X() ), 
  life(true)
  
{
  Y(Gamedata::getInstance().getXmlInt("world/groundLevel") - 100 );
  if (X() < 660) {
	  int x = rand() % 2000;
	  X( X() + x);
  }
  if ( X() > Gamedata::getInstance().getXmlInt("world/width") -400 ){
	  int x = rand() % 2000;
	  X( x);
  }
	  
}

EnemySprite::EnemySprite( const EnemySprite& e):
  twoWaySprite(e.getName()),
  explosion(NULL),
  dir(e.dir),
  attack(e.attack),
  range(e.range),
  health(e.health),
  home( e.X() ), 
  life(e.life)
{
	Y(e.Y() );
}

void EnemySprite::draw() const{
  attack.draw();
  if (explosion) {
    explosion->draw();
    return;
  }
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  if( velocityX() >=0 ) frames[currentFrame]->draw(x, y);
  if ( velocityX() < 0) framesLeft[currentFrame]->draw(x, y);
}

void EnemySprite::update(Uint32 ticks){
  advanceFrame(ticks);
  attack.update(ticks);
  if(health <=0) explode();
  if(explosion) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 || explosion->getLife() > 4500) {
      delete explosion;
      explosion = NULL;
      life = false;
    }
    return;
  }
  
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( X() < 2){
	   dir *= -1;
	   velocityX( velocityX() * dir);
  }
  if ( X()+ ( 4 + frameWidth) >= worldWidth ){
	   dir *= -1;
       velocityX( velocityX() * dir);
  }
  if( std::abs( X() - home)  > range) {
	  dir *= -1; 
    velocityX( velocityX() * dir);
  }
  
}

void EnemySprite::explode() { 
  if ( explosion ) return;
  Sprite sprite(getName(), getPosition(), getVelocity(), getFrame());
  explosion = new ExplodingSprite(sprite); 
}

bool EnemySprite::shots( const Drawable* obj){
	return attack.collisions(obj);
}

void EnemySprite::fire(){
	Vector2f firePos= getPosition();
	Vector2f fireVel= getVelocity();
	if (velocityX() > 0 )
	{
		firePos[0] +=  200;
		fireVel[0] += 300;
	}
	else{
		fireVel[0] -= 300;
	}
	//fireVel[0] += Gamedata::getInstance().getXmlInt("iceCube/speedX") ; 
	if( attack.inUseSize() < 3) 
      attack.getAttack(firePos, fireVel );
}


void EnemySprite::protectTurf(const Drawable* obj){
	if(attack.inUseSize() < 2){
	 if( X()+ 100 > obj->X() || X() - 100 < obj->X() ){
		if(obj->X() < X() && velocityX() > 0 ){
			dir *=-1;
			velocityX( velocityX() * dir);
		    fire();
		}
		if( obj->X() < X() && velocityX() < 0 )  fire();
		if( obj->X() > X() && velocityX() > 0)  fire();
		if(obj->X() > X() && velocityX() < 0 ){
			dir *=-1;
			velocityX( velocityX() * dir);
		    fire();
		}
	 }
	} 
}
