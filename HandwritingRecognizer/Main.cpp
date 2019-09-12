#include "NeuralNetwork.h"
#include "Converter.h"
	
NeuralNetwork net;

int main()
{
	Converter::ConvertFile();
	net.Run();
	system("PAUSE");
}