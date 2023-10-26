#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

struct SV
{
    string MaSV;
    string Ho;
    string Ten;
    double DM1;
    double DM2;
};

void Info(SV S, int n)
{
    if(n==0)
    cout << "| " << S.MaSV << " | " << setw(20) << S.Ho << " | "  << setw(10) << S.Ten << " | "<< setw(4) << S.DM1 << " | "<< setw(4) << S.DM2 << " |" ;
    if(n==1)
    cout << "\nThong tin sinh vien: \n MSSV: " << S.MaSV << "\n Ho va ten: " << S.Ho + ' ' + S.Ten << "\n DM1: " << S.DM1 << "\n DM2: " << S.DM2 << endl; 
}

double Average(SV S)
{
    return (S.DM1+S.DM2)/2;
}

struct Double
{
    SV Data;
    struct Double *pre;
    struct Double *next;

    Double *First, *Last;
    void init(Double *&First, Double *&Last)
    {
        First=Last=NULL;
    }

    void InsB(Double *&First, Double *&Last, SV x)
    {
        Double *p= new Double;
        p->Data=x;
        p->next=NULL;
        p->pre=Last;
        if(Last==NULL)
        Last=First=p;
        else
        {
            Last->next=p;
            if(Last->pre==NULL)
                First=Last;
            Last=p;
        }
    }


    void ListF(Double *First)
    {
            cout << " _______________________________________________________________\n";
            cout << "| MSSV |          Ho          |     ten    |  DM1 |  DM1 |  DTB |\n";
            cout << "|______|______________________|____________|______|______|______|\n";
        for(Double *p=First; p!=NULL; p=p->next){
            cout << "|      |                      |            |      |      |      |\n";
            Info(p->Data,0);
            cout << " "<< setw(4)  <<  Average(p->Data) << " |" << endl;
            cout << "|______|______________________|____________|______|______|______|\n";
        }
    }

    Double *FindID(string ID)
    {
        Double *S=NULL;
        if(First!=NULL)
        {
            for(Double *p=First; p!=NULL; p=p->next)
            {
                if(ID==p->Data.MaSV)
                    S=p;
            }
        }
        return S;
    }
    void standard(string &X)
    {
        for(int i = 0; i<X.length(); i++)
                X[i]=tolower(X[i]);
        for(int i = 0; i<X.length();i++)
            {
                if(X[i-1]==' ' || i==0)
                    X[i]=toupper(X[i]);
            }
        
    }
    int FindName(string name)
    {
        standard(name);
        Double *S=NULL;
        if(First!=NULL)
        {
            for(Double *p=First; p!=NULL; p=p->next)
            {
                if(name==p->Data.Ten){
                    S=p;
                Info(p->Data,1);
                }
            }
            return 1;
        }
        return 0;
    }

    void InsF(Double *&First, Double *&Last)
    {
        SV tam;
        cout << "Nhap ma so SV: ";
        getline(cin,tam.MaSV);
        if(FindID(tam.MaSV)==NULL)
        {
            cout << "Nhap Ho: ";
            getline(cin,tam.Ho);
            cout << "Nhap ten: ";
            getline(cin, tam.Ten);
            cout << "Nhap diem mon 1: ";
            cin >> tam.DM1;
            cout << "Nhap diem mon 2: ";
            cin >> tam.DM2;
            InsB(First,Last,tam);
            IDAsc(First);
            update(First);
        }
        else
        cout << "\nLoi! trung ma so SV!\n";
    }

    int DelFr(Double *&First, Double *&Last)
    {
        Double *p=First;
        if(First==NULL)
        return 0;
        else
        {
            if(First->next==NULL)
            First=Last=NULL;
            else
            {
                First=First->next;
                First->pre=NULL;
                delete p;
            }
            return 1;
        }
    }

    int DelBck(Double *&First, Double *&Last)
    {
        if(Last==NULL)
        return 0;
        else{
            if(Last->pre==NULL)
            First=Last=NULL;
            else
            {
                Double *p=Last;
                Last = Last->pre;
                Last->next=NULL;
                delete p;
            }
            return 1;
        }
        return 0;
    }

    int DelSV(Double *&First, Double *&Last, string ID)
    {
        if(First!=NULL)
        {
        if(First==FindID(ID))
            DelFr(First,Last);
        else{
        if(Last==FindID(ID))
            DelBck(First, Last);
        else{
            Double* p = FindID(ID);
            p->pre->next=p->next;
            p->next->pre=p->pre;
            delete p;
        }
        }
        return 1;
        }
        return 0;
    }

    void update(Double *First)
    {
        ofstream OUT;
        OUT.open("DSSV.txt",ios::out);
        if(OUT.is_open())
        {
            for(Double *p=First; p!=NULL; p=p->next)
            {
                OUT << p->Data.MaSV << '-' << p->Data.Ho << '-' << p->Data.Ten << '-' << p->Data.DM1 << '-' << p->Data.DM2;
                if(p->next!=NULL) OUT << endl;
            }
        }
        else cout << "Khong the sao luu!\n";
    }

    void NameAsc(Double *First)
    {
        for(Double *p=First; p!=NULL; p=p->next)
            for(Double *q=p->next; q!=NULL; q=q->next)
                if(p->Data.Ten>q->Data.Ten)
                    {
                        SV tam= p->Data;
                        p->Data=q->Data;
                        q->Data=tam;
                    }
        ListF(First);
    }

    void AvergDesc(Double *First)
    {
        for(Double *p=First; p!=NULL; p=p->next)
            for(Double *q=p->next; q!=NULL; q=q->next)
                if(Average(p->Data)<Average(q->Data))
                    {
                        SV tam= p->Data;
                        p->Data=q->Data;
                        q->Data=tam;
                    }
        ListF(First);
    }

    void IDAsc(Double *First)
    {
        for(Double *p=First; p!=NULL; p=p->next)
            for(Double *q=p->next; q!=NULL; q=q->next)
                if(p->Data.MaSV>q->Data.MaSV)
                    {
                        SV tam= p->Data;
                        p->Data=q->Data;
                        q->Data=tam;
                    }
    }

    void PassList(Double *First)
    {
        cout << "Danh sach cac sinh vien dau (DTB>=5):\n";
        for(Double *p=First; p!=NULL; p=p->next)
        {
            if(Average(p->Data)>=5)
            {
                Info(p->Data,0);
                cout << "Diem trung binh: " << Average(p->Data) << endl;
            }
        }

        cout << "Danh sach cac sinh vien rot (DTB<5):\n";
        for(Double *p=First; p!=NULL; p=p->next)
        {
            if(Average(p->Data)<5)
            {
                Info(p->Data,0);
                cout << "Diem trung binh: " << Average(p->Data) << endl;
            }
        }
    }
};