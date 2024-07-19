#include <iostream> //C++ standard library header file for input and output streams.it allows you to work with the console (standard input and output).
#include <fstream> //classes and functions to work with files.Useful when dealing with file I/O in your program
#include <vector> //C++ Standard Template Library (STL) vector container.use vectors to store and manipulate collections of elements.
#include <string> //It provides classes and functions to work with strings 
#include <regex> //Regular expressions allow you to search for and manipulate patterns within strings.Useful for tasks like pattern matching, validation, and text processing.
// The #include <cctype> directive includes the cctype header file,
// which provides functions for character handling, like:-
// isdigit, isalpha, islower, isupper, tolower, toupper, etc.
#include <cctype>

// The using namespace std; directive allows us to use the standard library
// names (like cout, cin, string, etc.) without prefixing them with std::.
using namespace std;


// The struct keyword is used to define a structure, which is a user-defined
// data type that can hold multiple related variables under one name.
// Struct to hold player information
struct Player 
{
    int registrationNumber;// This line declares an integer variable named registrationNumber,
    string firstName;// This line declares a string variable named firstName,
    string lastName;// This line declares a string variable named lastName,
    string dateOfBirth;// This line declares a string variable named dateOfBirth,
    int runsScored;// This line declares an integer variable named runsScored,
    vector<int> teamIds; // This line declares a vector of integers named teamIds. which will store the IDs of the teams the player has been part of.
    
};

// Struct to hold team information
struct Team 
{
    int teamId; // integer variable for tamId
    string teamName; // string variable for teamName
    vector<int> playerRegistrationNumbers; // vector of integers named playerRegistrationNumbers .its can save mutiple player reg num.
};

//global variables
vector<Player> players; // Vector to store players
vector<Team> teams; // Vector to store teams
bool loggedIn = false; // Flag to check login status

void getPlayers(); // Function to load players from file
void savePlayers(); // Function to save players to file
void getTeams(); // Function to load teams from file
void saveTeams(); // Function to save teams to file
void addPlayer(); // Function to add a new player
void deletePlayer(); // Function to delete a player
void displayPlayers(); // Function to display all players
void manageTeams(); // Function to manage teams
void searchPlayers(); // Function to search for a player
bool login(); // Function to handle login
void logout(); // Function to handle logout
void exitApp(); // Function to exit the application
void viewTeamDetails(); // Function to view team details
void editPlayer(); // Function to edit a player's details
void editTeam(); // Function to edit a team's details
void deleteTeam(); // Function to delete a team
bool isValidDate(const string &date); // Function to validate date format
bool isValidNumber(const string &input); // Function to validate if a string is a number
bool isValidName(const string &name); // Function to validate if a string is a valid name

void setPresetTeams(); // Function to  predefined teams

