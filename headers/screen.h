#pragma once
#include <iostream>
#include <string>

class Screen{

public:
	Screen(int w, int h) : rows(w), columns(h), view(new char(w * h)) {};
	void init();
	void render();
	void setPixel(char c, int w, int h);
	void flush();

private:
	void clear();
	void clearLine();
	void setCoursor(int u, int v);
	void hideCoursor();

	int rows = 100;
	int columns = 100;
	char* view;
};
