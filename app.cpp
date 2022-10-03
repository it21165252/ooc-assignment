#include <iostream>
#include <cmath>
#define g 9.81  //ms^-2

using namespace std;

int main(){
    double u = 20.0; //m/s`
    double angle = 45.0; //degrees

    cout<<"Enter the initial velocity of the object: ";
    cin<<u;

    cout<<"Enter the angle of projection: ";
    cin<<angle;
 
    /********finding h***********/

    double h = (u*u*sin(2*angle))/g;

    /********finding t***********/

    double t = (2*u*sin(angle))/g;

    /********finding range***********/

    double range = (2*u*u*sin(angle)*cos(angle))/g;

    cout << "The height of the projectile is " << h << "m" << endl;
    cout << "The time of flight is " << t << "s" << endl;
    cout << "The range of the projectile is " << range << "m" << endl;


}