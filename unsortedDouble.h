/**************************************************************************//**
 * @file
 * @brief UnsortedDouble Template Class
 *
 *****************************************************************************/

#include <iostream>
#include <string>
#include <functional>
using std::nothrow;
using std::ostream;
using std::string;
using std::function;


#ifndef UNSORTEDDOUBLE__H
#define UNSORTEDDOUBLE__H
/*!
 * @brief allows for the creation of a unsorted list object
 */
template <class DT>
class unsortedDouble
{
    public:
        unsortedDouble();

        unsortedDouble ( const unsortedDouble<DT> &l ); 
        ~unsortedDouble();

        void clear();
        void print ( ostream &out, bool forward = true,
                     string seperator = ", " );
        bool insert ( DT val, int pos = 1 );
        bool remove ( int pos = 1 );

        bool removeVal ( DT val );
        bool rfind ( DT val );
        bool find ( DT val );
        
        bool isEmpty( );
        int size();
        bool push_back ( DT val );
        bool push_front ( DT val );
        bool pop_back ( DT &val );
        bool pop_front ( DT &val );
        
        void swap ( unsortedDouble<DT> &l );
        int countIf ( function<bool ( DT ) > cond );
        int retrieve ( DT val );
        int rretrieve ( DT val );
        bool retrieve ( DT &item, int position );
        
    private:
        /*!
        * @brief Holds information for each node in the list
        * files
        */
        struct node/*!< Structure containing for each node in list*/
        {
            DT item;/*!< The item to be kept*/
            node *next;/*!< The next node in the list*/
            node *last;/*!< The previous node in the list*/
        };
        node *headptr;/*!< The headpointer of the linked list*/
        node *tailptr;/*!< The tailpointer of the linked list*/
};
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Allows for a list to be destroyed
 *
 *****************************************************************************/
