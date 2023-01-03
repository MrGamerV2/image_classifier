#pragma once

#define IMAGE_SIZE 28
#define BATCH_SIZE 100
#define IMAGE_BUFFER_SIZE 784
// Personal edits
#define IMAGE_DATA_LIMIT 100
#include "timer.hpp"

#include <iostream>
#include <string>
#include <iomanip>
#include <filesystem>
#include <cmath>
#include <fstream>

void ImageLoad(std::string, int, float[IMAGE_SIZE][IMAGE_SIZE]);
std::string interpolation(std::string, std::string, std::string);
int file_count(std::string);

// Structues

struct TrainSet
{
    int Label{-1};
    float imgs[IMAGE_DATA_LIMIT][32];
};

//      Function Declaration

void StartMenu_print();

void ClearScreen();

// @param opt Options
int CheckInput(int opt);

void Info_print();

// @param img Image
void Image_print(float img[][IMAGE_SIZE]);

// @param Label Number Label @param PicNum Picture Numer
void ExploreMenu_print(int *Label, int *PicNum);
void ExploreMenu(float img[][IMAGE_SIZE]);

void TrainMenu_print();
void TrainMenu(TrainSet TrainSets[], float img[][IMAGE_SIZE]);

void TestMenu_print(int *Label, int *PicNum, float ImgFeatures[]);
void TestMenu(float img[IMAGE_SIZE][IMAGE_SIZE]);

void FunctionTesting_menu();
void FunctionTesting_menu_print();

float DistanceCalculator(float ArryA[], float ArryB[], int size);

void MatrixDistanceCalculator(float ArryA[], float MatrixA[][IMAGE_SIZE], float DistanceArry[]);

void BreakDown(float SourceMatrix[IMAGE_SIZE][IMAGE_SIZE], float Values[32]);

float Matrix7squar_mean(float Matrix[][7]);

float Matrix7squar_std(float Matrix[][7], float Mean);

void Matrix7squar_loader(float Matrix[][7]);

void Array_loader(float Arry[], int N);