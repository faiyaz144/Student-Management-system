#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Student {
    string name;
    int rollNo;
    float marks;
};

// Function to add a new student
void addStudent(vector<Student>& students) {
    Student newStudent;
    cout << "Enter student name: ";
    cin.ignore(); // Clear newline character from previous input
    getline(cin, newStudent.name);
    cout << "Enter roll number: ";
    cin >> newStudent.rollNo;
    cout << "Enter marks: ";
    cin >> newStudent.marks;
    students.push_back(newStudent);
    cout << "Student added successfully!" << endl;
}

// Function to display all students
void displayStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students found." << endl;
    } else {
        cout << "-----------------------------------------" << endl;
        cout << "Name\t\tRoll No\tMarks" << endl;
        cout << "-----------------------------------------" << endl;
        for (const Student& student : students) {
            cout << student.name << "\t\t" << student.rollNo << "\t\t" << student.marks << endl;
        }
        cout << "-----------------------------------------" << endl;
    }
}

// Function to search for a student by roll number
void searchStudent(const vector<Student>& students) {
    int rollNo;
    cout << "Enter roll number to search: ";
    cin >> rollNo;
    bool found = false;
    for (const Student& student : students) {
        if (student.rollNo == rollNo) {
            cout << "Student Found:" << endl;
            cout << "Name: " << student.name << endl;
            cout << "Roll No: " << student.rollNo << endl;
            cout << "Marks: " << student.marks << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Student not found." << endl;
    }
}

// Function to delete a student by roll number
void deleteStudent(vector<Student>& students) {
    int rollNo;
    cout << "Enter roll number to delete: ";
    cin >> rollNo;
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->rollNo == rollNo) {
            students.erase(it);
            cout << "Student deleted successfully!" << endl;
            return;
        }
    }
    cout << "Student not found." << endl;
}

// Function to save student data to a file
void saveToFile(const vector<Student>& students) {
    ofstream outfile("students.txt");
    if (outfile.is_open()) {
        for (const Student& student : students) {
            outfile << student.name << "," << student.rollNo << "," << student.marks << endl;
        }
        outfile.close();
        cout << "Data saved to file successfully!" << endl;
    } else {
        cout << "Error: Unable to open file for writing." << endl;
    }
}

// Function to load student data from a file
void loadFromFile(vector<Student>& students) {
    ifstream infile("students.txt");
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            Student student;
            size_t pos1 = line.find(",");
            student.name = line.substr(0, pos1);
            line = line.substr(pos1 + 1);
            size_t pos2 = line.find(",");
            student.rollNo = stoi(line.substr(0, pos2));
            student.marks = stof(line.substr(pos2 + 1));
            students.push_back(student);
        }
        infile.close();
        cout << "Data loaded from file successfully!" << endl;
    } else {
        cout << "Error: Unable to open file for reading." << endl;
    }
}

int main() {
    vector<Student> students;
    int choice;

    // Load data from file (optional)
    loadFromFile(students);

    do {
        cout << "\nStudent Management System" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Display Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Delete Student" << endl;
        cout << "5. Save Data" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                displayStudents(students);
                break;
            case 3:
                searchStudent(students);
                break;
            case 4:
                deleteStudent(students);
                break;
            case 5:
                saveToFile(students);
                break;
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
