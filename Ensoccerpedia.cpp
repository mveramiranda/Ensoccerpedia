//Ensoccerpedia: this program uses two data structure, a hash table and a bst, to compare their perfomance when doing the same tasks
//It reads from 4 different soccer data sets of 4 different leagues and can search for specific matches or a team's performance in one season
//Authors: Eitan Kogutek and Manuel Vera Miranda
//Special acknowledgement to James Curley who compiled the datasets used here for his R packet "engsoccerdata"
//It can be found in https://github.com/jalapic/engsoccerdata

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Hash.h"
#include "redBlackTree.h"
using namespace std;

//function to run the program using the hash table
void mainHash() {
    cout << "Welcome to the Ensoccerpedia!" << endl;
    cout << "An accessible soccer database with over 290,000 historical results from Europe's top 4 leagues" << endl;
    cout << "To begin, select which league you would like to explore: " << endl;
    cout << "1. England (available 1888-1889 to 2019-2020) \n2. Spain (available 1928-1929 to 2019-2020)" << endl;
    cout << "3. Italy (available 1934-1935 to 2019-2020) \n4. Germany (available 1963-1964 to 2019-2020)" << endl;

    short selection;
    cin >> selection;

    string fileName;
    int hashSize = 0;

    switch (selection) {
    case 1:
        fileName = "england.csv";
        hashSize = 199884;
        cout << "You have chosen the English league.";
        break;
    case 2:
        fileName = "spain.csv";
        hashSize = 25435;
        cout << "You have chosen the Spanish league.";
        break;
    case 3:
        fileName = "italy.csv";
        hashSize = 26924;
        cout << "You have chosen the Italian league.";
        break;
    case 4:
        fileName = "germany.csv";
        hashSize = 35858;
        cout << "You have chosen the German league.";
        break;
    default:
        cout << "Invalid input! Please try running the program again" << endl;
        exit(0);
    }

    cout << "There are " << hashSize << " games in the database." << endl;

    Hash hash = Hash(hashSize);

    ifstream spain(fileName);
    string line;
    getline(spain, line);
    while (getline(spain, line, ',')) {
        string date = line;
        getline(spain, line, ',');
        int season = stoi(line);
        getline(spain, line, ',');
        string homeTeam = line;
        getline(spain, line, ',');
        string awayTeam = line;
        getline(spain, line, ',');
        getline(spain, line, ',');
        getline(spain, line, ',');
        int hGoals = stoi(line);
        getline(spain, line, ',');
        int aGoals = stoi(line);
        getline(spain, line, ',');
        getline(spain, line, ',');
        getline(spain, line, ',');
        getline(spain, line, '\n');
        Game game(date, season, homeTeam, awayTeam, hGoals, aGoals);

        hash.Insert(season, game);
    }

    cout << "Which action would you like to perform?" << endl;

    cout << "1. Specific match (requires season year and home and away teams)" << endl;
    cout << "2. Season records (requires season year and team)" << endl;

    cin >> selection;
    int season = 0;
    string home = "";
    string away = "";
    Game found;

    switch (selection) {
        case 1:
            cout << "Please enter the season year (i.e. for 2018-19 season enter 2018)" << endl;
            cin >> season;

            cout << "Please enter the home team" << endl;

            cin.ignore();
            getline(cin, home);
            home = "\"" + home + "\"";

            cout << "Please enter the away team" << endl;

            getline(cin, away);
            away = "\"" + away + "\"";

            cout << "\nSearching..." << endl << endl;

            found = hash.Search(season, home, away);

            cout << "Game found!" << endl;
            cout << "Date: " << found.date << endl;
            cout << "Teams: " << found.homeTeam.substr(1, found.homeTeam.size() - 2) << " - " << found.awayTeam.substr(1, found.awayTeam.size() - 2) << endl;
            cout << "Result: " << found.hGoals << "-" << found.aGoals << endl << endl;

            break;
        case 2:
            cout << "Please enter the season year (i.e. for 2018-19 season enter 2018)" << endl;
            cin >> season;

            cout << "Please enter the team you would like to search the record for: " << endl;

            cin.ignore();
            getline(cin, home);

            hash.Search(season, home);
            break;


        default:
            cout << "Invalid input! Please try running the program again" << endl;
            exit(0);
    }
}

