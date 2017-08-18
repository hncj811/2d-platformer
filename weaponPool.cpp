#include <cmath>
#include "weaponPool.h"
#include "explodingSprite.h"

WeaponPool::~WeaponPool(){
  std::list<Bullet*>::iterator ptr = inUse.begin();
  while( ptr != inUse.end()){
	  delete *ptr;
	  ++ptr;
  }
  ptr = available.begin();
  while (ptr != available.end() ){
	  delete *ptr;
	  ++ptr;
  }	
	
}

void WeaponPool::getAttack(const Vector2f& pos, const Vector2f& vel){
  std::list<Bullet*>::iterator ptr;
  //std::cout<< "getting bullet\n";
  if( !available.empty() ){
	 
    ptr = available.begin();
    //std::cout<< "bullet from available pool\n";
    (*ptr)->reset( pos, vel);
     
    inUse.push_back(*ptr);
    ptr = available.erase(ptr );    
  }
  else{
    Bullet* s = new Bullet(name, pos, vel);
    inUse.push_back(s);
    //std::cout<< "new bullet\n";
  }
  return;
}

void WeaponPool::update(Uint32 ticks){
  processAttacks();
  std::list<Bullet*>::iterator ptr = inUse.begin();
  while(ptr != inUse.end() ){
	  (*ptr)->update(ticks);
	  ptr++;
  }
}

void WeaponPool::draw() const{
  if(!inUse.empty() ){
    std::list<Bullet*>::const_iterator ptr = inUse.begin();
    while(ptr != inUse.end() ){
	  (*ptr)->draw();
	  ptr++;
    }
  }
}


void WeaponPool::processAttacks(){
  std::list<Bullet*>::iterator ptr = inUse.begin();
  while(ptr != inUse.end() ){
	if ( (*ptr)->lifeStatus() == false ){ 
	  available.push_back(*ptr);
	  ptr = inUse.erase(ptr);
    }
    else ptr++;
  }
}

bool WeaponPool::collisions(const Drawable* obj)
{
  std::list<Bullet*>::iterator ptr = inUse.begin();
  bool hit = false;
  while(ptr != inUse.end() ){
    if ( (*ptr)->explodeStatus() ) { 
		++ptr;
		break;
	}
    hit =(*ptr)->collidedWith(obj); 
    if(hit) return hit; 
    ptr++;
  }
  return hit;
}
