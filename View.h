#pragma once
#include "Model.h"
#include "TUIAdapter.h"
#include "StatusBar.h"

class View
{

public:
	View();
	void update(const Model& model);
	void printStatusBar(const Model& model);

private:
	static const int cWindowLines = 30;
	static const int cWindowCols = 120;
	StatusBar statusBar;
	TUIAdapter textwin_;
};

