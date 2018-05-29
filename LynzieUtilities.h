/**************************************************************************//**
 * @file
 * @brief Lynzie Utilities Header File
 *
 *****************************************************************************/

#ifndef _LYNZIEUTILITIES_H_
#define _LYNZIEUTILITIES_H_

#include "Belt.h"
#include <fstream>
#include <string>

using namespace std;

bool getConveyorDimensions(ifstream &infile, int &widthBeltA, 
	int &widthBeltB, int &widthBeltC);

bool getBoxDimensions(ifstream &infile, int &width, int &length, 
	int &height, int &boxNumber);

void rotateBox(int &width, int &length, int &height);


#endif