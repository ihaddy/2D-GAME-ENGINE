#include "graphics.h" //main header file with definitions in it we need


////Graphical constructor function


Graphics::Graphics()

{
	direct3d = NULL;
	device3d = NULL;
	fullscreen = false;
	width = GAME_WIDTH; //the width and height are replaced in the initialize function to come
	height = GAME_HEIGHT;

}