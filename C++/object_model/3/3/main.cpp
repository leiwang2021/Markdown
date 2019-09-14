#include<iostream>
#include<stdio.h>
using namespace std;

class Point3d{
    public:
        virtual ~Point3d(){}
        static Point3d origin;
        float x,y,z;

};
int main()
{
    Point3d A;
    cout<<sizeof(A)<<endl;
  /*  printf("&Point3d::x=%p\n",&Point3d::x);
    printf("&Point3d::y=%p\n",&Point3d::y);
    printf("&Point3d::z=%p\n",&Point3d::z);
    */

    //cout<<&Point3d::x<<endl;
    //cout<<&Point3d::y<<endl;
    //cout<<&Point3d::z<<endl;
    //cout<<&Point3d::origin<<endl;
    return 0;
}
