#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

enum class FileType { Gas, Particle };


void cleanData(const string& inputPath, const string& outputPath);

void calculateStatistics(const string& inputPath);

void splitDateAndTime(const string& inputPath, const string& outputPath);

int main() {
    string choice = "c";

    while (choice == "c") {
        FileType fileType;
        string path, fname;

        cout << "Turing Moore Engineering Environmental Data Analyser 1.0" << endl;
        cout << "Your name" << endl;
        cout << "221202072" << endl;
        cout << "02/09/2022" << endl;
        cout << "Level of mark - HD" << endl;
        cout << "How to use the program" << endl;
        cout << "* Enter the name of the file, e.g., test3" << endl;

        cout << "What type of file do you want to open?" << endl;
        cout << "1. Gas" << endl;
        cout << "2. Particle" << endl;
        cout << "Enter your choice: ";
        int typeChoice;
        cin >> typeChoice;

        if (typeChoice == 1)
            fileType = FileType::Gas;
        else if (typeChoice == 2)
            fileType = FileType::Particle;
        else {
            cout << "Invalid choice" << endl;
            continue;
        }

        cout << "Enter the file name: ";
        cin >> fname;
        fname += ".csv";

        if (fileType == FileType::Gas)
            path = "./data/gas/";
        else if (fileType == FileType::Particle)
            path = "./data/particle/";

        string fullPath = path + fname;

        ifstream fileRead(fullPath);
        if (!fileRead.is_open()) {
            cout << "Unable to open " << fname << " file" << endl;
            system("pause");
            return -1;
        }

        // Clean data
        string tempOutputPath = "temp.csv";
        cleanData(fullPath, tempOutputPath);

        // Calculate statistics
        calculateStatistics(tempOutputPath);

        // Split date and time
        string processedOutputPath = "processed.csv";
        splitDateAndTime(tempOutputPath, processedOutputPath);

        cout << "Data processing completed." << endl;

        // Remove temporary files
        remove(tempOutputPath.c_str());

        cout << "Press 'c' to continue or 'e' to quit: ";
        cin >> choice;
    }

    return 0;
}

void cleanData(const string& inputPath, const string& outputPath) {
    ifstream fileRead(inputPath);
    ofstream fileWrite(outputPath);

    if (!fileRead.is_open()) {
        cout << "Unable to open input file for cleaning" << endl;
        return;
    }

    string heading;
    getline(fileRead, heading); // Store heading
    fileWrite << heading << endl; // Write heading to output

    string line;
    while (getline(fileRead, line)) {
        vector<string> row;
        stringstream str(line + ',');
        string word;
        while (getline(str, word, ','))
            row.push_back(word);

        int checkForEmptyCol = 0;
        for (int i = 1; i < row.size(); i++) {
            if (!row[i].empty()) {
                checkForEmptyCol++;
            }
        }

        if (checkForEmptyCol != row.size() - 1) {
            for (int i = 0; i < row.size(); i++) {
                fileWrite << row[i];
                if (i != row.size() - 1)
                    fileWrite << ",";
            }
            fileWrite << endl;
        }
    }

    fileRead.close();
    fileWrite.close();
}

void calculateStatistics(const string& inputPath) {
    ifstream fileRead(inputPath);

    if (!fileRead.is_open()) {
        cout << "Unable to open input file for calculating statistics" << endl;
        return;
    }

    string line;
    getline(fileRead, line); // Skip heading

    int newNumOfCols = 0;
    vector<float> highest, lowest, dailyAverage;
    vector<string> highestDate, lowestDate;
    bool initialized = false;

    while (getline(fileRead, line)) {
        vector<string> row;
        stringstream str(line + ',');
        string word;
        while (getline(str, word, ','))
            row.push_back(word);

        if (!initialized) {
            newNumOfCols = row.size() - 1;
            highest.resize(newNumOfCols);
            lowest.resize(newNumOfCols, 100.0);
            dailyAverage.resize(newNumOfCols);
            highestDate.resize(newNumOfCols);
            lowestDate.resize(newNumOfCols);
            initialized = true;
        }

        for (int i = 1; i < row.size(); i++) {
            if (!row[i].empty()) {
                float value = stof(row[i]);
                dailyAverage[i - 1] += value;

                if (value < lowest[i - 1]) {
                    lowest[i - 1] = value;
                    lowestDate[i - 1] = row[0];
                }

                if (value > highest[i - 1]) {
                    highest[i - 1] = value;
                    highestDate[i - 1] = row[0];
                }
            }
        }
    }

    cout << "\nStatistics:\n" << endl;

    for (int i = 0; i < newNumOfCols; i++) {
        cout << "Maximum of value of col " << i + 1 << " is: " << highest[i] << " on " << highestDate[i] << endl;
        cout << "Minimum of value of col " << i + 1 << " is: " << lowest[i] << " on " << lowestDate[i] << endl;
        cout << "Average of value of col " << i + 1 << " is: " << dailyAverage[i] / newNumOfCols << endl;
        cout << endl;
    }




    std::cout << "Enter the initial velocity of the object (m/s): ";
    std::cin >> u;

    std::cout << "Enter the angle of projection (degrees): ";
    std::cin >> angle_degrees;

    double angle_rad = angle_degrees * M_PI / 180.0;

    double height = calculateHeight(u, angle_rad);
    double time_of_flight = calculateTimeOfFlight(u, angle_rad);
    double range = calculateRange(u, angle_rad);

    std::cout << "Initial velocity: " << u << " m/s\n";
    std::cout << "Launch angle: " << angle_degrees << " degrees\n";
    std::cout << "Height of the projectile: " << height << " meters\n";
    std::cout << "Time of flight: " << time_of_flight << " seconds\n";
    std::cout << "Horizontal range: " << range << " meters\n";
    /******************splitng date and time*************************/
    
    fstream fileRead5 ("temp2.csv", ios::in);
    if(type == 1)
        path = "output/gas/";

    else
        path = "output/particle/";

    fstream fileWrite5 (path + fname + "-processed.csv", ios::out);

    while(getline(fileRead5 , line)){
        
        row.clear();
        stringstream str(line +','); // add , to make sorting easier
        while(getline(str, word, ',')){
            row.push_back(word);
        }
        stringstream str2(row[0]); 

    fileRead.close();
}


void splitDateAndTime(const string& inputPath, const string& outputPath) {
    ifstream fileRead(inputPath);
    ofstream fileWrite(outputPath);

    if (!fileRead.is_open()) {
        cout << "Unable to open input file for splitting date and time" << endl;
        return;
    }

    string line;
    while (getline(fileRead, line)) {
        vector<string> row;
        stringstream str(line + ',');
        string word;
        while (getline(str, word, ','))
            row.push_back(word);

        stringstream str2(row[0]);
        string date, time;
        str2 >> date >> time;
        row.erase(row.begin());
        row.insert(row.begin() + 1, date);
        row.insert(row.begin() + 2, time);

        for (int i = 0; i < row.size(); i++) {
            fileWrite << row[i];
            if (i != row.size() - 1)
                fileWrite << ",";
        }
        fileWrite << endl;
    }

    fileRead.close();
    fileWrite.close();
}
