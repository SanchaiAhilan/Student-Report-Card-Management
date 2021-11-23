#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

class Student
{
  int rollno;
  char name[50];
  int p_score,c_score,m_score,e_score,cs_score;
  float percentage;
  char grade;

  public:
  void get_info();      // function to get details of the student
  void show_info();     // function to show details of the student
  void calc();          // function to calculate percentage and grade
  void show_row();      // function to show details of the student in a row
  int get_roll_no();    // function to get details of the student
};

void result();          // function to display result menu
void entry_menu();      // Entry / Edit Menu function
void write_student();   // function to write a record into the file
void modify_student();  // function to modify record of file
void delete_student();  // function to delete record of file
void class_report();    // function to display whole class result
void display_all();     // function to read all records from file
void display_sp();      // function to read specific record from file

fstream fp;             // global declaration for stream object, object
Student st;

void Student::get_info()
{
  cout<<"Enter Roll No :";
  cin>>rollno;
  cout<<"Enter Name : ";
  cin>>name;
  cout<<"Enter marks in physics : ";
  cin>>p_score;
  cout<<"Enter marks in chemistry : ";
  cin>>c_score;
  cout<<"Enter marks in maths : ";
  cin>>m_score;
  cout<<"Enter marks in english : ";
  cin>>e_score;
  cout<<"Enter marks in computer science : ";
  cin>>cs_score;
  calc();
}

void Student::calc()
{
  percentage=(p_score+c_score+m_score+e_score+cs_score)/5.00;
  if(percentage>=90)
      grade='O';
  else if(percentage>=80 && percentage<90)
      grade='A';
  else if(percentage>=70 && percentage<80)
      grade='B';
  else if(percentage>=50 && percentage<70)
      grade='C';
  else
      grade='F';
}

void Student::show_info()
{
  cout<<"\nRoll No : "<<rollno;
  cout<<"\nName : "<<name;
  cout<<"\nMarks in Physics : "<<p_score;
  cout<<"\nMarks in Chemistry : "<<c_score;
  cout<<"\nMarks in Maths : "<<m_score;
  cout<<"\nMarks in English : "<<e_score;
  cout<<"\nMarks in Computer Science :"<<cs_score;
  cout<<"\nPercentage :"<<setprecision(2)<<percentage<<"%";
  cout<<"\nGrade :"<<grade;
}

void Student::show_row()
{
  cout<<setw(2)<<rollno<<"       "<<name<<"\t\t"<<setw(3)<<p_score<<" "<<setw(3)<<c_score<<" "<<setw(3)<<m_score<<" "<<setw(3)<<e_score<<" "<<setw(3)<<cs_score<<"\t"<<setprecision(4)<<percentage<<"\t    "<<grade<<endl;
}

int Student::get_roll_no()
{
  return rollno;
}

int main()//     Main
{
  char ch;

  system("cls");
  cout<<"\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  cout<<"\t\t  STUDENT REPORT CARD MANAGEMENT  \n";
  cout<<"\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  cout<<"\nPress enter key to continue.";
  getchar();

  do
  {
    system("cls");
    cout<<"*** MAIN MENU *** ";
    cout<<"\n 1) Show Reports";
    cout<<"\n 2) Entry/Edit Reports";
    cout<<"\n 3) Exit";
    cout<<"\nEnter choice (1-3):";
    cin>>ch;

    switch(ch)
    {
    case '1':
      result();
      break;

    case '2':
      entry_menu();
      break;

    case '3':
      cout<<"\nExiting program...";
      exit(0);

    default :
      cout<<"\a\nInvalid option. Press enter key to try again.";
      getchar();
    }
  }
  while(ch!='3');
}

void write_student()
{
  system("cls");
  fp.open("Report.dat",ios::out|ios::app);
  st.get_info();
  fp.write((char*)&st,sizeof(Student));
  fp.close();
  cout<<"\nStudent Record Has Been created";
}

void modify_student()
{
  system("cls");
  int no,flag=0;
  cout<<"Enter Roll No : ";
  cin>>no;
  fp.open("Report.dat",ios::in|ios::out);
  while(fp.read((char*)&st,sizeof(Student)))
  {
    if(st.get_roll_no()==no)
    {
      st.show_info();
      cout<<"\n\nEnter the new Details :"<<endl;
      st.get_info();
      fp.seekp((-1)*sizeof(st),ios::cur);
      fp.write((char*)&st,sizeof(Student));
      cout<<"\nRecord Updated";
      flag=1;
      break;
    }
  }
  fp.close();

  if(flag==0)
      cout<<"\nRecord Not Found ";
}

