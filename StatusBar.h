#pragma once
#include "curses.h"
#include "../../ostrovski_a_lab1_string/MyString.h"


class StatusBar {
private:
	WINDOW* _parent;
	MyString _text;

public:
	StatusBar(WINDOW* parent = stdscr);

	void setText(MyString text);
	void draw();
};