#include "Model.h"	

void Model::write(int ch)
{
	MyString& cur_line = lines_[line_pos_].line;
	cur_line.insert(col_pos_, 1, ch);

	if (cur_line.length() >= COLS) {
		if (lines_[getLine()].isOverflow == true) {
			int curLine = getLine(),curCol=getCol();
			char ch = cur_line[COLS - 1];
			lines_[getLine()].line.erase(COLS - 1, 1);
			if (getLine() + 1 < getLines().size()) {
				setLine(getLine() + 1);
				setCol(0);
				write(ch);
				setLine(curLine);
				setCol(curCol);

			}
			else {
				goto label;
			}
			
			
		}
		else {
			label:
			lines_[getLine()].isOverflow = true;
			StringArr newLine;
			newLine.line = getLines()[getLine()].line.substr(getLines()[getLine()].line.length()-1);
			newLine.isOverflow = false;
			lines_[getLine()].line.erase(lines_[getLine()].line.length()-1,1);
			lines_[getLine()].line.shrink_to_fit();
			auto it = lines_.begin();
			lines_.insert(std::next(it, getLine() + 1),newLine);
		}
		cur_line[cur_line.length() - 1];
	}
	if (getCol() == COLS-1) {
		keyRight();
	}
	keyRight();
	
}
Model::Model(){
	for (int i = 0; i < 1; i++) {
		StringArr newLine;
		newLine.line = "";
		newLine.isOverflow = false;

		lines_.push_back(newLine);
	}
}

std::vector<StringArr> Model::getLines() const { 
	/*std::vector<MyString> string;
	for (auto line : lines_) {
		string.push_back(line.line);
	}
	return string; */
	return lines_;
};
int Model::getLine() const { return line_pos_; }
int Model::getCol() const { return col_pos_; }

void Model::enter() {
	auto it = lines_.begin();
	MyString cur_line = getLines()[getLine()].line;
	StringArr newLine;
	newLine.line = cur_line.substr(getCol(), cur_line.length());
	newLine.isOverflow = false;
	lines_[getLine()].isOverflow = false;
	lines_.insert(std::next(it,getLine()+1), newLine);

	//del remain
	MyString& line = lines_[line_pos_].line;
	line.erase(getCol(), cur_line.length() - getCol());
	line.shrink_to_fit();
	setCol(0);
	if (getLine() - getTopLine() == 28) setTopLine(getTopLine()+1);
	setLine(getLine() + 1);
	
}
void Model::delButton() {
	if (getLines().size() == getLine()+1 && getCol() == getLines()[getLine()].line.length()) {
		return;
	}
	keyRight();
	backspace();
}
void Model::backspace() {
	if (getCol() > 0) {
		lines_[line_pos_].line.erase(getCol()-1,1);	
		lines_[line_pos_].line.shrink_to_fit();
		int curpos = getLine();
		//строка переполнена и необходимо перенести символ со следующей
		while (lines_[curpos].isOverflow) {
			//следующая строка закончена
			if (getLines()[curpos + 1].line.length() == 1) {
				lines_[curpos].isOverflow = false;
				lines_[curpos].line.append(1, getLines()[curpos + 1].line[0]);
				auto it = lines_.begin();
				lines_.erase(std::next(it, curpos + 1));
				curpos--;
			}

			else{
					lines_[curpos].line.append(1, getLines()[curpos + 1].line[0]);
					lines_[curpos + 1].line.erase(0, 1);
					lines_[curpos + 1].line.shrink_to_fit();
			}
			curpos++;
		}
		setCol(getCol()-1);
	}
	else if(getLine()>0) {
		MyString cur_line = getLines()[getLine()].line;
		int curLine = getLine();

		setCol(getLines()[getLine()-1].line.length());
		lines_[getLine() - 1].line += cur_line;

		auto it = lines_.begin();
		lines_.erase(std::next(it, getLine()));
		
		curLine--;
		
		while (curLine  < getLines().size() && getLines()[curLine].line.length() > 119) {
				lines_[curLine].isOverflow = true;
				MyString remains = lines_[curLine].line.substr(119);
				lines_[curLine].line.erase(119, remains.length());
				lines_[curLine].line.shrink_to_fit();
				curLine++;
				if (curLine == getLines().size()) {
					StringArr newstr;
					newstr.line = remains.c_str();
					newstr.isOverflow = false;
					lines_.push_back(newstr);
				}
				else {
				lines_[curLine].line.insert(0, remains.c_str());
				}
		}
		
		
		setLine(getLine() - 1);
	}
}


int Model::getMode() const {
	return mode;
};
void Model::setMode(int newMode) {
	buffer = "";
	mode = newMode;
};
void Model::setCol(int value) {
	col_pos_ = value;
};
void Model::setLine(int value) {
	line_pos_ = value;
};

