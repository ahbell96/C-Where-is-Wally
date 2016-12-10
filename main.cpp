//
//  main.cpp
//  Where's_Wally
//
//  Created by Andrew on 24/11/2016.
//  Copyright © 2016 Andrew. All rights reserved.
//

#include <sstream>
#include <iostream>
#include <fstream>
#include <istream>
#include <array>
#include <vector>
#include <cmath>
#include <cstdlib>
#include "Matrix.hpp"
#include "LargeImage.hpp"
#include "MatchImage.hpp"

using namespace std;

// Input data are provided in .txt format and can be converted to .pgm files for visualization
// Download (free) ImageJ for plotting images in .pgm format
// http://rsb.info.nih.gov/ij/download.html

double* readTXT(char *fileName, int sizeR, int sizeC);

// Converts a 1D array of doubles of size R*C to .pgm image of R rows and C Columns
// and stores .pgm in filename
// Use Q = 255 for greyscale images and Q=1 for binary images.
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q);

int SSD(Matint &matrix1, Matint &matrix2);
// & -- passing address.

int main()
{
    // This part will show you how to use the two functions.
    //M and N represent the number of rows and columns in the image,
    //e.g. Cluttered_scene, M = 768, N = 1024
    //e.g. Wally_grey, M = 49, N =  36
    // input_data is a pointer to a 1D array of M*N doubles stored in heap. Memory allocation is performed
    // putting M & N into Two dimensional Array.
    
    std::cout << endl;
    std::cout << "--------------------DATA FROM FILE-------------------" << endl;
    
    // .pgm image is stored in inputFileName, change the path in your program appropriately.
    
    double* Input_Data_Clutter = 0;
    double* Input_Data_Wally = 0;
    char* InputClutterFile = "/Users/Andrew/Desktop/Year 2/OOP/Assignment /V2/Where's_Wally/Supporting Files/Cluttered_scene.txt";
    char* InputWallyFile = "/Users/Andrew/Desktop/Year 2/OOP/Assignment /V2/Where's_Wally/Supporting Files/Wally_grey.txt";
    int M = 768;
    int N = 1024;
    int WallyM = 49;
    int WallyN = 36;
    Matint ClutterScene(M, N);
        // large scale image, inputted into matrix.
        // matrix instance, with M & N Values.
    Matint WallyImage(WallyM, WallyN);
        // wally scaled image, inputted into matrix.
        // Matrix Instance, with Wally image M & N values.
    
        // Clutter Image
    Input_Data_Clutter = readTXT(InputClutterFile, M, N);
        // populating the matrix with the values from the cluttered_scene.txt
    ClutterScene.populatematrix(Input_Data_Clutter, M * N);
        // I now need to include the smaller image into the code.
    
    Input_Data_Wally = readTXT(InputWallyFile, WallyM, WallyN);
    WallyImage.populatematrix(Input_Data_Wally, M * N);
    
    // WallyImage.print();
    //cout << " " << endl;
    // ClutterScene.print();
    
    // SSD(WallyImage, ClutterScene);
        // Overloading SSD with Wallyimage and the Cluttered Scene.
    
    /*
    // writes data back to .pgm file stored in outputFileName
    char* outputFileName = "Clutered_scene.pgm";
    // Use Q = 255 for greyscale images and 1 for binary images.
    int Q = 255;
    WritePGM(outputFileName, input_data, M, N, Q);
    
    delete [] input_data;
     */
    
    return 0;
}

int SSD(Matint &Matrix1, Matint &Matrix2)
{
    // i have to return the rows and columns of the required matrix class.
    // wally image = matrix 1.
    // clutter scene = matrix 2.
    
    double difference = 0.0, SSDscore = 0.0;
    // vector of scores.
    vector<double> SSDTotal;
    
    for(int i = 0; i < Matrix1.GetRows(); i++)
    {
        for(int j = 0; j < Matrix1.GetCols(); j++)
        {
            difference = Matrix1.getvalue(i, j) - Matrix2.getvalue(i, j);
            SSDscore = difference * difference;
        }
                SSDTotal.push_back(SSDscore);
    }
    
    for(std::vector<double>::iterator Result = SSDTotal.begin(); Result != SSDTotal.end(); Result++)
    {
        std::cout << " " << *Result;
    }
    return 0;
}

// Read .txt file with image of size RxC, and convert to an array of doubles
double* readTXT(char *fileName, int sizeR, int sizeC)
{
    double* data = new double[sizeR*sizeC];
    int i=0;
    ifstream myfile (fileName);
    if (myfile.is_open())
    {
        
        while ( myfile.good())
        {
            if (i>sizeR*sizeC-1) break;
            myfile >> *(data+i);
            // cout << *(data+i) << ' '; // This line display the converted data on the screen, you may comment it out.
            i++;
        }
        myfile.close();
    }
    
    else cout << "Unable to open file";
    //cout << i;
    
    return data;
}
// convert data from double to .pgm stored in filename
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q)
{
    
    int i, j;
    unsigned char *image;
    ofstream myfile;
    
    image = (unsigned char *) new unsigned char [sizeR*sizeC];
    
    // convert the integer values to unsigned char
    
    for(i=0; i<sizeR*sizeC; i++)
        image[i]=(unsigned char)data[i];
    
    myfile.open(filename, ios::out|ios::binary|ios::trunc);
    
    if (!myfile) {
        cout << "Can't open file: " << filename << endl;
        exit(1);
    }
    
    myfile << "P5" << endl;
    myfile << sizeC << " " << sizeR << endl;
    myfile << Q << endl;
    
    myfile.write( reinterpret_cast<char *>(image), (sizeR*sizeC)*sizeof(unsigned char));
    
    if (myfile.fail()) {
        cout << "Can't write image " << filename << endl;
        exit(0);
    }
    
    myfile.close();
    
    delete [] image;
    
}
