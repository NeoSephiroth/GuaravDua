#include <iostream>
#include <string>
#include "prices.h"



int main ()
{

    //	double strike0, double spot0, double sigma, double Time, double rate

    cout << "American puts" << endl << endl;

    //TEST VALUES

    AmericanPut test1(100.0,81.0,.4,1.0,.01);

    double P1 = test1.getValue();

    cout << "Test Values" << endl;
    cout << "Put Fair Value = " << P1 << endl;




    system("pause");
    return 0;
}