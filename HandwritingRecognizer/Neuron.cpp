#include "Neuron.h"

Neuron::Neuron()
{
	// TODO: randomize the bias.
	bias = (float)(rand()) / (float)(RAND_MAX);
}

Neuron::~Neuron()
{
}
