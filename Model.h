#pragma once
#include <vector>
#include "main.h"
#include <string>
#include "../../ostrovski_a_lab1_string/MyString.h"


struct StringArr {
	MyString line;
	bool isOverflow;
};

class Model
{

public:
	Model();

	void write(int ch);

	std::vector<StringArr> getLines() const;
	void setFileName(MyString newName);
	MyString getFileName() const;
	MyString getBuffer() const;
	int getLine() const;
	int getCol() const;
	int getMode() const;

	void clearWindow();

	void deleteButton();
	void deleteWord();
	void goToLine(MyString num);

	void toStartWord();
	void toEndWord();
	void toEndLine();
	

	void clearBuffer();
	void addBuffer(int sym);
	void setMode(int newMode);
	void setCol(int value);
	void setLine(int value);

	void deleteLine();
	void cutLine();
	void copyLine();
	void copyWord();
	void insertBuffer();
	void setCopyBuffer(MyString buf);
	MyString getCopyBuffer();

	//commands

	int getTopLine() const;
	void setTopLine(int value);


	void enter() ;
	void backspace();
	void delButton();
	void keyLeft();
	void keyRight();
	void keyDown();
	void keyUp();
	void registerObserver(Model* observer) {};
	void replaceSymbol();
	void pageUp();
	void pageDown();
	void toLastPage();
	void toFirstPage();
	void setFind(MyString newstr);
	MyString getFind();
	void findForward();
	void findBack();

	void closeWithSaving();
	void writeCloseFile();
	void helpInfo();
	bool writeFile();
	bool openFile(MyString filename);

	void backspaceCommand();
private:
	MyString findString;
	int topline = 0;
	MyString copyBuffer;
	MyString buffer;
	int mode = NAV_MODE;
	MyString fileName = "Unnamed.txt";
	int line_pos_ = 0, col_pos_ = 0;
	std::vector<StringArr> lines_;
};

