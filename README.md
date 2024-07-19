# Upcountry Warriors Management System

Welcome to the Upcountry Warriors Management System! This application helps manage player and team information for the Upcountry Warriors. Below you'll find detailed instructions on how to use the application.

## Table of Contents
- [Installation](#installation)
- [Running the Application](#running-the-application)
- [Features](#features)
  - [Display Players Information](#display-players-information)
  - [Add New Player](#add-new-player)
  - [Delete Player](#delete-player)
  - [Manage Teams](#manage-teams)
  - [Search Players](#search-players)
  - [View Team Details](#view-team-details)
  - [Edit Player](#edit-player)
  - [Edit Team](#edit-team)
  - [Delete Team](#delete-team)
  - [Login](#login)
  - [Logout](#logout)
  - [Exit](#exit)

## Installation

1. **Clone the repository:**
   ```sh
   git clone https://github.com/baasith6/upcountry-warriors-management-system.git
   
## Navigate to the project directory
cd upcountry-warriors-management-system

## Compile the application
g++ -o upcountry_warriors main.cpp

## Running the Application
To run the application, use the following command:
./final.exe

## Features

## Login
1.When you start the application, you will be prompted to log in.
2.Enter the username (admin) and password (password).

## Display Players Information
1.After logging in, choose option 1 from the menu to display all player information.
2.The application will list each player's registration number, name, date of birth, runs scored, and teams they belong to.

## Add New Player
1.Choose option 2 from the menu.
2.Enter the player's registration number, first name, last name, date of birth (in YYYY-MM-DD format), runs scored, and team ID (or 0 to skip).
3.The player will be added to the system and saved to the file.

## Delete Player
1.Choose option 3 from the menu.
2.Enter the registration number of the player you wish to delete.
3.The player will be removed from the system and saved to the file.

## Manage Teams
1.Choose option 4 from the menu.
2.You will have the option to:
3.Add a new team
4.Add a player to a team
5.Remove a player from a team
6.Follow the on-screen instructions to manage teams.

## Search Players
1.Choose option 5 from the menu.
2.Enter the registration number of the player you wish to search for.
3.The application will display the player's information if found.

## View Team Details
1.Choose option 6 from the menu.
2.Enter the team ID you wish to view details for.
3.The application will display the team's information, including team name and players.

## Edit Player
1.Choose option 7 from the menu.
2.Enter the registration number of the player you wish to edit.
3.Follow the on-screen instructions to update the player's information. Enter 0 to skip a field.

## Edit Team
1.Choose option 8 from the menu.
2.Enter the team ID of the team you wish to edit.
3.Follow the on-screen instructions to update the team's name. Enter 0 to skip a field.

## Delete Team
1.Choose option 9 from the menu.
2.Enter the team ID of the team you wish to delete.
3.The team will be removed from the system and saved to the file.

## Logout
1.Choose option 10 from the menu to log out.
2.You will need to log in again to access the menu options.

## Exit
1. Choose option 11 from the menu to exit the application.
