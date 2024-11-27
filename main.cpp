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
#include <string>


// using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


int CHAR_ROWS = 70, CHAR_COLS = 300;
int desired_frame_rate = 15;
int KERNEL_SIZE = 5;
int ms_per_frame = 1000 / desired_frame_rate;

char intensity_table[] = {' ', '.', '-', 'o', '0', 'B'}; 
std::string green_color = "";

int main(){
  Screen* screen = new Screen(CHAR_ROWS, CHAR_COLS);
  screen->init();
  auto t1 = high_resolution_clock::now();
  auto t2 = high_resolution_clock::now();
  auto dt = duration_cast<milliseconds>(t2 - t1);


  cv::VideoCapture cap("/home/klaiddom/Downloads/Telegram Desktop/demo_0010.mp4");
  cap.set(cv::CAP_PROP_AUTOFOCUS, 0); 
  // cv::Mat img = cv::imread("/home/klaiddom/Desktop/photo_2024-11-13_22-55-49.jpg");
  cv::Mat gray_img, img, resized_img;
  int intensity_index = 0;
  bool ret = true;
  int div = 255 / (sizeof(intensity_table) / sizeof(intensity_table[0]));
  int iter = 0;
  std::vector<cv::Mat> v;
  std::vector<cv::Mat> colored;
  while(iter < 1500){
    
    
    ret = cap.read(img);
    // std::cout << "Transformed"<< std::endl;
    if(!ret)
      break;
    //cv::resize(img, resized_img, cv::Size(CHAR_COLS, CHAR_ROWS));
    cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(img, img, cv::Size(KERNEL_SIZE, KERNEL_SIZE), 1.0);
    
    
    v.push_back(gray_img.clone());
    colored.push_back(img.clone());
    iter++;
    // std::cout << "Iter: " << iter << std::endl;
    continue;
    // cv::imshow("TEST", resized_img);
    // cv::waitKey(1);
    screen->flush();

    
    // for(int i=0; i < CHAR_ROWS; i++){
    //   for(int j=0; j < CHAR_COLS; j++){
    //     intensity_index = (int)resized_img.at<uchar>(j, i) / div;
    //     char symbol = intensity_table[std::min(intensity_index, 5)];
    //     if(symbol == ' ')
    //       screen->setPixel(symbol, j, i, 6);
    //     else
    //       screen->setPixel(symbol, j, i, 0);
    //   }
    // }
    // screen->render();
    
    t2 = high_resolution_clock::now();
    dt = duration_cast<milliseconds>(t2 - t1);
    std::this_thread::sleep_for(std::chrono::milliseconds(std::max((int)(ms_per_frame - dt.count()), 0)));
    // cv::waitKey(1);  
    
  }

  for(int frame_id=0; frame_id < v.size(); frame_id++){
    t1 = high_resolution_clock::now();
    screen->flush();

    std::vector<double> blue = {1, 0, 0}, green = {0, 1, 0}, red = {0, 0, 1}, yellow = {0, 0.707, 0.707},
     magenta = {0.707, 0, 0.707}, cyan={0.707, 0.707, 0}, white={0.577, 0.577, 0.577};

    for(int i=0; i < CHAR_ROWS; i++){
      for(int j=0; j < CHAR_COLS; j++){
        intensity_index = (int)v[frame_id].at<uchar>(i, j) / div;
        auto color = colored[frame_id].at<cv::Vec3b>(i, j);
        cv::normalize(color, color);
        std::vector<double> scores;
        for(auto c: {red, green, yellow, blue, magenta, cyan, white}){
          scores.push_back(color[0] * c[0] + color[1] * c[1] + color[2] * c[2]);
        }
        int max_id = 0;
        // std::cout << scores[0] << " ";
        for(int k=1; k < scores.size(); k++){
            if(scores[k] > scores[max_id]){
              max_id = k;
            }
            // std::cout << scores[k] << " ";
        }
        // std::cout << std::endl;

        char s = intensity_table[std::min(intensity_index, 5)];
        screen->setPixel(s, i, j, max_id);
      }
    }
    screen->render();
    
    // cv::imshow("frame", colored[frame_id]);
    // cv::waitKey(0);

    t2 = high_resolution_clock::now();
    dt = duration_cast<milliseconds>(t2 - t1);
    std::cout << iter << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(std::max((int)(ms_per_frame - dt.count()), 0)));
  }
  screen->flush();
  screen->render();
  // cv::imshow("TEST", resized_img);
  // cv::waitKey(0);

  // char chars[] = {'a', 'b', 'c', 'd', 'e', 'f', '.'};
  // for(char c: chars){
  //   for(int i=0; i < CHAR_ROWS; i++){
  //     for(int j=0; j < CHAR_COLS; j++){
  //       t1 = high_resolution_clock::now();
  //       screen->flush();
  //       screen->setPixel(c, i, j);
  //       screen->render();
  //       t2 = high_resolution_clock::now();
  //       dt = duration_cast<milliseconds>(t2 - t1);
  //       std::this_thread::sleep_for(std::chrono::milliseconds(std::max((int)(ms_per_frame - dt.count()), 0)));
  //     }
      
  //   }
    
  // }
  return 0;
}
