/**************************************************************************//**
 * @file
 * @brief conveyorBelt functions
 *
 *****************************************************************************/
#include "Belt.h"
#include "unsortedDouble.h"
#include "TimUtils.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  The constructor for the conveyorBelt class
 *
 *****************************************************************************/
conveyorBelt::conveyorBelt()
{
    unsortedDouble<box> boxes; //list of boxes
    int length = 0;//length to be assigned
    int width = 0;//width to be assigned
    char letter = NULL; //character to be assinged
    theBelt = boxes;
    theLength = length;
    theWidth = width;
    letter = letter;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Gets the width of the conveyorBelt
 *
 *  @returns An integer of the width of the conveyorBelt
 *
 *****************************************************************************/
int conveyorBelt::getWidth()
{
    return theWidth;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Gets the ltter of the conveyorBelt
 *
 *  @returns An character of the letter of the conveyorBelt
 *
 *****************************************************************************/
char conveyorBelt::getLetter()
{
    return letter;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Gets the length of the conveyorBelt
 *
 *  @returns An integer of the length of the conveyorBelt
 *
 *****************************************************************************/
int conveyorBelt::getLength()
{
    return theLength;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Gets the total used length of the boxes in the conveyorBelts queue
 *
 *  @returns An integer of the total length of boxes
 *
 *****************************************************************************/
int conveyorBelt::totalUsedLength()
{
    unsortedDouble<box> tempQ ( this->theBelt );//copy of the queue
    box temp;//temporary box
    int dist = 0;//length of all boxes
    //goes through the copied queue and adds the box lengths up
    while ( !tempQ.isEmpty() )
    {
        tempQ.pop_back ( temp );
        dist += temp.depth;
    }
    
    return dist;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Overides the "=" operator for assigning one conveyor belt to another
 *
 *  @param[in] right - The conveyor belt to assign the current conveyor to
 *
 *  @returns A reference to the conveyor belt assigned
 *
 *****************************************************************************/
conveyorBelt &conveyorBelt::operator= ( conveyorBelt right )
{
    this->theLength = right.getLength();
    this->letter = right.getLetter();
    this->theWidth = right.getWidth();
    return *this;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Gets the last box in the queue without dequeueing it
 *
 *  @returns A box struct that is the last box in the queue
 *
 *****************************************************************************/
box conveyorBelt::getLast()
{
    unsortedDouble<box> temp1(this->theBelt);//copy of the queue
    box temp;//temporary box
    temp1.pop_back(temp);
    return temp;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Clears a conveyorBelt of its "theBelt" linked list
 *
 *****************************************************************************/
void conveyorBelt::clear()
{
    theBelt.clear();
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Sets the length of the conveyorBelt
 *
 *  @param[in] length - Length to be assigned
 *
 *****************************************************************************/
void conveyorBelt::setLength ( int length )
{
    theLength = length;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Sets the width of the conveyorBelt
 *
 *  @param[in] width - Width to be assigned
 *
 *****************************************************************************/
void conveyorBelt::setWidth ( int width )
{
    theWidth = width;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Sets the letter of the conveyorBelt
 *
 *  @param[in] letter1 - Letter to be assigned
 *
 *****************************************************************************/
void conveyorBelt::setLetter ( char letter1 )
{
    letter = letter1;
}

/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Adds a box to the conveyorBelt's queueueueueue
 *
 *  @param[in] package - The box to be added to the queue
 *
 *  @returns True if the package is added successfully  false otherwise
 *
 *****************************************************************************/
bool conveyorBelt::addBox ( box  package )
{
    return theBelt.push_front ( package );
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Destoyer of the conveyorBelt Class
 *
 *
 *****************************************************************************/
conveyorBelt::~conveyorBelt()
{
}
