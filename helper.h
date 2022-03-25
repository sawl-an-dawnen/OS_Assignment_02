#ifndef HELPER_H
#define HELPER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct process {
    int deadline;
    int computationTime;
    vector<string> instructions;
};

struct resource {
    string type;

};

class Manager {
    public:
    bool isMatrix = true;
    int r; //number of resources
    int p; //number of processes
    vector<int> available; //number of available resources from resource 1, 2, ... r
    vector<vector<int>> max; //maximum demand for resource r by process n. takes the form max[n,m]
    vector<process> processes; //a vector of processes with deadlines, compTimes, and their instructions
    void initilize(string argument); //argument is the argv[1] from the input
    void initilize_alt(string argument); //argument is argv[1]
};

void Manager::initilize (string argument) {
    ifstream input(argument);
    string temp;

    //number of resources
    getline(input, temp);
    r = stoi(temp);
    cout <<"r: " << r << endl;

    //number of processes
    getline(input, temp);
    p = stoi(temp);
    cout <<"p: " << p << endl << endl;

    //first line of available[] input, will determine if isMatrix remains true;
    getline(input, temp);
    if (temp.find("available") != string::npos) {
        isMatrix = false;
    }

    if(!isMatrix) {
        //call alternative initilize
        initilize_alt(argument);
        return;
    }

    //matrix info
    while(temp.find("process") == string::npos) {
        getline(input, temp);
        cout << temp << endl;
    }
    cout << endl << endl;
    cout << temp;

    /*
    while(!input.eof()) {
        getline(input, temp);
        cout << temp << endl;
    }
    */

    return;
}

void Manager::initilize_alt (string argument) {
    ifstream input(argument);
    string temp;

    cout << "Enter alternative initilize function." << endl << endl;

    //number of resources
    getline(input, temp);
    r = stoi(temp);
    cout <<"r: " << r << endl;

    //number of processes
    getline(input, temp);
    p = stoi(temp);
    cout <<"p: " << p << endl << endl;

    //matrix info
    cout << "matrix info:" << endl;
    //available
    cout << "available:" << endl;
    for(int i = 0; i < r; i++)  {
        getline(input, temp);
        cout << temp << endl; 
    }
    //max
    cout << "max:" << endl;
    for(int i = 0; i < p; i++)  {
        for (int j = 0; j < r; j++) {
            getline(input, temp);
            cout << i << " " << j << " " << temp << endl; 
        }
    }

    while(temp.find("process") == string::npos) {//first occurance of a process
        getline(input, temp);
        if(temp.find("process") != string::npos) {continue;}
        cout << temp << endl;
    }
    cout << endl;
    cout << temp << endl;

    while(!input.eof()) {
        getline(input, temp);
        cout << temp << endl;
    }

    return;
}

#endif