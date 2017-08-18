#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "clock.h"
#include "gamedata.h"
#include "ioManager.h"

Clock& Clock::getInstance() {
  if ( SDL_WasInit(SDL_INIT_VIDEO) == 0) {
    throw std::string("Must init SDL before Clock");
  }
  static Clock clock; 
  return clock;
}

Clock::Clock() :
  deltaTicksReal(0),
  totalTicksReal(0),
  lastTicksReal(0), 
  deltaTicksGame(0), 
  totalTicksGame(0),
  lastTicksGame(0),
  ticksQueue(),
  aveDeltaTicks(0),
  deltaSum(0),
  count(0),
  started(false), 
  paused(false), 
  sloMo(false), 
  pos( Gamedata::getInstance().getXmlInt("clock/locX"),
       Gamedata::getInstance().getXmlInt("clock/locY"))
{
  start();
}

void Clock::draw() const { 
  IOManager::getInstance().
    printMessageValueAt("Seconds: ", getSeconds(), pos[0], pos[1]);
  IOManager::getInstance().
    printMessageValueAt("fps: ", getFps(), pos[0], pos[1]+20);
}

void Clock::update() { 

  lastTicksReal = totalTicksReal; 
  totalTicksReal = SDL_GetTicks(); 
  deltaTicksReal = totalTicksReal - lastTicksReal;
  
  deltaTicksGame= deltaTicksReal;
  if(paused == true){
    deltaTicksGame =0; 
  }
  
  else if(sloMo)
  {
    deltaTicksGame /=2;
  }
  lastTicksGame = totalTicksGame;
  totalTicksGame += deltaTicksGame; 
  
  if(count< 200){
    ticksQueue.push_back(deltaTicksGame); 
    deltaSum += ticksQueue.back();  count++;
  }
  //keep running sum subtrack first element then pop it
  // then add current deltaGameTicks to end and add to running sum  
  else{
    deltaSum -= ticksQueue.front();
    ticksQueue.pop_front();
    ticksQueue.push_back(deltaTicksGame);
    deltaSum += ticksQueue.back(); 
  }
   
  aveDeltaTicks = deltaSum /ticksQueue.size();
  SDL_Delay( delay() ); 
  totalTicksGame += delay();
  
}
unsigned int Clock::delay()
{
  unsigned int x = ( 1000/ 25 );	
  if( deltaTicksGame < x) 
  {	  //Sleep the remaining frame time 
	  int delayedTime = int(1000 / 25)  - deltaTicksGame ;
	  return delayedTime;
	  //std::cout<< deltaSum <<"\t" << aveDeltaTicks << std::endl;
  }
  return 0;
}	
	

unsigned int Clock::getTicksSinceLastFrame() const {
  return deltaTicksGame;
}

void Clock::toggleSloMo() {
  sloMo = ! sloMo;
}

int Clock::getFps() const { 
  if(aveDeltaTicks > 0) return 1000/aveDeltaTicks;
  return 0;
}

void Clock::start() { 
  started = true; 
  paused = false; 
}

void Clock::pause() { 
   paused = true; 
}

void Clock::unpause() { 
   paused = false;
}

