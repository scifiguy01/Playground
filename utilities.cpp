#include "utilities.h"
#include "imageDimensions.h"
#include "imageClassifier.h"


/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* getExt is a function used to store into image structure the value of the ext.
* the values are stored in a string, and are used to create the new name of 
* the file.
*
* @param[in,out]      img - calls the structure stored in utilities.h for
*                           easy storage of variables.
******************************************************************************/
void getExt ( image& img )
{
    if( img.gif == true )//check flags if one is true set ext for 
        //bmp,gif,jpg,png
    {
        img.ext = ".gif";
    }
    if( img.png == true )
    {
        img.ext = ".png";
    }
    if( img.jpg == true )
    {
        img.ext = ".jpg";
    }
    if( img.bmp == true )
    {
        img.ext = ".bmp";
    }
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* renameS is a function that takes takes the original name and converts it by
* combining the original name with the width and height of the image file. An
* 'x' will seperate the width and the height. The new name is then ended with
* the extension type.
*
* @param[in,out]      argv - command line that will be used to load only files
* @param[in]          argc - command line counter used for pointing to option.
* @param[in,out]      img - calls the structure stored in utilities.h for
*                           easy storage of variables.
******************************************************************************/
void renameS ( int argc, char *argv[], image &img )
{
    const char* t = " \t\n\r\f\v\\";
    string width;
    string height;

    getExt ( img );
    if( img.ext == ".gif" || img.ext == ".bmp" || img.ext == ".jpg" ||
        img.ext == ".png" )//if ext then rename
    {
        img.newname = img.original.erase(0, img.original.find_last_of(t)+1);
        img.newname.erase(img.newname.find_last_of('.'), img.newname.size() );

    }

    if( img.gif == true || img.png == true || img.bmp ==true )//check flags
    {
        width = to_string( img.width );//if true then add height width
        height = to_string( img.height );
        img.newname =  img.newname + "_" + width + "x" + height;
        img.newname = img.newname + img.ext;
    }
    else if( img.jpg == true )//rename
    {
        img.newname = img.newname + img.ext;
    }   
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* printPng combines several function to create a new name. The function 
* calls for the original name and cacatenates with an "_", height "x",
* width, then the img.ext. Finally img.png is set to false so that the 
* struct can help identify the next image type.
*
* @param[in]          argc - command line counter used for pointing to option.
* @param[in,out]      argv - command line that will be used to load only files
* @param[in,out]      fin - fin is the image file that is being accessed
* @param[in,out]      img - calls the structure stored in utilities.h for
*                           easy storage of variables.
* @param[in,out]      aFile - Is the stored and current file being assesed
*                           to find if it is an image to be renamed.
******************************************************************************/
void printPng ( int argc, char *argv[], ifstream &fin, image& img,
    _finddata_t &aFile )
{
    img.original = aFile.name;//save original
    findpngHeight ( fin, img );//call height
    findpngWidth ( fin, img );//call width
    renameS ( argc, argv, img );//rename
    img.png = false;//reset flag

}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* printJpg combines several function to create a new name. Finally 
* img.jpg is set to false so that the struct can help identify the
* next image type.
*
* @param[in]          argc - command line counter used for pointing to option.
* @param[in,out]      argv - command line that will be used to load only files
* @param[in,out]      fin - fin is the image file that is being accessed
* @param[in,out]      img - calls the structure stored in utilities.h for
*                           easy storage of variables.
* @param[in,out]      aFile - Is the stored and current file being assesed
*                           to find if it is an image to be renamed.
******************************************************************************/
void printJpg ( int argc, char *argv[], ifstream &fin, image& img,
    _finddata_t &aFile )
{
    img.original = aFile.name;//save original
    renameS ( argc, argv, img );//rename
    img.jpg = false;//reset flag
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* printBmp combines several function to create a new name. The function 
* calls for the original name and cacatenates with an "_", height "x",
* width, then the img.ext. Finally img.bmp is set to false so that the 
* struct can help identify the next image type.
*
* @param[in]          argc - command line counter used for pointing to option.
* @param[in,out]      argv - command line that will be used to load only files
* @param[in,out]      fin - fin is the image file that is being accessed
* @param[in,out]      img - calls the structure stored in utilities.h for
*                           easy storage of variables.
* @param[in,out]      aFile - Is the stored and current file being assesed
*                           to find if it is an image to be renamed.
******************************************************************************/
void printBmp ( int argc, char *argv[], ifstream &fin, image& img,
    _finddata_t &aFile )
{
    img.original = aFile.name;//copy name
    findbmpHeight ( fin, img );//call height function
    findbmpWidth ( fin, img );//call width function
    renameS ( argc, argv, img );//call rename function
    img.bmp = false;//reset flag

}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* printGif combines several function to create a new name. The function 
* calls for the original name and cacatenates with an "_", height "x",
* width, then the img.ext. Finally img.gif is set to false so that the 
* struct can help identify the next image type.
*
* @param[in]          argc - command line counter used for pointing to option.
* @param[in,out]      argv - command line that will be used to load only files
* @param[in,out]      fin - fin is the image file that is being accessed
* @param[in,out]      img - calls the structure stored in utilities.h for
*                           easy storage of variables.
* @param[in,out]      aFile - Is the stored and current file being assesed
*                           to find if it is an image to be renamed.
******************************************************************************/
void printGif ( int argc, char *argv[], ifstream &fin, image& img,
        _finddata_t &aFile )
{
    img.original = aFile.name;//save name
    findgifHeight ( fin, img );//call height function
    findgifWidth ( fin, img );//call width funtion
    renameS ( argc, argv, img );//call rename function
    img.gif = false;//reset flag

}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* This function merely calls four other functions isGIF, isPNG, isJPG, and
* isBMP. This is a simple function used to save space.
*
* @param[in,out]      fin - fin is the image file that is being accessed
* @param[in,out]      img - calls the structure stored in utilities.h for
*                           easy storage of variables.
******************************************************************************/
void isFile ( ifstream &fin, image& img )
{
    if( isBMP( fin ) == true )//if bmp,png,jpg,gif are true then flags are set
    {
        img.bmp = true;
    }
    else if( isPNG( fin ) == true )
    {
        img.png = true;
    }
    else if( isJPG( fin ) == true )
    {
        img.jpg = true;
    }
    else if( isGIF( fin ) == true )
    {
        img.gif = true;
    }
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* changeName overwrites the file names saved in the directories. By using 
* the structure to access the name.
*
* @param[in,out]      aFile - Is the stored and current file being assesed
*                           to find if it is an image to be renamed.
* @param[in,out]      img - calls the structure stored in utilities.h for
*                           easy storage of variables.
******************************************************************************/
void changeName ( _finddata_t &aFile, image &img )
{
    char * str = new char [ img.newname.size( ) +1 ];
    strcpy( str, img.newname.c_str( ) );//copy and rename
    rename( aFile.name, str);

    delete [] str;
    
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* The function usage is used to output the user what is to be outputed if they
* are unaware. A path is shown. The function will then exit the program.
*
* @param[in]          argc - command line counter used for pointing to option.
* @param[in,out]      argv - command line that will be used to load only files
******************************************************************************/
void usage( int argc, char *argv[] )
{
    if( argc < 1 )//usage statement all are invalid if less than 1
    {
        cout << "invalid number of arguments." << endl;
        cout << "usage: " << endl;
        cout << "prog1.exe options must be the directory path" << endl;
        cout << "directory paths must start with C colon." << endl;
        cout << "there is no limit in the amount of directory paths" << endl;
        exit( 1 );
    }
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* openFile will open the file in binary by accessing aFile.name.
*
* @param[in,out]      fin - fin is the image file that is being accessed
* @param[in,out]      aFile - Is the stored and current file being assesed
*                           to find if it is an image to be renamed.
******************************************************************************/
void openFile( ifstream &fin,  _finddata_t &aFile )
{
    fin.open( aFile.name, ios::in | ios::binary );//open file in binary
    if( !fin )
    {
        cout << "error, file not opened";
        exit( 1 );//error check and exit
    }
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* searchForMatch is a way to condense main. It uses a do while loop to walk
* through directories looking for png, gif, jpg and bmp images. These images,
* are then altered with the help of rename functions.
*
* @param[in]          argc - command line counter used for pointing to option.
* @param[in,out]      argv - command line that will be used to load only files
* @param[in,out]      aFile - Is the stored and current file being assesed
*                           to find if it is an image to be renamed.
* @param[in]          dHandle - is used to move through directories
* @param[in,out]      img - calls the structure stored in utilities.h for
*                           easy storage of variables
* @param[in,out]      fin - fin is the image file that is being accessed
******************************************************************************/
void searchForMatch( int argc, char *argv[], _finddata_t &aFile, 
    intptr_t dHandle, image &img, ifstream &fin ) 
{
    do
    {
        if( !( aFile.attrib & _A_SUBDIR ) )
        {
            openFile( fin, aFile );//open file
            isFile ( fin, img );//check 

            if( img.gif == true )//call gif,bmp,png,jgp print if true
            {
                printGif ( argc, argv, fin, img, aFile );
            }
            else if( img.png == true )
            {
                printPng ( argc, argv, fin, img, aFile );
            }
            else if( img.bmp == true )
            {
                printBmp ( argc, argv, fin, img, aFile );
            }
            else if( img.jpg == true )
            {
                printJpg ( argc, argv, fin, img, aFile );
            } 
            fin.close( );
            changeName( aFile, img );//change name
        }
    }while( _findnext( dHandle, &aFile ) == 0 );
    _findclose( dHandle );//close
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* isOriginalDirectory will determine if the original directory is accessed.
* if it fails it will output a message stating so. A message will also be 
* stated if the directory was successfully reached.
*
* @param[in]          argc - command line counter used for pointing to option.
* @param[in,out]      argv - command line that will be used to load only files
* @param[in]          originalDir - original path of the directories that are
*                           to be renamed
* @param[in]          i - simple iterator used to navigate through directory
******************************************************************************/
void isOriginalDirectory( int argc, char *argv[], char originalDir[_MAX_PATH],
    int i )
{
    if( _chdir( originalDir ) ==0 )//change directory
        return;
    else
        cout << "Unable to change to the directory: " << argv[ i ] << endl;
}





