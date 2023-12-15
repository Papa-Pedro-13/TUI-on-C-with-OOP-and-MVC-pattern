#include"View.h"
#include <string>


View::View() : textwin_(cWindowLines, cWindowCols, 0, 0) {};

void View::update(const Model& model)
{
	textwin_.clearWindow();
	int lineCnt = 0;
	std::vector<StringArr> lines = model.getLines();
	int lineSize = lines.size();
	printStatusBar( model);
	for (int i = model.getTopLine(); i < model.getTopLine() + 29 && i<lineSize;i++) {
		textwin_.moveprint(lineCnt, 0, lines[i].line);
		
		lineCnt++;
	
	}
	textwin_.movecursor(model.getLine()-model.getTopLine(), model.getCol());
	textwin_.update();
}
void View::printStatusBar( const Model& model) {
	MyString mode;
	switch (model.getMode()) {
	case NAV_MODE:
		mode = " NAVIGATION MODE  Command: ";
		mode += model.getBuffer();
		break;
	case COMMAND_MODE:
		mode = " COMMAND MODE  Command: ";
		mode += model.getBuffer();
		break;
	case WRITE_MODE:
		mode = " WRITE MODE ";
		break;
	case FIND_MODE:
		mode = " FIND MODE  Command: ";
		mode += model.getBuffer();
		break;

	};

	mode += " - ";
	mode += model.getFileName() + " - ";

	mode += std::to_string(model.getLine() + 1);
	mode += "/";
	mode += std::to_string(model.getLines().size());
	statusBar.setText(mode);
	statusBar.draw();
}