int main() {
    getPlayers(); // Load players from file
    getTeams(); // Load teams from file
    setPresetTeams(); // Initialize predefined teams

    // Display welcome message
    cout <<"************************************************************************************************\n";
    cout <<"|======================WELCOME TO UPCOUNTRY WARRIROR MANAGMENT SYSTEM ========================|\n";
    cout <<"________________________________________________________________________________________________\n";
    cout << "\n\n";
    cout << "_______________________________________________________________________________________________\n";
    cout <<"\n|-------------------------------LOGIN TO START THE SYSTEM... ----------------------------------|\n";
    cout << "_________________________________________________________________________________________________\n";

    // Prompt for login, allow up to 3 attempts
    for (int attempts = 0; attempts < 3; ++attempts) {
        if (login()) {
            break;
        } else if (attempts == 2) {
            cout << "---------------------Too many failed attempts. Exiting the application.------------------\n";
            return 0;
        }
    }

    int choice;
    do {
        if (loggedIn) {
            // Display menu options
            cout << "\n=========================== MAIN MENU....=============================================\n";
            cout << "|------------------------------1. Display players information--------------------------|\n";
            cout << "|------------------------------2. Add new player---------------------------------------|\n";
            cout << "|------------------------------3. Delete player----------------------------------------|\n";
            cout << "|------------------------------4. Manage teams-----------------------------------------|\n";
            cout << "|------------------------------5. Search players---------------------------------------|\n";
            cout << "|------------------------------6. View team details------------------------------------|\n";
            cout << "|------------------------------7. Edit player------------------------------------------|\n";
            cout << "|------------------------------8. Edit team--------------------------------------------|\n";
            cout << "|------------------------------9. Delete team------------------------------------------|\n";
            cout << "|------------------------------10. Logout----------------------------------------------|\n";
            cout << "|------------------------------11. Exit------------------------------------------------|\n";
            cout << "\n______________________________________________________________________________________\n";
            cout <<   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Enter your choice: ";
            cin >> choice;
            cout << "________________________________________________________________________________________\n";

            // Handle user's choice
            switch (choice) {
                case 1: displayPlayers(); break;
                case 2: addPlayer(); break;
                case 3: deletePlayer(); break;
                case 4: manageTeams(); break;
                case 5: searchPlayers(); break;
                case 6: viewTeamDetails(); break;
                case 7: editPlayer(); break;
                case 8: editTeam(); break;
                case 9: deleteTeam(); break;
                case 10: logout(); break;
                case 11: exitApp(); break;
                default: cout << "--------------------------Invalid choice. Please try again.---------------------\n";
            }
        } else {
            // Prompt user to login if not already logged in
            cout << "---------------------------------------Please login first.-------------------------------------\n";
            for (int attempts = 0; attempts < 3; ++attempts) {
                if (login()) {
                    break;
                } else if (attempts == 2) {
                    cout << "-------------------Too many failed attempts. Exiting the application.-------------------\n";
                    return 0;
                }
            }
        }
    } while (choice != 11);

    return 0;
}

// Function to initialize predefined teams
void setPresetTeams() 
{
    if (teams.empty()) // Check if the teams vector is empty
    {
        Team team1 = {1, "Warriors", {}}; // Create a Team object named team1 with ID 1 and name "Warriors"
        Team team2 = {2, "Gladiators", {}}; // Create a Team object named team2 with ID 2 and name "Gladiators"
        Team team3 = {3, "Titans", {}};   // Create a Team object named team3 with ID 3 and name "Titans"
        teams.push_back(team1); // Add team1 to the teams vector
        teams.push_back(team2);   // Add team2 to the teams vector
        teams.push_back(team3); // Add team3 to the teams vector
        saveTeams(); // Save the teams to a persistent storage (implementation of saveTeams is not shown)
    }
}

// Function to load players from file
void getPlayers() 
{
    ifstream file("players.txt"); // Open the file named "players.txt" for reading
    // Check if the file could not be opened
    if (!file) 
    {
        // Output an error message if the file couldn't be opened
        cerr << "-----------------------Error opening players file.--------------------------------\n";
        // Exit the function
        return;
    }

    players.clear(); // Clear the players vector to avoid duplicate entries
    while (!file.eof()) // Loop until the end of the file is reached
    {
        Player p;   // Declare a Player object named p
        // Read the player's data from the file
        file >> p.registrationNumber >> p.firstName >> p.lastName >> p.dateOfBirth >> p.runsScored;
        // Check if reading the data failed
        if (file.fail()) 
        {
             // Output an error message if reading the data failed
            cerr << "-------------------Error reading player data. Possibly reached end of file.------------------\n";
            break; // Exit the loop
        }
         // Clear the teamIds vector for the player
        p.teamIds.clear();
        int teamId;
        // Loop to read team IDs until a newline or end of file is reached
        while (file >> teamId) 
        {
            p.teamIds.push_back(teamId);  // Add the team ID to the player's teamIds vector
             // Check if the next character is a newline or end of file
            if (file.peek() == '\n' || file.eof()) break; 
        }
         // Check if reading the data was successful
        if (!file.fail()) 
        {
            players.push_back(p); // Add the player to the players vector
        } else {
             // Output an error message if reading the team IDs failed
            cerr << "-------------------Error reading player team IDs.-----------------------------------\n";
        }
    }
     // Close the file
    file.close();
    // Output a message indicating successful loading of players
    cout << "---------------------------Players loaded successfully. Total players: " << players.size() << "\n";
}

