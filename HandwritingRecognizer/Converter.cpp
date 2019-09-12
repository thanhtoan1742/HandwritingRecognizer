#include "Converter.h"

std::ifstream Converter::inputFile("train-images.idx3-ubyte", std::ifstream::binary);

Converter::Converter()
{
}

Converter::~Converter()
{
}

char Converter::ReadChar()
{
	char c;
	inputFile.read(&c, sizeof(char));
	return c;
}

int Converter::ReadInt()
{
	int i;
	char c[sizeof(int)];
	inputFile.read(c, sizeof(c));
	std::reverse(c, c + sizeof(c));
	memcpy(&i, c, sizeof(i));
	return i;
}

void Converter::ConvertFile()
{
	int luckyNumber = ReadInt();
	int nImage = ReadInt();
	int nRow = ReadInt();
	int nCol = ReadInt();


	for (int x = 0; x < 10; x++)
	{
		//std::ofstream fo((std::string("Tests/CI_") + std::to_string(x) + std::string("_Image.txt")));

		for (int i = 0; i < nRow; i++)
		{
			for (int j = 0; j < nCol; j++)
			{
				char pixelData = ReadChar();
				data[x][i][j] = pixelData;
				//fo << int(pixelData) << ' ';
			}
			//fo << '\n';
		}
	}
}
