#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

bool validated;
struct administrator {
    char name[20];
    char password[20];
};
struct Pirate{
    char name[35];
    char crew[50];
    char combatAbility[20];
    bool haki;

    float  bounty;
    string bountyMagnitude;

};
struct Marine{
    char name[20];
    char rank[20];
    char combatAbility[20];
    bool haki;
};

struct Revolutionary{
    char name[20];
    char rank[20];
    char combatAbility[20];
    bool haki;

    float bounty;
    string bountyMagnitude;
};
struct DBSystem{
    string currentUserName;
    vector<Pirate> pirates;
    vector<Marine> marines;
    vector<Revolutionary> revolutionaries;
};



vector<administrator> LoadAdmins(){
    //This loads the admins from the csv file
    ifstream inputFile("admins.csv");
    if(!inputFile.is_open()){
        cout << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }
    vector<administrator> admins;
    string line;
    while(getline(inputFile, line)){
        administrator admin;
        stringstream ss(line);
        ss.getline(admin.name, 20, ',');
        ss.getline(admin.password, 20, ',');
        admins.push_back(admin);
    }
    inputFile.close();
    return admins;

}
vector<Pirate> loadPirates() {
    // This loads the pirates from the CSV file
    ifstream inputFile("pirates.csv");
    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }
    vector<Pirate> pirates;
    string line;
    while (getline(inputFile, line)) {
        Pirate pirate;
        stringstream ss(line);
        ss.getline(pirate.name, 35, ',');
        ss.getline(pirate.crew, 50, ',');
        ss.getline(pirate.combatAbility, 20, ',');
        ss >> pirate.haki;
        ss.ignore();
        ss >> pirate.bounty;
        ss.ignore();
        ss >> pirate.bountyMagnitude;
        pirates.push_back(pirate);
    }
    inputFile.close();
    return pirates;
}
vector<Marine> loadMarines(){
    //This loads the marines from the CSV file
    ifstream inputFile("marines.csv");
    if(!inputFile.is_open()){
        cout << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }
    vector<Marine> marines;
    string line;
    while(getline(inputFile, line)){
        Marine marine;
        stringstream ss(line);
        ss.getline(marine.name, 20, ',');
        ss.getline(marine.rank, 20, ',');
        ss.getline(marine.combatAbility, 20, ',');
        ss >> marine.haki;
        ss.ignore();
        marines.push_back(marine);
    }
    inputFile.close();
    return marines;
}
vector<Revolutionary> loadRevolutionaries(){
    //This loads the revolutionaries from the CSV file
    ifstream inputFile("rev.csv");
    if(!inputFile.is_open()){
        cout << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }
    vector<Revolutionary> revolutionaries;
    string line;
    while(getline(inputFile, line)){
        Revolutionary revolutionary;
        stringstream ss(line);
        ss.getline(revolutionary.name, 20, ',');
        ss.getline(revolutionary.rank, 20, ',');
        ss.getline(revolutionary.combatAbility, 20, ',');
        ss >> revolutionary.haki;
        ss.ignore();
        ss >> revolutionary.bounty;
        ss.ignore();
        ss >> revolutionary.bountyMagnitude;
        revolutionaries.push_back(revolutionary);
    }
    inputFile.close();
    return revolutionaries;
}
DBSystem DatabaseSystem();

