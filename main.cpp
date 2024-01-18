#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include <cstdlib>

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

    int bounty;

};
struct Marine{
    char name[20];
    char rank[20];
    char combatAbility[20];
    bool haki;

    int bounty;
};

struct Revolutionary{
    char name[20];
    char rank[20];
    char combatAbility[20];
    bool haki;

    int bounty;
};
struct DBSystem{
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
        ss >> marine.bounty;
        marines.push_back(marine);
    }
    inputFile.close();
    return marines;
}
vector<Revolutionary> loadRevolutionaries(){
    //This loads the revolutionaries from the CSV file
    ifstream inputFile("revolutionaries.csv");
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
        revolutionaries.push_back(revolutionary);
    }
    inputFile.close();
    return revolutionaries;
}
void DatabaseSystem(){
    //This defines the database
    DBSystem db;
    db.pirates = loadPirates();
    //db.marines = loadMarines();
    //db.revolutionaries = loadRevolutionaries();

    for (int i = 0; i < db.pirates.size(); i++) {
        cout <<"NAME:"<< db.pirates[i].name <<"\n"<<"BOUNTY:"<<db.pirates[i].bounty << endl;
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
