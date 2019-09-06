#include<iostream>

using namespace std;

class Widget{
    public:
        virtual void flip() const
        {
            cout<<"Widget flip"<<endl;
        }

        void test() const
        {
            cout<<"Widget test"<<endl;
        }
};

class Bell:public Widget{
    public:
        void flip() const
        {
            cout<<"Bell flip"<<endl;
        }
};
class Whistle:public Widget
{
    public:
         void flip() const
        {
            cout<<"Whistle flip"<<endl;
        }
};

void fli(const Widget& widget)
{
    widget.flip();
    widget.test();
}

int main()
{
    Bell b;
    Whistle w;

    fli(b);
    fli(w);
    return 0;
    
}