void PirateDB(DBSystem* db){
    cout << "Welcome to the Pirate Database\n\n" << endl;
    cout << "What would you like to do?\n" << endl;
    cout << "1. View Pirates by Crew\n" << endl;
    cout << "2. View Pirates by Name\n" << endl;
    cout << "3. View Pirates Bounties\n" << endl;
    cout << "4. Return to the World Database\n" << endl;

    int choice;
    cin >> choice;
    //Switch statement to allow the user to choose what they want to do
    switch(choice) {
        case 1: {
            cout << "Which crew would you like to view?\n" << endl;
            //Here we are creating a vector of strings to store the names of the crews
            vector<string> CrewNames;
            for (int i = 0; i < db->pirates.size(); i++) {
                if (db->pirates[i].crew != db->pirates[i + 1].crew) {
                    CrewNames.push_back(db->pirates[i].crew);
                }
            }
            //Here we are sorting the vector and removing duplicates, crews display once
            sort(CrewNames.begin(), CrewNames.end());
            auto last = unique(CrewNames.begin(), CrewNames.end());
            CrewNames.erase(last, CrewNames.end());
            for (int i = 0; i < CrewNames.size(); i++) {
                cout << i + 1 << ". " << CrewNames[i] << endl;
            }
            int crewChoice;
            cin >> crewChoice;
            //Here we display all the pirates in the chosen crew
            cout << "Pirates in " << CrewNames[crewChoice - 1] << " crew: " << endl;
            //Search through pirates vector and if CrewNames[crewChoice-1] == pirates[i].crew, display pirates[i].name
            for (int i = 0; i < db->pirates.size(); i++) {
                if (CrewNames[crewChoice - 1] == db->pirates[i].crew) {
                    cout << db->pirates[i].name << endl;
                }
            }
            PirateDB(db);
            break;
        }
        case 2:
        {
            cout << "Which pirate would you like to view?\n" << endl;
            //Here we display all the pirates in the pirates vector as options
            for (int i = 0; i < db->pirates.size(); i++) {
                cout << i + 1 << ". " << db->pirates[i].name << endl;
            }
            int pirateChoice;
            cin >> pirateChoice;
            //Here we display the chosen pirate's information
            cout << "Name: " << db->pirates[pirateChoice - 1].name << endl;
            cout << "Crew: " << db->pirates[pirateChoice - 1].crew << endl;
            cout << "Combat Ability: " << db->pirates[pirateChoice - 1].combatAbility << endl;
            //strcmp compares to see if pirate has haki
            if(db->pirates[pirateChoice-1].haki == true){
                cout <<db->pirates[pirateChoice-1].name <<" has mastered Haki." << endl;
            }
            else{
                cout << db->pirates[pirateChoice-1].name << " has not mastered Haki." << endl;
            }
            cout << "Bounty: " << db->pirates[pirateChoice - 1].bounty << db->pirates[pirateChoice - 1].bountyMagnitude<<"\n\n"<< endl;
            PirateDB(db);
            break;
        }
        case 3:
        {
            cout << "Current Highest Unclaimed Bounties:\n" << endl;
            // We need to create a vector to store the indexes of the pirates
            vector<int> PirateIndexes;
            for (int i = 0; i < db->pirates.size(); i++) {
                PirateIndexes.push_back(i);
            }
            //Now we need to rearrange the indexes so that the pirates are in order of their bounties
            //But first, we primarily sort the pirates by their bounty magnitude, then by their bounty
            //Billions, then millions, then thousands

            sort(PirateIndexes.begin(), PirateIndexes.end(), [&db](int i1, int i2) {
                if (db->pirates[i1].bountyMagnitude == "Billion" && db->pirates[i2].bountyMagnitude == "Million") {
                    return true;
                }
                else if (db->pirates[i1].bountyMagnitude == "Billion" && db->pirates[i2].bountyMagnitude == "Thousand") {
                    return true;
                }
                else if (db->pirates[i1].bountyMagnitude == "Million" && db->pirates[i2].bountyMagnitude == "Thousand") {
                    return true;
                }
                else if (db->pirates[i1].bountyMagnitude == db->pirates[i2].bountyMagnitude) {
                    return db->pirates[i1].bounty > db->pirates[i2].bounty;
                }
                else {
                    return false;
                }
            });
            //Now we display the pirates in order of their bounties
            for (int i = 0; i < PirateIndexes.size(); i++) {
                cout << i + 1 << ". " << db->pirates[PirateIndexes[i]].name << ": $" << db->pirates[PirateIndexes[i]].bounty
                << db->pirates[PirateIndexes[i]].bountyMagnitude << endl;
            }
            PirateDB(db);
            break;
        }
        case 4:
        {
            DatabaseSystem();
            break;
        }
    }

}
void marineDB(DBSystem* db){
    cout << "Welcome to the Marine Database\n\n" << endl;
    cout << "What would you like to do?\n" << endl;
    cout << "1. View Marines by Rank\n" << endl;
    cout << "2. View Marines by Name\n" << endl;
    cout << "3. Return to the World Database\n" << endl;

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
        {
            cout << "Which rank would you like to view?\n" << endl;
            //We need to create a vector of strings to store the ranks of the marines
            vector<string> MarineRanks;
            for (int i = 0; i < db->marines.size(); i++) {
                if (db->marines[i].rank != db->marines[i + 1].rank) {
                    MarineRanks.push_back(db->marines[i].rank);
                }
            }

            //Now we sort the vector and remove duplicates, ranks display once
            sort(MarineRanks.begin(), MarineRanks.end());
            auto last = unique(MarineRanks.begin(), MarineRanks.end());
            MarineRanks.erase(last, MarineRanks.end());
            //Display the ranks
            for(int i = 0; i < MarineRanks.size(); i++){
                cout << i+1 << ". " << MarineRanks[i] << endl;
            }

            int rankChoice;
            cin >> rankChoice;
            //Here we display all the marines in the chosen rank
            cout << "Marines in " << MarineRanks[rankChoice - 1] << " rank: " << endl;
            //Search through marines vector and if MarineRanks[rankChoice-1] == marines[i].rank, display marines[i].name
            for (int i = 0; i < db->marines.size(); i++) {
                if (MarineRanks[rankChoice - 1] == db->marines[i].rank) {
                    cout << db->marines[i].name << endl;
                }
            }
            marineDB(db);
            break;
        }
        case 2:
        {
            cout << "Which member of personnel would you like to view?\n" << endl;
            //Here we display all the marines in the marines vector as options
            for (int i = 0; i < db->marines.size(); i++) {
                cout << i + 1 << ". " << db->marines[i].name << endl;
            }
            int marineChoice;
            cin >> marineChoice;

            //Here we display the chosen marine's information
            cout << "Name: " << db->marines[marineChoice - 1].name << endl;
            cout << "Rank: " << db->marines[marineChoice - 1].rank << endl;
            cout << "Combat Ability: " << db->marines[marineChoice - 1].combatAbility << endl;
            if(db->marines[marineChoice-1].haki == true){
                cout <<db->marines[marineChoice-1].name <<" has mastered Haki." << endl;
            }
            else{
                cout << db->marines[marineChoice-1].name << " has not mastered Haki." << endl;
            }
            marineDB(db);
            break;
        }
        case 3:
        {
            DatabaseSystem();
            break;
        }

    }
}
void revDB(DBSystem* db){
    cout << "Welcome to the Revolutionary Database\n\n" << endl;
    cout << "WARNING: This database is still under construction\n\n" << endl;
    cout << "What would you like to do?\n" << endl;
    cout << "1. View Revolutionaries by Divisional Leadership\n" << endl;
    cout << "2. View Revolutionaries by Name\n" << endl;
    cout << "3. View Revolutionaries Bounties\n" << endl;
    cout << "4. Return to the World Database\n" << endl;

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
        {
            cout << "Which Leader would you like to view?\n" << endl;
            //We need to create a vector of strings to store the indexes of the revolutionaries
            vector<string> RevolutionaryLeaderRoles;
            for (int i = 0; i < db->revolutionaries.size(); i++) {
                if (db->revolutionaries[i].rank != db->revolutionaries[i + 1].rank) {
                    RevolutionaryLeaderRoles.push_back(db->revolutionaries[i].rank);
                }
            }
            //Clear Duplicate Roles
            sort(RevolutionaryLeaderRoles.begin(), RevolutionaryLeaderRoles.end());
            auto last = unique(RevolutionaryLeaderRoles.begin(), RevolutionaryLeaderRoles.end());
            RevolutionaryLeaderRoles.erase(last, RevolutionaryLeaderRoles.end());
            //Display the Revolutionary Leader Roles
            for(int i = 0; i < RevolutionaryLeaderRoles.size(); i++){
                cout << i+1 << ". " << RevolutionaryLeaderRoles[i] << endl;
            }
            int revChoice;
            cin >> revChoice;
            //Here we string compare the chosen revolutionary leader's role to the revolutionaries vector
            //and display the revolutionaries with the same role
            cout << "Revolutionaries in " << RevolutionaryLeaderRoles[revChoice - 1] << " role: " << endl;
            for (int i = 0; i < db->revolutionaries.size(); i++) {
                if (RevolutionaryLeaderRoles[revChoice - 1] == db->revolutionaries[i].rank) {
                    cout << db->revolutionaries[i].name << endl;
                }
            }
            revDB(db);
            break;
        }
        case 2:
        {
            cout << "Which revolutionary would you like to view?\n" << endl;
            //Here we display all the revolutionaries in the revolutionaries vector as options
            for (int i = 0; i < db->revolutionaries.size(); i++) {
                cout << i + 1 << ". " << db->revolutionaries[i].name << endl;
            }
            int revChoice;
            cin >> revChoice;

            //Here we display the chosen revolutionary's information
            cout << "Name: " << db->revolutionaries[revChoice - 1].name << endl;
            cout << "Rank: " << db->revolutionaries[revChoice - 1].rank << endl;
            cout << "Combat Ability: " << db->revolutionaries[revChoice - 1].combatAbility << endl;
            if(db->revolutionaries[revChoice-1].haki == true){
                cout <<db->revolutionaries[revChoice-1].name <<" has mastered Haki." << endl;
            }
            else{
                cout << db->revolutionaries[revChoice-1].name << " has not mastered Haki." << endl;
            }
            cout << "Bounty: " << db->revolutionaries[revChoice - 1].bounty << db->revolutionaries[revChoice - 1].bountyMagnitude<<"\n\n"<< endl;
            revDB(db);
            break;
        }
        case 3:
        {
            cout << "Current Highest Unclaimed Bounties (Revolutionaries):\n" << endl;
            // We need to create a vector to store the indexes of the revolutionaries
            vector<int> RevolutionaryIndexes;
            for (int i = 0; i < db->revolutionaries.size(); i++) {
                RevolutionaryIndexes.push_back(i);
            }
            //Now we need to rearrange the indexes so that the revolutionaries are in order of their bounties
            //But first, we primarily sort the revolutionaries by their bounty magnitude, then by their bounty
            //Billions, then millions, then thousands

            sort(RevolutionaryIndexes.begin(), RevolutionaryIndexes.end(), [&db](int i1, int i2) {
                if (db->revolutionaries[i1].bountyMagnitude == "Billion" && db->revolutionaries[i2].bountyMagnitude == "Million") {
                    return true;
                }
                else if (db->revolutionaries[i1].bountyMagnitude == "Billion" && db->revolutionaries[i2].bountyMagnitude == "Thousand") {
                    return true;
                }
                else if (db->revolutionaries[i1].bountyMagnitude == "Million" && db->revolutionaries[i2].bountyMagnitude == "Thousand") {
                    return true;
                }
                else if (db->revolutionaries[i1].bountyMagnitude == db->revolutionaries[i2].bountyMagnitude) {
                    return db->revolutionaries[i1].bounty > db->revolutionaries[i2].bounty;
                }
                else {
                    return false;
                }
            });
            //Now we display the revolutionaries in order of their bounties
            for (int i = 0; i < RevolutionaryIndexes.size(); i++) {
                cout << i + 1 << ". " << db->revolutionaries[RevolutionaryIndexes[i]].name << ": $" << db->revolutionaries[RevolutionaryIndexes[i]].bounty
                     << db->revolutionaries[RevolutionaryIndexes[i]].bountyMagnitude << endl;
            }
            revDB(db);
            break;
        }
        case 4:
        {
            DatabaseSystem();
            break;
        }

    }


}

