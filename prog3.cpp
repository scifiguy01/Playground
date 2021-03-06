/*************************************************************************//**
* @file
* @brief The Knights Tour
*
* @mainpage program 3 - The Knights Tour
*
* @section course_section Course Information
*
* @author Levi Bergevin
*
* @date 03/26/2018
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
* A knight's tour is a sequence of moves of a knight on a chessboard such that 
* the knight visits every square once and only once. So given the size of 
* the board and a starting position you are to show how the knight would move 
* to complete its tour. Its starting spot would be labeled with a 1 and 
* the next move would be labeled as 2 and so on. If the n was equal
* to 8, the final step would be 64 (8x8). You must use the mcs gitlab 
* repository csc215s18programs.git and create a project
* named prog3 within it. This should be a multiple source file program with 
* files named prog3.cpp, menu.h and menu.cpp.
*
*
* Output:
* 1) C:\> prog3.exe
* 2) C:\> prog3.exe tourfile
* 3) C:\> prog3.exe -fancy
* 4) C:\> prog3.exe -fancy tourfile
*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions:
*      none
*
*  @par Usage:
* Program execution: 
*
*  @verbatim
*  c:\> <prog1>.exe
*  d:\> c:\bin\<prog2>.exe "somefile"
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
*  <a href ="https://gitlab.mcs.sdsmt.edu/csc215s18prog2/team03/commits/master"
*  </a>
*  @endverbatim
*
/*****************************************************************************/
#include "menu.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ostream>

using namespace std;

/*!
*@brief Stores the information for choice == 2, so that the read in 
*       portion is easier to keep track of its variables.
*/
struct tour
{
/*! 
* @brief determines row start point
*/
    int row;
/*! 
* @brief determines collumn start point
*/
    int col;
/*! 
 * @brief determines board size
 */
    int board;       
};

bool permutation(int **board, int count, int row, int col,
    int board_size, ostream &out, bool &flag, bool fancy);
void openFile(int **board, int count, int argc, char *argv[],
    ifstream &fin, ofstream &fout, tour &tr);
void print_usage();
void printBoard(int **board, int board_size, ostream &out);
bool isFancy( int argc, char *argv[] );
void menuSelect(int **board, int count, int row, int col, int board_size, 
    ostream &out, menu myMenu, string menuUpdate, bool fancy);
void printFancy(int **board, int board_size, ostream &out);
int** alloc2d(int board_size);
void fill2d(int**board, int board_size);
void free2d(int** board, int board_size);
void fileTour (ifstream &fin, ofstream &fout, tour &tr, int **board, 
    int count, bool flag, bool fancy);


/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* Option 1)
* This will present a menu to the user show the board size and default 
* coordinates of where the knight will start. The default board size is 8x8 
* and the default starting position is in row 7 column 7. As the user make 
* changes, you must update your menu. When the user selects option 3, you sole 
* the tour with the selected values and show your solution to the screen. 
* Error checking is a must, you can not change the board size to 5 while 
* starting position is 7,7. You can not change the starting location to 9,7 
* on an 8x8 board.
*
* Option 2)
* If an input file is given at the command prompt, it will contain tours in 
* the following format. You are not guaranteed that a tour will be in the 
* file(empty) but you are guaranteed that if one exists, it is valid. There 
* will be many tours inside this file and you will need to process every tour. 
* The first number in the file will be the size of the board (n). The next
 *two numbers will be the starting row and starting column respectively. 
