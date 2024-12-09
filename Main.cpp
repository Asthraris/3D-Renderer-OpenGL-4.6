#include "Engine.h"
	
const short int WIDTH = 1080;
const short HEIGHT = 720;

int main() {

	Engine gigachad(WIDTH,HEIGHT,"TIRBO");

	gigachad.process();
	gigachad.run();
	gigachad.terminate();
	return 0;
}
