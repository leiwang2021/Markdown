#include<iostream>
#include<cstring>

using namespace std;

class CMyString{
    public:
        CMyString(char const * pData=nullptr);
        CMyString(const CMyString & str);
        ~CMyString(void);

        CMyString& operator = (const CMyString & str);

        void Print();
    private:
        char* m_pData;
};

CMyString::CMyString(char const * pData)
{
    if(pData==nullptr)
    {
        m_pData=new char[1];
        m_pData[0]='\0';
    }
    else{
        int length=strlen(pData);
        m_pData=new char[length+1];
        strcpy(m_pData,pData);
    }
    
}

CMyString::CMyString(const CMyString & str)
{
    int length=strlen(str.m_pData);
    m_pData=new char[length+1];
    strcpy(m_pData,str.m_pData);
}

CMyString::~CMyString(void)
{
    delete [] m_pData;
}

CMyString& CMyString::operator=(const CMyString & str)
{
    if(this==&str)
        return *this;
    delete [] m_pData;
    int length=strlen(str.m_pData);
    m_pData=nullptr;
    m_pData=new char[length+1];
    strcpy(m_pData,str.m_pData);
    return *this;
}
void CMyString::Print()
{
    cout<<m_pData<<endl;
}

void Test1()
{
    cout<<"Test1 begin:"<<endl;
    char const * text="Hello World";
    CMyString str1(text);
    CMyString str2;
    str2=str1;
    cout<<"The expected result is:"<<text<<endl;
    cout<<"The actual result is:"<<endl;
    str2.Print();
}

void Test2()
{
    cout<<"Test2 begin:"<<endl;
    char const * text="Hello World";
    CMyString str1(text);
    str1=str1;
    cout<<"The expected result is: "<<text<<endl;
    cout<<"The actual result is:"<<endl;
    str1.Print();
}

void Test3()
{
    cout<<"Test3 begin:"<<endl;
    char const * text="Hello World";
    CMyString str1(text);
    CMyString str2;
    CMyString str3;
    str3=str2=str1;
    cout<<"The expected result is:"<<text<<endl;
    cout<<"The actual result is:"<<endl;
    str2.Print();
    str3.Print();
}

int main()
{
    Test1();
    Test2();
    Test3();
    return 0;
}
