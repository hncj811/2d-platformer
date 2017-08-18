#include <list>
#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "twoWaySprite.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "playerSprite.h"
#include "enemySprite.h"
#include "hud.h"
#include "multiWorld.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  bool play();
  void switchSprite();

private:
  const bool env;
  const IOManager& io;
  Clock& clock;

  SDL_Surface * const screen;
  World sky;
  World clouds;
  World hills;
  MultiWorld grass;
  Viewport& viewport;
  
  //hud 
  Hud gameMenu;
  bool menuToggle, manualToggle;  // flag turn on or off
  int timer;
  
  std::list<Drawable*> sprites;
  std::list<Drawable*>::iterator currentSprite;
  
  std::list<Drawable*> obstacles;
  std::list<Drawable*>::iterator currentObstacle;
  
  std::list<EnemySprite*> enemies;
  //scaledSprite crow;
  int currentObj;
  PlayerSprite player;
  bool godMode;
  bool makeVideo;
  int frameCount;
  const std::string username;
  const std::string title;
  const int frameMax;

  void draw() const;
  void update();

  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();
};
