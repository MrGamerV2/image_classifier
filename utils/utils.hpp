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

void explore_menu_print(std::string *imgP1, std::string *imgP2);
void explore_menu(std::string *imgP1, std::string *imgP2);

void train_menu_print(float ValueP1[32], float ValueP2[32]);
void train_menu(float ValuesPic1[32], float ValuesPic2[32], float img[][IMAGE_SIZE]);

void test_menu_print();
void test_menu();

void FunctionTesting_menu();
void FunctionTesting_menu_print();

float Distance_Cal(float ArryA[], float ArryB[], int size);

void DistanceForMatrix_Cal(float ArryA[], float MatrixA[][IMAGE_SIZE], float DistanceArry[]);

void Break_Down(float SourceMatrix[IMAGE_SIZE][IMAGE_SIZE], float Values[32]);

float Mean_Matrix7by7(float Matrix[][7]);

float Std_Matrix7by7(float Matrix[][7], float Mean);

void Input_7By7Matrix(float Matrix[][7]);

void Input_Arry(float Arry[], int N);