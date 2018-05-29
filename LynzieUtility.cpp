/**************************************************************************//**
 * @file
 * @brief Utility functions
 *
 *****************************************************************************/
#include "belt.h"
#include "LynzieUtilities.h"


/**************************************************************************//**
 * @author Lynzie Trively
 *
 * @par Description:
 *  Reads in the conveyor belt widths and returns them.
 *
 *  @param[in,out] infile - The input file to read from
 *  @param[in,out] widthBeltA - The width of the first belt
 *  @param[in,out] widthBeltB - The width of the second belt
 *  @param[in,out] widthBeltC - The width of the third belt
 *
 *  @returns True if the dimensions were read in correctly
 *  @returns False if the end of the simulation was read in (0 0 0)
 *
 *****************************************************************************/
bool getConveyorDimensions(ifstream &infile, int &widthBeltA, int &widthBeltB, int &widthBeltC)
{
	string temp;
	
	//Read in the first line until a space is reached
	getline(infile, temp, ' ');

	if (!temp.empty())
	{
		//Convert the string to a c string and then to an int
		widthBeltA = atoi(temp.c_str());

		//Clear the temp string
		temp.clear();

		//Read in the first line until a space is reached
		getline(infile, temp, ' ');
		//Convert the string to a c string and then to an int
		widthBeltB = atoi(temp.c_str());

		//Clear the temp string
		temp.clear();

		//Read in the first line until a space is reached
		getline(infile, temp);
		//Convert the string to a c string and then to an int
		widthBeltC = atoi(temp.c_str());

		//Clear the temporary variable
		temp.clear();

		if (widthBeltA == 0 && widthBeltB == 0 && widthBeltC == 0)
			return false;
		else
			return true;
	}
	return false;
}

/**************************************************************************//**
 * @author Lynzie Trively
 *
 * @par Description:
 *  Reads in the box dimensions and returns them.
 *
 *  @param[in,out] infile - The input file to read from
 *  @param[in,out] width - The width of the box
 *  @param[in,out] length - The length/depth of the box
 *  @param[in,out] height - The height of the box
 *  @param[in,out] boxNumber - The number of the box 
 *
 *  @returns True if the boxes were successfully read in
 *  @returns False if the end of the boxes (-1 -1 -1) was read in
 *
 *****************************************************************************/
bool getBoxDimensions(ifstream &infile, int &width, int &length, int &height, int &boxNumber)
{
	string temp;

	//Read in the box dimensions until a space is reached
	getline(infile, temp, ' ');
	if (!temp.empty())
	{
		//Convert the string to an int
		width = atoi(temp.c_str());

		//Clear the temp string
		temp.clear();

		//Read in the box dimensions until a space is reached
		getline(infile, temp, ' ');
		//Convert the string to an int
		length = atoi(temp.c_str());

		//Clear the temp string
		temp.clear();

		//Read in the box dimensions until a space is reached
		getline(infile, temp);
		//Convert the string to an int
		height = atoi(temp.c_str());

		//Clear the temp string
		temp.clear();

		//Check not end of the boxes
		if (width == -1 && length == -1 && height == -1)
			return false;

		//Increment box number
		boxNumber++;

		return true;
	}
	else
		return false;
}

/**************************************************************************//**
 * @author Lynzie Trively
 *
 * @par Description:
 *  Orders the box dimensions from smallest to largest 
 *  (width < length < height).
 *
 *  @param[in,out] width - The width of the box
 *  @param[in,out] length - The length/depth of the box
 *  @param[in,out] height - The height of the box
 *
 *****************************************************************************/
void rotateBox(int &width, int &length, int &height)
{
	//Width < Length < Height
	//If length is smaller, swap them
	if (width > length)
		swap(length, width);

	//If height is smaller, swap them
	if (width > height)
		swap(height, width);

	//If the height is smaller than length, swap them
	if (length > height)
		swap(height, length);
}
