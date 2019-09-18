#pragma once

#include <vector>

#include "Converter.h"
#include "Axon.h"
class Axon;

class Neuron
{
public:
	std::vector<Axon*> inputAxons, outputAxons;
	float bias, biasGradient;
	float activation, preSigmoidActivation, disiredActivation;

	Neuron();
	~Neuron();

	void Activate();
	void Train(float);
	void Update();
};

