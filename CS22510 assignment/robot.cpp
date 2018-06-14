#include <iostream>

using namespace std;

class Robot // Standard way of defining the class
{
public:
  // This means that all of the functions below this(and any variables)
  //  are accessible to the rest of the program.
  //  NOTE: That is a colon, NOT a semicolon...
  Robot();
  // Constructor
  ~Robot();
  // Destructor
  void setspeed ( int p );
  int readspeed();
protected:
  // This means that all the variables under this, until a new type of
  //  restriction is placed, will only be accessible to other functions in the
  //  class.  NOTE: That is a colon, NOT a semicolon...
  int processorspeed;
  
    std::vector < std::vector <float> > poses;
    std::vector < std::vector <float> > ranges;
    std::vector < std::vector <char> > grid;
  
};
// Do Not forget the trailing semi-colon

Robot::Robot()
{
  //Constructors can accept arguments, but this one does not
  processorspeed = 0;
  
    read_poses(poses);
    read_ranges(ranges);
  
}

Robot::~Robot()
{
  //Destructors do not accept arguments
}

void Robot::setspeed ( int p )
{
  // To define a function outside put the name of the class
  //  after the return type and then two colons, and then the name
  //  of the function.
  processorspeed = p;
}
int Robot::readspeed()  
{
  // The two colons simply tell the compiler that the function is part
  //  of the class
  return processorspeed;
}


static void read_poses(vector < vector<float> > &poses) {
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

int main()
{
  Robot my_robot;  
  // To create an 'instance' of the class, simply treat it like you would
  //  a structure.  (An instance is simply when you create an actual object
  //  from the class, as opposed to having the definition of the class)
  my_robot.setspeed ( 100 ); 
  // To call functions in the class, you put the name of the instance,
  //  a period, and then the function name.
  cout<< my_robot.readspeed();
  // See above note.
}