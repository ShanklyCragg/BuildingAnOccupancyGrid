#ifndef OCCUPANCY_GRID_MAIN_H
#define OCCUPANCY_GRID_MAIN_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <vector>



double getXCoordinate (double x_r, double sensors_range, double senor_alpha, double senor_beta);
double getYCoordinate(double y_r, double senor_range, double senor_alpha, double senor_beta);
double convert_to_radians (double degrees);
double getCellIndexY(double y);
double getCellIndexX(double x);
void readPosesData(std::vector<std::vector<double>> & poses);
void readRangeData(std::vector<std::vector<double>> & ranges);
void printGrid(std::vector<std::vector<int >> & grid);
void buildingGrid(std::vector<std::vector<double> > & poses,
                  std::vector<std::vector<double>> & ranges,
                  std::vector<std::vector<int>> & grid);
static double RADS_TO_DEGREES = 57.2958;
static double GRID_OFF_SET = 0.2;


#endif //OCCUPANCY_GRID_MAIN_H