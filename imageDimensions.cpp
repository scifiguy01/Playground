#include "imageDimensions.h"


/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* findbmpWidth reads the input file in binary where it extracts
* the width from byte 19, 20, 21, and 22.
* 
*
* @param[in,out]      fin - fin is the image file that is being accessed
* @param[in,out]      img - calls the structure stored in utilities.h for
*                           easy storage of variables.
*
******************************************************************************/
void findbmpWidth( ifstream &fin, image& img )
{
    unsigned char tempBmp[4];
    img.width =0;

    fin.seekg(18, ios::beg); //seek to the 18th byte from the begining
    fin.read( (char*) &tempBmp, 4);// read in four bytes between each
    //byte shift
    img.width = tempBmp[3];
    img.width = img.width << 8;
    img.width = img.width|tempBmp[2];
    img.width = img.width << 8;
    img.width = img.width|tempBmp[1];
    img.width = img.width << 8;
    img.width = img.width|tempBmp[0];

}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* findpngWidth reads the input file in binary where it extracts
* the width from byte 17, 18, 19, and 20.
*
* @param[in,out]      fin - fin is the image file that is being accessed
* @param[in,out]      img - calls the structure stored in utilities.h for
*                           easy storage of variables.
*
******************************************************************************/
void findpngWidth( ifstream &fin, image& img )
{
    unsigned char tempPng[4];
    img.width = 0;

    fin.seekg(16, ios::beg); //seek 16 bytes from the begining
    fin.read( (char*) &tempPng, 4);//read in 4 bytes and shift in between.
    img.width = tempPng[0];
    img.width = img.width << 8;
    img.width = img.width|tempPng[1];

    img.width = img.width << 8;
    img.width = img.width|tempPng[2];
 
    img.width = img.width << 8;
    img.width = img.width|tempPng[3];
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* findgifWidth reads the input file in binary where it extracts
* the width from byte 7 and 8.
*
* @param[in,out]      fin - fin is the image file that is being accessed
* @param[in,out]      img - calls the structure stored in utilities.h for
*                           easy storage of variables.
*
******************************************************************************/
void findgifWidth( ifstream &fin, image& img )
{
    unsigned char tempGif[2];
    img.width =0;

    fin.seekg(6, ios::beg);//seek to byte 6 from the begining
    fin.read( (char*) &tempGif, 2);//read in two bytes and shift inbetween
    img.width = tempGif[1];
    img.width = img.width << 8;
    img.width = img.width|tempGif[0];
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* findbmpHeight reads the input file in binary where it extracts
* the width from byte 23, 24, 25, and 26.
*
* @param[in,out]      fin - fin is the image file that is being accessed
* @param[in,out]      img - calls the structure stored in utilities.h for
*                           easy storage of variables.
*
******************************************************************************/
void findbmpHeight ( ifstream &fin, image& img )
{
    unsigned char tempBmp[4];
    img.height = 0;

    fin.seekg(22, ios::beg);//seek to byte 22 from th begining
    fin.read( (char*) &tempBmp, 4);//        
    img.height = img.height|tempBmp[3];//read in four bytes one by one and then
    //shift after each byte is read
    img.height = img.height << 8;
    img.height = img.height|tempBmp[2];
    img.height = img.height << 8;
    img.height = img.height|tempBmp[1];
    img.height = img.height << 8;
    img.height = img.height|tempBmp[0];

}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* findpngHeight reads the input file in binary where it extracts
* the width from byte 21, 22, 23, and 24.
*
* @param[in,out]      fin - fin is the image file that is being accessed
* @param[in,out]      img - calls the structure stored in utilities.h for
*                           easy storage of variables.
*
******************************************************************************/
void findpngHeight ( ifstream &fin, image& img )
{
    unsigned char tempPng[4];
    img.height = 0;

    fin.seekg(20, ios::beg);//see to byte 20
    fin.read( (char*) &tempPng, 4);
    img.height = tempPng[0];//read in a byte then shift repeat three times for
    //four bytes
    img.height = img.height << 8;
    img.height = img.height|tempPng[1];
    img.height = img.height << 8;
    img.height = img.height|tempPng[2];
    img.height = img.height << 8;
    img.height = img.height|tempPng[3];

}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* findgifHeight reads the input file in binary where it extracts
* the width from byte 9 and 10.
*
* @param[in,out]      fin - fin is the image file that is being accessed
* @param[in,out]      img - calls the structure stored in utilities.h for
*                           easy storage of variables.
*
******************************************************************************/
void findgifHeight ( ifstream &fin, image& img )
{
    unsigned char tempGif[ 2 ];
    img.height = 0;

    fin.seekg( 8, ios::beg ); //seek to the 8th spot
    fin.read( ( char* ) &tempGif, 2 );//read in two bytes
    img.height = tempGif[ 1 ];//store height byte one
    img.height = img.height << 8;//shift
    img.height = img.height|tempGif[ 0 ];//store height byte two
}



