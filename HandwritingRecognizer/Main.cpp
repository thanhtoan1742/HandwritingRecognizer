#include "NeuralNetwork.h"
#include "Converter.h"
	
NeuralNetwork net;

int main()
{
	Converter::ConvertFile();
	net.ImportNetwork();

	for (int i = 0; i < Converter::N_IMAGE; i++)
	{
		net.Recognize(Converter::data[i]);
		for (int i = 0; i < 10; i++)
			printf("%02f ", net.result[i]);
		printf("%d \n", int(Converter::labels[i]));
		//net.Train(Converter::labels[i]);
	}

	net.ExportNetwork();
	system("pause");
}