* This pattern will repeat until end of file is reach. The tours in the file 
* will be valid.
*
* @param[in,out]      argv - command line that will be used to load only files
* @param[in]          argc - command line counter used for pointing to option.
*
* @returns 0 program ran successful.
* @returns -1 if program ran wihtout proper user implementations.
* @returns -2 if program ran without -fancy being called with argc==3
******************************************************************************/
int main(int argc, char *argv[])
{
    //declared variables
    int board_size = 8;
    int row = 7;
    int col = 7;
    int count = 0;
    int counter =1;
    int **board = {0};
    bool flag = false;
    bool fancy = false;
    
    tour tr;  
    ofstream fout;
    menu myMenu;
    string menuUpdate;
    ifstream fin;


    // check command line arguments
    if (argc < 1 || argc > 3)
    {
        print_usage();
        return -1;
    }
    //determine if argc==1 and call menu 
    if(argc == 1)
    {
        menuSelect( board, count, row, col, board_size, 
            cout, myMenu, menuUpdate, fancy);
    }
    //determine if argc==2 and call if not fancy call openfile
    if( argc == 2 )
    {
        if(!(isFancy( argc, argv )))
        {
           openFile( board, count, argc, argv, fin, fout, tr);
           fileTour(fin, fout, tr, board, count, flag, fancy);
        }
        else
        {
            //call print fancy since isFancy is true
            fancy = true;
            menuSelect( board, count, row, col, board_size, 
                cout, myMenu, menuUpdate, fancy);
        }
    }
    //determine if fancy matches and open file and fun fancy
    if( argc == 3 )
    {
        if(!(isFancy( argc, argv )))
        {
            return -2;
        }
        fancy = true;
        openFile( board, count, argc, argv, fin, fout, tr);
        fileTour(fin, fout, tr, board, count, flag, fancy);
            
    }
    //close both files
    fin.close();
    fout.close();

    return 0;
}

/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* The knight has 8 possible moves it can do. It can move 2 squares in the
* horizontal direction and 1 move in the vertical direction or it can move 
* 2 squares in the vertical direction and 1 move in the horizontal direction. 
* This function uses all eight moves while being dynamically allocating the 
* array for board size. This permutation will find a true solution.
*
* @param[in,out]      board - The array board that is used for permuting
* @param[in]          count - An index to find board size^2
* @param[in]          row - stores the current row
* @param[in]          col - stores the current collumn
* @param[in]          board_size - The board size stored
* @param[in,out]      out - output for file
* @param[in,out]      flag - A flag that is used to identify the first real 
*                            solution
* @param[in]          fancy - a flag to determine if fancy
*
* @returns true if permutation ran successful.
* @returns false if permutation failed
******************************************************************************/
bool permutation(int ** board, int count, int row, int col, int board_size,
    ostream &out , bool &flag, bool fancy)
{
    //base case if count equals total array positions return solution
    if( count == board_size*board_size && !flag)
    {
        if(fancy)
            printFancy(board, board_size, out);
        else
            printBoard( board, board_size, out);
        flag = true;
        
    }
    //increment count for board movement picture
    count++;
    //check boundaries and that flag is false
    if( !flag && row >= 0 && col >= 0 && row < board_size
        && col < board_size && board[row][col] == 0) 
    {
        
        board[row][col] = count;
        //permute the eight movements of the knight
        permutation( board, count, row-2, col+1, board_size, out, flag, fancy ); 
        permutation( board, count, row-1, col+2, board_size, out, flag, fancy );
        permutation( board, count, row+1, col+2, board_size, out, flag, fancy );
        permutation( board, count, row+2, col+1, board_size, out, flag, fancy );
        permutation( board, count, row+2, col-1, board_size, out, flag, fancy );
        permutation( board, count, row+1, col-2, board_size, out, flag, fancy );
        permutation( board, count, row-1, col-2, board_size, out, flag, fancy );
        permutation( board, count, row-2, col-1, board_size, out, flag, fancy );

        board[row][col] = 0;
    }
    //check flag for the solution
    if (flag == true)
        return true;

    return false;
}

