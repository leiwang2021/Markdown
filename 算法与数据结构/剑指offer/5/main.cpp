#include<iostream>

using namespace std;

void replaceSpace(char* str,int length)
{
    if(str==nullptr || length<0)
        return;
    //先统计空格的个数
    int originLength=1;  //'\0'
    int bankLength=0;
    int i=0;
    cout<<str<<endl;
    while(str[i]!='\0')
    {
        originLength++;
        if(str[i]==' ')
            bankLength++;
        i++;

    }
    bankLength=originLength+2*bankLength;
    cout<<bankLength<<" "<<originLength<<endl;
    while(bankLength!=originLength)
    {
        if(str[originLength]!=' ')
        { str[bankLength]=str[originLength];
          bankLength--;
          originLength--;
        }
        else{
            str[bankLength--]='0';
            str[bankLength--]='2';
            str[bankLength--]='%';
            originLength--;
        }

    }
}

void test1()
{
    char str1[100]=" helloworld";
    char str2[100]="helloworld ";
    char str3[100]="hello world";
    char str4[100]="h e l l o w o r l d";
    char str5[100]="helloworld";
    char str7[100]="";
    char str8[100]=" ";
    char str9[100]="            ";
    cout<<str1<<endl;
    cout<<str2<<endl;
    cout<<str3<<endl;
    cout<<str4<<endl;
    cout<<str5<<endl;
    cout<<str7<<endl;
    cout<<str8<<endl;
    cout<<str9<<endl;
    replaceSpace(str1,sizeof(str1));
    cout<<"str1"<<endl;
    replaceSpace(str2,sizeof(str2));
    cout<<"str2"<<endl;
    replaceSpace(str3,sizeof(str3));
    cout<<"str3"<<endl;
    replaceSpace(str4,sizeof(str4));
    cout<<"str4"<<endl;
    replaceSpace(str5,sizeof(str5));
    cout<<"str5"<<endl;
    replaceSpace(str7,sizeof(str7));
    cout<<"str7"<<endl;
    replaceSpace(str8,sizeof(str8));
    cout<<"str8"<<endl;
    replaceSpace(str9,sizeof(str9));
    cout<<"str9"<<endl;
    cout<<str1<<endl;
    cout<<str2<<endl;
    cout<<str3<<endl;
    cout<<str4<<endl;
    cout<<str5<<endl;
    cout<<str7<<endl;
    cout<<str8<<endl;
    cout<<str9<<endl;
}
int main()
{
    test1();
    return 0;
}

