#include "hud.h"


void Hud::drawHud(SDL_Surface* screen) const {
  const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
  Draw_AALine(screen, posX, posY+HUD_height/2,
                      posX+HUD_width,posY+HUD_height/2,
                      HUD_height, 0xff, 0xff, 0xff, 0xff/2);
  Draw_AALine(screen, posX, posY, posX+HUD_width, posY, RED);
}

void Hud::drawHud(SDL_Surface* screen, std::vector<std::string> text) const {
  const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
  Draw_AALine(screen, posX, posY+HUD_height/2,
                      posX+HUD_width,posY+HUD_height/2,
                      HUD_height, 0xff, 0xff, 0xff, 0xff/2);
  Draw_AALine(screen, posX, posY, posX+HUD_width, posY, RED);
  for(int i =0; i < int( text.size() ); i++){
	  io.printMessageAt( text[i], posX + 10, posY +(i+1)*20);
  }
}
