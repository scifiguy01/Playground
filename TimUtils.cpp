/**************************************************************************//**
 * @file
 * @brief Utility functions
 *
 *****************************************************************************/
#include "TimUtils.h"
#include "Belt.h"
#include <fstream>
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Output the boxes number and which conveyor it was on
 *
 *  @param[in] out - The stream to be outputted
 *  @param[in] pack - The box to be outputed
 *  @param[in] conv - The conveyor the box came from
 *
 *
 *****************************************************************************/
void outputBox ( ostream &out, box pack, conveyorBelt conv )
{
    out << "Box " << pack.boxNumber << " fell off conveyor " <<
        conv.getLetter() << endl;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Output the simulation number
 *
 *  @param[in] out - The stream to be outputted
 *  @param[in] simNum - The simulation number to be outputed
 *
 *
 *****************************************************************************/
void outputSimNum ( ostream &out, int simNum )
{
    out << "Simulation " << simNum << ": " << endl;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Checks whether a box will fall of the conveyor belt
 *
 *  @param[in] belt - The belt to be checked
 *
 *  @returns True if a box will fall false otherwise
 *
 *****************************************************************************/
bool willFall ( conveyorBelt belt )
{
    //checks if the used length is greater than the length of the conveyor
    if ( belt.totalUsedLength() > belt.getLength() )
    {
        return ( ( belt.getLast().depth / 2 ) <= belt.totalUsedLength() -
                 belt.getLength() );
    }
    
    return false;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Overrides the "<" operator for use with the STL sort
 *
 *  @param[in] left - The input on the left hand side
 *  @param[in] right - The input on the right hand side
 *
 *  @returns True if the left hand side is less than the right hand side false otherwise
 *
 *****************************************************************************/
bool operator< ( conveyorBelt left, conveyorBelt right )
{
    return ( left.getWidth() < right.getWidth() );
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Checks if the box will fit on a conveyor then returns the character assign to the conveyor
 *
 *  @param[in] package - The input on the left hand side
 *  @param[in] small - The smallest width conveyorBelt
 *  @param[in] middle - The middle sized width conveyorBelt
 *  @param[in] larg - The largest width conveyorBelt
 *
 *  @returns The character assigned to the conveyor belt the box fits best on
 *
 *****************************************************************************/
char getFitConveyor ( box package, conveyorBelt small, conveyorBelt middle,
                      conveyorBelt larg )
{
    //checks if the width will fit on the large conveyor
    if ( package.width > middle.getWidth() )
    {
        return 'l';
    }
    
    //checks if the widht will fit on the small conveyor
    else if ( package.width < middle.getWidth() &&
              package.width <= small.getWidth() )
    {
        return 's';
    }
    
    else
    {
        return 'm';
    }
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Resets the boxes dimensions to optimise length
 *
 *  @param[in] pack - Box to be optimised
 *  @param[in] conv - The vonceyorBelt the belt goes on

 *
 *  @returns The character assigned to the conveyor belt the box fits best on
 *
 *****************************************************************************/
box getPropDims ( box pack, conveyorBelt conv )
{
    int width = conv.getWidth();
    int temp;
    int temp2;
    
    if ( pack.height <= width )
    {
        temp = pack.width;
        temp2 = pack.depth;
        pack.width = pack.height;
        pack.depth = temp;
        pack.height = temp2;
        return pack;
    }
    
    if ( pack.depth <= width )
    {
        temp = pack.width;
        pack.width = pack.depth;
        pack.depth = temp;
        return pack;
    }
    
    return pack;
}




