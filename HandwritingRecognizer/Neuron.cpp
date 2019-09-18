#include "Neuron.h"

Neuron::Neuron()
{
	bias = (float)(rand()) / (float)(RAND_MAX);
}

Neuron::~Neuron()
{
}

void Neuron::Activate()
{
	preSigmoidActivation = bias;
	for (int i = 0; i < inputAxons.size(); i++)
		preSigmoidActivation += inputAxons[i]->source->activation * inputAxons[i]->weight;
	activation = Converter::Sigmoid(preSigmoidActivation);
}

void Neuron::Train(float eta)
{
	disiredActivation = activation;
	for (int i = 0; i < outputAxons.size(); i++)
	{
		float _biasGradient = eta * 2 * (outputAxons[i]->target->activation - outputAxons[i]->target->disiredActivation)
			* Converter::DerivativeOfSigmoid(preSigmoidActivation);

		biasGradient += _biasGradient;
		outputAxons[i]->weightGradient += _biasGradient * activation;
		disiredActivation -= _biasGradient * outputAxons[i]->weight;
	}
}

void Neuron::Update()
{
	bias -= biasGradient / Converter::MINI_BATCH_SIZE;
}