void delete_student()
{
  int no,flag=0;
  system("cls");
  cout<<"Enter Roll No : ";
  cin>>no;
  fp.open("Report.dat",ios::in|ios::out);
  fstream fp_temp;
  fp_temp.open("Report2.dat",ios::out);
  fp.seekg(0,ios::beg);
  while(fp.read((char*)&st,sizeof(Student)))
  {
    if(st.get_roll_no()!=no)
      fp_temp.write((char*)&st,sizeof(Student));
    else
      flag=1;
  }
  fp_temp.close();
  fp.close();
  remove("Report.dat");
  rename("Report2.dat","Report.dat");

  if(flag==1)
    cout<<"\nRecord Deleted";
  else
    cout<<"\nRecord Not Found ";
}

void entry_menu()
{
  system("cls");
  char ch2;
  cout<<"*** ENTRY/EDIT MENU ***";
  cout<<"\n 1) Create student record";
  cout<<"\n 2) Modify a student record";
  cout<<"\n 3) Delete a student record";
  cout<<"\n 4) Main Menu";
  cout<<"\nEnter choice (1-4):";
  cin>>ch2;
  switch(ch2)
  {
  case '1':
    write_student();
    cout<<"\n\nPress enter key to continue.";
    getchar();
    getchar();
    break;

  case '2':
    modify_student();
    cout<<"\n\nPress enter key to continue.";
    getchar();
    getchar();
    break;

  case '3':
    delete_student();
    cout<<"\n\nPress enter key to continue.";
    getchar();
    getchar();
    break;

  case '4':
    break;

  default:
    cout<<"\a";
    cout<<"\nInvalid option. Press enter key to try again.";
    getchar();
    entry_menu();
  }
}

void class_report()
{
  system("cls");
  fp.open("Report.dat",ios::in);
  if(!fp)
  {
    cout<<"File not found. Enter student details to create file.\nPress enter to continue.";
    getchar();
  }

  cout<<" *** DISPLAYING WHOLE CLASS RESULT ***\n\n";
  cout<<"Roll No  Name\t\t\t P   C   M   E   CS  Percentage  Grade\n\n";

  while(fp.read((char*)&st,sizeof(Student)))
    st.show_row();

  fp.close();
}

void display_all()
{
  system("cls");
  cout<<"*** DISPLAYING ALL RECORDS ***\n";
  fp.open("Report.dat",ios::in);
  while(fp.read((char*)&st,sizeof(Student)))
  {
    st.show_info();
    cout<<"\n";
  }
  fp.close();
}

void display_sp()
{
  system("cls");
  int flag=0,no;
  cout<<"Enter Roll No : ";
  cin>>no;
  fp.open("Report.dat",ios::in);
  while(fp.read((char*)&st,sizeof(Student)))
  {
    if(st.get_roll_no()==no)
    {
      system("cls");
      st.show_info();
      flag=1;
    }
  }
  fp.close();
  if(flag==0)
    cout<<"\nRecord doesn't exist";
}

void result()
{
  char ans;
  system("cls");
  cout<<"*** RESULT MENU ***";
  cout<<"\n 1) Display whole class result";
  cout<<"\n 2) Display all records";
  cout<<"\n 3) Display a specific record ";
  cout<<"\n 4) Main Menu";
  cout<<"\nEnter Choice (1-4): ";
  cin>>ans;

  switch(ans)
  {
  case '1' :
    class_report();
    cout<<"\n\nPress enter key to continue.";
    getchar();
    getchar();
    break;

  case '2':
    display_all();
    cout<<"\n\nPress enter key to continue.";
    getchar();
    getchar();
    break;

  case '3' :
    display_sp();
    cout<<"\n\nPress enter key to continue.";
    getchar();
    getchar();
    break;

  case '4':
    break;

  default:
    cout<<"\a";
    cout<<"\nInvalid option. Press enter key to try again.";
    getchar();
    result();
  }
}
