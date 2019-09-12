#pragma once

#include <vector>

#include "Axon.h"
class Axon;

class Neuron
{
public:
	std::vector<Axon*> inputAxons, outputAxons;
	float bias;

	Neuron();
	~Neuron();
};

