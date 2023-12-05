#include"View.h"
#include <string>


View::View() : textwin_(cWindowLines, cWindowCols, 0, 0) {};

void View::update(const Model& model)
{
	textwin_.clearWindow();
	int lineCnt = 0;

	


	printStatusBar( model);
	for (auto line: model.getLines()) {
		textwin_.moveprint(lineCnt, 0, line);
		
		/*textwin_.update();*/
		lineCnt++;
	
	}
	textwin_.movecursor(model.getLine(), model.getCol());
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