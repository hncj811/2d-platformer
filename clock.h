#include <SDL.h>
#include <string>
#include <deque>
#include "vector2f.h"

class Manager;

class Clock {
public:
  static Clock& getInstance();  // This class is a Singleton
  unsigned int getTicksSinceInit() const { return totalTicksGame; }
  unsigned int getSeconds() const { return totalTicksGame/1000; }

  void toggleSloMo();
  bool isStarted() const { return started; }
  bool isPaused() const  { return paused;  }
  int getFps() const;
  unsigned int delay();
  void start();
  void pause();
  void unpause();
  void draw() const;  // For debugging

private:
  unsigned int deltaTicksReal;  
  unsigned int totalTicksReal;
  unsigned int lastTicksReal; 
  unsigned int deltaTicksGame; 
  unsigned int totalTicksGame; 
  unsigned int lastTicksGame;
  std::deque <unsigned int> ticksQueue;
  unsigned int aveDeltaTicks;
  unsigned int deltaSum;
  int count;
  bool started;
  bool paused;
  bool sloMo;
  Vector2f pos;

  friend class Manager; 

  unsigned int getTicksSinceLastFrame() const;
  void update();  // Increments time/ticks
  Clock();
  Clock(const Clock&);
  Clock&operator=(const Clock&);
};

