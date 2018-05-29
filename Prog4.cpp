#include "TimUtils.h"
#include "LynzieUtilities.h"
#include "unsortedDouble.h"
#include "levi.h"
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>


int main(int argc, char **argv)
{
    ifstream inFile;
    ofstream outFile;\


    string temp;
    char *convertTemp = nullptr;
    char beltPathSize;

    box dimensions;
    box tempBox;

    int conveyorBeltLength = 0;
    int widthBeltA = 0;
    int widthBeltB = 0;
    int widthBeltC = 0;
    int boxWidth = 0;
    int boxLength = 0;
    int boxHeight = 0;
    int boxNumber = 0;	
    int sumNum = 1;
    int excess = 0;

    vector<conveyorBelt> sortVector;

    conveyorBelt beltA;
    conveyorBelt beltB;
    conveyorBelt beltC;

    conveyorBelt smallBelt;
    conveyorBelt medBelt;
    conveyorBelt largeBelt;

    unsortedDouble<box> inBoxDimensions;

    //Must be 3 command line arguments
    if (argc != 3)
    {
        cout << "Usage: prog4.exe <boxFile>.sim <int conveyorLength>" << endl;
        return -1;
    }

    //Copy agrv to a temp variable to not change it
    temp = argv[2];

    //Convert the string to an int
    conveyorBeltLength = strtol(temp.c_str(), &convertTemp, 10);
    temp.clear();
    temp = convertTemp;
    //Check that the conveyor width is an integer
    if (!temp.empty())
    {
        cout << argv[2] << " is not a valid integer." << endl;
        return -2;
    }
    
    beltA.setLength(conveyorBeltLength);
    beltB.setLength(conveyorBeltLength);
    beltC.setLength(conveyorBeltLength);

    //Open input and output
    inFile.open(argv[1]);
    outFile.open("run.out");

    //Check that input file is open
    if (!inFile.is_open())
    {
        cout << "Unable to open file " << argv[1] << endl;
        return -3;
    }

    //Check that output file is open
    if (!outFile.is_open())
    {
        cout << "Unable to open file \"run.out\"" << endl;
        return -4;
    }

    //While not end of case
    //Get the initial conveyor belt dimensions 
    while (getConveyorDimensions(inFile, widthBeltA, widthBeltB, widthBeltC))
    {
		boxNumber = 0;
        outputSimNum(cout, sumNum);
        sumNum ++;
        //Assign the belts the widths read in

        beltA.setWidth(widthBeltA);
        beltB.setWidth(widthBeltB);
        beltC.setWidth(widthBeltC);

        //Assign the belts a letter
        beltA.setLetter('A');
        beltB.setLetter('B');
        beltC.setLetter('C');

        //Add the belts to a vector to sort
        sortVector.push_back(beltC);
        sortVector.push_back(beltB);
        sortVector.push_back(beltA);

        //Sort the belts
        sort(sortVector.begin(), sortVector.end());

        smallBelt = sortVector.at(0);
        medBelt = sortVector.at(1);
        largeBelt = sortVector.at(2);

        //While not end of boxes for case
        while (getBoxDimensions(inFile, boxWidth, boxLength, boxHeight, boxNumber))
        {
            //Find the smallest dimension for width
            //Find the second smallest dimension for length
            //Assign the largest value to the height
            //Assign to a box structure
            rotateBox(boxWidth, boxLength, boxHeight);
            dimensions.boxNumber = boxNumber;
            dimensions.depth = boxLength;
            dimensions.width = boxWidth;
            dimensions.height = boxHeight;

            //Add the box to the back of an unsorted list
            inBoxDimensions.push_back(dimensions);
        }

        // Figure out what belt the box goes on and add it to the belt
        while (!inBoxDimensions.isEmpty())
        {
            inBoxDimensions.pop_front(dimensions);

            beltPathSize = getFitConveyor( dimensions, smallBelt, medBelt, largeBelt );

            switch (beltPathSize)
            {
            case 's':
				dimensions = getPropDims(dimensions, smallBelt);
                smallBelt.addBox(dimensions);
                excess = smallBelt.is_full(smallBelt, conveyorBeltLength);
                if(excess)
                    if(smallBelt.removeBox(tempBox, excess))
                        outputBox(outFile, tempBox, smallBelt);
                break;
            case 'm':
				dimensions = getPropDims(dimensions, medBelt);
                medBelt.addBox(dimensions);
                excess = medBelt.is_full(medBelt, conveyorBeltLength);
                if(excess)
                    if(medBelt.removeBox(tempBox, excess))
                        outputBox(outFile, tempBox, medBelt);
                break;
            case 'l':
				dimensions = getPropDims(dimensions, largeBelt);
                largeBelt.addBox(dimensions);
                excess = largeBelt.is_full(largeBelt, conveyorBeltLength);
                if(excess)
                    if(largeBelt.removeBox(tempBox, excess))
                        outputBox(outFile, tempBox, largeBelt);
                break;
            default:
                cout << "The box does not fit on any belt." << endl;
                break;
            }
        }
        sortVector.clear();
        beltA.clear();
        beltB.clear();
        beltC.clear();

        smallBelt.clear();
        medBelt.clear();
        largeBelt.clear();
    }

    return 0;
}