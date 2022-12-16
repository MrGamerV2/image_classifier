#pragma once

#define IMAGE_SIZE 28
#define BATCH_SIZE 100
#define IMAGE_BUFFER_SIZE 784

#include <iostream>
#include <iomanip>
#include <filesystem>
#include <cmath>
#include <fstream>

void load_image(std::string, int, float[IMAGE_SIZE][IMAGE_SIZE]);
std::string interpolation(std::string, std::string, std::string);
int file_count(std::string);

//      Function Declaration

void start_menu_print();

void clear_screen();

int CheckInput(int opt);

void info_print();

void explore_menu_print();
void explore_menu();

void train_menu_print();
void train_menu();

void test_menu_print();
void test_menu();

float Distance_Cal(float ArryA[], float ArryB[]);

void DistanceForMatrix_Cal(float ArryA[], float MatrixA[][IMAGE_SIZE], float DistanceArry[]);

void Break_Down(float SourceMatrix[IMAGE_SIZE][IMAGE_SIZE], float Values[32]);