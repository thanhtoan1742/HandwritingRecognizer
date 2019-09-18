#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork()
{
	for (int i = 0; i < INPUT_SIZE; i++)
	for (int j = 0; j < LAYER_SIZE; j++)
	{
		Axon *axon = new Axon(&input[i], &layers[0][j]);
		input[i].outputAxons.push_back(axon);
		layers[0][j].inputAxons.push_back(axon);
	}

	for (int x = 1; x < NUMBER_OF_LAYERS; x++)
		for (int i = 0; i < LAYER_SIZE; i++)
		for (int j = 0; j < LAYER_SIZE; j++)
		{
			Axon *axon = new Axon(&layers[x - 1][i], &layers[x][j]);
			layers[x - 1][i].outputAxons.push_back(axon);
			layers[x][j].inputAxons.push_back(axon);
		}

	for (int i = 0; i < LAYER_SIZE; i++)
	for (int j = 0; j < OUTPUT_SIZE; j++)
	{
		Axon *axon = new Axon(&layers[NUMBER_OF_LAYERS - 1][i], &output[j]);
		layers[NUMBER_OF_LAYERS - 1][i].outputAxons.push_back(axon);
		output[j].inputAxons.push_back(axon);
	}
}


NeuralNetwork::~NeuralNetwork()
{
	for (int i = 0; i < INPUT_SIZE; i++)
		while (!input[i].outputAxons.empty())
		{
			delete input[i].outputAxons.back();
			input[i].outputAxons.pop_back();
		}

	for (int i = 0; i < NUMBER_OF_LAYERS; i++)
	for (int j = 0; j < LAYER_SIZE; j++)
		while (!layers[i][j].outputAxons.empty())
		{
			delete layers[i][j].outputAxons.back();
			layers[i][j].outputAxons.pop_back();
		}
}

void NeuralNetwork::ImportNetwork()
{
	// Biases.
	std::ifstream fi("NeuralNetwork.txt");
	for (int i = 0; i < INPUT_SIZE; i++)
		fi >> input[i].bias;

	for (int x = 0; x < NUMBER_OF_LAYERS; x++)
		for (int i = 0; i < LAYER_SIZE; i++)
			fi >> layers[x][i].bias;

	for (int i = 0; i < OUTPUT_SIZE; i++)
		fi >> output[i].bias;

	// Weights.
	for (int i = 0; i < INPUT_SIZE; i++)
	{
		for (int j = 0; j < input[i].outputAxons.size(); j++)
			fi >> input[i].outputAxons[j]->weight;
	}

	for (int x = 0; x < NUMBER_OF_LAYERS; x++)
	{
		for (int i = 0; i < LAYER_SIZE; i++)
		{
			for (int j = 0; j < layers[x][i].outputAxons.size(); j++)
				fi >> layers[x][i].outputAxons[j]->weight;
		}
	}
}

void NeuralNetwork::ExportNetwork()
{
	// The format is:
	// Biases of each neuron in each layer (each layer has a separate line, input layer does not have bias i.e. bias = 0).
	// Weight of 1st layer to 2nd layer (1st neuron of 1st layer then so on).
	// Weight of 2nd layer to 3rd layer.
	// ...
	// Weight of (N-1)th layer to Nth layer.

	std::ofstream fo("NeuralNetwork.txt");

	// Biases.
	for (int i = 0; i < INPUT_SIZE; i++)
		fo << input[i].bias << ' ';
	fo << '\n';

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
	for (int i = 0; i < INPUT_SIZE; i++)
	{
		for (int j = 0; j < input[i].outputAxons.size(); j++)
			fo << input[i].outputAxons[j]->weight << ' ';
		fo << '\n';
	}

	for (int x = 0; x < NUMBER_OF_LAYERS; x++)
	{
		for (int i = 0; i < LAYER_SIZE; i++)
		{
			for (int j = 0; j < layers[x][i].outputAxons.size(); j++)
				fo << layers[x][i].outputAxons[j]->weight << ' ';
			fo << '\n';
		}
	}
}

void NeuralNetwork::GetData(char data[][INPUT_IMAGE_LENGTH], char answer)
{
	// Get data for recognizing and training. If no training needed, provide answer with 
	// any character and do not call the Train(float) method.
	for (int i = 0; i < INPUT_IMAGE_LENGTH; i++)
	for (int j = 0; j < INPUT_IMAGE_LENGTH; j++)
		input[i * INPUT_IMAGE_LENGTH + j].activation = data[i][j];

	for (int i = 0; i < OUTPUT_SIZE; i++)
		output[i].disiredActivation = 0;
	output[int(answer)].disiredActivation = 1;
}

void NeuralNetwork::Recognize()
{
	for (int x = 0; x < NUMBER_OF_LAYERS; x++)
		for (int i = 0; i < LAYER_SIZE; i++)
			layers[x][i].Activate();

	for (int i = 0; i < OUTPUT_SIZE; i++)
	{
		output[i].Activate();
		result[i] = output[i].activation;
	}
}

void NeuralNetwork::Train(float eta)
{
	for (int x = NUMBER_OF_LAYERS - 1; x >= 0; x--)
		for (int i = 0; i < LAYER_SIZE; i++)
			layers[x][i].Train(eta);

	for (int i = 0; i < INPUT_SIZE; i++)
		input[i].Train(eta);
}

void NeuralNetwork::Update()
{
	for (int i = 0; i < INPUT_SIZE; i++)
	{
		input[i].Update();
		for (int j = 0; j < input[i].outputAxons.size(); j++)
			input[i].outputAxons[j]->Update();
	}

	for (int x = 0; x < NUMBER_OF_LAYERS; x++)
		for (int i = 0; i < LAYER_SIZE; i++)
		{
			layers[x][i].Update();
			for (int j = 0; j < layers[x][i].outputAxons.size(); j++)
				layers[x][i].outputAxons[j]->Update();
		}
}

float NeuralNetwork::Cost()
{
	float cost = 0;
	for (int i = 0; i < OUTPUT_SIZE; i++)
		cost += pow(output[i].activation - output[i].disiredActivation, 2);
	return cost;
}

int NeuralNetwork::GetResult()
{
	int res = 0;
	for (int i = 0; i < OUTPUT_SIZE; i++)
		if (output[i].activation > output[res].activation)
			res = i;
	return res;
}