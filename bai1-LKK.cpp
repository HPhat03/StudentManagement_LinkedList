#include <iostream>
#include <fstream>
#include "bai1-LKK-list.cpp"
using namespace std;

int main()
{

   Double S;
   S.init(S.First,S.Last);
   ifstream IN;
   ofstream OUT;
   IN.open("DSSV.txt",ios::in);
   SV tam;

   if(IN.is_open())
   {
      while(!IN.eof())
      {
         getline(IN,tam.MaSV,'-');
         getline(IN,tam.Ho,'-');
         getline(IN,tam.Ten,'-');
         IN >> tam.DM1;
         IN.ignore(1);
         IN >> tam.DM2;
         IN.ignore(1);
         S.InsB(S.First,S.Last,tam);
      }
      string ID;
      cout << "Da sao luu thong tin! \n";
      IN.close();
      int sort = 0;
      do{
         system("cls");
         if(sort==0)
         {
            S.IDAsc(S.First);
            S.ListF(S.First);
         }
         else if(sort==1){
               S.NameAsc(S.First);
               S.update(S.First);}
               else if(sort==2){
                  S.AvergDesc(S.First);
                   S.update(S.First);}
         cout << "\nMENU: \n 1.Tim thong tin 1 sinh vien.\n 2.Them vao thong tin 1 sinh vien moi.\n 3. Xoa theo MSSV. \n 4. Danh sach theo ten. \n 5.Danh sach sinh vien theo diem trung binh giam dan \n 6.Danh sach sinh vien theo MSSV. \n 7.Danh sach sinh vien dau. \n 8.Thoat";
         int choice;
         cout << "\nAns: ";
         cin >> choice;
         cin.ignore();
         cout << endl;
         
         if(choice >=1 && choice <=7)
         {
         switch (choice)
         {
            case 1:
            {
               cout << "1.Tim theo MSSV\n2.Tim theo Ten\n";
               cout << "Ans: ";
               cin >> choice;
               switch (choice)
               {
               case 1:
                  cout << "Nhap ma so ban can tim: ";
                  getline(cin,ID);
                  S.standard(ID);
                  cout << ID << endl;
                  if(S.FindID(ID)==NULL)
                  cout << "Khong tim thay!\n";
                  else
                  Info(S.FindID(ID)->Data,1);
                  break;
   
               case 2:
                  cout << "Nhap ten ban can tim: ";
                  cin.ignore();
                  getline(cin,ID);
                  if(S.FindName(ID)==NULL)
                  cout << "Khong tim thay!\n";
                  else
                  S.FindName(ID);
                  break;
               }

            }
            break;

            case 2:
            {
               cout << "Nhap vao thong tin mot sinh vien:\n";
               S.InsF(S.First,S.Last);
            }
               break;
            case 3:
            {
               cout << "Nhap vao MSSV ban muon xoa: ";
               getline(cin,ID);
               if((S.First ==NULL && S.Last == NULL) || S.FindID(ID)==NULL)
               cout << "Danh sach rong hoac khong the tim thay mssv!\n";
               else{
                  S.DelSV(S.First, S.Last, ID);
                  cout << "Da xoa sinh vien " << ID << endl;
                  S.update(S.First);
               }
            }
            break;
            case 4:
            {
               sort=1;
               cout << "Da sap xep!\n";
            }
            break;
            case 5:
            {
               sort=2;
               cout << "Da sap xep!\n";
               break;
            }
            case 6:
            {
               sort=0;
               cout << "Da sap xep!\n";
               break;
            }
            case 7:
            {
               S.PassList(S.First);
               break;
            }
         }
      }
      else{
         if(choice==8)
            break;
            else
            cout <<"Khong hop le!\n";
         }
      system("pause");
      }while(true);
   }
   else
   cout << "Khong the mo file!\n";

   return 0;
}