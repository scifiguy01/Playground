/*************************************************************************//**
 * @file
 * @brief File containing the function definitions for header file menu.h
 *****************************************************************************/
#include "menu.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* The constructor creates a blank slate of operators.
*
******************************************************************************/
menu::menu( )
{
    
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* The aMenu is now the theMenu
* 
* @param[in,out]      aMenu - the current menu item  
******************************************************************************/
menu::menu ( menu &aMenu )
{
    theMenu = aMenu.theMenu;
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* The theMenu is now the list of menu items
*
* @param[in,out]      menuList - a list of all menu items
******************************************************************************/

menu::menu( vector<string> &menuList )
{
    theMenu = menuList;
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* The function clear() erases all menu items
*
******************************************************************************/

void menu::clear()
{
    theMenu.erase(theMenu.begin(), theMenu.end());
}

/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* Sets up the main menu on the screen
*
* @param[in,out]      aMenu - vector of strings to hold the menu entries. 
******************************************************************************/
void menu::setUpMainMenu ( menu &aMenu )
{
    aMenu.theMenu = {"Change Board Size From 8 X 8", 
        "Change Starting Location From [7, 7]", "Exit and Solve the Tour"};
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* will update a menu location given by position (starts at 1) with
* the new entry phrase. If successfully updated, true will be returned.
* Otherwise false is returned.
*
* @param[in]          pos - determines where the menu item will be added
* @param[out]         item - the string containing the new menu item
*
* @returns true if successfully updated
* @returns false otherwise
******************************************************************************/
bool menu::updateMenuItem ( string item, int pos )
{
    if (pos <= theMenu.size() )
    {
        theMenu.at ( pos ) = item;
        return true;
    }
    
    else
    {
        return false;
    }
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* This function will place a menu entry at the given location if the
* position (starts at 1) provided is valid. If the entry is stored, true
* will be returned. Otherwise false will be returned.
*
* @param[in]          item - the menu item that is being added
* @param[in]          pos - position where the menu item will be added
*
* @returns If the entry is stored, true will be returned
* @returns Otherwise false will be returned.
*****************************************************************************/
bool menu::addMenuItem ( string item, int pos )
{
    cout << theMenu.size();
    //if position is somewhere in the middle or at the beginning of theMenu
    if ( pos <= theMenu.size() )
    {
        //insert item into the menu
        theMenu.insert ( theMenu.begin() + pos, item );
        
        return true;
    }
    
    //if the menu is empty, add item as the first element
    else if ( theMenu.size() == 0 )
    {
        theMenu.push_back ( item );
    }
    
    else
    {
        cout << "Invalid position" << endl;
    }
    
    return false;
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* This function will remove the menu item at the given position (starts at 1).
* If the item is removed, true will be returned. If it fails,
* false will be returned.
*
* @param[in]          pos - position in the menu where we will remove item
*
* @returns true if the item was removed
* @returns false otherwise
******************************************************************************/
bool menu::removeMenuItem ( int pos )
{
    //if the position is within the number of items in the menu
    if ( pos <= theMenu.size() )
    {
        theMenu.erase ( theMenu.begin() + pos );
        return true;
    }
    
    else
        return false;
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* If a value of true is passed in to the function for withMenu, the menu
* will be displayed before prompting for any value from the user. If
* the value is not an entry for the menu, an error message will be displayed,
* and the function will continue prompting for an integer that represents
* a valid menu choice. Remember, counting starts at 1. Upon successful
* data entry, return this value.
*
* @param[in,out]      withMenu - a bool variable. If true, display the menu
*                                before prompting for an input selection.
*
* @returns 0 program ran successful.
*****************************************************************************/
int menu::getMenuSelection ( bool withMenu )
{

    int selection = 0;      //user's menu selection
    bool valid = false;
    
    if ( withMenu == true )
    {
        /*printMenu();*/
    }
    
    //repeat until input is valid
    while ( valid == false )
    {
        //ask user for their menu selection
        cout << "Enter choice: ";
        cin >> selection;
        
        if ( selection <= theMenu.size() )
        {
            valid = true;
        }
        
        else
        {
            cout << "Invalid entry. Try again." << endl;
            valid = false;
        }
    }

    cout << endl;
    
    return selection;
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* prints the main menu on the screen
*
******************************************************************************/
void menu::printMenu ( )
{
    for (long long unsigned int i = 0; i < size(); i++)
    {
        cout << i + 1 << ") " << theMenu.at(i) << endl;
    }

}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* finds the size of the menu
*
* @returns the sizeof the menu.
******************************************************************************/
int menu::size( )
{
    return (int)theMenu.size();
}
