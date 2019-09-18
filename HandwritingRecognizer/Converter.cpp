#include "Converter.h"

std::ifstream Converter::imagesFile("TrainImages", std::ifstream::binary);
std::ifstream Converter::labelsFile("TrainLabels", std::ifstream::binary);
std::ofstream Converter::exportFile("TestData");
std::ifstream Converter::importFile("TestData");

char Converter::data[Converter::N_IMAGE][Converter::N_ROW][Converter::N_ROW];
char Converter::labels[N_IMAGE];

Converter::Converter()
{
	std::ios_base::sync_with_stdio(false);
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

void Converter::ImportConvertedFile()
{
	for (int x = 0; x < N_IMAGE; x++)
		for (int i = 0; i < N_ROW; i++)
		for (int j = 0; j < N_COL; j++)
			importFile >> data[x][i][j];

	for (int i = 0; i < N_IMAGE; i++)
		importFile >> labels[i];
}

void Converter::ExportConvertedFile()
{
	// All data then labels.
	for (int x = 0; x < N_IMAGE; x++)
		for (int i = 0; i < N_ROW; i++)
		for (int j = 0; j < N_COL; j++)
				exportFile << data[x][i][j] << ' ';

	for (int i = 0; i < N_IMAGE; i++)
		exportFile << labels[i] << ' ';
}

float Converter::Sigmoid(const float &x)
{
	if (x > 5) return 1;
	if (x < -5) return 0;
	return 1 / (1 + exp(-x));
}

float Converter::DerivativeOfSigmoid(float x)
{
	if (abs(x) > 5) return 0;
	x = exp(-x);
	return x / pow(1 + x, 2);
}