//HEADER----------------------------

#ifndef HEADER_H
#define HEADER_H


//void readPoses(float (*poses[40][2]));
//void readPoses();
//void readPoses(float (&poses)[40][2]);;
void read_poses(std::vector < std::vector <float> > &poses);
void read_ranges(std::vector < std::vector <float> > &ranges);
float data_to_Xcoor (float xcoor, float range, double alpha, double beta);
float data_to_Ycoor (float ycoor, float range, double alpha, double beta);
float degrees_to_radians (float degrees);
float coor_to_cell(float x);
void grid_create(std::vector < std::vector<char> > &grid);
void grid_build(std::vector < std::vector <float> > &poses, 
        std::vector < std::vector <float> > &ranges,
        std::vector < std::vector<char> > &grid);
void grid_print(std::vector < std::vector<char> > &grid);


const float DEGREES_TO_RADS = 0.0174533;

#endif /* HEADER_H */