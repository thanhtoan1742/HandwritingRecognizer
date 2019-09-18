#pragma once

#include <fstream>

#include "Axon.h"
#include "Neuron.h"

class NeuralNetwork
{
public:
	static const int INPUT_IMAGE_LENGTH = 28;
	static const int INPUT_SIZE = 28 * 28;
	static const int OUTPUT_SIZE = 10;
	static const int LAYER_SIZE = 20;
	static const int NUMBER_OF_LAYERS = 2;

private:
	Neuron input[INPUT_SIZE], output[OUTPUT_SIZE];
	Neuron layers[NUMBER_OF_LAYERS][LAYER_SIZE];

public:
	float result[OUTPUT_SIZE];

	NeuralNetwork();
	~NeuralNetwork();

	void ImportNetwork();
	void ExportNetwork();

	void GetData(char[][INPUT_IMAGE_LENGTH], char);
	void Recognize();
	void Train(float);

	// to be called after having ran all tests or a mini-batch.
	void Update();
	int GetResult();
	float Cost();
};

