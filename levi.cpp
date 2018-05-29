#include "levi.h"
#include "Belt.h"

/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* Is used to determine if the conveyer belt is full or not with additional
* package
*
* @param[in,out]      package - Is the package being inserted onto the 
*                               conveyer belt.
* @param[in]          max_length - set length for conveyer 
*
* @returns false if conveyer belt is full.
* @returns true if conveyer belt is not full.
******************************************************************************/
int conveyorBelt::is_full( conveyorBelt belt, int max_length)
{ 
    int queue_length = 0;
    box bx;

    for(int i = 0; i < belt.theBelt.size(); i++)
    {
        belt.theBelt.pop_front(bx); 
        queue_length += bx.size;
        belt.theBelt.push_back(bx);
    }
    if (queue_length > max_length)
        return queue_length - max_length;
    return 0;
}

/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* Is used to determine the optimum conveyer belt option.
*
* @returns 0 if there is no path 
* @returns s for belt A.
* @returns m for belt B.
* @returns l for belt C.
******************************************************************************/
char beltPath( box &bx )
{
    bx.size = bx.width;

    if (bx.depth < bx.size)
        bx.size = bx.depth;
    if (bx.height < bx.size)
        bx.size = bx.height;

    if(bx.size > 0 && bx.size <= 10)
        return 's';
    else if (bx.size > 10 && bx.size <= 20)
        return 'm';
    else if (bx.size > 20 && bx.size <= 30)
        return 'l';
    else
        cout << "This box does not fit on any conveyor belt";
    return 0;
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* Is used to decrement a box from the conveyer belt.
*
* @param[in,out]      package - Is the package being inserted onto the 
*                               conveyer belt.
* @param[in,out]      excess - Is the package overhang 
*
******************************************************************************/
bool conveyorBelt::removeBox ( box & package, int excess)
{
    if(package.size/2.0 > excess)
        return false;
    theBelt.pop_front( package );
    return true;
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* Is used to determine if the conveyer belt is full or not with additional
* package
*
* @param[in,out]      bx - Is the the dimensions for the  
*                          conveyer belt.
*
******************************************************************************/
void conveyorBelt::loadBelt( box &bx )
{
    theBelt.push_back(bx);
}
