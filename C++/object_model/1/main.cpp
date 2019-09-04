#include<iostream>
#include<cstring>
using namespace std;

struct mumble{
    char pc[1];
};

int main()
{
    char const* string="Heelo";
    struct mumble* pmumb1=(struct mumble*)malloc(sizeof(struct mumble)+strlen(string)+1);
    strcpy(pmumb1->pc,string);
    cout<<pmumb1->pc<<endl;
    return 0;
}
