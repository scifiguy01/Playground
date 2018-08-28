//https://www.hackerrank.com/challenges/box-it/problem
//Implement the class Box  
//l,b,h are integers representing the dimensions of the box

// The class should have the following functions : 

// Constructors: 
class Box{
    int l;
    int b;
    int h;
    
    public: 
    
    Box(){
        l = 0;
        b = 0;
        h = 0;
    }
    Box(int length,int breadth,int height){
        l = length;
        h = height;
        b = breadth;
    }   
    Box(const Box &B){
        l = B.l;
        h = B.h;
        b = B.b;
    }

    int getLength(){

        return l; 
    }
    int getBreadth () // Return box's breadth
    {
        return b;
    }
    int getHeight ()  //Return box's height
    {
        return h;
    }
    long long CalculateVolume() // Return the volume of the box
    {
        return (long long)l*b*h;
    }
//Overload operator < as specified
friend bool operator<(Box& A, Box& B)
{
    if((A.l<B.l) ||(A.b < B.b) && (A.l == B.l) || (A.h < B.h) && (A.b == B.b) && (A.l == B.l))
        return true;
    else 
        return false;
}
friend ostream& operator<<(ostream& out, Box& B)
{
    cout << B.l << " " << B.b << " " << B.h;
    return out;
}
};