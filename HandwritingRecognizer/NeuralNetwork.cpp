#include "NeuralNetwork.h"

inline float sigmoid(const float &x)
{
	return 1 / (1 - exp(-x));
}

float derivativeOfSigmoid(float x)
{
	x = exp(x);
	return x / pow(1 + x, 2);
}

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
		fo << '\n';
	}
}

void NeuralNetwork::Recognize(char data[][INPUT_IMAGE_LENGTH])
{
	for (int i = 0; i < INPUT_IMAGE_LENGTH; i++)
	for (int j = 0; j < INPUT_IMAGE_LENGTH; j++)
		input[i * INPUT_IMAGE_LENGTH + j].activation = data[i][j];

	for (int x = 0; x < NUMBER_OF_LAYERS; x++)
		for (int i = 0; i < LAYER_SIZE; i++)
		{
			layers[x][i].activation = layers[x][i].bias;
			for (int j = 0; j < layers[x][i].inputAxons.size(); j++)
				layers[x][i].activation += layers[x][i].inputAxons[j]->source->activation * layers[x][i].inputAxons[j]->weight;
			layers[x][i].activation = sigmoid(layers[x][i].activation);
		}

	for (int i = 0; i < OUTPUT_SIZE; i++)
	{
		output[i].activation = output[i].bias;
		for (int j = 0; j < output[i].inputAxons.size(); j++)
			output[i].activation += output[i].inputAxons[j]->source->activation * output[i].inputAxons[j]->weight;

		result[i] = output[i].activation;
		output[i].activation = sigmoid(output[i].activation);
	}
}

void NeuralNetwork::Train(char answer)
{
	for (int i = 0; i < OUTPUT_SIZE; i++)
		output[i].disiredActivation = 0;
	output[int(answer)].disiredActivation = 1;
}