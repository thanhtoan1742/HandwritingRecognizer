#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <fstream>
#include <string>

class Converter
{
private:
	static std::ifstream inputFile;
public:
	static const int N_IMAGE = 60000;
	static const int N_ROW = 28;
	static const int N_COL = 28;
	static char data[N_IMAGE][N_ROW][N_COL];

private:
	static char ReadChar();
	static int ReadInt();
public:
	Converter();
	~Converter();
	static void ConvertFile();
};