// Function to save players to file
void savePlayers() 
{
    // Open the file named "players.txt" for writing
    ofstream file("players.txt");
    // Check if the file could not be opened
    if (!file) 
    {
        // Output an error message if the file couldn't be opened
        cerr << "-------------------------Error saving players file.--------------------------------------\n";
        return;  // Exit the function
    }
    // Loop through each player in the players vector
    for (int i = 0; i < players.size(); i++) 
    {
        Player p = players[i]; // Get the player at index i
        // Write the player's data to the file
        file << p.registrationNumber << " " << p.firstName << " " << p.lastName << " " << p.dateOfBirth << " " << p.runsScored;
         // Loop through each team ID for the player
        for (int j = 0; j < p.teamIds.size(); j++) 
        {
            // Write the team ID to the file
            file << " " << p.teamIds[j];
        }
        // Write a newline character to the file
        file << endl;
    }
     // Close the file
    file.close();
}
/*
##################get teams & save teams similer to getplayer & save player#################
*/
// Function to load teams from file
void getTeams() {
    ifstream file("teams.txt");
    if (!file) {
        cerr << "--------------------------------Error opening teams file.----------------------------------\n";
        return;
    }

    teams.clear(); // Clear the teams vector to avoid duplicate entries
    while (!file.eof()) {
        Team t;
        file >> t.teamId >> t.teamName;
        if (file.fail()) {
            cerr << "------------------------Error reading team data. Possibly reached end of file.------------\n";
            break;
        }

        t.playerRegistrationNumbers.clear();
        int playerRegNum;
        while (file >> playerRegNum) 
        {
            t.playerRegistrationNumbers.push_back(playerRegNum);
            if (file.peek() == '\n' || file.eof()) break;
        }
        if (!file.fail()) {
            teams.push_back(t);
        } else {
            cerr << "-----------------------Error reading team player registration numbers.-----------------------\n";
        }
    }
    file.close();
    cout << "-------------------------------Teams loaded successfully. Total teams: " << teams.size() << "\n";
}

// Function to save teams to file
void saveTeams() {
    ofstream file("teams.txt");
    if (!file) {
        cerr << "---------------------------Error saving teams file--------------.\n";
        return;
    }
    for (int i = 0; i < teams.size(); i++) {
        Team t = teams[i];
        file << t.teamId << " " << t.teamName;
        for (int j = 0; j < t.playerRegistrationNumbers.size(); j++) 
        {
            file << " " << t.playerRegistrationNumbers[j];
        }
        file << endl;
    }
    file.close();
}

