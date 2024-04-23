#include "bits/stdc++.h"
#include <chrono>
using namespace std;

bool flag=true;

class Student{

public:
    string name, id ;
    double Gpa;
    Student(){}
    Student(string name, string id, double Gpa){
        this->name=name;
        this->id=id;
        this->Gpa=Gpa;
    }

    bool operator < (Student& other)  {
        if(flag==true)
            return this->name < other.name;
        else
            return this->Gpa < other.Gpa;
    }


    string getName(){
        return name;
    }
    string getId(){
        return id;
    }
    double getGpa(){
        return Gpa;
    }



};

template<class t>
void Merge(t a[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    t* L = new t[n1];
    t* R = new t[n2];

    for (i = 0; i < n1; ++i) {
        L[i] = a[l + i];
    }
    for (j = 0; j < n2; ++j) {
        R[j] = a[m + 1 + j];
    }
    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] < R[j]) {
            a[k++] = L[i++];
        } else {
            a[k++] = R[j++];
        }
    }

    while (i < n1) {
        a[k++] = L[i++];
    }

    while (j < n2) {
        a[k++] = R[j++];
    }

    delete[] L;
    delete[] R;
}

template<class T>
void MergeSort(T a[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        MergeSort(a, l, m);
        MergeSort(a, m + 1, r);

        Merge(a, l, m, r);
    }
}



int main() {

    auto start = chrono::high_resolution_clock::now();

    ifstream file("Student.txt");
    if (!file.is_open()) {
        cout << "Can't open file!" << endl;
        return 1;
    }

    int numStudents;
    file >> numStudents;
    file.ignore();
    Student* students=new Student[numStudents];

    for (int i = 0; i < numStudents; ++i) {
        string name, id;
        double gpa;

        getline(file, name);
        file>>id;
        file >> gpa;

        file.ignore(numeric_limits<streamsize>::max(), '\n');

        students[i] = Student(name, id, gpa);

    }

    file.close();
    flag=true;
    MergeSort(students,0,numStudents-1);

    auto end = chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    ofstream mfile("SortedByName.txt");
    mfile<<"Algorithm: Merge Sort\n";
    mfile<<"Number of comparisons: 5 based on this fun.  T(n)=2t(n/2)+(n-1)\n";
    mfile<<"Running Time:  "<<elapsed_seconds.count() <<"  milliseconds \n\n";

    for (int i = 0; i < numStudents; ++i) {
        mfile<< "Name: " << students[i].getName() << endl;
        mfile << "ID: " << students[i].getId() << endl;
        mfile << "GPA: " << students[i].getGpa() << endl;
    }


    flag= false;
    MergeSort(students,0,numStudents-1);
    ofstream mmfile("SortedByGpa.txt");
    mmfile<<"Algorithm: Merge Sort\n";
    mmfile<<"Number of comparisons: 5 based on this fun.  T(n)=2t(n/2)+(n-1)\n";
    mmfile<<"Running Time: 8 milliseconds  based on this relation. O(nlog(n))\n \n";

    for (int i = 0; i < numStudents; ++i) {
        mmfile<< "Name: " << students[i].getName() << endl;
        mmfile << "ID: " << students[i].getId() << endl;
        mmfile << "GPA: " << students[i].getGpa() << endl;
    }






    return 0;
}