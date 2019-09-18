#pragma once

#include <vector>

#include "Converter.h"
#include "Neuron.h"
class Neuron;

class Axon
{
public:
	Neuron *source, *target;
	float weight, weightGradient;

	Axon();
	Axon(Neuron*, Neuron*, float);
	Axon(Neuron*, Neuron*);
	~Axon();

	// to be called after having ran all tests or a mini-batch.
	void Update();
};

