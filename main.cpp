#include "main.h"
#include "Controller.h"

int main(int argc, char* argv[])
{
	TUIAdapter::init();

	Controller controller;
	controller.loop();


	
	/*TUIAdapter win1(1, 120, 0, 0);
	TUIAdapter win2(2, 120, 3, 0);

	win1.moveprint(0, 0, "test1");
	win2.moveprint(0, 0, "test2");
	win1.update();
	win2.update();
	TUIAdapter::getchar();
	TUIAdapter::getchar();
	TUIAdapter::getchar();
	*/

	// navigation mode - arrows
	// input mode - add enter
	// command - 
	// status bar (view) - if you have time
	// vim.exe for reference
}