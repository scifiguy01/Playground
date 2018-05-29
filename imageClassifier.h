/**************************************************************************//**
* @file
* @brief Header file containing the functions for determining image type.
* 
******************************************************************************/

#include "utilities.h"
/*******************************************************************************
 *                         Function Prototypes
 ******************************************************************************/
bool isPNG( ifstream &fin );
bool isBMP( ifstream &fin );
bool isGIF( ifstream &fin );
bool isJPG( ifstream &fin );