#include<iostream>

using namespace std;

typedef int length;

class Point3d{
    public:
        typedef float length;
        void mumble1(){
            length val=2.1;
            _val=val;
        }

        length mumble(){return _val;}
    private:
        //typedef float length;
        length _val;
};

int main()
{
    Point3d point;
    point.mumble1();
    cout<<point.mumble()<<endl;
    return 0;
}
