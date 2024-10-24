#include <iostream>
#include <cstdlib>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdio>
#include <chrono>
#include <thread>
#include <cmath>
#include "headers/screen.h"

// using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


int CHAR_ROWS = 25, CHAR_COLS = 100;
int desired_frame_rate = 15;
int ms_per_frame = 1000 / desired_frame_rate;


int main(){
	Screen* screen = new Screen(CHAR_ROWS, CHAR_COLS);
	screen->init();
	auto t1 = high_resolution_clock::now();
	auto t2 = high_resolution_clock::now();
	auto dt = duration_cast<milliseconds>(t2 - t1);
	char chars[] = {'a', 'b', 'c', 'd', 'e', 'f', '.'};
	for(char c: chars){
		for(int i=0; i < CHAR_ROWS; i++){
			for(int j=0; j < CHAR_COLS; j++){
				t1 = high_resolution_clock::now();
				screen->flush();
				screen->setPixel(c, i, j);
				screen->render();
				t2 = high_resolution_clock::now();
				dt = duration_cast<milliseconds>(t2 - t1);
				std::this_thread::sleep_for(std::chrono::milliseconds(std::max((int)(ms_per_frame - dt.count()), 0)));
			}
			
		}
		
	}
	return 0;
}