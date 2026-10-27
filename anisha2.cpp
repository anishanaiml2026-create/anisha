#include <iostream>
using namespace std;
class Student
{
    int rollNo;
    string name;
    public:
    student(int r, string n)
    {
        rollNo = r;
        name = n;
        count << "student object created" << endl;
    }
    void display()
    {
        count << "Roll Number:" << rollNo << endl;
        count << "Name:" << name << endl;
    }
    ~student()
    {
        cout << "student object destroyed" << endl;
    }
};
int main()
    {
        student s1(101,"Arun");
        s1.display();
        return 0;
    }


