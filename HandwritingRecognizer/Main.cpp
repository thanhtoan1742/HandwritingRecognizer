#include <chrono>

#include "NeuralNetwork.h"
#include "Converter.h"
	
const float eta = 0.5;
NeuralNetwork net;
int testOrder[Converter::N_IMAGE];

std::mt19937 randomGenerator(std::chrono::steady_clock::now().time_since_epoch().count());

int main()
{
	Converter::ConvertFile();
	net.ImportNetwork();
		
	for (int i = 0; i < Converter::N_IMAGE; i++) testOrder[i] = i;
	std::shuffle(testOrder, testOrder + Converter::N_IMAGE, randomGenerator);

	float aveAllCost = 0;
	for (int x = 0; x < Converter::N_IMAGE / Converter::MINI_BATCH_SIZE; x++)
	{
		float averageCost = 0;
		for (int i = 0; i < Converter::MINI_BATCH_SIZE; i++)
		{
			net.GetData(Converter::data[testOrder[x * Converter::MINI_BATCH_SIZE + i]], Converter::labels[testOrder[x * Converter::MINI_BATCH_SIZE + i]]);
			net.Recognize();

			averageCost += net.Cost();
			//printf("%d %02f\n", net.GetResult(), net.Cost());

			net.Train(eta);

			net.ExportNetwork();
		}

		aveAllCost += averageCost;
		averageCost /= Converter::MINI_BATCH_SIZE;
		printf("Average cost of minibatch # %d: %02f\n", x, averageCost);

		net.Update();
	}

	aveAllCost /= Converter::N_IMAGE;
	printf("Cost of all tests : %02f\n", aveAllCost);
	net.ExportNetwork();
	system("pause");
}