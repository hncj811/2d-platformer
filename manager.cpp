#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "vector2f.h"
#include "multisprite.h"
#include "twoWaySprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include "extractSurface.h"
#include "frameFactory.h"
#include "SDL/SDL_rotozoom.h"
#include "explodingSprite.h"
 

Manager::~Manager() { 
  std::list<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    delete (*ptr);
    ++ptr;
  }
  std::list<Drawable*>::const_iterator ptr2 = obstacles.begin();
  while ( ptr2 != obstacles.end() ) {
    delete (*ptr2);
    ++ptr2;
  }
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  sky( "sky", Gamedata::getInstance().getXmlInt("sky/factor") ),
  clouds( "clouds", Gamedata::getInstance().getXmlInt("clouds/factor") ),
  hills( "hills", Gamedata::getInstance().getXmlInt("hills/factor") ),
  grass( "grass2", Gamedata::getInstance().getXmlInt("grass2/factor") ),
  
  viewport( Viewport::getInstance() ),
  
  gameMenu(10, 10, 300, 200),
  menuToggle(true),
  manualToggle(false),
  timer(0),
  sprites(),
  currentSprite(),
  obstacles(),
  currentObstacle(),
  enemies(),
  //crow("crow", 2 ),
  currentObj(0),
  player(PlayerSprite("tiger") ),
  godMode(false),
  makeVideo( false ),
  frameCount( 0 ),
  username(  Gamedata::getInstance().getXmlStr("username") ),
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") )
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit);

   
  //sprites.push_back(new MultiSprite("spinstar") );
  //for(int i= 0; i< 3; i++)
  //  sprites.push_back(new scaledSprite("crow" );
  obstacles.push_back(new MultiSprite("flame" ) );
  enemies.push_back( new EnemySprite("tiger" ,"iceCube" ) );
  for(int i=0 ; i< 10; i++)
    sprites.push_back(new twoWaySprite("littleCrow") );
  for(int i= 0; i< 8; i++)
    sprites.push_back(new twoWaySprite("crow") );

  currentSprite = sprites.begin();
  viewport.setObjectToTrack(&player);
}

void Manager::draw() const {
  sky.draw();
  //clock.draw();
  clouds.draw();
  //crow.draw();
  std::list<Drawable*>::const_iterator ptr = sprites.begin();
  for(int i=0; i<10; i++) {
    (*ptr)->draw();
    ++ptr;
  }
  hills.draw();
  
  while ( ptr != sprites.end() ) {
    (*ptr)->draw();
    ++ptr;
  }
  grass.draw();
  std::list<Drawable*>::const_iterator ptr2 = obstacles.begin();
  while ( ptr2 != obstacles.end() ) {
    (*ptr2)->draw();
    ++ptr2;
  }
  
  std::list<EnemySprite*>::const_iterator eit = enemies.begin();
  while ( eit != enemies.end() ) {
    (*eit)->draw();
    ++eit;
  }
  player.draw();
  
  std::vector<std::string> menuText;
  
  menuText.push_back("F1: Display Menu"); 
  menuText.push_back("aswd to Move Player");
  menuText.push_back("P: Puase/Unpause");
  menuText.push_back("G: for God mode");
  int sec = clock.getSeconds();
  std::ostringstream oss;
  std::string a= "Seconds: ";
  oss<<a<<sec;
  std::string secs= oss.str();
  menuText.push_back( secs);
  oss.str("");  oss.clear();
  int fps = clock.getFps();
  a= "FPS: ";
  oss<<a<<fps;
  std::string f= oss.str(); //f = fps
  menuText.push_back(f);
  oss.str("");  oss.clear();
  int inUseSize = player.inUse();
  int avail = player.available();
  oss<< "Shots In Use: "<<inUseSize;
  f = oss.str();
  menuText.push_back(f); 
  oss.str("");  oss.clear();
  oss <<"Available shots: "<< avail;
  f = oss.str();
  menuText.push_back(f); 
  
    
  if(menuToggle)  gameMenu.drawHud(screen, menuText);
  
  //io.printMessageAt("Hakeem's Game", 10, 70);
  io.printMessageAt(title, 10, 450);
  //viewport.draw();

  SDL_Flip(screen);
}

// Move this to IOManager
void Manager::makeFrame() {
  std::stringstream strm;
  strm << "frames/" << username<< '.' 
       << std::setfill('0') << std::setw(4) 
       << frameCount++ << ".bmp";
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  SDL_SaveBMP(screen, filename.c_str());
}

