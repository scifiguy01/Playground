/*************************************************************************//**
* @file
* @brief Header file containing the includes for this program, the image
* structure definition, and all function prototypes not including height
* and width functions and the isbmp, isgif, isjpg, ispng
*****************************************************************************/

#ifndef _UTILITIES_H_
#define _UTILITIES_H_
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <direct.h>
#include <io.h>

using namespace std;



/*!
 * @brief Allows for easy manipulation of an image
 */
struct image
{
        /*!
    * @brief flag used to find file type
    */
    bool jpg/* = false*/;
    /*!
    * @brief flag used to find file type
    */
    bool bmp/*= false*/;
    /*!
    * @brief flag used to find file type
    */
    bool png/* = false*/;
    /*!
    * @brief flag used to find file type
    */
    bool gif/* = false*/;
    /*!
    * @brief stores an extension if file is true
    */
    string ext;
    /*!
    * @brief stores size of columns
    */
    int height;
    /*!
    * @brief stores size of rows
    */
    int width;    
    /*!
    * @brief stores argv name that was passed in for new file name
    */
    string newname;   
    /*!
    * @brief stores argv name that was passed in for new file name
    */
    string original;
};
/******************************************************************************
*                          Function Prototypes
******************************************************************************/

    void getExt ( image& img );
    void usage( int argc, char *argv[] );
    void isFile ( ifstream &fin, image& img );
    void renameS ( int argc, char *argv[], image &img );
    void changeName ( _finddata_t &aFile, image &img );
    void openFile( ifstream &fin,  _finddata_t &aFile );
    void printGif ( int argc, char *argv[], ifstream &fin, image& img,
        _finddata_t &aFile );
    void printBmp ( int argc, char *argv[], ifstream &fin, image& img,
        _finddata_t &aFile );
    void printJpg ( int argc, char *argv[], ifstream &fin, image& img, 
        _finddata_t &aFile );
    void printPng ( int argc, char *argv[], ifstream &fin, image& img, 
        _finddata_t &aFile );
    void searchForMatch( int argc, char *argv[], _finddata_t &aFile, 
    intptr_t dHandle, image &img, ifstream &fin );
    void isOriginalDirectory( int argc, char *argv[], 
        char originalDir[_MAX_PATH], int i );

#endif

