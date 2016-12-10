//
//  Matrix.hpp
//  Where's_Wally
//
//  Created by Andrew on 30/11/2016.
//  Copyright © 2016 Andrew. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include <iostream>
#include <array>

class Matint
{
public:
    Matint(int rows, int columns) : RoWs(rows), ColuMNs(columns) // in heritance.
    {
        PMatrix = generatematrix(rows, columns);
    }
        // ~ deconstructor --> objects are deallocated.
    ~Matint();
    
    double** generatematrix(int rows, int columns);
    double getvalue(int rows, int columns);
    
    void print();
    void populatematrix(double* source, int size);
    void setvalue(int rows, int columns, int value);
    
    int GetCols();
    int GetRows();
    
private:
    double RoWs = 0;
    double ColuMNs = 0;
    double** PMatrix;
        // an array of pointers
};

#endif /* Matrix_hpp */
