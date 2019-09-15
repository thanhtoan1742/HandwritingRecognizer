#include "Converter.h"

std::ifstream Converter::imagesFile("TrainImages", std::ifstream::binary);
std::ifstream Converter::labelsFile("TrainLabels", std::ifstream::binary);
char Converter::data[Converter::N_IMAGE][Converter::N_ROW][Converter::N_ROW];
char Converter::labels[N_IMAGE];
int currentTest = 0;

Converter::Converter()
{
}

Converter::~Converter()
{
}

char Converter::ReadChar(std::ifstream &file)
{
	char c;
	file.read(&c, sizeof(char));
	return c;
}

int Converter::ReadInt(std::ifstream &file)
{
	int i;
	char c[sizeof(int)];
	file.read(c, sizeof(c));
	std::reverse(c, c + sizeof(c));
	memcpy(&i, c, sizeof(i));
	return i;
}

void Converter::ConvertFile()
{
	int luckyNumber = ReadInt(imagesFile);
	luckyNumber = ReadInt(labelsFile);
	int nImage = ReadInt(imagesFile);
	nImage = ReadInt(labelsFile);
	int nRow = ReadInt(imagesFile);
	int nCol = ReadInt(imagesFile);

	for (int x = 0; x < N_IMAGE; x++)
	{
		for (int i = 0; i < N_ROW; i++)
		for (int j = 0; j < N_COL; j++)
			data[x][i][j] = ReadChar(imagesFile);

		labels[x] = ReadChar(labelsFile);
	}
}
