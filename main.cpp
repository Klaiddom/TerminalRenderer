#include <iostream>
#include <cstdlib>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdio>
#include <chrono>
#include <thread>
#include <cmath>
#include "headers/screen.h"

#include <vector>
#include <opencv2/opencv.hpp>


// using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


int CHAR_ROWS = 90, CHAR_COLS = 320;
int desired_frame_rate = 15;
int ms_per_frame = 1000 / desired_frame_rate;

char intensity_table[] = {' ', '.', '-', 'o', '0', 'B'}; 


int main(){
	Screen* screen = new Screen(CHAR_ROWS, CHAR_COLS);
	screen->init();
	auto t1 = high_resolution_clock::now();
	auto t2 = high_resolution_clock::now();
	auto dt = duration_cast<milliseconds>(t2 - t1);


	cv::VideoCapture cap("/home/klaiddom/Desktop/IMG_0074.MP4");
	cap.set(cv::CAP_PROP_AUTOFOCUS, 0); 
	// cv::Mat img = cv::imread("/home/klaiddom/Desktop/photo_2024-11-13_22-55-49.jpg");
	cv::Mat gray_img, img, resized_img;
	int intensity_index = 0;
	bool ret = true;
	int div = 255 / (sizeof(intensity_table) / sizeof(intensity_table[0]));
	int iter = 0;
	while(ret){
		t1 = high_resolution_clock::now();
		ret = cap.read(img);
		if(!ret)
			break;
		cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
		cv::resize(gray_img, resized_img, cv::Size(CHAR_COLS, CHAR_ROWS));
		screen->flush();

		
		for(int i=0; i < CHAR_ROWS; i++){
			for(int j=0; j < CHAR_COLS; j++){
				intensity_index = (int)resized_img.at<uchar>(i, j) / div;
	 			screen->setPixel(intensity_table[std::min(intensity_index, 5)], i, j);
			}
		}
		screen->render();
		
		t2 = high_resolution_clock::now();
		dt = duration_cast<milliseconds>(t2 - t1);
		std::this_thread::sleep_for(std::chrono::milliseconds(std::max((int)(ms_per_frame - dt.count()), 0)));
		
	}
	// char chars[] = {'a', 'b', 'c', 'd', 'e', 'f', '.'};
	// for(char c: chars){
	// 	for(int i=0; i < CHAR_ROWS; i++){
	// 		for(int j=0; j < CHAR_COLS; j++){
	// 			t1 = high_resolution_clock::now();
	// 			screen->flush();
	// 			screen->setPixel(c, i, j);
	// 			screen->render();
	// 			t2 = high_resolution_clock::now();
	// 			dt = duration_cast<milliseconds>(t2 - t1);
	// 			std::this_thread::sleep_for(std::chrono::milliseconds(std::max((int)(ms_per_frame - dt.count()), 0)));
	// 		}
			
	// 	}
		
	// }
	return 0;
}