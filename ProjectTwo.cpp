#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Define Course structure
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

// Global hash table (key = courseNumber, value = Course object)
unordered_map<string, Course> courseTable;

// Helper function to convert string to uppercase for search
string toUpperCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

// Function to load course data from file into hash table. 
void loadFile() {
    courseTable.clear(); // Start fresh

    //hardcoded file name to read - for ease 
    string fileName = "CS 300 ABCU_Advising_Program_Input.csv";
    ifstream file(fileName);

    //Checks that file opened correctly
    if (!file.is_open()) {
        cout << "Could not open file." << endl;
        return;
    }

    //reads each line of the file line by line 
    string line;
    while (getline(file, line)) { 
        vector<string> parts;     // A list to store each part
        string word;
        stringstream ss(line);    // allows line to be broken apart

        while (getline(ss, word, ',')) { // Split the line by commas
            parts.push_back(word);       
        }
    

        // Skip lines with missing info (lines with less than 2 parameters).
        if (parts.size() < 2) {
            continue;
        }

        //Creates Course object and fills in course info.
        Course course;
        course.courseNumber = parts[0];
        course.title = parts[1];

        // Add prerequisites, if any.
        for (int i = 2; i < parts.size(); i++) {
            course.prerequisites.push_back(parts[i]);
        }

        // Add to hash table using course number as key
        courseTable[course.courseNumber] = course;
    }

    // closes file to prevent memory leak
    file.close();
    cout << "Data loaded successfully!" << endl;
}

// Function to print all courses in alphanumeric order
void printCourseList() {
    
    //prevents user to try option before loading data first.
    if (courseTable.empty()) {
        cout << "No data loaded." << endl;
        return;
    }
    
    // List to hold all course numbers 
    vector<string> courseNumbers;

    // Loop to get all course numbers from hash table 
    for (auto pair : courseTable) {
        courseNumbers.push_back(pair.first);
    }

    // Sorts Courses in alphanumeric order
    sort(courseNumbers.begin(), courseNumbers.end());

    // Print each course number and title
    for (string number : courseNumbers) {
        Course course = courseTable[number];
        cout << course.courseNumber << ", " << course.title << endl;
    }
}

// Function to search for a course by number and print details
void searchCourse(string courseNumber) {
    
    //check if course exists
    if (courseTable.find(courseNumber) == courseTable.end()) {
        cout << "Course not found." << endl;
        return;
    }

    // Get course from Hashtable and print course number and title.
    Course course = courseTable[courseNumber];
    cout << course.courseNumber << ", " << course.title << endl;

    //will print prerequisites if any. 
    if (course.prerequisites.empty()) {
        cout << "No Prerequisites" << endl;
    }
    else {
        cout << "Prerequisites: ";
        for (int i = 0; i < course.prerequisites.size(); i++) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

// Function to show menu and handle user input
void displayMenu() {
    int choice = 0;

    while (choice != 9) {
        cout << "\nMenu:" << endl;
        cout << "  1. Load file data into data structure" << endl;
        cout << "  2. Print Course List (alphanumerically ordered)" << endl;
        cout << "  3. Print Course and Prerequisites" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1: //uses hardcoded file
            loadFile();
            break;

        case 2:
            printCourseList();
            break;

        case 3: {
            string courseNumber;
            cout << "Enter course number: ";
            cin.ignore(); // clear leftover newline in buffer to prevent endless loop
            getline(cin, courseNumber); //gets input 
            courseNumber = toUpperCase(courseNumber);
            searchCourse(courseNumber);
            break;
        }

        case 9:
            cout << "Good-bye!" << endl;
            break;

        default:
            cout << "Invalid entry. Try again." << endl;
            break;

        }
    }
}

// Main function to run the program
int main() {
    displayMenu();
    return 0;
}
