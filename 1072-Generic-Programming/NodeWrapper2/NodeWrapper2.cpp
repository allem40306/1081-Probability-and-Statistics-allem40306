#include <iostream>
#include <string>
#include <algorithm>
#include "ListNode.h"
using namespace std;

int main( void )
{
    test_linklist(5,{1,3,4,5,6},2);
    test_linklist(5.0,{2.55},2.633);
    test_linklist("5",{"5","3,4","5,6"},"3,4");
    test_linklist('a',{'k'},'a');   
}