// Function to add a new player
void addPlayer() {
    Player p;// Declare a Player object named p
    string input; // Declare a string variable to hold user input

    cout <<"_____________________________________________________________________________________________________________.\n";
    cout << "---------------------------Enter player registration number(enter an integer): ";
    while (true) 
    {
        //read user input
        cin >> input;
        // check user input valid or not
        if (isValidNumber(input)) 
        {
            // convert to integer and assign to input
            p.registrationNumber = stoi(input);
            break; // exit loop
        } else {
            // in valid inout again enter
            cout << "-------------------Invalid registration number. --------------------------------- \n";
            cout <<"--------------------Please enter a valid number(enter an integer):";

        }
    }

    cout << "---------------------------Enter first name(enter a string): ";
    while (true) 
    { 
        // read user input
        cin >> input;
        if (isValidName(input)) 
        {
            p.firstName = input;
            break;
        } else {
            cout << "-------------------Invalid first name.---------------------------------------------\n  ";
            cout << "-------------------Please enter a valid name(enter a string):";
        }
    }

    cout << "---------------------------Enter last name: ";
    while (true) 
    {
        cin >> input;
        if (isValidName(input)) 
        {
            p.lastName = input;
            break;
        } else {
            cout << "------------------Invalid last name.-------------------------------------------------\n ";
            cout << " -----------------Please enter a valid name(enter a string):";
        }
    }

    cout << "--------------------------Enter date of birth (YYYY-MM-DD): ";
    while (true) 
    {
        cin >> input;
        if (isValidDate(input)) 
        {
            p.dateOfBirth = input;
            break;
        } else {
            cout << "-----------------Invalid date.  ------------------------------------------------------\n";
            cout << "-----------------Please enter a valid date (YYYY-MM-DD):";
        }
    }

    cout << "--------------------------Enter runs scored: ";
    while (true) 
    {
        cin >> input;
        if (isValidNumber(input)) 
        {
            p.runsScored = stoi(input);
            break;
        } else {
            cout << "-----------------Invalid number of runs. ----------------------------------------------\n ";
            cout << "-----------------Please enter a valid number:";

        }
    }

    int teamId;
    // user have to enter 2 or 01 teams
    for (int i = 0; i < 2; ++i) 
    {
        
        cout << " select the team from this :- 1.Warriors, 2. Gladiators, 3.Titans\n";
        cout << "---------------------Enter team ID (or 0 to skip): ";
        
        cin >> input;
        // check validation from user input
        if (isValidNumber(input)) 
        {
            //convert user input to integer and assign to input
            teamId = stoi(input);
            //if user enter 0 loop will end
            if (teamId == 0) break;
            p.teamIds.push_back(teamId);
        } else {
            // if user enter wrong team id
            cout <<"------------------Invalid input.--------------------------------------------------------\n ";
            cout << "-----------------Please enter a valid team ID: ";
            --i;
        }
    }

    // add player to vector players
    players.push_back(p);
    //update the player list
    savePlayers();
    //inform user add player successfully
    cout << "------------------------Player added successfully.------------------------------------------------\n";
    cout << "__________________________________________________________________________________________________________\n\n";
}

// Function to delete a player
void deletePlayer() 
{
    int regNum; // declare variable integer registernumber
    string input;
    cout <<"_______________________________________________________________________________________________________________\n\n";
    cout << "-----------------------Enter player registration number to delete: ";
    while (true) 
    {
        //read user input
        cin >> input;
        //check input valid
        if (isValidNumber(input)) 
        {
            //conver user input to integer. 
            regNum = stoi(input);
            break; // exit loop
        } else {

            cout << "--------------Invalid registration number.-------------------------------------------------------------- \n";
            cout << "--------------Please enter a valid number: ";
        }
    }
    // Loop through the players vector
    for (int i = 0; i < players.size(); i++) 
    {
        // Check if the current player's registration number matches regNum
        if (players[i].registrationNumber == regNum) 
        {
             // Erase the player from the players vector
            players.erase(players.begin() + i);
            // Save the updated players list to the file
            savePlayers();
            // inform player delete succesfully
            cout << "-----------------------------Player deleted successfully.--------------------------------------------\n";
            cout << "_________________________________________________________________________________________________________";
            //exit funtion
            return;
        }
    }
    cout << "----------------------Player not found.-----------------------------------------------------------------------\n";
    cout << "_________________________________________________________________________________________________________________..\n\n";
}

