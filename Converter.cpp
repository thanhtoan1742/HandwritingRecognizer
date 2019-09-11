#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

ifstream inputFile("train-images.idx3-ubyte", ifstream::binary);

char readChar()
{
	char c;
	inputFile.read(&c, sizeof(char));
	return c;
}

int readInt()
{
	int i;
	char c[sizeof(int)];
	inputFile.read(c, sizeof(c));
	reverse(c, c + sizeof(c));
	memcpy(&i, c, sizeof(i));
	return i;
}

int main()
{
	int luckyNumber = readInt();
	int nImage = readInt();
	int nRow = readInt();
	int nCol = readInt();

	freopen("convertedImage.txt", "w", stdout);

	for (int x = 0; x < 1; x++)
	{
		for (int i = 0; i < nRow; i++)
		{
			for (int j = 0; j < nCol; j++)
			{
				char pixelData = readChar();
				printf("%d ", pixelData );
			}
			printf("\n");
		}
	}
}
