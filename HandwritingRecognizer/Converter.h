#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <fstream>
#include <string>
#include <time.h>
#include <random>
#include <chrono>

class Converter
{
private:
	static std::ifstream imagesFile;
	static std::ifstream labelsFile;

public:
	static const int N_IMAGE = 60000; //60000
	static const int N_ROW = 28;
	static const int N_COL = 28;
	static const int MINI_BATCH_SIZE = 100;

	static char data[N_IMAGE][N_ROW][N_COL];
	static char labels[N_IMAGE];

private:
	static char ReadChar(std::ifstream&);
	static int ReadInt(std::ifstream&);

public:
	Converter();
	~Converter();

	static void ConvertFile();
	static float Sigmoid(const float&);
	static float DerivativeOfSigmoid(float);
};
