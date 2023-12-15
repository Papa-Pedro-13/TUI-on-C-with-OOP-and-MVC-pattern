#pragma once
#include "curses.h"
#include "../../ostrovski_a_lab1_string/MyString.h"


class StatusBar {
private:
	
	MyString _text;

public:
	StatusBar();

	void setText(MyString text);
	void draw();
};