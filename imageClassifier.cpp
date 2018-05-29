#include "utilities.h"

/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* isPNG determines if the file is an actual png image. isPNG checks the magic
* number to determine if it is true.
*
*
*
* @param[in,out]      fin - fin is the image file that is being accessed
*
* @returns true if program found a png.
* @returns false if the program did not find a png.
******************************************************************************/
bool isPNG( ifstream &fin )
{
    int i = 0;
    unsigned char arr[ 8 ] = { 137, 80, 78, 71, 13, 10, 26, 10 };
    unsigned char png[ 8 ];

    fin.seekg( 0, ios::beg ); //seek to the begining
    fin.read( ( char* ) &png, 8);//check #s

    for( i = 0; i < 8; i++)
    {
        if( png[ i ] != arr[ i ] )//if all #s don't match, false
        {
            //cout << "false";
            return false;
        }
        else if( i == 7 )//else it is true
        {
            return true;
        }
    }
    return false;
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* isBMP determines if the file is an actual png image. isBMP checks the magic
* number to determine if it is true.
*
*
*
* @param[in,out]      fin - fin is the image file that is being accessed
*
* @returns true if program found a bmp.
* @returns false if the program did not find a bmp.
******************************************************************************/
bool isBMP( ifstream &fin )
{
    unsigned char bmp[ 2 ];

    fin.seekg( 0, ios::beg ); //read in file from begining
    fin.read( ( char* ) &bmp, 2 );//2 bytes should match 'BM'
    if( bmp[ 0 ] == 'B' && bmp[ 1 ] == 'M' )
    {
        return true;
    }
    return false;
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* isGIF determines if the file is an actual gif image. isGIF checks the magic
* number to determine if it is true.
*
* @param[in,out]      fin - fin is the image file that is being accessed
*
* @returns true if program found a gif.
* @returns false if the program did not find a gif.
******************************************************************************/
bool isGIF( ifstream &fin )
{
    string option = "GIF89a";
    string optionTwo = "GIF87a";
    unsigned char gif[ 6 ];

    fin.seekg( 0, ios::beg );//seek to the begining
    fin.read( ( char* ) &gif, 6);//read in 6 bytes
    if(gif[ 0 ] == 'G' && gif[ 1 ] == 'I' && gif[ 2 ] == 'F'
        && gif[ 3 ] == '8' && gif[ 4 ] == '9' &&
        gif[ 5 ] == 'a' )//two options could match this or...
        {
            return true;
        }
        else if( gif[ 0 ] == 'G' && gif[ 1 ] == 'I' && gif[ 2 ] == 'F'
        && gif[ 3 ] == '8' && gif[ 4 ] == '7' &&
        gif[ 5 ] == 'a' )//this is other option
        {
            return true;
        }
    return false;
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* isJPG determines if the file is an actual jpg image. isJPG checks the magic
* number to determine if it is true.
*
* @param[in,out]      fin - fin is the image file that is being accessed
*
* @returns true if program found a jpg.
* @returns false if the program did not find a jpg.
******************************************************************************/
bool isJPG( ifstream &fin )
{
    unsigned char bmpF[ 2 ];
    unsigned char bmpE[ 2 ];

    fin.seekg( ios::beg, ios::end );
    int count = ( int ) fin.tellg( );//determine count size
    count = count - 3;
    fin.seekg( 0, ios::beg ); //seek to the begining
    fin.read( ( char* ) &bmpF, 2 );
    if( bmpF[ 0 ] == 255 && bmpF[ 1 ] == 216 )//if bytes equal
    {
        fin.seekg( count, ios::beg );//then seek to the end -3
        fin.read( ( char* ) &bmpE, 2 );//read in two bytes

        if( bmpE[ 0 ] == 255 && bmpE[ 1 ] == 217 )
        {
            return true;
        }
        return false;
    }

    return false;
}

