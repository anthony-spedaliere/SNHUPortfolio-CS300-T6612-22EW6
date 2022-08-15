//============================================================================
// Name        : Main.cpp
// Author      : Anthony Spedaliere
// Version     : 1.0.0
// Copyright   : Copyright © 8/6/2022 
// Description : Project 2 CS300
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ostream>
#include <iomanip>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// define a structure to hold course information
struct Course {
	string courseNumber;
	string courseName;
	vector<string> prereq;
};

// vector to hold the course data
vector<Course> courses;

//============================================================================
// methods 
//============================================================================

/**
 * Load a text file containing courses into a container
 *
 * @param courses reference to a vector of type Course
 * @param fileName the local file name of the file to load
 * @return a container holding all the bids read
 */

int loadCourseData(vector<Course> &courses, string fileName) {
	// instantiate file stream variable
	ifstream inFS;

	// open text document
	inFS.open(fileName);

	// error handling if the file does not exist or is in use by another program
	if (!inFS.is_open()) {
		cout << "Could not open the file. Please restart." << endl;
		return 1; // indicates error
	}

	// read data
	string myChar;
	while (inFS) {
		// declare a new course object
		Course course;
		// declare a new string object to hold next line of file
		string line;
		// get the next line
		getline(inFS, line);
		// position tracker
		int pos = 0;
		// delimiter to look for in string
		string delim = ",";
		// counter for commas
		int counter = 0;
		// iterate over line of text file and save information into course object
		while ((pos = line.find(delim)) != string::npos) {
			if (counter == 0) {
				course.courseNumber = line.substr(0, pos);
				line.erase(0, pos + delim.length());
				counter++;
			}
			else if (counter == 1) {
				course.courseName = line.substr(0, pos);
				line.erase(0, pos + delim.length());
				counter++;
			}
			else {
				course.prereq.push_back(line.substr(0, pos));
				line.erase(0, pos + delim.length());
				
			}
		}
		// get last line of data after last comma delimiter
		if (counter == 1) {
			course.courseName = line.substr(0, pos);
			line.erase(0, pos + delim.length());
			counter++;
		}
		else {
			course.prereq.push_back(line.substr(0, pos));
			line.erase(0, pos + delim.length());
		}
		courses.push_back(course);
	}

	// close the open file
	inFS.close();

	cout << "Data succesfully loaded." << endl;

	return 0;
}

/**
 * Print the menu
 *
 * @param none
 * @return none
 */
void printMenu() {
	cout << "------------------------------" << endl;
	cout << "Menu:" << endl;
	cout << "  1. Load Data Structure" << endl;
	cout << "  2. Print Course List" << endl;
	cout << "  3. Print Course" << endl;
	cout << "  4. Exit" << endl;
	cout << "------------------------------" << endl;
	cout << "Enter choice: ";
}

/**
 * Get the text file name from the user
 *
 * @param none
 * @return none
 */
string getString() {
	string userInput = "";
	bool loopVar = true;

	while (loopVar) {
		cin >> userInput;

		if (!cin) {
			cin.clear(); // reset failbit
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			loopVar = false;
		}

		continue;
	}
	return userInput;
}

/**
 * Retrieve the user input
 *
 * @param none
 * @return none
 */
double getMenuChoice() {
	int valueInput = 0;
	bool loopVar = true;

	while (loopVar) {
		cin >> valueInput;

		if (!cin) {
			cin.clear(); // reset failbit
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (valueInput > 0 && valueInput <= 4) {
			loopVar = false;
		}
		else if (valueInput <= 0 && valueInput > 4) {
			cout << "Please enter a number between 1 and 4." << endl;
			continue;
		}

		continue;
	}
	return valueInput;
}

/**
 * Sort the complete course list in alphanumeric order
 *
 * @param reference to the courses vector
 * @return none
 */

void sortCourses(vector<Course>& courses) {
	int size = courses.size();
	int min;

	for (int i = 0; i < size - 1; i++) {
		min = i;
		for (int j = i + 1; j < size; j++) {
			if (courses[j].courseNumber.compare(courses[min].courseNumber) < 0) {
				min = j;
			}
		}
		if (min != i) {
			swap(courses.at(i), courses.at(min));
		}
	}
}

/**
 * Display course list in alphanumeric order
 *
 * @param reference to the course object
 * @return none
 */

void displayBids(Course course) {
	cout << course.courseNumber << ", " << course.courseName << endl;
	return;
}

/**
 * Display a requested course as entered by the user
 *
 * @param reference to the course object
 * @return none
 */

void displayCourse(string courseName) {
	Course course;
	bool courseNotFound = true;
	// convert user input uppercase
	for (int i = 0; i < courseName.length(); i++) {
		courseName[i] = toupper(courseName[i]);
	}

	for (int i = 1; i < courses.size(); i++) {
		if (courseName == courses.at(i).courseNumber) {
			cout << "------------------------------" << endl;
			cout << "Course Name: " << courses.at(i).courseNumber << ", " << courses.at(i).courseName << endl;
			cout << "Prequisites:" << endl;				
				for (int j = 0; j < courses.at(i).prereq.size(); j++) {
					cout << courses.at(i).prereq.at(j) << endl;
				}
				if (courses.at(i).prereq.size() == 0) {
					cout << "None" << endl;
				}
			cout << "------------------------------" << endl;
			courseNotFound = false;
			break;
		}
	}
	if (courseNotFound) {
		cout << "That course was not found. Please try again." << endl;
		cout << "------------------------------" << endl;
	}
}


int main() {
	cout << "Welcome to the Course Planner" << endl;
	cout << "------------------------------" << endl;
	cout << "Enter the name of the text file in the following format: filename.txt" << endl;
	cout << "------------------------------" << endl;
	cout << "Enter: ";
	string filename = getString();
	bool loadDataCheck = true;

	printMenu();

	while (true) {
		try {
			int userInput = getMenuChoice();

			if (userInput == 1) {
				if (loadDataCheck) {
					loadCourseData(courses, filename);
					printMenu();
					loadDataCheck = false;
					continue;
				}
				else {
					cout << "------------------------------" << endl;
					cout << "Data already loaded. Please choose another option or restart to load other data." << endl;
					cout << "Enter: ";
				}

			}
			else if (userInput == 2) {
				sortCourses(courses);
				for (int i = 1; i < courses.size(); i++) {
					displayBids(courses[i]);
				}
				cout << endl;
				printMenu();
				continue;
			}
			else if (userInput == 3) {
				cout << "------------------------------" << endl;
				cout << "Enter the course number in the following format: CSCI100" << endl;
				cout << "------------------------------" << endl;
				cout << "Enter: ";
				string courseNameUserInput = getString();
				displayCourse(courseNameUserInput);
				printMenu();
				continue;
			}
			else {
				cout << "Thank you for the course planner!" << endl;
				break;
			}
		}
		catch (runtime_error& excpt) {
			cout << excpt.what() << endl;
			cout << "Error caught in main." << endl;
		}
	}
	return 0;
}