// Function to display all players
void displayPlayers() 
{
    // Loop through the players vector
    for (int i = 0; i < players.size(); i++) 
    {
        // Get the current player
        Player p = players[i];
        cout <<"________________________________________________________________________________________________________________\n\n";
        cout << "\n=============================PLAYERS OF UPCOUNTRY WARRIORS=================================\n";
        //display player registration number
        cout << "------------------Registration Number: " << p.registrationNumber << "\n";
        //display player name
        cout << "------------------Name: " << p.firstName << " " << p.lastName << "\n";
        //display birth of date
        cout << "------------------Date of Birth: " << p.dateOfBirth << "\n";
        //display player already scored runs
        cout << "------------------Runs Scored: " << p.runsScored << "\n";
        //diplay player teams id
        cout << "------------------Teams: ";
        //// Loop through the teams vector
        for (int j = 0; j < p.teamIds.size(); j++) 
        {   
            // Output each team ID followed by a space
            cout << p.teamIds[j] << " ";
        }
         // Move to the next line after displaying all team IDs
        cout << "\n";
        cout <<"_______________________________________________________________________________________________________________\n\n";
    }
}

// Function to manage teams
void manageTeams() 
{
    int choice;
    cout <<"___________________________________________________________________________________________________________________\n\n";
    //ask user to select choice
    cout << "----------------------1. Add new team\n";
    cout << "----------------------2. Add player to team\n";
    cout << "----------------------3. Remove player from team\n";
    cout << "----------------------Enter your choice: ";
    //read user input to choice
    cin >> choice;

    if (choice == 1) 
    {
        //t is a object for a team
        Team t;
        // declare variable input as a string
        string input;
        cout <<"_________________________________________________________________________________________________________________\n\n";

        cout << "------------------Enter team ID(enter the integer): ";
        while (true) 
        {
            //read user input
            cin >> input;
            if (isValidNumber(input)) 
            {
                //convert user input string to integer
                t.teamId = stoi(input);
                break; // exit loop
              // if not enter valid team id  
            } else {
                cout << "-----------------------------Invalid team ID.-------------------------------------------------- \n ";
                cout << "----------Please enter a valid number(enter the integer): ";
            }
        }

        cout << "------------------Enter team name(enter the string): ";
        while (true) 
        {
            cin >> input;
            if (isValidName(input)) 
            {
                t.teamName = input;
                break;
            } else {
                cout << "----------------------------Invalid team name.------------------------------------------------\n  ";
                cout << "----------Please enter a valid name(enter the string): ";
            }
        }
        // add team to vector players
        teams.push_back(t);
        //update team list
        saveTeams();
        cout << "-----------------------------------Team added successfully.---------------------------------------------\n";
        cout <<"\n__________________________________________________________________________________________________________\n\n";
    } else if (choice == 2) 
    {
        //declarte integer variable for user input teamid ,registation number
        int teamId, regNum;
        string input;
        cout <<"____________________________________________________________________________________________________________\n\n";

        cout << "-------------------Enter team ID(enter the integer): ";
        while (true) 
        {
            cin >> input;
            if (isValidNumber(input)) 
            {
                teamId = stoi(input);
                break;
            } else {
                cout << "----------------------------Invalid team ID.--------------------------------------------------\n";
                cout <<" -----------Please enter a valid number(enter the integer): ";
            }
        }

        cout << "-------------------Enter player registration number(enter the integer): ";
        while (true) 
        {
            cin >> input;
            if (isValidNumber(input)) 
            {
                regNum = stoi(input);
                break;
            } else {
                cout << "---------------------------Invalid registration number.------------------------------------------\n  ";
                cout <<"------------Please enter a valid number(enter the integer): ";
            }
        }
        // Loop through the team vector
        for (int i = 0; i < teams.size(); i++) 
        {
            if (teams[i].teamId == teamId) 
            {   
                // Check if the current player's registration number matches regNum
                teams[i].playerRegistrationNumbers.push_back(regNum);
                //update team list
                saveTeams();
                //inform team add 
                cout << "---------------------------Player added to team successfully.--------------------------------------\n";
                return;
            }

        }
        cout << "-----------------------------------Team not found.----------------------------------------------------------\n";
        cout <<"______________________________________________________________________________________________________________\n\n";


    } else if (choice == 3) 
    {
        int teamId, regNum; // variable for team id and registration number
        string input; // variable for user input

        cout << "------------------Enter team ID(enter the integer): ";
        while (true) 
        {
            cin >> input; // read user input
            if (isValidNumber(input)) // check validation
            {
                teamId = stoi(input); // convert user input to interger and assign to team id
                break; // exit from loop if it is not valid
            } else {
                cout << "---------------------------Invalid team ID.---------------------------------------------------------\n ";
                cout << " ---------Please enter a valid number(enter the integer): ";
            }
        }

        cout << "------------------Enter player registration number(enter the integer): ";
        while (true) 
        {
            cin >> input; // red user input
            if (isValidNumber(input))  // check validation
            {
                regNum = stoi(input); // convert user input to integer and assign to regNam
                break;//exit from loop if its is note valid
            } else {
                cout << "---------------------------Invalid registration number.-----------------------------------------------\n  ";
                cout << "----------Please enter a valid number(enter the integer): ";
            }
        }
         // Loop through the teams vector
        for (int i = 0; i < teams.size(); i++) 
        {
            if (teams[i].teamId == teamId) // check current team id match user input team id
            {
                 // Loop through the player registration numbers of the team
                for (int j = 0; j < teams[i].playerRegistrationNumbers.size(); j++) 
                {

                    if (teams[i].playerRegistrationNumbers[j] == regNum) 
                    {
                         // Remove the player registration number from the team's player list
                        teams[i].playerRegistrationNumbers.erase(teams[i].playerRegistrationNumbers.begin() + j);
                        saveTeams(); // update team list
                        cout << "-------------------Player removed from team successfully.---------------------------------------\n";
                        return;
                    }
                }
                cout << "---------------------------Player not found in this team.------------------------------------------------\n";
                return;
            }
        }
        cout << "-----------------------------------Team not found.----------------------------------------------------------------\n";
    } else {
        cout << "-----------------------------------Invalid choice.----------------------------------------------------------------\n";
    }
    cout <<"_____________________________________________________________________________________________________________________________\n\n";
}

