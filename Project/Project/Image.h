#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

class Image
{
	char array[625]; //pixels for image with size 45x45
	string type; //class of the image

public:
	Image(string); //build pixel array out of name of jpg file

	double getValue(int index) const
	{
		return array[index] / 256;
	}

	string getType() const { return type; }

	int size() const { return 625; }
};
