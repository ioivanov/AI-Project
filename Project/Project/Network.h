#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Image.h"
#include "Functions.h"

using namespace std;

struct Layer
{
	vector<vector<double> > weights; //matrix of weights
};

struct Output
{
	int arr[31]; //array of probabilities for each class

	Output() = default;

	Output(string const& s)
	{
		int index = getIndex(s);

		for (size_t i = 0; i < 31; i++)
		{
			arr[i] = 0;
		}
		arr[index] = 1;
	}

	string getClass()
	{
		double maxProb = 0;
		int maxIndex = 0;

		for (size_t i = 0; i < 31; i++)
		{
			if (arr[i] > maxProb)
			{
				maxProb = arr[i];
				maxIndex = i;
			}
		}

		return getName(maxIndex);
	}
};

class Network
{
	vector<Layer> network; //the neural network is vector of layers

	vector<double> deltas; //for dynamical programming the deltas when backpropagating
	vector<double> values; //filled in forward pass used in backpropagating
	vector<int> sizes; //relative position of neuron in network depending on the layer index

	double calcucateDelta(int, int);
	Output pass(Image const&); //pass image through the neural network
	void propagate(Output const&, double); //adjust network weights through backpropagation

public:
	Network();

	void train(Image const&);
	string clasify(Image const&);

};

double Network::calcucateDelta(int layer, int neuronInLayer)
{
	int sum = 0;
	//go trought all successors of neuron
	for (size_t i = 0; i < network[layer].weights[neuronInLayer].size(); i++)
	{
		//deltas of successors*edgeWeight
		sum += deltas[sizes[layer + 1] + i] * network[layer].weights[neuronInLayer][i];
	}

	double neuronOutput = values[sizes[layer] + neuronInLayer];
	//sum of successors errors*derivativeOfActivationFunction
	double delta = sum * neuronOutput * (1 - neuronOutput);

	//save delta for future use;
	deltas[sizes[layer] + neuronInLayer] = delta;

	return delta;
}

Network::Network() //create network with hard coded size
{
	sizes.push_back(0);
	sizes.push_back(625);
	sizes.push_back(725);
	sizes.push_back(825);


	//input to hidden
	Layer inputToHidden;
	for (size_t i = 0; i < 100; i++) //weights for each neuron from hidden layer 1
	{
		vector<double> weights;
		for (size_t j = 0; j < 625; j++) //weight from each input neuron
		{
			double weight = (rand() % 1000) / (double)1000;
			weights.push_back(weight);
		}
		inputToHidden.weights.push_back(weights);
	}
	network.push_back(inputToHidden);

	//hidden1 to hidden2
	Layer hiddenToHidden;
	for (size_t i = 0; i < 100; i++) //weights for each neuron from hidden layer 2
	{
		vector<double> weights;
		for (size_t j = 0; j < 100; j++) //weight from each neuron from hidden layer 1
		{
			double weight = (rand() % 1000) / (double)1000;
			weights.push_back(weight);
		}
		hiddenToHidden.weights.push_back(weights);
	}
	network.push_back(hiddenToHidden);

	//hidden2 to output
	Layer hiddenToOutput;
	for (size_t i = 0; i < 31; i++) //weights for each output neuron
	{
		vector<double> weights;
		for (size_t j = 0; j < 100; j++) //weight from each neuron from hidden layer 2
		{
			double weight = (rand() % 1000) / (double)1000;
			weights.push_back(weight);
		}
		hiddenToOutput.weights.push_back(weights);
	}
	network.push_back(hiddenToOutput);
}


Output Network::pass(Image const& image) //forward pass
{
	for (size_t i = 0; i < image.size(); i++)
	{
		double value = image.getValue(i);
		values.push_back(value);
	}

	//for each layer
	for (size_t i = 0; i < network.size(); i++)
	{
		//starting index of neurons in the prevoius layer
		int startIndex = sizes[i];
		//for each neuron in layer
		for (size_t j = 0; j < network[i].weights.size(); j++)
		{
			double sum = 0;
			for (size_t k = 0; k < network[i].weights[j].size(); k++)
			{
				//weight * the value from neuron from previous layer
				sum += network[i].weights[j][k] * values[startIndex + k];
			}
			//sizes[i + 1] is starting index of neurons in the current layer
			values[sizes[i + 1] + j] = sigmoid(sum);
		}
	}

	Output out;
	for (size_t i = 0; i < 31; i++)
	{
		out.arr[i] = values[3] + i;
	}
	return out;
}

void Network::propagate(Output const& target, double rate) //backpropagation
{
	//output neuron
	int startIndex = sizes[3];
	for (size_t i = values.size() - 1; i >= startIndex; i--)
	{
		//calculate error based on the output of the last pass and target
		deltas[i] = (values[i] - target.arr[i - startIndex])*values[i] * (1 - values[i]);
	}

	//for each layer from back to front
	for (size_t i = network.size() - 1; i < 0; i--)
	{
		//for each neuron in layer
		for (size_t j = 0; j < network[i].weights.size(); j++)
		{
			//for each successor
			for (size_t k = 0; k < network[i].weights[j].size(); k++)
			{
				//weight correction learningRate*outputOfNeuron*deltaOfSuccessor
				network[i].weights[j][k] += rate*values[sizes[i] + j] * calcucateDelta(i, j);
			}
		}
	}
}

void Network::train(Image const& image)
{
	double rate;

	pass(image);

	Output target(image.getType());
	propagate(target, rate);
}

string Network::clasify(Image const& image)
{
	Output result = pass(image);
	return result.getClass();
}