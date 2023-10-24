#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
 
using namespace std;
 
int main(){

string choice = "c";
string path;

while(choice == "c"){


    int type;
    int newNumOfRows = 0;
    int newNumOfCols = 0;

    vector<string> row; // one row
    string line, word ,fname , heading;



    cout<<"what type of file do you want to open? \n"
        <<"1. Gas\n"
        <<"2. Particle\n"
        <<"Enter your choice: ";
    cin>>type;

    if(type == 1)
        path = "./data/gas/";
    else if(type == 2)
        path = "./data/particle/";
    else{
        cout<<"Invalid choice";
        continue;
    }

    cout<<"Enter the file name: ";
    cin>>fname;
    fname += ".csv";
    path += fname;

    fstream fileRead (path, ios::in);
    fstream fileWrite ("temp.csv", ios::out);
    
    //check if file can be opened
    if(fileRead.is_open()){
        cout<<fname <<" file successfully opened"<<endl;
    }else{
        cout<<"Unable to open " << fname << " file"<<endl;
        remove( "temp.csv" );
        system("pause");
        return -1;
    }

    //remove rows
    getline(fileRead, heading); //store heading
    while(getline(fileRead, line)){

        row.clear();

        stringstream str(line+','); // add , to make the sorting easier
        while(getline(str, word, ','))
            row.push_back(word);

        int checkForEmptyCol = 0; // check for empty rows

        for( int i = 1; i < row.size(); i++){
            if(row[i].empty()){
                checkForEmptyCol++;
            }
        }

        if(checkForEmptyCol != row.size()-1){ 

            for(int i = 0; i < row.size(); i++){
                fileWrite << row[i];
                if(i != row.size()-1)
                    fileWrite << ",";
            }
            fileWrite << "\n";
        }

    }
    fileRead.close();
    fileWrite.close();

    // remove colomns
    fstream fileRead2 ("temp.csv", ios::in);
    fstream fileWrite2 ("temp2.csv", ios::out);
    
     vector<int> finalCol;
     int checkEmptyCol [row.size()] = {0};


    //check for empty colomns
    while(getline(fileRead2, line)){

        row.clear();
        
        stringstream str(line + ','); // add , to make the sorting easier
        while(getline(str, word, ','))
            row.push_back(word);


        for( int i = 0; i < row.size(); i++){
   
            if(row[i].empty()){

            }else{
                checkEmptyCol[i] = 1;
            }
        }
    }

    //arry with colom indexs that are not empty
    for( int i = 0; i < sizeof(checkEmptyCol)/sizeof(int); i++){

        if(checkEmptyCol[i] == 1){
   
                finalCol.push_back(i);
        }
    }

    fileRead2.close();
    fileWrite2.close();


   
    fstream fileRead3 ("temp.csv", ios::in);
    fstream fileWrite3 ("temp2.csv", ios::out);

    while(getline(fileRead3, line)){
        
        row.clear();

        stringstream str(line +','); // add , to make the sorting easier
        while(getline(str, word, ','))
            row.push_back(word);

        for( int i = 0; i < finalCol.size(); i++){
            newNumOfCols = finalCol.size();
            fileWrite3 << row[finalCol[i]];
            if(i != finalCol.size()-1)
                fileWrite3 << ",";
        }
        fileWrite3 << "\n";
        newNumOfRows++;
    }


 

    fileRead3.close();
    fileWrite3.close();
    //remove temp file

    /**********calculate highest and lowest****************/

    fstream fileRead4 ("temp2.csv", ios::in);

    int counter = 0;
    float highest [newNumOfCols] = {0}; //we are gonna ignore colomn number 1 beacause it is a date
    float loweset [newNumOfCols] = {100}; //we are gonna ignore colomn number 1 beacause it is a date
    float dailyAverage [newNumOfCols] = {0}; 
    string highestDate [newNumOfCols];
    string lowesetDate [newNumOfCols];

    for(int i = 1; i < newNumOfCols; i++){
        loweset[i] = 100.00;
    }

    while(getline(fileRead4 , line)){
        row.clear();
        stringstream str(line +','); // add , to make sorting easier
        while(getline(str, word, ','))
            row.push_back(word);

        for(int i = 1; i < row.size(); i++){
            if(row[i].empty()){

            }else{
                dailyAverage[i] += stof(row[i]);

                if( stof(row[i]) < loweset[i] ){
                    loweset[i]  = stof(row[i]);
                    lowesetDate[i] = row[0];
                }
                    
                if( stof(row[i]) > highest[i] ){
                    highest[i]  = stof(row[i]);
                    highestDate[i] = row[0];
                }

            }
        }

    }

    fileRead4.close();

    cout<<"\n"<<endl;
    
    for(int i = 1; i < newNumOfCols; i++){
        cout<<"maximum of value of col " << i+1 << " is : " <<  highest[i] << " on " <<highestDate[i] << endl;
        cout<<"minimum of value of col " << i+1 << " is : " <<  loweset[i] << " on " <<lowesetDate[i] << endl;
        // cout<<"average of value of col " << i+1 << " is : " <<  dailyAverage[i]/newNumOfRows << endl;
        cout<<endl;
    }

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

        while(getline(str2, word, ' ')){
            row.insert(row.begin()+1, word);
            
        }
            string temp = row[1]; 
            row[1] = row[2];
            row[2] = temp; // swap data and time

        for( int i = 1; i < row.size(); i++){
            newNumOfCols = row.size();
            fileWrite5 << row[i];
            if(i != row.size()-1)
                fileWrite5 << ",";
        }
        fileWrite5 << "\n";

    }
    fileRead5.close();
    fileWrite5.close();

    cout << "Total number of rows: " << newNumOfRows << endl;
    cout << "Total number of cols: " << newNumOfCols-1<< endl; //-1 because we split the date and time
    
    /************************Write output data*************************/

    fstream fileWrite6 (path + fname +"-output.csv", ios::out);
    fstream fileWrite7 (path + fname +"-dailyAverage.csv", ios::out);

    fileWrite6 << "File tested: " << fname << endl;
    fileWrite6 << "Total number of rows: " << newNumOfRows << endl;
    fileWrite6 << "Total number of cols: " << newNumOfCols-1<< endl;

    for(int i = 2; i < newNumOfCols-1; i++){
        fileWrite6<<endl;
        fileWrite6<<"maximum of value of col " << i+1 << " is : " <<  highest[i-1] << " on " <<highestDate[i-1] << endl;
        fileWrite6<<"minimum of value of col " << i+1 << " is : " <<  loweset[i-1] << " on " <<lowesetDate[i-1] << endl;
        // fileWrite6<<"average of value of col " << i+1 << " is : " <<  dailyAverage[i-1]/newNumOfRows << endl;
        // fileWrite7<<"average of value of col " << i+1 << " is : " <<  dailyAverage[i-1]/newNumOfRows << endl;
        fileWrite6<<endl;
    }



    fileWrite6.close();
    fileWrite7.close();

    /*************************get average of each day**********************/

    fstream fileWrite8 ("dailyAverage.csv", ios::out);
    fstream fileRead8 (path + fname + "-processed.csv", ios::in);
    string  day = "";
    string temp = "1";
    vector<vector<string>> dates;
    int counter2 = 0;

    while(getline(fileRead8 , line)){
        
        row.clear();
        stringstream str(line +','); // add , to make sorting easier
        while(getline(str, word, ',')){
            row.push_back(word);
        }
        day = row[0];

        if(temp != day){
            dates.push_back(row[0]);
            temp = day;
        }

    }

    for (int i = 0; i < dates.size(); i++)
    {
       cout<<dates[i][0]<<endl;
    }
    

    /***********************Remove temp file*************************/


    remove("temp2.csv");
    remove("temp.csv"); 

    
    cout<<"Press c to continue or e to quit"<<endl;
    cin>>choice;

    }

}