/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* Output for usage statement of how the program should be laid out.
*
******************************************************************************/
void print_usage()
{
    //output to show how to run program if put in incorrectly
    cout << "To run the program choose a way to format for compilling from" 
         << "the options shown below" << endl;
    cout << "1)  prog3.exe" << endl; 
    cout << "2)  prog3.exe tourfile" << endl;
    cout << "3)  prog3.exe -fancy" << endl;
    cout << "4)  prog3.exe -fancy tourfile" << endl;

}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* This function prints to the screen the permutation results.
*
* @param[in,out]      board - The array board that is used for permuting
* @param[in]          board_size - The board size stored
*
******************************************************************************/
void print_board(int **board, int board_size)
{
    int r, c;
    //loop for outputting array
    for (r = 0; r < board_size; r++)
    {
        for (c = 0; c < board_size; c++)
        {
            if (board[r][c] == 0)
                cout << "[ ]";
            else
            {
                if(board[r][c] < 10)
                    cout << " ";
                cout << board[r][c] << " ";
            }
        }
        cout << endl;
    }
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* This function prints to a file the permutation results of the tours provided.
*
* @param[in,out]      board - The array board that is used for permuting
* @param[in]          board_size - The board size stored
* @param[in,out]      out - output for file
*
******************************************************************************/
void printBoard(int **board, int board_size, ostream &out)
{
    int r, c;
    //loop for outputting array
    for (r = 0; r < board_size; r++)
    {
        for (c = 0; c < board_size; c++)
        {
            if (board[r][c] == 0)
                out << "[ ]";
            else
            {
                if(board[r][c] < 10)
                    out << " ";
                out << board[r][c] << " ";
            }
        }
        out << endl;
    }
}

/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* Is used to determine if the -fancy option was called.
*
* @param[in,out]      argv - command line that will be used to load only files
* @param[in]          argc - command line counter used for pointing to option.
*
* @returns true if fancy is found.
* @returns false if fancy is not found.
******************************************************************************/
bool isFancy( int argc, char *argv[] )
{ 
    //comparing strings to check if fancy is true
    if(strcmp(argv[1], "-fancy")==0)
    {
        return true;
    }
    else 
        return false;
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* The knight has 8 possible moves it can do. It can move 2 squares in the
* horizontal direction and 1 move in the vertical direction or it can move 
* 2 squares in the vertical direction and 1 move in the horizontal direction. 
* This function uses all eight moves while being dynamically allocating the 
* array for board size. This permutation will find a true solution.
*
* @param[in,out]      board - The array board that is used for permuting
* @param[in]          count - An index to find board size^2
* @param[in,out]      argv - command line that will be used to load only files
* @param[in]          argc - command line counter used for pointing to option.
* @param[in,out]      fin - input for file
* @param[in,out]      fout - output for file
* @param[in,out]      tr - calls a structure with 3 variables stored for easy
*                            access for reading in numbers.
*
* @returns true if permutation ran successful.
* @returns false if permutation failed
******************************************************************************/
void openFile(int **board, int count, int argc, char *argv[],
    ifstream &fin, ofstream &fout, tour &tr)
{
    //open file depending on if isFancy for position of filename
    if(!(isFancy(argc, argv )))
    {
        fin.open(argv[1]);
    }
    else
        fin.open(argv[2]);

    //error check file to see if it is opened
    if(!fin)
    {
            fin.close();
            exit(1);
    }
    //open output file
    fout.open("solutions.tours", std::fstream::app);
    //error check file to see if it is opened
    if(!fout)
    {
        fout.close();
        exit(1);
    }

}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* If argc == 1 menuSelect will be called to bring up a menu for the user
* to select one of three options. The first being a board size, the second
* is the rows and collumns size, and finally option 3 is to exit and run
* the permutation. The board, row and collumn all have a default size that
* they will start at.
*
* @param[in,out]      board - The array board that is used for permuting
* @param[in]          count - An index to find board size^2
* @param[in]          row - stores the current row
* @param[in]          col - stores the current collumn
* @param[in]          board_size - The board size stored
* @param[in,out]      out - output for file
* @param[in,out]      myMenu - calls the menu 
* @param[in,out]      menuUpdate - calls an update menu
* @param[in]          fancy - a flag to determine if fancy
*
******************************************************************************/
void menuSelect(int **board, int count, int row, int col,
    int board_size, ostream &out, menu myMenu, string menuUpdate, bool fancy)
{
    //declare variables
    bool withMenu = true;
    int choice = 0;
    bool flag = false;

    //setup menu
    myMenu.setUpMainMenu(myMenu);
    do
    {
        myMenu.printMenu();
        choice = myMenu.getMenuSelection(withMenu);
    
        //choice for board size
        if( choice == 1 )
        {
            cout << "Enter the size of the NxN Board ( > 3, < 9 ): ";
            cin >> board_size;
            while(board_size < 4 || board_size > 8)
            {
                cout << "Please choose a size between 4 and 8, inclusive: ";
                cin >> board_size;
            }
        
            menuUpdate = "Change Board Size From ";
            menuUpdate += to_string(board_size);
            menuUpdate += " X ";
            menuUpdate += to_string(board_size);

            myMenu.updateMenuItem(menuUpdate, 0);

            //update menu starting location
            menuUpdate = "Change Starting Location From [";
            menuUpdate += to_string(board_size - 1);
            menuUpdate += ",  ";
            menuUpdate += to_string(board_size - 1);
            menuUpdate +="]";

            myMenu.updateMenuItem(menuUpdate, 1);
        }
        //choice for row and column size
        else if( choice == 2 )
        {
            cout << "Enter starting location: ";
            cin >> row >> col;
            while( row >= board_size || row < 0 || col >= board_size || col < 0)
            {
                cout << "Please choose values between 0 and " << board_size - 1 
                    << ":";
                cin >> row >> col;
            }
            //update menu
            menuUpdate = "Change Starting Location From [";
            menuUpdate += to_string(row);
            menuUpdate += ",  ";
            menuUpdate += to_string(col);
            menuUpdate +="]";

            myMenu.updateMenuItem(menuUpdate, 1);

        }
        //start permutation
        else if ( choice == 3 )
        {
            board = alloc2d(board_size);
            fill2d(board, board_size);
            permutation(board, count, row, col, board_size, out, flag, fancy);
            free2d(board, board_size);
        }
    }while( choice != 3);
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* PrintFancy will convert board into a checkerboard with black and white, and
* this checkerboard will in the middle contain the value of when the 
* permutation reached its position for the solution.
*
* @param[in,out]      board - The array board that is used for permuting
* @param[in]          board_size - The board size stored
* @param[in,out]      out - output for file or print to screen
*
******************************************************************************/
void printFancy(int **board, int board_size, ostream &out)
{
    int r, c;
    bool fancy = true;
    out << endl;
    //ouptut 176 for white coloring and 178 for dark shading
    for (r = 0; r < board_size; r++)
    {
        for(c = 0; c < board_size; c++)
        {
            fancy = !fancy;
            if(fancy)
                out << char(176)<< char(176)<< char(176)<< char(176)
                << char(176)<< char(176)<< char(176);
            else
                out << char(178)<< char(178)<< char(178)<< char(178)
                << char(178)<< char(178)<< char(178);
        }
        out << endl;
        //ensuring checker boxes based on even odd
        if((board_size*3)%2 == 1)
            fancy = !fancy;

        //outputting color
        for(c = 0; c < board_size; c++)
        {
            fancy = !fancy;
            if(board[r][c] < 10)
            {
                if(fancy)
                    out << char(176)<< char(176)<< char(176)<< board[r][c]
                    << char(176)<< char(176)<< char(176);
                else
                    out << char(178)<< char(178)<< char(178)<< board[r][c]
                    << char(178)<< char(178)<< char(178);
            }
            else
            {
                if(fancy)
                    out << char(176)<< char(176)<< board[r][c]
                    << char(176)<< char(176)<< char(176);
                else
                    out << char(178)<< char(178)<< board[r][c]
                    << char(178)<< char(178)<< char(178);
            }
        }
        out << endl;
        //checking checkerboxes
        if((board_size*3)%2 == 1)
            fancy = !fancy;

        for(c = 0; c < board_size; c++)
        {
            fancy = !fancy;
            if(fancy)
                out << char(176)<< char(176)<< char(176)<< char(176)
                << char(176)<< char(176)<< char(176);
            else
                out << char(178)<< char(178)<< char(178)<< char(178)
                << char(178)<< char(178)<< char(178);
        }
        out << endl;
        //if checkerbox is even
        if((board_size*7)%2 == 0)
            fancy = !fancy;
    }
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* allocates memory for board array.
*
* @param[in]          board_size - The board size stored
*
* @returns ptr2d if program ran successful.
******************************************************************************/
int** alloc2d(int board_size)
{
    int i, j;
    int** ptr2d =  nullptr;
    ptr2d = new (nothrow) int*[board_size];
    if( ptr2d == nullptr)
    {   
        cout<< "Memory Allocation Error" << endl;
        exit(1);
    }
    for( i = 0; i < board_size; i++)
    {    
        ptr2d[i] = new int[board_size];
        if( ptr2d[i] == nullptr)
        {    
            for ( j = 0; j < i; j++)
                delete[] ptr2d[j];
            delete[]  ptr2d;
            cout<< "Memory Allocation Error" << endl;
            exit(1);
        }
    }
    return ptr2d;
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* Frees up the board array.
*
* @param[in,out]      board - The array board that is used for permuting
* @param[in]          board_size - The board size stored
*
******************************************************************************/
void free2d(int** board, int board_size)
{
    for ( int j = 0; j < board_size; j++)
        delete[] board[j];
    delete[]  board;
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* fills the 2d board with 0s.
*
* @param[in,out]      board - The array board that is used for permuting
* @param[in]          board_size - The board size stored
*
******************************************************************************/
void fill2d(int**board, int board_size)
{
    for ( int r = 0; r < board_size; r++)
    {
        for ( int c = 0; c < board_size; c++)
        {
            board[r][c] = 0;
        }
    }
}
/**************************************************************************//**
* @author Levi Bergevin
*
* @par Description:
* The knight has 8 possible moves it can do. It can move 2 squares in the
* horizontal direction and 1 move in the vertical direction or it can move 
* 2 squares in the vertical direction and 1 move in the horizontal direction. 
* This function uses all eight moves while being dynamically allocating the 
* array for board size. This permutation will find a true solution.
*
* @param[in,out]      fin - input for file
* @param[in,out]      fout - output for file
* @param[in,out]      tr - calls a structure with 3 variables stored for easy
*                            access for reading in numbers.
* @param[in,out]      board - The array board that is used for permuting
* @param[in]          count - An index to find board size^2
* @param[in]          flag - sets a true false to find a solution
* @param[in]          fancy - a flag to determine if fancy
*
******************************************************************************/
void fileTour (ifstream &fin, ofstream &fout, tour &tr, int **board, 
    int count, bool flag, bool fancy)
{
    int counter = 1;
    //loop to get input from knights tour and permute
    while(fin >> tr.board >> tr.row >> tr.col)
    {
        flag = false;
        fout << "Tour # " << counter << endl << "     " << tr.board << "x"
            << tr.board << " starting at (" << tr.row << "," << tr.col 
            << ")" << endl << endl;
        counter++;
        board = alloc2d(tr.board);
        fill2d(board, tr.board);
        //if no solutions state that
        if(!permutation( board, count, tr.row, tr.col, tr.board, fout, flag, fancy))
        {
            fout << "No solutions for this case";
        }
        free2d(board, tr.board);
            
        fout << endl;
    }
}