/*************************************************************************//**
* @file 
* @brief The Disgruntled Employee
*
* @mainpage program 1 - The Disgruntled Employee
* 
* @section course_section Course Information 
*
* @author Levi Bergevin
* 
* @date 02.23.2018
* 
* @par Professor: 
*         Professor Schrader
* 
* @par Course: 
*         CSC 215 - section 01 -  1 pm
* 
* @par Location: 
*         Classroom Bldg - Room 205
*
* @section program_section Program Information 
* 
* @details 
* Data:
* The data will come from a directory located somewhere on a hard disk. 
* The directories will be processed from the users via the command prompt.
* The program will process all files within each directory. If an image 
* is found, the program will rename it appropriately. If a file is not 
* an image, the program will not rename it. The only image files that
* will be altered are bmp, gif, png, and jpg.
*
*
* Output:
* While processing each file within the directory, if the
* file is a gif, png or bmp it will be extracted with the width and 
* height of the image and renaming the file using the original filename, the
* width, the height and the extension to form a new filename.
*
* If determined that the file is a jpeg file the program will not need 
* to extract the width and height of the image, but, will need rename 
* the file adding on the extension of jpg.
*
* @section compile_section Compiling and Usage 
*
* @par Compiling Instructions: 
*      none
* 
*  @par Usage: 
* Program execution:
* To start your program, at least one command line argument is needed. 
* The argument must be a directory and contains files to be processed. 
* If the directory does not exist or is unable to be opened, an error 
* output will be processed in the next directory provided.
*
*
*
*
*  @verbatim  
*  c:\> <prog1>.exe 
*  d:\> c:\bin\<prog1>.exe dir1 dir2 dir3... dirn
*  @endverbatim
*
*  @section todo_bugs_modification_section Todo, Bugs, and Modifications
*  @bug working as intended
*  @todo n/a
*
*  @par Modifications and Development Timeline:
*  @verbatim
*  date               Modiciation
*  -------------   ---------------------
*
*  <a href = "https://gitlab.mcs.sdsmt.edu/7428447/csc215s18programs"
*  </a>
*  @endverbatim 
* 
* 
/*****************************************************************************/
#include "utilities.h"
#include "imageDimensions.h"
#include "imageClassifier.h"

using namespace std;

/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* MainWhile processing each file within the directory, if you determine 
* that the file is a gif, png or bmp you will extract the width and 
* height of the image and rename the file using the original filename, 
* the width, the height and the extension to form a new filename.Ex.  
* 
* You determine that the file name frog is a gif image with a width of 50 and a 
* height of 75, you will rename the file to frog_50x75.gifIf you determine 
* that the file is a jpeg file you will not need to extract the width and 
* height of the image but you will need to rename the file adding on the 
* extension of jpg.Ex.   You determine that the file name cat is a jpg image. 
* You will need to rename the file to cat.jpg
*
* @param[in,out]      argv - command line that will be used to load only files
* @param[in]          argc - command line counter used for pointing to option.
*
* @returns 0 program ran successful.
******************************************************************************/
int main( int argc, char *argv[] )
{ 
    int i = 0;  
    image img; 
    string temp;
    ifstream fin;
    intptr_t dHandle;
    _finddata_t aFile; 
    char holdDir[ _MAX_PATH ];
    char pattern[30] = "*.*";
    char originalDir[ _MAX_PATH ]; 

    usage( argc, argv );
    for( i = 1; i < argc; i++ )//loop of total arguments via command line
    {
        _getcwd( originalDir, _MAX_PATH );
        strcpy_s( originalDir, argv[ i ] );
        strcpy_s( holdDir, argv[ i ] );//copy path from command line
        
        if( strcmp ( holdDir, argv[ i ] ) == 0 ) 
        {
            cout << "changed directories" << endl;    
            if ( _chdir( holdDir ) == 0 ) //changing directories w/ error check
            {
                cout << "Starting Directory: " << argv[ i ] << endl;
                dHandle = _findfirst( pattern, &aFile );
                if( dHandle == -1 )
                    return 1;
                searchForMatch( argc, argv, aFile, dHandle, img, fin ); 
            }

         isOriginalDirectory( argc, argv, originalDir, i );
        }
        
    }
    return 0;
}
