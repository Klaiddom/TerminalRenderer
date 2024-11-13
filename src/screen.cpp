#include "../headers/screen.h"

void Screen::init(){
	std::cout << "\e[8;" << this->rows << ";" << this->columns << "t" << std::endl;
	this->hideCoursor();
	this->clear();
}

void Screen::render(){
	this->clear();
	std::string out;
	for(int i=0; i < this->rows; i++){
		for(int j=0; j < this->columns; j++){
			out += this->view[i * columns + j];
		}
		out += '\n';
	}
	std::cout << out;
}

void Screen::setPixel(char c, int w, int h){
	if(w > this->rows || h > this->columns || w < 0 || h < 0)
		return;
	view[w * columns + h] = c;
}

void Screen::clearLine(){
	std::cout << "\033[K";
}

void Screen::setCoursor(int u, int v){
	if(u >= this->rows || v >= this->columns || u < 0 || v < 0)
		return;
	std::string command = "\033[" + std::to_string(u + 1) + ";" + std::to_string(v + 1) + "H";
	std::cout << command.c_str();
}

void Screen::hideCoursor(){
	std::cout << "\033[?25l";
}

void Screen::clear(){
	// for(int i=0; i < this->rows; i++){
	// 	this->setCoursor(1, i + 1);
	// 	this->clearLine();
	// }
	// this->setCoursor(1, 1);
	std::cout << "\033c";
}

void Screen::flush(){
	for(int i=0; i < this->rows; i++){
		for(int j=0; j < this->columns; j++){
			this->view[i * columns + j] = ' ';
		}
	}
}