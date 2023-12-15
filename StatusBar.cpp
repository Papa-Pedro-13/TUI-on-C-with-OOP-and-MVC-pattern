#include "StatusBar.h"

StatusBar::StatusBar() {
	
	_text = "";
}

void StatusBar::setText(MyString text) {
	_text = text;
}
void StatusBar::draw(){
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_BLUE);
	attron(COLOR_PAIR(1));
	mvprintw(LINES - 1, 0, _text.c_str());
	attroff(COLOR_PAIR(1));
}