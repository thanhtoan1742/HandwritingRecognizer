#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork()
{
	input.resize(INPUT_SIZE);

	for (int i = 0; i < NUMBER_OF_LAYERS; i++)
	{
		layers.emplace_back(LAYER_SIZE);
		if (i == 0)
			for (int j = 0; j < INPUT_SIZE; j++)
			for (int k = 0; k < LAYER_SIZE; k++)
			{
				// TODO: edit the initial weight to be random.
				Axon *axon = new Axon(&input[j], &layers[i][k]);
				input[j].outputAxons.push_back(axon);
				layers[i][k].inputAxons.push_back(axon);
			}
		else
			for (int j = 0; j < LAYER_SIZE; j++)
			for (int k = 0; k < LAYER_SIZE; k++)
			{
				// TODO: edit the initial weight to be random.
				Axon *axon = new Axon(&layers[i - 1][j], &layers[i][k]);
				layers[i - 1][j].outputAxons.push_back(axon);
				layers[i][k].inputAxons.push_back(axon);
			}
	}

	output.resize(OUTPUT_SIZE);
}


NeuralNetwork::~NeuralNetwork()
{
	for (int i = 0; i < NUMBER_OF_LAYERS; i++)
	for (int j = 0; j < LAYER_SIZE; j++)
	{
		while (!layers[i][j].inputAxons.empty())
		{
			// just safety check.
			if (layers[i][j].inputAxons.back())
				delete layers[i][j].inputAxons.back();
			layers[i][j].inputAxons.pop_back();
		}

		while (!layers[i][j].outputAxons.empty())
		{
			if (layers[i][j].outputAxons.back())
				delete layers[i][j].outputAxons.back();
			layers[i][j].outputAxons.pop_back();
		}
	}
}

void NeuralNetwork::Run()
{

}
