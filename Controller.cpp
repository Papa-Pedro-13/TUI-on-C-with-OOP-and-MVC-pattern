#include "Controller.h"

void Controller::refreshView() {
	view_.update(model_);
}
bool Controller::process(int ch) {
	switch (model_.getMode()) {
	case NAV_MODE:
		if (ch == ':') {
			model_.setMode(COMMAND_MODE);
		}
		else if (ch == 'i') {
			model_.setMode(WRITE_MODE);
		}
		else if (ch == 'I') {
			model_.setCol(0);
			model_.setMode(WRITE_MODE);
		}
		else if (ch == 'S') {
			model_.toEndLine();
			model_.setMode(WRITE_MODE);
		}
		else if (ch == 'A') {
			model_.deleteLine();
			model_.setMode(WRITE_MODE);
		}
		else if (ch == 'r') {
			model_.replaceSymbol();
			model_.setMode(WRITE_MODE);
		}
		else if (ch == KEY_CODE_BACKSPACE) {
			model_.backspace();
		}
		else if (ch == KEY_LEFT) {
			model_.keyLeft();
		}
		else if (ch == KEY_UP) {
			model_.keyUp();
		}
		else if (ch == KEY_DOWN) {
			model_.keyDown();
		}
		else if (ch == KEY_RIGHT) {
			model_.keyRight();
		}
		else if (ch == KEY_DEL) {
			model_.delButton();
		}
		else if (ch == PAGE_UP) {
			model_.pageUp();
		}
		else if (ch == PAGE_DOWN) {
			model_.pageDown();
		}
		else if (ch == 'g') {
			model_.toFirstPage();
		}
		else if (ch == 'G') {
			model_.toLastPage();
		}
		else if (ch == KEY_CODE_ENTER) {
			MyString command = model_.getBuffer();
			if (command == "^") { model_.setCol(0); }
			else if (command == "$") { model_.toEndLine(); }
			else if (command == "w") { model_.toEndWord(); }
			else if (command == "b") { model_.toStartWord(); }
			else if (command == "x") { model_.deleteButton(); }
			else if (command == "dw") { model_.deleteWord(); }
			else if (command == "dd") { model_.cutLine(); }
			else if (command == "y") { model_.copyLine(); }
			else if (command == "yw") { model_.copyWord(); }
			else if (command == "p") { model_.insertBuffer(); }
			else if (command[command.length() - 1] == 'N') { model_.goToLine( command.substr(0, command.length() - 1)); }
			else if (command[0] == '/') {
				model_.setFind(command.substr(1, command.length() - 1));
				model_.findForward();
				model_.setMode(FIND_MODE);
			}
			else if (command[0] == '?') {
				model_.setFind(command.substr(1, command.length() - 1));
				model_.findBack();
				model_.setMode(FIND_MODE);
			}
			model_.clearBuffer();
		}
		else {
			model_.addBuffer(ch);
		}
		break;
	case COMMAND_MODE:

		if (ch == KEY_ESC) {
			model_.setMode(NAV_MODE);
		}
		else if (ch == KEY_CODE_BACKSPACE) {
			model_.backspaceCommand();
		}
		else if (ch == KEY_CODE_ENTER) {
			MyString command = model_.getBuffer();
			if (command[0] == 'o') { model_.openFile(command.substr(2)); }
			else if (command[0] == 'x' && command.length() == 1) { model_.writeCloseFile(); }
			else if (command[0] == 'w' && command.length() == 1) { model_.writeFile(); }
			else if (command[0] == 'h' && command.length() == 1) { model_.helpInfo(); view_.update(model_); getch(); model_.clearWindow(); }
			else if (command[0] == 'w' && command.length() >= 1) { model_.setFileName(command.substr(2)); model_.writeFile(); }
			else if (command[0] == 'q' && command.length() == 1) { model_.closeWithSaving(); }
			else if (command[0] == 'w' && command[1] == 'q' && command[2] == '!' && command.length() == 3) { model_.closeWithSaving(); }
			else if (command[0] == 'q' && command[1] == '!' && command.length() == 2) { exit(0); }
			else if (command[0] > '0' && command[0] < '9') { model_.goToLine(command.substr(0, command.length())); };
			model_.clearBuffer();
		}
		else {
			model_.addBuffer(ch);
		}
		break;
	case FIND_MODE:

		if (ch == KEY_ESC) {
			model_.setMode(NAV_MODE);
		}
		else if (ch==KEY_BACKSPACE){
			model_.backspaceCommand();
		}
		else if (ch == 'n') {
			model_.findForward();
		}
		else if (ch == 'N') {
			model_.findBack();
		}
		break;
	case WRITE_MODE:
		if (ch == KEY_ESC) {
			model_.setMode(NAV_MODE);
		}
		else if (ch == KEY_CODE_ENTER) {
			model_.enter();
		}
		else if (ch == KEY_CODE_BACKSPACE) {
			model_.backspace();
		}
		else if (ch == KEY_LEFT) {
			model_.keyLeft();
		}
		else if (ch == KEY_UP) {
			model_.keyUp();
		}
		else if (ch == KEY_DOWN) {
			model_.keyDown();
		}
		else if (ch == KEY_RIGHT) {
			model_.keyRight();
		}
		else if (ch == KEY_DEL) {
			model_.delButton();
		}
		else {
			model_.write(ch);
		}
		break;
	}
	
	return false;
}
Controller::Controller() {

	model_.registerObserver((Model*)&view_);
}
void Controller::loop(){

	view_.printStatusBar(model_);
	move(0, 0);
	while (!process(TUIAdapter::getchar()))
	{
		refreshView();
	}
}
