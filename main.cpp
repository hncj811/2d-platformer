// Brian Malloy        Game Construction
#include "manager.h"

int main(int, char*[]) {
	bool play = true;
   while(play) {
      Manager manager;
      play =manager.play();
   }
   
   return 0;
}
