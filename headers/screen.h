#pragma once
#include <iostream>
#include <string>

class Screen{

public:
	Screen(int w, int h) : rows(w), columns(h), view(new char[w * h]), color_matrix(new int[w * h]) {};
	void init();
	void render();
	void setPixel(char c, int w, int h, int color_id);
	void flush();

private:
	void clear();
	void clearLine();
	void setCoursor(int u, int v);
	void hideCoursor();

	int rows = 100;
	int columns = 100;
	char* view;
	int* color_matrix;
	std::string color_prefix = "\e[";
	std::string color_midfix = "m";
	std::string color_postfix = "\e[0m";
	int color_ids[7] = {31, 32, 33, 34, 35, 36, 37};
};
