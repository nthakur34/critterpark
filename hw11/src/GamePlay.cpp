/*
HW11 for 600.120.02, Fall 2015

Navjyoth Thakur
*/

#include "../include/GamePlay.hpp"
#include "../include/Encoding.hpp"

GamePlay::GamePlay() {

 //set up farm critter list, and park display critters

  std::map<std::string, Critter> BarnCritters;
  std::map<std::string, Critter> ParkCritters;

  //Create first critter
  std::cout << "Ok, what is the name of your first critter? (Cannot be 'q')\n→ ";
  std::string name;
  std::cin >> name;
  //NAME CANNOT BE Q, SINCE IT IS A COMMAND
  while (name.compare("q") == 0) {
    std::cout << "Make it a unique name please!\n→ ";
    std::cin >> name;
  }

  Critter critter1(name);
  BarnCritters[name] = critter1;
  std::cout << "\x1b[33m";
  std::cout << "Congratulations! You made " << name << "!\n";
  std::cout << "\x1b[0m";

  //create second critter and make sure that the name is not already used
  std::cout << "Ok, what is the name of your second critter?\n→ ";
  std::cin >> name;
  while (contains(name, BarnCritters) || name.compare("q") == 0) {
    std::cout << "Make it a unique name please!\n→ ";
    std::cin >> name;
  }
  Critter critter2(name);
  BarnCritters[name] = critter2;
  std::cout << "\x1b[33m";
  std::cout << "Congratulations! You made " << name << "!\n";
  std::cout << "\x1b[0m";

  //create third critter and make sure that the name is not already used
  std::cout << "Ok, what is the name of your third critter?\n→ ";
  std::cin >> name;
  while (contains(name, BarnCritters) || name.compare("q") == 0) {
    std::cout << "Make it a unique name please!\n→ ";
    std::cin >> name;
  }
  Critter critter3(name);
  BarnCritters[name] = critter3;
  std::cout << "\x1b[33m";
  std::cout << "Congratulations! You made " << name << "!\n";
  std::cout << "\x1b[0m";

  //create fourth critter and make sure that the name is not already used
  std::cout << "Ok, what is the name of your fourth critter?\n→ ";
  std::cin >> name;
  while (contains(name, BarnCritters) || name.compare("q") == 0) {
    std::cout << "Make it a unique name please!\n→ ";
    std::cin >> name;
  }
  Critter critter4(name);
  ParkCritters[name] = critter4;
  std::cout << "\x1b[33m";
  std::cout << "Congratulations! You made " << name << "!\n";
  std::cout << "\x1b[0m";

  std::cout << "Press \"enter\" to continue...\n";
  std::cin.ignore();
  std::cin.get();
  std::cout << "\x1b[2J"; //clears screen
  //passes on map to the critter farm

  GameStats stats(ParkCritters, BarnCritters);
  getMenu(stats);

  //By using GamePlay, the critter map can be passed onto different classes
  //such as FarmUI or ParkUI

}

void GamePlay::getMenu(GameStats & stats) {

  Park parkActions(stats);
  FarmUI farm(stats, parkActions);
  ParkUI park(stats, parkActions, farm);

  std::string display = "MENU - Make a decision:\n\
                         p: access Park\n\
                         f: access Farm\n\
                         d: display park status\n\
                         e: end turn\n\
                         i: instructions\n\
                         q: quit game\n→ ";
  std::cout << "\x1b[36m"; //changes color to cyan
  std::cout << stats << "\n" << display;
  std::cout << "\x1b[0m"; //sets back to default color
  char userChoice;
  std::cin >> userChoice;

  while (userChoice != 'q') {
    switch (userChoice) {

      case 'p':   //runs ParkUI
        park.runPark();
        break;
      case 'f':   //runs farmUI
        farm.barn();
        break;
      case 'd':   //displays all stats
        std::cout << stats << "\n";
        break;
      case 'e':   //ends turn for effect phase
        parkActions.effectPhase();
        farm.endTurn();
        //checks if game is won
        if (stats.money >= 10000 && stats.gameWon == 0) {
          std::cout << "Congratulations, you've won! Would you like to continue"
            << " or quit?\n(q to quit or any other key to continue)\n";
          std::cin >> userChoice;
          stats.gameWon = 1;
        }
        //checks if game is lost
        if (stats.money <= 0 || stats.overallRep <= 0) {
          std::cout << stats << "\n" << display;
          std::cout << "Sorry It seems You've lost!\n";
          stats.gameWon = -1;
          std::cout << "Press \"enter\" to continue...\n";
          std::cin.ignore();
          std::cin.get();
        }

        break;
      case 'i':
        std::cout << "\x1b[2J";
        std::cout << "\x1b[36m";
        std::cout << stats.instructions;
        std::cout << "\x1b[0m";
        std::cout << "Press \"enter\" to continue...\n";
        std::cin.ignore();
        std::cin.get();
        std::cout << "\x1b[2J"; //clears screen
        break;
      default:
        std::cout << "Please enter valid input\n→ ";
        break;
    }
    if (userChoice == 'q')
      break;
    else if (stats.gameWon == -1)
      break;
    std::cout << "\x1b[36m";
    std::cout << stats << "\n" << display;
    std::cout << "\x1b[0m";
    std::cin >> userChoice;

  }

  std::cout << "\x1b[2J"; //clears screen
  std::cout << "\x1b[35;5;4;1m"; //adds majenta, blinking, bold, and underline
  std::cout << "Ok, See you next time!\n";
  std::cout << "\x1b[0m";


}

//makes sure that the name is not already used

int GamePlay :: contains(std::string name, std::map<std::string, Critter>
  allCritters) {

  int contains = 0;
  if (allCritters.find(name) != allCritters.end()) {
    contains = 1;
  }

  return contains;
}

/*void GamePlay::setDifficulty(std::vector<int> &parkVals, int diff) {

  if (diff == 1) { //For easy

    parkVals.push_back (500); //index 0 is cash on hand
    parkVals.push_back (0); //index 1 is income
    parkVals.push_back (0); //index 2 is expenses
    parkVals.push_back (0); //index 3 is park popularity

  } else if (diff == 2) { //For medium

    parkVals.push_back (500); //index 0 is cash on hand
    parkVals.push_back (0); //index 1 is income
    parkVals.push_back (0); //index 2 is expenses
    parkVals.push_back (0); //index 3 is park popularity

  } else { //For hard

    parkVals.push_back (500); //index 0 is cash on hand
    parkVals.push_back (0); //index 1 is income
    parkVals.push_back (0); //index 2 is expenses
    parkVals.push_back (0); //index 3 is park popularity

  }

}*/

