
//CHOLOHAN 4/18/2025
//CS300 PROJ2 FINAL


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cctype>
using namespace std;

class course {
public:
    string id;
    string name;
    vector<string> prereq;
};

unordered_map<string, course> courseMap;

//uppercase
string touppercase(string s) {
    for (char& c : s) {
        c = toupper(c);

    }
    return s;
}

// trim 
string trim(string str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");

    if (start == string::npos) return "";
    return str.substr(start, end - start + 1);
}

// load csv file
void loadFile(string file) {
    ifstream in(file);
    if (!in.is_open()) {
        cout << "ERROR" << endl;
        return;
    }

    string line;
    while (getline(in, line)) 
    {
        vector<string> parts;
        stringstream ss(line);
        string piece;

        while (getline(ss, piece, ',')) 
        {
            parts.push_back(trim(piece));
        }

        if (parts.size() < 2) {
            cout << "ERROR" << endl;
            continue;
        }

        course c;
        c.id = touppercase(parts[0]);
        c.name = parts[1];

        for (size_t i = 2; i < parts.size(); i++) {
            c.prereq.push_back(touppercase(parts[i]));
        }

        courseMap[c.id] = c;
    }

    in.close();
}

// check if prereqs exist
void check() {
    for (auto p : courseMap) {
        course c = p.second;

        for (string r : c.prereq) {
            // Skip empty prereqs

            if (r.empty()) {
                continue;
            }

            if (courseMap.find(r) == courseMap.end()) {
                cout << "ERROR: prereq " << r << " not found for " << c.id << endl;
            }
        }
    }
}

// show single course
void showCourse(string id) {
    id = touppercase(id);

    if (courseMap.find(id) == courseMap.end()) {
        cout << "ERROR: Course " << id << " not found" << endl;
        return;
    }

    course c = courseMap[id];
    cout << c.id << ", " << c.name << endl;

    if (c.prereq.size() == 0) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < c.prereq.size(); i++) {
            cout << c.prereq[i];
            if (i < c.prereq.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}

// print all sorted
void showAll() {
    vector<string> ids;
    for (auto p : courseMap) {
        ids.push_back(p.first);
    }

    sort(ids.begin(), ids.end());

    cout << "Sample Schedule:" << endl;
    for (string id : ids) {
        cout << courseMap[id].id << ", " << courseMap[id].name << endl;
    }
}

// menu






void printMenu() {
    cout << endl;
    cout << "1. Load Courses." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
}

int main() {
    string fname;
    bool loaded = false;
    int choice = 0;


    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        printMenu();
        cout << "What would you like to do? ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();                  // clear error
            cin.ignore(1000, '\n');       // throw out bad input
            choice = -1;                  // make it invalid
        }

        if (choice == 1) {
            cout << "Enter file name: ";
            cin >> fname;
            loadFile(fname);
            check();
            loaded = true;
        }

        else if (choice == 2) {
            if (!loaded) {
                cout << "ERROR COURSE DATA NOT LOADED" << endl;
            }
            else {
                showAll();
            }
        }

        else if (choice == 3) {
            if (!loaded) {
                cout << "ERROR COURSE DATA NOT LOADED" << endl;
            }

            else {
                string cid;
                cout << "What course do you want to know about? ";
                cin >> cid;
                showCourse(cid);
            }
        }

        else if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
        }

        else {
            cout << choice << " is not a valid option." << endl;
        }
    }


    return 0;
}

