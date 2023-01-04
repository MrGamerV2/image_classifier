#pragma once

#define IMAGE_SIZE 28
#define BATCH_SIZE 100
#define IMAGE_BUFFER_SIZE 784
// Personal edits

#define IMAGE_DATABASE_LIMIT 500 
#define FEATURE_LIMIT 32

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
    float imgs[IMAGE_DATABASE_LIMIT][32];
};

//      Function Declaration

void StartMenu_print();

// Clears the screen :)
void ClearScreen();

// Makes sure input is only numeric.
int CheckInput(int Input);

// Prints the authors info.
void Info_print();

// @param img Image
void Image_print(float img[][IMAGE_SIZE]);

// @param Label Number Label @param PicNum Picture Numer
void ExploreMenu_print(int *Label, int *PicNum);

// @param img 28x28 Image loaded as matrix
void ExploreMenu(float img[][IMAGE_SIZE]);

void TrainMenu_print();
// @param img 28x28 Image loaded as matrix @param TrainSets 
void TrainMenu(TrainSet TrainSets[], float img[][IMAGE_SIZE], int *IsDatabaseReady);

// @param Label Number Label @param PicNum Picture Numer @param ImgFeatures The array which holds the featues
void TestMenu_print(int *Label, int *PicNum, float ImgFeatures[], int *ChosenLabel);

// @param img 28x28 Matrix @param IsDatabaseReady A fail safe
void TestMenu(TrainSet Trainsets[],float img[][IMAGE_SIZE] , int *IsDatabaseReady);

void FunctionTesting_menu();

void FunctionTesting_menu_print();

// Calculates distance of two arrays. @param size Length of arrays.
float DistanceCalculator(float ArrayA[], float ArrayB[], int size);

// Compares distance of an array to a matrix.
void MatrixDistanceCalculator(float Matrix[][FEATURE_LIMIT], float Array[], float DistanceArry[]);

// Calculates features of 28x28 matrix @param Values The array which holds the features.
void BreakDown(float SourceMatrix[IMAGE_SIZE][IMAGE_SIZE], float Values[32]);

float Matrix7squar_mean(float Matrix[][7]);

// This function needs mean of the matrix before hand.
float Matrix7squar_std(float Matrix[][7], float Mean);

// Loads 7x7 matrix.
void Matrix7squar_loader(float Matrix[][7]);

// Loads Array with N lengh @param N Lengh of the array
void Array_loader(float Arry[], int N);