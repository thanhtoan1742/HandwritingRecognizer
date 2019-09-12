#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

ifstream inputFile("train-images.idx3-ubyte", ifstream::binary);

char ReadChar()
{
	char c;
	inputFile.read(&c, sizeof(char));
	return c;
}

int ReadInt()
{
	int i;
	char c[sizeof(int)];
	inputFile.read(c, sizeof(c));
	reverse(c, c + sizeof(c));
	memcpy(&i, c, sizeof(i));
	return i;
}

void ConvertAllFile()
{
	int luckyNumber = ReadInt();
	int nImage = ReadInt();
	int nRow = ReadInt();
	int nCol = ReadInt();

	freopen("convertedImage.txt", "w", stdout);

	for (int x = 0; x < nImage; x++)
	{
		for (int i = 0; i < nRow; i++)
		{
			for (int j = 0; j < nCol; j++)
			{
				char pixelData = ReadChar();
				printf("%d ", pixelData );
			}
			printf("\n");
		}
	}
}