void Model::keyLeft() {
	if (getCol() > 0) { setCol(getCol() - 1); }
	else if(getLine()>0) {
		keyUp();
		setCol(getLines()[getLine()].line.length());
	}
}
void Model::keyRight() {
	if (getCol() < getLines()[getLine()].line.length()) { setCol(getCol() + 1); }
	else if (getLine() + 1 < getLines().size()) {
		keyDown();
		setCol(0);
	}
};
void Model::keyDown() {
	std::vector<StringArr> lines=getLines();
	if (getLine()+1 < lines.size()) {
		if (getLine() - getTopLine() == 28) {
			setTopLine(getTopLine() + 1);
			
		}
		MyString cur_line = lines[getLine()].line;
		MyString new_line = lines[getLine()+1].line;
		if (getCol() > new_line.length()) {
			setCol(new_line.length());
		}
		setLine(getLine() + 1); 
	}
	
}; 
void Model::toStartWord() {
	MyString cur_str = getLines()[getLine()].line;
	int pos = getCol();
	while (cur_str[pos-1] == ' ' && pos != 0) { pos--; }
	while (cur_str[pos-1] != ' ' && pos != 0) { pos--; }
	setCol(pos);
}
void Model::toEndWord() {
	MyString cur_str = getLines()[getLine()].line;
	int pos = getCol();
	while (cur_str[pos] == ' ' && cur_str[pos] != '\0') { pos++; }
	while (cur_str[pos] != ' ' && cur_str[pos] != '\0') { pos++; }
	setCol(pos);
}
void Model::toEndLine() {
	setCol(getLines()[getLine()].line.length());
	
};
void Model::clearBuffer() {
	buffer = "";
};
void Model::addBuffer(int sym) {
	MyString* add = new MyString(1, (char)sym);
	buffer += *add;
}
void Model::setFileName(MyString newName) {
	fileName = newName;
};
MyString Model::getFileName() const {
	return fileName;
};
MyString Model::getBuffer() const {
	return buffer;
}
void Model::keyUp() {
	if (getLine() > 0) {
		if (getLine() == getTopLine() ) {
			setTopLine(getTopLine() - 1);
		}
		MyString cur_line = getLines()[getLine()].line;
		MyString new_line = getLines()[getLine() - 1].line;
		if (getCol() > new_line.length()) {
			setCol(new_line.length());
		}
		setLine(getLine() - 1); 
	}
};

void Model::deleteButton(){
	if (getCol() < getLines()[getLine()].line.length()) {
		MyString& cur_line = lines_[line_pos_].line;
		lines_[line_pos_].line = cur_line.substr(0, getCol()) + cur_line.substr(getCol()+1,cur_line.length());
		lines_[line_pos_].line.shrink_to_fit();
	}
	else if(getLine() +1 < getLines().size()){
		MyString next_line = getLines()[getLine()+1].line;
		lines_[getLine()].line += next_line;
		auto it = lines_.begin();
		lines_.erase(std::next(it, getLine()+1));

	}
}
void Model::deleteWord(){
	while (getCol() > 0 && getLines()[getLine()].line[getCol()-1] != ' ') {
		setCol(getCol() - 1);
	}

	while (getLines()[getLine()].line[getCol()] != ' ' && getCol()< getLines()[getLine()].line.length()) {
		lines_[getLine()].line.erase(getCol(), 1);
	}
	if(getLines()[getLine()].line[getCol()] == ' ') lines_[getLine()].line.erase(getCol(), 1);
		
}
void Model::goToLine(MyString num) {
	int k = 0,lineNum=0;
	for (int i = num.length() - 1; i >= 0; i--) {
		lineNum += pow(10,k) * ((num[i] - '0'));
		k++;
	}
	setTopLine(lineNum-1);
	if(lineNum<=getLines().size())	setLine(lineNum-1);
};
void Model::copyLine() {

	setCopyBuffer(getLines()[getLine()].line);
}

void Model::copyWord() {
	int init_pos = getCol();
	toStartWord();
	int start = getCol();
	
	toEndWord();
	int end = getCol();
	setCopyBuffer(getLines()[getLine()].line.substr(start,end-start));
	setCol(init_pos);
};
void Model::insertBuffer() {
	lines_[getLine()].line.insert(getCol(),getCopyBuffer().c_str());
};
void Model::setCopyBuffer(MyString buf) {
	copyBuffer.clear();
	copyBuffer.shrink_to_fit();
	copyBuffer = buf;
}
MyString Model::getCopyBuffer() {
	return copyBuffer;
};
void Model::cutLine() {
	copyLine();
	deleteLine();
};
void Model::deleteLine() {

	if (getLines().size() == 1 && getLines()[0].line != "") {
		setCol(0);
		lines_[0].line = "";
	}
	else if (!(getLines()[0].line =="" && getLines().size() == 1)) {
		setCol(0);
		auto it = lines_.begin();
		lines_.erase(std::next(it, getLine()));
		if (getLine() + 1 >= getLines().size()) setLine(getLines().size() - 1);
	}	
};

