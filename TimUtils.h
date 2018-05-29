#ifndef __TIMUTILS__H__
#define __TIMUTILS__H__
#include "Belt.h"
#include <iostream>
#include <algorithm>
using namespace std;

void outputBox ( ostream &out, box pack, conveyorBelt conv );
void outputSimNum ( ostream &out, int simNum );
bool willFall ( conveyorBelt belt );
bool  operator< ( conveyorBelt left, conveyorBelt right );
char getFitConveyor ( box package, conveyorBelt small, conveyorBelt middle,
                      conveyorBelt larg );
box getPropDims(box pack, conveyorBelt conv);


#endif