//function to run the program using the binary search tree
void mainTree() {
    cout << "Welcome to the Ensoccerpedia!" << endl;
    cout << "An accessible soccer database with over 290,000 historical results from Europe's top 4 leagues" << endl;
    cout << "To begin, select which league you would like to explore: " << endl;
    cout << "1. England (available 1888-1889 to 2019-2020) \n2. Spain (available 1928-1929 to 2019-2020)" << endl;
    cout << "3. Italy (available 1934-1935 to 2019-2020) \n4. Germany (available 1963-1964 to 2019-2020)" << endl;

    short selection;
    cin >> selection;

    string fileName;
    int hashSize = 0;

    switch (selection) {
    case 1:
        fileName = "england.csv";
        hashSize = 199884;
        cout << "You have chosen the English league.";
        break;
    case 2:
        fileName = "spain.csv";
        hashSize = 25435;
        cout << "You have chosen the Spanish league.";
        break;
    case 3:
        fileName = "italy.csv";
        hashSize = 26924;
        cout << "You have chosen the Italian league.";
        break;
    case 4:
        fileName = "germany.csv";
        hashSize = 35858;
        cout << "You have chosen the German league.";
        break;
    default:
        cout << "Invalid input! Please try running the program again" << endl;
        exit(0);
    }

    cout << "There are " << hashSize << " games in the database." << endl;

    redBlackTree tree;

    ifstream spain(fileName);
    string line;
    getline(spain, line);
    while (getline(spain, line, ','))
    {
        string date = line;
        getline(spain, line, ',');
        int season = stoi(line);
        getline(spain, line, ',');
        string homeTeam = line;
        getline(spain, line, ',');
        string awayTeam = line;
        getline(spain, line, ',');
        getline(spain, line, ',');
        getline(spain, line, ',');
        int hGoals = stoi(line);
        getline(spain, line, ',');
        int aGoals = stoi(line);
        getline(spain, line, ',');
        getline(spain, line, ',');
        getline(spain, line, ',');
        getline(spain, line, '\n');
        Game game(date, season, homeTeam, awayTeam, hGoals, aGoals);

        tree.insert(season, game);
    }

    cout << "Which action would you like to perform?" << endl;

    cout << "1. Specific match (requires season year and home and away teams)" << endl;
    cout << "2. Season records (requires season year and team)" << endl;

    cin >> selection;
    int season = 0;
    string home = "";
    string away = "";
    Game found;

    switch (selection) {
    case 1:
        cout << "Please enter the season year (i.e. for 2018-19 season enter 2018)" << endl;
        cin >> season;

        cout << "Please enter the home team" << endl;

        cin.ignore();
        getline(cin, home);
        home = "\"" + home + "\"";

        cout << "Please enter the away team" << endl;

        getline(cin, away);
        away = "\"" + away + "\"";

        cout << "\nSearching..." << endl << endl;

        found = tree.search(season, home, away);

        cout << "Game found!" << endl;
        cout << "Date: " << found.date << endl;
        cout << "Teams: " << found.homeTeam.substr(1, found.homeTeam.size() - 2) << " - " << found.awayTeam.substr(1, found.awayTeam.size() - 2) << endl;
        cout << "Result: " << found.hGoals << "-" << found.aGoals << endl << endl;

        break;
    /*case 2:
        cout << "Please enter the season year (i.e. for 2018-19 season enter 2018)" << endl;
        cin >> season;

        cout << "Please enter the team you would like to search the record for: " << endl;

        cin.ignore();
        getline(cin, home);

        hash.Search(season, home);
        break;*/


    default:
        cout << "Invalid input! Please try running the program again" << endl;
        exit(0);
    }
}

int main() {
    
    cout << "Select which data structure to run the program with " << endl;
    cout << "1. Hash Table (uses a hash table of maps)" << endl;
    cout << "2. Binary Search Tree (uses a red-black tree of maps)" << endl;

    int selection;

    cin >> selection;

    //runs the program depending on which data structure was chosen
    if (selection == 1) {
        mainHash();
    }
    else if (selection == 2) {
        mainTree();
    }

    return 0;
}