void Manager::switchSprite() {
  ++currentSprite;
  currentObj++;
  if ( currentSprite == sprites.end() ) {
    currentSprite = sprites.begin();
    currentObj=0;
  }
  //Drawable *playerPtr = const player&;
  if ( currentObj %2 ==0) 
    viewport.setObjectToTrack(&player);
  else 
    viewport.setObjectToTrack(*currentSprite);
}

void Manager::update() {
  clock.update();
  Uint32 ticks = clock.getTicksSinceLastFrame();
  timer +=ticks;
  if( timer > 3000  && timer< 5000  && !manualToggle) menuToggle = false;
  std::list<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    (*ptr)->update(ticks);
    ++ptr;
  }
  std::list<Drawable*>::const_iterator ptr2 = obstacles.begin();
  if(!godMode){
    while ( ptr2 != obstacles.end() ) 
    {
		if(player.collidedWith(*ptr2) )
		{
			if(player.velocityX() <0 ){
			  player.X( player.X() + 10);
			  player.velocityX(0);
			}
			else{
			  player.X( player.X() - 10);
			  player.velocityX(0.001);
			}
		}
		//if (player.shots(*ptr2) ) {  std::cout <<"hii\n"; }
		(*ptr2)->update(ticks);
		++ptr2;
	}
  }	
  std::list<EnemySprite*>::iterator eit2 = enemies.begin();
  while ( eit2 != enemies.end() ) 
  { (*eit2)->update(ticks);
    if(!godMode){
		
		if( ticks% 23) (*eit2)->protectTurf(&player);
		if( (*eit2)->getHealth() > 0) {
		  if( player.collidedWith(*eit2 ) ){
			player.changeHealth(-17);
			if( player.velocityX() > 0 )	player.X( player.X() - 30 );
			else player.X( player.X() + 30 );
			//player.velocityX(0);
		  }
		}
	}
    if(player.shots( *eit2) ){
		 (*eit2)->changeHealth(-17); 
		 std::cout<<"Player hit a foe\n";
    }
	if( (*eit2)->shots(&player) ) player.changeHealth( -6);
	
    if( (*eit2)->getLife() == false ){
		EnemySprite* tmp = *eit2;
		delete tmp;
		eit2 = enemies.erase(eit2);
		break;
	}
	++eit2;
  }
  player.update(ticks);
  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
  sky.update();
  clouds.update();
  hills.update();
  grass.update(ticks);
  viewport.update(); // always update viewport last
}

//bool Manager::restart(){
	

bool Manager::play() {
  SDL_Event event;
  bool done = false;
  bool playAgain = false;
  clock.start();

  while ( not done ) {
    while ( SDL_PollEvent(&event) ) 
    {
      Uint8 *keystate = SDL_GetKeyState(NULL);
      if (event.type == SDL_QUIT) done = true;
      if (event.type == SDL_KEYDOWN) 
      {
        if (event.key.keysym.sym == SDLK_ESCAPE) done = true;
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
            done = true;
            break;
        }
        if ( keystate[SDLK_t] ) switchSprite();  //toggle sprite
        if ( keystate[SDLK_p] ) {
            if ( clock.isPaused() ) clock.unpause();
            else clock.pause();
        }
        if ( keystate[SDLK_r] ){  //reset
			playAgain = true;
			done = true; break;
		}
		if ( keystate[SDLK_g] ){  //godMode
			godMode= godMode ? false: true;
		}
		if ( keystate[SDLK_1] ){  //explode
			player.explode();
		}
		if ( keystate[SDLK_SPACE] ){  //explode
			player.fire();
		}
	    if ( keystate[SDLK_w] || keystate[SDLK_UP]){  //reset
			player.jump();
		}
        if (keystate[SDLK_o])  clock.toggleSloMo(); //sloMo
        if (keystate[SDLK_F1] ){
			 menuToggle= menuToggle ? false: true; 
                         manualToggle = true;
		}
			
        if (keystate[SDLK_F4] && !makeVideo) {
            std::cout << "Making video frames" << std::endl;
            makeVideo = true;
        }
      }
    }
    Uint8 *keysHeld = SDL_GetKeyState(NULL);
    SDL_PollEvent(&event);
    if (event.type == SDL_KEYDOWN) 
    {
       if ( keysHeld[SDLK_LEFT] || keysHeld[SDLK_a] )  player.moveLeft();
       if ( keysHeld[SDLK_RIGHT] || keysHeld[SDLK_d] ) player.moveRight();	    }
    draw();
    update();
  }
  return playAgain;
}
