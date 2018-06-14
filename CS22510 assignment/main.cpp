/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Shankly
 *
 * Created on March 13, 2016, 4:27 PM
 */

/*
 * poses file reads x and y positions, and orientation
 * Orientation works counter clockwise
 * "Robot" can see in 8 directions at any time like a compass
 * north, north-west, west and so on
 * Each direction has a range associated with it at each position
 * max of 2.5m but can and is less sometimes
 * 
 * Grid is 50x50 cells
 * Each cell is 0.2x0.2 meters
 * Total grid is 10x10 meters large
 * Range can therefore be upto a quarter of the whole grid
 * 
 * So go to position given
 * Look in 1 direction and at how far it goes
 * If sensor goes less than 2.5 then it must have hit something
 * Work out which cell it stopped at using position of robot, orientation and
 *  which sensor we were using as well as range
 * Mark that cell as occupied
 * so position, 8 ranges to check, next position
 * 
 * to get a coordinate you use the following maths
 * 
 * x = xr + r * cos(a + b)
 * 
 * xr = first value in poses
 * r = range
 * a = 45* index position of range
 * b is 3rd value in pos
 * 
 * going to need 2 2d arrays to store poses and ranges
 * 
 * not sure about how to do objects yet, wait and get rich to help later
 * 
 */


#include <cstdlib> //The standard library
#include <iostream> //cout
#include <vector> //For vectors
#include <cmath> //For sin and cos
#include <fstream> //Included to read inout from file
#include <unistd.h> //for using the function sleep
#include "header.h"

//#include <stdio.h>
//#include <time.h>
//#include <dos.h>
//#include <windows.h>


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    std::vector < std::vector <float> > poses;
    std::vector < std::vector <float> > ranges;
    std::vector < std::vector <char> > grid;
    read_poses(poses);
    read_ranges(ranges);
    grid_create(grid);
    grid_build(poses, ranges, grid);
    grid_print(grid);
    return 0;
}

void read_poses(vector < vector<float> > &poses) {
    std::ifstream infile("poses.txt"); //open connection to file
    float x, y, a;
    while (infile >> x >> y >> a)
    {
        vector<float> temp;
        temp.push_back(x);
        temp.push_back(y);
        temp.push_back(a);

        poses.push_back(temp);
    }
    
    for (int i=0;i<=40;i++) {
        cout << "\n" << i << ":  ";
        //cout << i;
        //cout << ":   ";
        for (int j=0;j<=2;j++){
            cout << poses[i][j] << " | ";
            //cout << " | ";
        }
    }
}

void read_ranges(vector < vector<float> > &ranges) {
    std::ifstream infile("ranges.txt"); //open connection to file
    float a, b, c, d, e, f, g, h;
    int i=0;
    while (infile >> a >> b >> c >> d >> e >> f >> g >> h)
    {
        vector<float> temp;
        temp.push_back(a);
        temp.push_back(b);
        temp.push_back(c);        
        temp.push_back(d);
        temp.push_back(e);
        temp.push_back(f);        
        temp.push_back(g);
        temp.push_back(h);
        
        ranges.push_back(temp);
        
        i++;
    }
    
    for (int i=0;i<=40;i++) {
        cout << "\n" << i << ":  ";
        //cout << i;
        //cout << ":   ";
        for (int j=0;j<=7;j++){
            cout << ranges[i][j] << " | ";
            //cout << " | ";
        }
    }
    
}

float data_to_Xcoor (float xcoor, float range, double alpha, double beta) {
    float Xcoor = xcoor + range * cos(alpha + beta);
    return Xcoor;
}

float data_to_Ycoor (float ycoor, float range, double alpha, double beta) {
    float Ycoor = ycoor + range * sin(alpha + beta);
    return Ycoor;
}

float degrees_to_radians (float degrees) {
    float rads = degrees * DEGREES_TO_RADS;
}

float coor_to_cell(float x) {
    float Cell_initial = (x / 0.2) + 0.2;
    int Cell_round = round(Cell_initial);
    return Cell_round;
}

void grid_create(vector < vector<char> > &grid) {
    for (int i=0;i<=49;i++) {
        vector <char> temp;
        for (int j=0;j<=49;j++) {
            temp.push_back('-');
        } 
        grid.push_back(temp);
    }
}

void grid_build(vector < vector<float> > &poses, 
        vector < vector<float> > &ranges,
        vector < vector<char> > &grid) {
    
    float xr, yr, beta_degrees;
    for (int i=0;i<=40;i++){
        xr = poses[i][0];
        yr = poses[i][1];
        beta_degrees = poses[i][2];
        for (int j=0;j<=7;j++) {
            float range = ranges[i][j];
            if (range<2.5) {
                float alpha_degrees = 45*j;
                float alpha_rads = degrees_to_radians(alpha_degrees);
                float beta_rads = degrees_to_radians(beta_degrees);
                float Xcoor = data_to_Xcoor(xr, range, alpha_rads, beta_rads);
                float Ycoor = data_to_Ycoor(yr, range, alpha_rads, beta_rads);
                int XCell = coor_to_cell(Xcoor);
                int YCell = coor_to_cell(Ycoor);
                grid[XCell][YCell] = '*';
                //grid_print(grid);
                //sleep(1);         //make the programme waiting for 5 secondes
                //cout << "Hit at x: " << XCell << " and at y: " << YCell << "\n";
            }
            else {
                //cout << "No hit \n";
            }
        }
    }
}

void grid_print(vector < vector<char> > &grid) {
    for (int i=49;i>=0;i--) {
        cout << "\n";
        for (int j=0;j<=49;j++) {
            if (grid[j][i] == '*') {
                cout << "*";
            }
            else {
                cout << "-";
            }
        } 
    }
}