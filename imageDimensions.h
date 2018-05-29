/*************************************************************************//**
 * @file
 * @brief Header file containing the height and width for all but jpg files.
 * 
 *****************************************************************************/

#include "utilities.h"

/******************************************************************************
*                          Function Prototypes
******************************************************************************/
void findpngHeight ( ifstream &fin, image& img );
void findbmpHeight ( ifstream &fin, image& img );
void findgifHeight ( ifstream &fin, image& img );
void findpngWidth ( ifstream &fin, image& img );
void findbmpWidth ( ifstream &fin, image& img );
void findgifWidth ( ifstream &fin, image& img );
