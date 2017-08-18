#ifndef ENEMYSPRITE__H
#define ENEMYSPRITE__H

#include "twoWaySprite.h"
#include "weaponPool.h"

class ExplodingSprite;
class EnemySprite : public twoWaySprite{

private:
  ExplodingSprite* explosion;
  int dir;
  WeaponPool attack;
  unsigned range;
  int health;
  int home;
  bool life;
  EnemySprite& operator=(const EnemySprite&);
public:
  EnemySprite(const std::string& n, const std::string& weapon);
  EnemySprite( const EnemySprite&);
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  void changeHealth(int hit) { health += hit; }
  int getHealth() { return health;  }
  void explode();
  void fire();
  bool getLife() {return life; }
  bool shots(const Drawable*);
  void protectTurf(const Drawable*);
  
  ~EnemySprite() { } 
}; 

#endif