// Function to search for a player
void searchPlayers() 
{
    int regNum; // variable for user input registration number
    string input; // variable for user input
    cout << "_______________________________________________________________________________________________________________________\n\n";
    cout << "---------------------Enter player registration number to search(enter the int): ";
    while (true) 
    {
        cin >> input; // read user input
        if (isValidNumber(input)) // check user input validation
        {
            regNum = stoi(input);  // convert user input to integer and assign to regNum
            break;
        } else {
            cout << "-------------------------------Invalid registration number.------------------------------------------------\n ";
            cout <<"--------------Please enter a valid number(enter the integer): ";
        }
    }
     // Loop through the players vector
    for (int i = 0; i < players.size(); i++) 
    {
        if (players[i].registrationNumber == regNum) // check current registration number matches user input registration number
        {
            Player p = players[i];  // assign user input to players variable p to give player details
            cout << "==========================PLAYER OF UPCOUNTRY WARRIORS======================================================\n\n";
            cout << "-------------Registration Number: " << p.registrationNumber << "\n";
            cout << "-------------Name: " << p.firstName << " " << p.lastName << "\n";
            cout << "-------------Date of Birth: " << p.dateOfBirth << "\n";
            cout << "-------------Runs Scored: " << p.runsScored << "\n";
            cout << "-------------Teams: ";
            // Iterates over the team id vector and prints each player's team id
            for (int j = 0; j < p.teamIds.size(); j++) 
            {
                cout << p.teamIds[j] << " "; // disaply each player team id
            }
            cout << "\n";
            return;
        }
    }
    cout << "Player not found.\n";
    cout << "___________________________________________________________________________________________________________________\n\n";
}

// Function to handle login
bool login() 
{
    string username, password;
    cout << "-------------------Enter username: ";
    cin >> username;
    cout << "-------------------Enter password: ";
    cin >> password;
    if (username == "admin" && password == "password") 
    {
        loggedIn = true;
        return true;
    }
    cout << "----------------------------------Invalid username or password. Please try again.-----------------------------------\n";
    return false; // exit the funtion if invalid input
}

