#include "Model.h"	

void Model::write(int ch)
{
	MyString& cur_line = lines_[line_pos_];
	cur_line.insert(col_pos_, 1, ch);

	if (cur_line.length() > COLS) {
		if (cur_line[cur_line.length() - 1]=='\n') {
			
		}
		else {
			auto it = lines_.begin();
			lines_.insert(std::next(it, getLine() + 1), cur_line.substr(120, cur_line.length()));
			lines_[line_pos_].erase(120,1);
			lines_[line_pos_].shrink_to_fit();
			lines_[line_pos_].append("\x17");
		}
		cur_line[cur_line.length() - 1];
	}
	col_pos_++;
	
}
Model::Model(){
	for (int i = 0; i < 1; i++)
		lines_.push_back("");
}

std::vector<MyString> Model::getLines() const { return lines_; };
int Model::getLine() const { return line_pos_; }
int Model::getCol() const { return col_pos_; }

void Model::enter() {
	auto it = lines_.begin();
	MyString cur_line = getLines()[getLine()];
	lines_.insert(std::next(it,getLine()+1), cur_line.substr(getCol(), cur_line.length()));

	//del remain
	MyString& line = lines_[line_pos_];
	line.erase(getCol(), cur_line.length() - getCol());
	line.shrink_to_fit();
	setCol(0);
	setLine(getLine() + 1);
	
}
void Model::delButton() {

}
void Model::backspace() {
	if (getCol() > 0) {
		MyString& cur_line = lines_[line_pos_];
		lines_[line_pos_] = cur_line.substr(0, cur_line.length() - 1) + "\0";
		setCol(getCol()-1);
	}
	else if(getLine()>0) {
		MyString cur_line = getLines()[getLine()];
		setCol(getLines()[getLine()-1].length());
		lines_[getLine() - 1] += cur_line;
		auto it = lines_.begin();
		lines_.erase(std::next(it, getLine()));
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
		setLine(getLine()-1);
		setCol(getLines()[getLine()].length());
	}
}
void Model::keyRight() {
	if (getCol() < getLines()[getLine()].length()) { setCol(getCol() + 1); }
	else if (getLine() + 1 < getLines().size()) {
		setLine(getLine() + 1);
		setCol(0);
	}
};
void Model::keyDown() {
	if (getLine()+1 < getLines().size()) {
		MyString cur_line = getLines()[getLine()];
		MyString new_line = getLines()[getLine()+1];
		if (getCol() > new_line.length()) {
			setCol(new_line.length());
		}
		setLine(getLine() + 1); 
	}
}; 
void Model::toStartWord() {
	MyString cur_str = getLines()[getLine()];
	int pos = getCol();
	while (cur_str[pos-1] == ' ' && pos != 0) { pos--; }
	while (cur_str[pos-1] != ' ' && pos != 0) { pos--; }
	setCol(pos);
}
void Model::toEndWord() {
	MyString cur_str = getLines()[getLine()];
	int pos = getCol();
	while (cur_str[pos] == ' ' && cur_str[pos] != '\0') { pos++; }
	while (cur_str[pos] != ' ' && cur_str[pos] != '\0') { pos++; }
	setCol(pos);
}
void Model::toEndLine() {
	setCol(getLines()[getLine()].length());
	
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
		MyString cur_line = getLines()[getLine()];
		MyString new_line = getLines()[getLine() - 1];
		if (getCol() > new_line.length()) {
			setCol(new_line.length());
		}
		setLine(getLine() - 1); 
	}
};

void Model::deleteButton(){
	if (getCol() < getLines()[getLine()].length()) {
		MyString& cur_line = lines_[line_pos_];
		lines_[line_pos_] = cur_line.substr(0, getCol()) + cur_line.substr(getCol()+1,cur_line.length());
		lines_[line_pos_].shrink_to_fit();
	}
	else if(getLine() +1 < getLines().size()){
		MyString next_line = getLines()[getLine()+1];
		lines_[getLine()] += next_line;
		auto it = lines_.begin();
		lines_.erase(std::next(it, getLine()+1));

	}
}
void Model::deleteWord(){
	while (getCol() > 0 && getLines()[getLine()][getCol()-1] != ' ') {
		setCol(getCol() - 1);
	}

	while (getLines()[getLine()][getCol()] != ' ' && getCol()< getLines()[getLine()].length()) {
		lines_[getLine()].erase(getCol(), 1);
	}
	if(getLines()[getLine()][getCol()] == ' ') lines_[getLine()].erase(getCol(), 1);
		
}
void Model::goToLine(MyString num) {
	int k = 0,lineNum=0;
	for (int i = num.length() - 1; i >= 0; i--) {
		lineNum += pow(10,k) * ((num[i] - '0'));
		k++;
	}
	if(lineNum<=getLines().size())	setLine(lineNum-1);
};
void Model::copyLine() {

	setCopyBuffer(getLines()[getLine()]);
}

void Model::copyWord() {
	int init_pos = getCol();
	toStartWord();
	int start = getCol();
	
	toEndWord();
	int end = getCol();
	setCopyBuffer(getLines()[getLine()].substr(start,end-start));
	setCol(init_pos);
};
void Model::insertBuffer() {
	lines_[getLine()].insert(getCol(),getCopyBuffer().c_str());
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

	if (getLines().size() == 1 && getLines()[0] != "") {
		setCol(0);
		lines_[0] = "";
	}
	else if (!(getLines()[0]=="" && getLines().size() == 1)) {
		setCol(0);
		auto it = lines_.begin();
		lines_.erase(std::next(it, getLine()));
		if (getLine() + 1 >= getLines().size()) setLine(getLines().size() - 1);
	}	
};

//commands
bool Model::openFile(MyString filename)
{
	
	std::ifstream input_file("C:\\test.txt");

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
				lines_.push_back(temp);
			}
			else
			{
				for (int i = 0; i < temp.length() / COLS; i++)
				{
					MyString ins = temp.substr(i * COLS, COLS);
					lines_.push_back(ins);
				}
				lines_.push_back(temp.substr(temp.length() - temp.length() % COLS, temp.length() % COLS));
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