template <class DT>
unsortedDouble<DT>::~unsortedDouble()
{
    clear();
    delete headptr;
    delete tailptr;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  prints out the list to an ostream
 *
 *  @param[in] out - The ostream to be outputted to
 *  @param[in] forward - Variable used to determine if the output should be reversed
 *  @param[in] seperator - The character that separates the items in the list
 *
 *
 *****************************************************************************/
template <class DT>
void unsortedDouble<DT>::print ( ostream &out, bool forward, string seperator )
{
    node *temp;//Temporary node
    node *prev;//Temporary node
    //checks if the node will print backword
    if ( forward )
    {
        temp = headptr;
        prev = headptr;
    }
    
    else
    {
        temp = tailptr;
        prev = tailptr;
    }
    //walk through list and print the seperator
    while ( forward && temp != nullptr )
    {
        out << temp->item;
        
        if ( temp->next != nullptr )
        {
            out << seperator;
        }
        
        temp = temp->next;
    }
    
    while ( !forward && temp != nullptr )
    {
        out << temp->item;
        
        if ( temp->last != nullptr )
        {
            out << seperator;
        }
        
        temp = temp->last;
    }
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Constructs a copy of the inputed list
 *
 *  @param[in] l - List to be copied
 *
 *****************************************************************************/
template <class DT>
unsortedDouble<DT>::unsortedDouble(const unsortedDouble<DT> &l)
{
    node *lnode; // node for the inputed list
    node *thisNode;//node for the current list
    //checks if the inputed list is empty
    if(l.headptr==nullptr)
    {
       headptr=nullptr;
       tailptr=nullptr;
       return;
    }
    headptr=new(nothrow)node
    {
        l.headptr->item,nullptr,nullptr
    };
    lnode=l.headptr->next;
    thisNode=headptr;
    //walks through the inputed list and copies data over
    while(lnode!=nullptr)
    {
        thisNode->next=new(nothrow)node
        {
            lnode->item,nullptr,thisNode
        
        
        };
            lnode=lnode->next;
            thisNode=thisNode->next;    
    }
    tailptr=thisNode;

}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Allows for a list to be created
 *
 *****************************************************************************/
template <class DT>
unsortedDouble<DT>::unsortedDouble()
{
    headptr = nullptr;
    tailptr = nullptr;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 * Clears the list of all items
 *
 *****************************************************************************/
template <class DT>
void unsortedDouble<DT>::clear()
{
    node *temp;//Temporary node
    node *remnod;//Temporary node for removal
    temp = headptr;
    //walks throught the list and removes nodes
    while ( temp != nullptr )
    {
        remnod = temp;
        temp = temp->next;
        delete remnod;
    }
    
    headptr = nullptr;
    tailptr = nullptr;
}

/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Inserts an item at a position
 *
 *  @param[in] val - Value to be inserted
 *  @param[in] pos - Position val will be inserted to
 *
 *  @returns true if item was added false otherwise
 *
 *****************************************************************************/
template <class DT>
bool unsortedDouble<DT>::insert ( DT val, int pos )
{
    int i = 1; //incrementor
    node *temp;//Temporary node
    node *prev;//Temporary node
    node *item = new ( nothrow ) node
    {
        val,
        nullptr,
        nullptr
    };
    //checks if the node should be inputed
    if ( pos < 1 || pos > size() + 1 )
    {
        delete item;
        return false;
    }
    //checks if the list is empty
    if ( isEmpty() )
    {
        headptr = item;
        tailptr = item;
        return true;
    }
    
    temp = headptr;
    prev = headptr;
    //walk through list and input in the position
    while ( temp != nullptr )
    {
        if ( pos == i && i == 1 )
        {
            headptr = item;
            item->next = temp;
            temp->last = item;
            return true;
        }
        
        if ( pos == i )
        {
            prev->next = item;
            temp->last = item;
            item->last = prev;
            item->next = temp;
            return true;
        }
        
        i++;
        prev = temp;
        temp = temp->next;
    }
    
    tailptr->next = item;
    item->last = tailptr;
    tailptr = item;
    return true;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Removes value from the list
 *
 *  @param[in] val - Value to be removed
 *
 *  @returns True if the value is removed false otherwise
 *
 *****************************************************************************/
template <class DT>
bool unsortedDouble<DT>::removeVal ( DT val )
{
    node *prev;//Temporary node
    node *temp;//Temporary node
    //checsk if the list is empty
    if( isEmpty() )
    {
        return false;
    }
    temp = headptr;
    prev = headptr;
    //walks through the list and checks if the value should be removed
    while ( temp != nullptr )
    {
        if(temp == tailptr && tailptr == headptr)
        {
            headptr = nullptr;
            tailptr = nullptr;
            delete temp;
            return true;

        }
        if ( temp->item == val && headptr == temp)
        {
            headptr = temp->next;
            temp->next->last=nullptr;
            delete temp;
            return true;
        }

         if( temp->item == val && temp == tailptr)
        {
            tailptr = temp->last;
            temp->last->next=nullptr;
            delete temp;
            return true;
        }
        
        if ( temp->item == val )
        {
            prev->next = temp->next;
            temp->next->last = prev;
            delete temp;
            return true;
        }
        

        prev = temp;
        temp = temp->next;
    }
    

    return false;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Removes an item from a position
 *
 *  @param[in] pos - Position to be removed from
 *
 *  @returns True if the item was removed false otherwise
 *****************************************************************************/
template <class DT>
bool unsortedDouble<DT>::remove ( int pos )
{
    node *prev;//Temporary Node
    node *temp;//Temporary Node
    int i = 1;
    //Checks if the list is empty
    if( isEmpty() )
    {
        return false;
    }
    temp = headptr;
    prev = headptr;
    //walks through the list and checks if the node should be removed
    while ( temp != nullptr )
    {
        if(i == pos && tailptr == headptr)
        {
            headptr = nullptr;
            tailptr = nullptr;
            delete temp;
            return true;

        }
        if ( i == pos && headptr == temp)
        {
            headptr = temp->next;
            temp->next->last=nullptr;
            delete temp;
            return true;
        }

         if( i == pos && temp == tailptr)
        {
            tailptr = temp->last;
            temp->last->next=nullptr;
            delete temp;
            return true;
        }
        
        if ( i == pos )
        {
            prev->next = temp->next;
            temp->next->last = prev;
            delete temp;
            return true;
        }
        
        i++;
        prev = temp;
        temp = temp->next;
    }
    

    return false;

}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Finds the value give
 *
 *  @param[in] val - Value to search for
 *
 *  @returns True if the value was found false otherwise
 *
 *****************************************************************************/
template <class DT>
bool unsortedDouble<DT>::find ( DT val )
{
    node *temp;//Temporary Node
    temp = headptr;
    //walks through the list checking if the value was found
     while ( temp != nullptr )
    {
        if( temp->item == val)
        {
        return true;
        }
        temp = temp->next;
    }

    return false;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Finds the value give starting from the end
 *
 *  @param[in] val - Value to search for
 *
 *  @returns True if the value was found false otherwise
 *
 *****************************************************************************/
template <class DT>
bool unsortedDouble<DT>::rfind ( DT val )
{
    node *temp;//Temporary Node
    temp = tailptr;
    //Walks through the list and checks for the val
     while ( temp != nullptr )
    {
        if( temp->item == val)
        {
        return true;
        }
        temp = temp->last;
    }

    return false;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Determines if the list is empty
 *
 *  @returns True if the list is empty false otherwise
 *
 *****************************************************************************/
template <class DT>
bool unsortedDouble<DT>::isEmpty()
{
     return (tailptr == nullptr&&headptr==nullptr);
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Determines the size of the list
 *
 *  @returns The size of the list
 *
 *****************************************************************************/
template <class DT>
int unsortedDouble<DT>::size()
{
    node *temp;//Temporary Node
    int count=0;//Incrementor
    temp = headptr;
    //walks through the list adding up to the size
    while ( temp != nullptr )
    {
        temp = temp->next;
        count++;
    }
    return count;

}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Adds a value to the back of the list
 *
 *  @param[in] val - Value to be added
 *
 *  @returns True if the value was added false otherwise
 *
 *****************************************************************************/
template <class DT>
bool unsortedDouble<DT>::push_back(DT val)
{
    return insert(val,size()+1);
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Adds a value to the front of the list
 *
 *  @param[in] val - Value to be added
 *
 *  @returns True if the value was added false otherwise
 *
 *****************************************************************************/
template <class DT>
bool unsortedDouble<DT>::push_front(DT val)
{
    return insert(val);
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Removes a value from the back of the list
 *
 *  @param[in] val - Value to be removed
 *
 *  @returns True if the value was removed false otherwise
 *
 *****************************************************************************/
template <class DT>
bool unsortedDouble<DT>::pop_back(DT &val)
{
    return retrieve(val,size())&&remove(size());   
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Removes a value to the front of the list
 *
 *  @param[in] val - Value to be removed
 *
 *  @returns True if the value was removed false otherwise
 *
 *****************************************************************************/
template <class DT>
bool unsortedDouble<DT>::pop_front(DT &val)
{
    return retrieve(val,1)&&remove(1);
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Swaps two lists
 *
 *  @param[in] l - List to be swapped with
 *
 *****************************************************************************/
template <class DT>
void unsortedDouble<DT>::swap(unsortedDouble<DT> &l)
{
    std::swap(l.headptr,this->headptr);
    std::swap(l.tailptr,this->tailptr);
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Retrieves a value from the list
 *
 *  @param[in] val - Value to be retrieved
 *
 *  @returns The position of the item 0 if it is not found
 *
 *****************************************************************************/
template <class DT>
int unsortedDouble<DT>::retrieve ( DT val )
{
    node *temp;//Temporary Node
    temp = headptr;
    int count = 1;
    //walks through the list checking for the value
    while ( temp != nullptr )
    {
        if ( temp->item == val )
        {
            return count;
        }
        
        temp = temp->next;
        count++;
    }
    
    return 0;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Retrieves a value from the list starting at the end
 *
 *  @param[in] val - Value to be retrieved
 *
 *  @returns The position of the item 0 if it is not found
 *
 *****************************************************************************/
template <class DT>
int unsortedDouble<DT>::rretrieve ( DT val )
{
    node *temp;//Temporary Node
    temp = tailptr;
    int count = size();
    //walks through the list and checks for the value
    while ( temp != nullptr )
    {
        if ( temp->item == val )
        {
            return count;
        }
        
        temp = temp->last;
        count--;
    }
    
    return 0;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Retrieves a value from the list
 *
 *  @param[in] item - Item to be retrieved
 *  @param[in] position - Position to be retrieved from 
 *
 *  @returns True if the item was found false otherwise
 *
 *****************************************************************************/
template <class DT>
bool unsortedDouble<DT>::retrieve ( DT &item, int position )
{
    node *temp;//Temporary Node
    temp = headptr;
    int count = 1;
    //checks if the list i empty
    if ( isEmpty() )
    {
        return false;
    }
    //Walks throught the list and checks if the value is found
    while ( temp != nullptr )
    {
        if ( count == position )
        {
            item = temp->item;
            return true;
        }
        
        temp = temp->next;
        count++;
    }
    
    return false;
}
/**************************************************************************//**
 * @author Tim Adcock
 *
 * @par Description:
 *  Counts how many value pass a given condition
 *
 *  @param[in] cond - Condition to be tested
 *
 *  @returns The count of passed items
 *
 *****************************************************************************/
template <class DT>
int unsortedDouble<DT>::countIf ( function<bool ( DT ) > cond )
{
    node *temp;//Temporary Node
    temp = headptr;
    int count = 0;
    //Walks through the function conting if a condition is true
    while ( temp != nullptr )
    {
        if ( cond ( temp->item ) )
        {
            count++;
        }
        
        temp = temp->next;
    }
    
    return count;
}


#endif


