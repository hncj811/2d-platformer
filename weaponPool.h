#ifndef WEAPONPOOL__H
#define WEAPONPOOL__H
#include <cstdlib>
#include <list>
#include <string>
#include "bullet.h"
#include "sprite.h"

class WeaponPool{
private:
  std::list<Bullet*> available;
  std::list<Bullet*> inUse;
  std::string name;

public:
  WeaponPool( std::string n) : available(), inUse(), name(n)  {  }
  WeaponPool( const WeaponPool& w) : available(), inUse(), name(w.name){
	  available = w.available;
	  inUse = w.inUse;
  }
  ~WeaponPool();
  void getAttack(const Vector2f& pos, const Vector2f& vel  );
  void update(Uint32 ticks); 
  void processAttacks();
  void draw() const;
  int inUseSize() const {  return inUse.size();  }
  int availableSize() const {   return  available.size();  }
  bool collisions(const Drawable*);
  
};
#endif
