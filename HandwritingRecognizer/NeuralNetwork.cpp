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
			delete layers[i][j].inputAxons.back();
			layers[i][j].inputAxons.pop_back();
		}
	}

	for (int i = 0; i < OUTPUT_SIZE; i++)
	{
		while (!output[i].inputAxons.empty())
		{
			delete output[i].inputAxons.back();
			output[i].inputAxons.pop_back();
		}
	}
}

void NeuralNetwork::Run()
{
	ExportNetwork();
}

void NeuralNetwork::ImportNetwork()
{
}

void NeuralNetwork::ExportNetwork()
{
	// The format is:
	// Number of processing layers.
	// Size of input layer.
	// Sizes of each layer.
	// Size of output layer.
	// Biases of each neuron in each layer (each layer has a separate line, input layer does not have bias i.e. bias = 0).
	// Weight of 1st layer to 2nd layer (1st neuron of 1st layer then so on).
	// Weight of 2nd layer to 3rd layer.
	// ...
	// Weight of (N-1)th layer to Nth layer.

	std::ofstream fo("NeuralNetwork.txt");

	// Sizes.
	fo << NUMBER_OF_LAYERS << '\n';
	fo << INPUT_SIZE << '\n';
	for (int i = 0; i < NUMBER_OF_LAYERS; i++)
		fo << LAYER_SIZE << '\n';
	fo << OUTPUT_SIZE << '\n';

	// Biases.
	for (int x = 0; x < NUMBER_OF_LAYERS; x++)
	{
		for (int i = 0; i < LAYER_SIZE; i++)
			fo << layers[x][i].bias << ' ';
		fo << '\n';
	}
	for (int i = 0; i < OUTPUT_SIZE; i++)
		fo << output[i].bias << ' ';
	fo << '\n';

	// Wieghts.
	// TODO: complete the code.
	for (int x = 0; x < NUMBER_OF_LAYERS; x++);
}