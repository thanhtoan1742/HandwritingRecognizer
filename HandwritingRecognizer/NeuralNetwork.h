#pragma once

#include <fstream>

#include "Axon.h"
#include "Neuron.h"

class NeuralNetwork
{
public:
	static const int INPUT_SIZE = 28 * 28;
	static const int OUTPUT_SIZE = 10;
	static const int LAYER_SIZE = 20;
	static const int NUMBER_OF_LAYERS = 2;

private:
	std::vector<Neuron> input, output;
	std::vector< std::vector<Neuron> > layers;

public:
	NeuralNetwork();
	~NeuralNetwork();

	void Run();
	void ImportNetwork();
	void ExportNetwork();
};

