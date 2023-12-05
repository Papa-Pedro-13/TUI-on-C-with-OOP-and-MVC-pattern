#pragma once
#include "curses.h"
#include "../../ostrovski_a_lab1_string/MyString.h"
class TUIAdapter
{

public:
	static void init()
	{
		initscr();
		cbreak();
		noecho();
		scrollok(stdscr, TRUE);
		keypad(stdscr, true);

	}

	static int getchar()
	{
		return getch();
	}
	void clearWindow(){
		clear();
		//update(); // think
	}
	static void movecursor(int x, int y)
	{
		move(x, y);
	}

	TUIAdapter(int lines, int cols, int x, int y)
	{
		window_ = newwin(lines, cols, x, y);
		//assert ideally
	}

	~TUIAdapter()
	{
		delwin(window_);
		window_ = nullptr;
	}

	void moveprint(int x, int y, MyString& str)
	{
		mvprintw(x, y, str.c_str());
	}

	void update()
	{
		wrefresh(window_);
		refresh(); // think
	}

private:
	WINDOW* window_ = nullptr;
};
