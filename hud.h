#ifndef HUD__H
#define HUD__H

#include "aaline.h"
#include "ioManager.h"
#include "SDL.h"
#include <vector>
#include <string>

class Hud {
private:
  int posX; 
  int posY;
  int HUD_width;
  int HUD_height;
  IOManager& io;

public:
  Hud() : posX(10), posY(10), HUD_width(250), HUD_height(100),
   io(IOManager::getInstance() ) { }
  Hud(int x, int y, int width, int height) 
  : posX(x), posY(y), HUD_width(width), HUD_height(height),
    io(IOManager::getInstance() ) { }
  void drawHud( SDL_Surface* screen) const;
  void drawHud(SDL_Surface* screen, std::vector<std::string> text) const;

};

#endif
