#pragma once

#include <vector>

#include "Neuron.h"
class Neuron;

class Axon
{
public:
	Neuron *source, *target;
	float weight;
	float change;

	Axon();
	Axon(Neuron*, Neuron*, float);
	Axon(Neuron*, Neuron*);
	~Axon();
};

