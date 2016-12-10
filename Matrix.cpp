//
//  Matrix.cpp
//  Where's_Wally
//
//  Created by Andrew on 30/11/2016.
//  Copyright © 2016 Andrew. All rights reserved.
//

#include "Matrix.hpp"
#include <iostream>

using namespace std;

Matint::~Matint()
    // deconstructor
{
    for (int i = 0; i < RoWs; i++)
    {
        delete[] PMatrix[i];
        // array of pointers called, to be deleted when used.
    }
    delete[] PMatrix;
        // deleting the array reduces the risk of memory leaking.
}

    // generating of matrix.
    // ** an array of pointers.
double** Matint::generatematrix(int rows, int columns)
{
    double** tempnum = new double*[rows];
    
    for(int i = 0; i < rows; i++)
    {
        tempnum[i] = new double[columns];
    }
    
    return tempnum;
}

void Matint::populatematrix(double* source, int size)
{
    int position = 0;
    
    for(int i = 0; i < RoWs; i++)
    {
        for(int j = 0; j < ColuMNs; j++)
        {
            this->PMatrix[i][j] = source[position++];
        }
    }
}

    // get-set

int Matint::GetRows()
{
    return RoWs;
}

int Matint::GetCols()
{
    return ColuMNs;
}

double Matint::getvalue(int rows, int columns)
{
    return this->PMatrix[rows][columns];
}

void Matint::setvalue(int rows, int columns, int value)
{
    PMatrix[rows][columns] = value;
}

void Matint::print()
{
    for(int i = 0; i < RoWs; i++)
    {
        for(int j = 0; j < ColuMNs; j++)
        {
            cout << PMatrix[i][j] << " ";
        }
        cout << " " << endl;
    }
}