//commands
bool Model::openFile(MyString filename)
{
	
	std::ifstream input_file(filename.c_str());

	if (input_file.is_open())
	{
		lines_.clear();
		lines_.shrink_to_fit();
		
		fileName = filename;
		while (!input_file.eof())
		{
			MyString temp;
			input_file >> temp;
			if (temp.length() < COLS)
			{
				StringArr newstr;
				newstr.line = temp;
				newstr.isOverflow = false;
				lines_.push_back(newstr);
			}
			else
			{
				for (int i = 0; i < temp.length() / COLS; i++)
				{
					StringArr ins;
					ins.line = temp.substr(i * (COLS-1), COLS-1);
					ins.isOverflow = true;
					lines_.push_back(ins);
				}
				StringArr newstr;
				newstr.line = temp.substr(temp.length() - temp.length() % (COLS - 1), temp.length() % (COLS - 1));
				newstr.isOverflow = false;
				lines_.push_back(newstr);

			}
			temp.clear();
		}

		setCol(0);
		setLine(0);
		//getScreen().printStatusBar(status_);
		input_file.close();
		return true;
	}
	else
	{
		
		input_file.close();
		return false;
	}


}

void Model::replaceSymbol() {
	if (getCol() == 0) {
		char symbol = getch();
		lines_[getLine()].line.insert(getCol(), 1,symbol);
		return;
	}
	char symbol = getch();
	MyString* newstr = new MyString(1, symbol);
	lines_[getLine()].line.replace(getCol()-1, 1, newstr->c_str());
	delete newstr;
}
void Model::pageUp() {

	setLine(getLine() - 29);
	setTopLine(getTopLine() - 29);
	if (getTopLine() < 0) {
		setTopLine(0);
	}
	if (getLine() < 0) {
		setLine(0);
	}
}
void Model::pageDown() {
	setTopLine(getTopLine() + 29);
	setLine(getLine() + 29);
	if ((getTopLine() + 29 )> getLines().size()) {
		if(getLines().size()  < 29){
			setTopLine(0);
		}
		else {
			setTopLine(getLines().size() - 29);
		}
	}
	if (getLine() > getLines().size()) {
		setLine(getLines().size()-1);
	}

}

void Model::toLastPage() {
	std::vector<StringArr> lines = getLines();
	setTopLine(lines.size()-29);
	if (getTopLine() < 0) setTopLine(0);
	setLine(lines.size()-1);
	setCol(0);
}
void Model::toFirstPage() {
	setTopLine(0);
	setLine(0);
	setCol(0);
}

int Model::getTopLine() const {
	return topline;
}
void Model::setTopLine(int value) {
	topline = value;
};
 
void Model::setFind(MyString newstr) {
	findString = newstr;
};
MyString Model::getFind() {
	return findString;
};
void Model::findForward() {
	int curpos = getLine()+1;
	int index = -1;
	int linesSize = getLines().size();
	while (curpos < linesSize && index == -1) {
		index = lines_[curpos].line.find(getFind().c_str());
		curpos++;
	}
	if (index != -1) {
		while (getLine() != curpos - 1) {
			setLine(getLine() + 1);
			setTopLine(getTopLine() + 1);
		}
		setCol(0);
	}
};
void Model::findBack() {
	int curpos = getLine() - 1;
	int index = -1;
	
	while (curpos >= 0 && index == -1) {
		index = lines_[curpos].line.find(getFind().c_str());
		curpos--;
	}
	if (index != -1) {
		while (getLine() != curpos + 1) {
			setLine(getLine() - 1);
			setTopLine(getTopLine() - 1);
		}
		setCol(0);
	}
};

void Model::closeWithSaving() {
	writeFile();
	exit(0);
};
void Model::writeCloseFile() {
	writeFile();
	clearWindow();
}
bool Model::writeFile()
{
	bool f = true;

	std::ofstream tmp;
	tmp.open(getFileName().c_str(),'w');
	f = tmp.is_open();
	std::vector<StringArr> lines = getLines();
	if (f)
	{
		for (int i = 0; i < lines.size(); i++)
		{
			if (i == lines.size() - 1 || lines_[i].isOverflow)
			{
				tmp << lines[i].line;
			}
			else
			{
				tmp << lines[i].line << std::endl;
			}
		}
		;
		setMode(NAV_MODE);
	}
	


	return f;
}
void Model::clearWindow() {
	setFileName("Unnamed.txt");
	lines_.clear();
	lines_.shrink_to_fit();
	for (int i = 0; i < 1; i++) {
		StringArr newLine;
		newLine.line = "";
		newLine.isOverflow = false;

		lines_.push_back(newLine);
	}
	setCol(0);
	setLine(0);
	setTopLine(0);
}
void Model::helpInfo() {
	clearWindow();
	StringArr newstr;
	newstr.line = "I - Go to the beginning of the lineand start entering text.\n\
S - Go to the end of the lineand start typing.\n\
A - Delete the contents of the rowand start typing.\n\
r - Replace one character under the cursor.\n\
/ - Activates search mode until the end of the document.\n\
? - Activates search mode until the start of the document.\n\ PAGE_UP - Raises the cursor one page.\n\
";
	lines_.push_back(newstr);
}

void Model::backspaceCommand() {
	if (buffer.length() > 0) {

		buffer.erase(buffer.length() - 1, 1);
		buffer.shrink_to_fit();
	}
};