// Function to handle logout
void logout() 
{
    loggedIn = false;
    cout << "----------------------------------Logged out successfully.--------------------------------------------------\n";
}

// Function to exit the application
void exitApp() 
{
    cout << "=================================EXTING THE APPLICATION. GOODBYE!============================================\n";
    exit(0);
}

// Function to view team details
void viewTeamDetails() 
{
    int teamId; // variable for team id
    string input; // variable for user input
    cout <<"______________________________________________________________________________________________________________\n\n";
    cout << "--------------------Enter team ID to view details: ";
    while (true) 
    {
        cin >> input; // read user input
        if (isValidNumber(input))  // checl user input valid
        {
            teamId = stoi(input); // convert user input to integer and assign to team id
            break;
        } else {
            cout << "-------------------------Invalid team ID.--------------------------------------------------------\n  ";
            cout <<"-------------Please enter a valid number(enter the integer):";
        }
    }
    // Iterates over the teams vector to find the team with the matching ID
    for (int i = 0; i < teams.size(); i++) 
    {
        if (teams[i].teamId == teamId) //check current teamid match to input team id
        {
            Team t = teams[i]; // assign user input to teams variable t to give player details
            cout << "========================TEAMS OF UPCOUNTRY WARRIORS============================================\n\n";
            cout << "---------Team ID: " << t.teamId << "\n";
            cout << "---------Team Name: " << t.teamName << "\n";
            cout << "---------Players: ";
            // Iterates over the playerRegistrationNumbers vector and prints each player's registration number
            for (int j = 0; j < t.playerRegistrationNumbers.size(); j++) 
            {
                cout << t.playerRegistrationNumbers[j] << " "; // Display each player's registration number
            }
            cout << "\n";
            return;
        }
    }
    cout << "---------------------------------Team not found.---------------------------------------------------------\n";
    cout << "____________________________________________________________________________________________________________\n\n";
}

// Function to edit a player's details
void editPlayer() 
{
    int regNum; //variable to store the registration number to be edited
    string input; // variable for user inupt
    cout << "______________________________________________________________________________________________________________\n\n";
    cout << "------------------Enter player registration number to edit: ";
    while (true) 
    {
        cin >> input; // read user input
        if (isValidNumber(input)) // check user input it valid
        {
            regNum = stoi(input); // convert input to integer and store in regnum
            break; // exit the loop if input is valid
        } else {
            cout << "-------------------------Invalid registration number. -------------------------------------------------\n";
            cout <<"---------- Please enter a valid number(enter the integer):";
        }
    }
    //Iterates over the players vector.
    for (int i = 0; i < players.size(); i++) 
    {
        if (players[i].registrationNumber == regNum) // check current regnum match to input id
        {
            Player &p = players[i]; // get refferance to the player to edited
            cout << "----------Editing details for " << p.firstName << " " << p.lastName << "\n";

            cout << "----------Enter new first name (or '0' to skip): ";
            cin >> input; //read user input
            if (input != "0" && isValidName(input))  // check input not = 0 and validate input
            {
                p.firstName = input; // update the player first name
            }

            cout << "----------Enter new last name (or '0' to skip): ";
            cin >> input;
            if (input != "0" && isValidName(input)) 
            {
                p.lastName = input; // update the player last name
            }

            cout << "----------Enter new date of birth (or '0' to skip): ";
            cin >> input;
            if (input != "0" && isValidDate(input)) 
            {
                p.dateOfBirth = input; // update the player birthofdate
            }

            cout << "----------Enter new runs scored (or '0' to skip): ";
            cin >> input;
            if (input != "0" && isValidNumber(input)) 
            {
                p.runsScored = stoi(input); // convert input to integer and store in runscored
            }

            savePlayers(); // update the player file
            cout << "-------------------------Player details updated successfully.-------------------------------------------\n";
            return; // exit from funtion
        }
    }
    cout << "---------------------------------Player not found.--------------------------------------------------------------\n";
    cout <<"____________________________________________________________________________________________________________________";
}

