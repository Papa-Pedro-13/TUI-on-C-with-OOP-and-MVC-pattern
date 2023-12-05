#pragma once
#include "Model.h"
#include "View.h"

class Controller
{
private:
	void refreshView();

	bool process(int ch);

	Model model_;
	View view_;
public:
	Controller();
	void loop();
};
