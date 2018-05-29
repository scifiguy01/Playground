#ifndef __BELT__H__
#define __BELT__H__
#include "unsortedDouble.h" 
struct box 
{ 
    int boxNumber; 
    int width; 
    int depth; 
    int height; 
    int size;
}; 
class conveyorBelt  
{ 
    public: 
        conveyorBelt(); 
        ~conveyorBelt(); 
        bool addBox ( box  package );
        bool removeBox ( box & package, int excess);
        void loadBelt( box &bx );
        int is_full( conveyorBelt belt, int max_length );
        // you add more functions here. 
        int getWidth();
        char getLetter();
        int getLength();
        int totalUsedLength();
        conveyorBelt &operator=(conveyorBelt right);

        box getLast();
        void clear();
        void setLength(int length);
        void setWidth(int width);
        void setLetter(char letter);
    private: 
        unsortedDouble<box> theBelt; 
        int theLength; 
        int theWidth; 
        char letter; 
}; 
#endif