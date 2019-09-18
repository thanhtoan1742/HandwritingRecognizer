#include "Axon.h"

Axon::Axon()
{
}

Axon::Axon(Neuron *_source, Neuron *_target, float _weight)
	:source(_source), target(_target), weight(_weight)
{
}

Axon::Axon(Neuron *_source, Neuron *_target)
	: source(_source), target(_target)
{
	weight = (float)(rand()) / (float)(RAND_MAX);
}

Axon::~Axon()
{
}

void Axon::Update()
{
	weight -= weightGradient / Converter::MINI_BATCH_SIZE;
}