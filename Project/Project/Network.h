#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Image.h"

using namespace std;

struct Layer
{
	vector<vector<int> > weights; //matrix of weights
};

struct Output
{
	int arr[31]; //array of probabilities for each class

	Output(string); //create array ot probabilities from string
	string getResult(); //returns +, -, V, cos, ...
};

class Network
{
	vector<Layer> network; //the neural network is vector of layers

	vector<double> deltas; //for dynamical programming the deltas when backpropagating
	vector<double> values; //filled in forward pass used in backpropagating

public:
	Network(); //create network with hard coded size


	Output pass(Image const&) const; //forward pass
	void propagate(int error); //backpropagation
	int calculateError(Output const&, Output const&); //calculates error

};