// Function to edit a team's details
void editTeam() 
{
    int teamId;// Variable to store the team ID to be edited
    string input;// Variable to store user input
    cout <<"_________________________________________________________________________________________________________________\n\n";
    cout << "------------------Enter team ID to edit: ";
    while (true) 
    {
        cin >> input;// Read user input
        if (isValidNumber(input)) // Check if the input is a valid number
        {
            teamId = stoi(input);// Convert input to integer and store in teamId
            break;// Exit the loop if input is valid
        } else {
            cout << "--------------------------Invalid team ID. -------------------------------------------------------------\n ";
            cout <<"-----------Please enter a valid number(enter the integer): ";
        }
    }
    //Iterates over the teams vector.
    for (int i = 0; i < teams.size(); i++) 
    {
        if (teams[i].teamId == teamId) // Check if the current team's ID matches the input ID
        {
            Team &t = teams[i];// Get a reference to the team to be edited
            cout << "---------Editing details for " << t.teamName << "\n";

            cout << "---------Enter new team name (or '0' to skip): ";
            cin >> input;
            if (input != "0" && isValidName(input)) // Check if input is not '0' and is a valid name
            {
                t.teamName = input;// Update the team's name
            }

            saveTeams(); //save updated team 
            cout << "---------------------------Team details updated successfully.----------------------------------------------\n";
            return; // exit from funtion
        }
    }
    cout << "-----------------------------------Team not found.------------------------------------------------------------------\n";
    cout << "_______________________________________________________________________________________________________________\n\n";
}

// Function to delete a team
void deleteTeam() 
{
    int teamId;// Variable to store the team ID to be deleted
    string input;// Variable to store user input
    cout << "-----------------Enter team ID to delete: ";
    while (true) 
    {
        cin >> input;// Read user input
        if (isValidNumber(input)) // Check if the input is a valid number
        {
            teamId = stoi(input);// Convert input to integer and store in teamId
            break;// Exit the loop if input is valid
        } else {
            cout << "----------------------------Invalid team ID. ---------------------------------------------------------\n ";
            cout <<"----------Please enter a valid number(enter the integer): ";
        }
    }
    //Iterates over the teams vector.
    for (int i = 0; i < teams.size(); i++) 
    {
        if (teams[i].teamId == teamId) //Check if the current team's ID matches the input ID
        {
            teams.erase(teams.begin() + i);// Remove the team from the vector
            saveTeams();// Save the updated teams list to file
            cout << "----------------------------Team deleted successfully.-------------------------------------------------\n";
            return;// Exit the function after deleting the team
        }
    }
    cout << "------------------------------------Team not found.------------------------------------------------------------\n";
    cout <<"________________________________________________________________________________________________________________\n\n";
}

// Function to validate date format
bool isValidDate(const string &date) 
{
     // Regular expression to match the date format YYYY-MM-DD
    regex datePattern("\\d{4}-\\d{2}-\\d{2}");
    // Check if the date string matches the regex pattern
    if (regex_match(date, datePattern)) 
    {
         // Extract year, month, and day from the date string
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));
         // Check if the year, month, and day are within valid ranges
        if (year > 1900 && year <= 2100 && month >= 1 && month <= 12 && day >= 1 && day <= 31) 
        {
            return true;// The date is invalid
        }
    }
    return false;// The date is invalid
}

// Function to validate if a string is a number
bool isValidNumber(const string &input) 
{
    // Check if the string is not empty and consists of digits only
    return !input.empty() && all_of(input.begin(), input.end(), ::isdigit);
}

// Function to validate if a string is a valid name
bool isValidName(const string &name) 
{
     // Check if the string is not empty and consists of alphabetic characters only
    return !name.empty() && all_of(name.begin(), name.end(), [](char c) { return isalpha(c); });
}