DBSystem DatabaseSystem(){
    //This defines the database
    DBSystem db;
    db.pirates = loadPirates();
    db.marines = loadMarines();
    db.revolutionaries = loadRevolutionaries();
    db.currentUserName = "Admin";

    cout << "Welcome to the World Database\n\n" << endl;
    cout << "What would you like to do?\n" << endl;
    cout << "1. View Pirates\n" << endl;
    cout << "2. View Marines\n" << endl;
    cout << "3. View Revolutionaries\n" << endl;
    cout << "4. Exit System\n" << endl;

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
        {
            PirateDB(&db);
            break;
        }
        case 2:
        {
            marineDB(&db);
            break;
        }
        case 3:
        {
            revDB(&db);
            break;
        }
        case 4:
        {
            cout << "Thank you for using the World Database"<< db.currentUserName << endl;
            exit(EXIT_SUCCESS);
        }

    }

}


void ExistingLogin() {
    // Allows input, checks if the input is valid, and then checks if the input is in the database
    vector<administrator> admins = LoadAdmins();
    char username[20];
    char password[20];
    bool validated = false; // Initialize validated inside the function

    cout << "Enter your username: " << endl;
    cin >> username;
    cout << "Enter your password: " << endl;
    cin >> password;

    for (int i = 0; i < admins.size(); i++) {
        if (strcmp(admins[i].name, username) == 0 && strcmp(admins[i].password, password) == 0) {
            validated = true;
            DatabaseSystem();
            break;
        }
    }

    if (validated) {
        cout << "Welcome " << username << endl;
    } else {
        cout << "Invalid username or password" << endl;
        ExistingLogin(); // Recursively call the function for another attempt
    }
}

void AddAdmin(){
    //Adds a new admin to the csv file
    char username[20];
    char password[20];
    ofstream outputFile("admins.csv", ios::app);

    if(!outputFile.is_open()){
        cout << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Enter your username: \n" << endl;
    cin >> username;
    cout << "Enter your password: \n" << endl;
    cin >> password;

    outputFile <<"\n"<< username << "," << password << endl;
    outputFile.close();
    cout << "Account created" << endl;
    ExistingLogin();
}

void LoginSystem(){
    char username[20];
    char password[20];
    cout << "Welcome to the Marine Database\n\n" << endl;

    cout << "Do you have an account? (Y/N)\n" << endl;
    char answer;
    cin >> answer;
    if( answer == 'Y' || answer == 'y'){
        ExistingLogin();
    }
    else if( answer == 'N' || answer == 'n'){
        AddAdmin();
    }
    else{
        cout << "Invalid input" << endl;
        LoginSystem();
    }
}

int main() {
    LoginSystem();
}
