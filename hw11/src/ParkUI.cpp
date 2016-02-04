/*
Navjyoth Thakur
2015-11-29
*/

#include "../include/ParkUI.hpp"

//constructor
ParkUI::ParkUI(GameStats & s, Park & p, FarmUI & f)
 : park(p), stats(s), farm(f)
 {
 }
void ParkUI::runPark() {
  command = 0;
  char input = 'x';
  while (command == 0) {
    std::cout << "\x1b[36m"; //changes color to cyan
    printMenu();
    std::cout << "\x1b[0m";
    input = getValidInput();
    decision(input);
  }
}

//prints the park menu
void ParkUI::printMenu() {
  std::cout << stats << "\n";
  std::cout << "PARK - Make a decision:\n\
                l Look At Stats\n\
                d Buy Display \n\
                b Move Critter To Barn\n\
                p Move Critter to Park\n\
                c Buy Critter\n\
                s Sell Critter\n\
                a Set Admission Fee\n\
                g Get Critter List\n\
                o Open Park!! (effect phase)\n\
                i Instructions\n\
                m Menu\n\
                Enter input: ";
}

//gets the valid input from user
char ParkUI::getValidInput() {
  std::string input;
  std::cin >> input;
  if (input != "l" && input != "d" && input != "b" && input != "p"
       && input != "c" && input != "s" && input != "a" && input != "g"
       && input != "o" && input != "i" && input != "m") {
    std::cout << "No valid input. Try again";
    return getValidInput();
  } else {
    return input.at(0);
  }
}

//implements the decision based on input
void ParkUI::decision(char input) {
  std::string name;
  double admission;
  std::map< std::string, Critter>::iterator iter;

  switch (input) {
    case 'l':
      std::cout << stats << "\n";
      break;
    case 'd':
      park.buyDisplay();
      break;
    case 'b':
      std::cout << "Enter the name of the Critter: ";
      std::cin >> name;
      park.critterToBarn(name);
      break;
    case 'p':
      std::cout << "Enter the name of the Critter: ";
      std::cin >> name;
      park.critterToPark(name);
      break;
    case 'c':
      //park.buyCritter();
      farm.buyCritter();
      break;
    case 's':
      std::cout << "Enter the name of the Critter: ";
      std::cin >> name;
      park.sellCritter(name);
      break;
    case 'a':
      std::cout << "For every dollar, ten points of reputation is removed.\n"
        << "Enter Admission Fee (Limit of $15): ";
      std::cin >> admission;
      //makes sure admission fee is appropriate
      if (admission == 0 || admission > 15) {
        std::cout << "Improper admission fee.\n";
      } else {
        park.setAdmission(admission);
      }
      break;
    case 'g':
      std::cout << "\x1b[32m"; // set foreground to green
      std::cout << "List of critters in barn: \n";
      for (iter = stats.allCritters.begin();
        iter != stats.allCritters.end(); iter++) {
        //display traits of all critters
        std::cout << (iter->first) << ": " << (iter->second).getTraits() << "\n";
      }
      std::cout << "\x1b[0m"; // reset to defaults
      std::cout << "\x1b[33m";
      std::cout << "List of critters in park: \n";
      for (iter = stats.parkCritters.begin();
        iter != stats.parkCritters.end(); iter++) {
        //display traits of all critters
        std::cout << (iter->first) << ": " << (iter->second).getTraits() << "\n";

      }

      std::cout << "\x1b[0m"; // reset to defaults

      break;
    case 'o':
      park.effectPhase();
      farm.endTurn();
      std::cout << stats << "\n";
      //checks if wins game
      if (stats.money >= 10000 && stats.gameWon == 0) {
          std::cout << "Congratulations, you've won! Feel free to continue,"
            << " or quit the game!\n";
          stats.gameWon = 1;
      }
      //checks if loses game
      if (stats.money <= 0 || stats.overallRep <= 0) {
          std::cout << "Sorry It seems You've lost!\n";
          stats.gameWon = -1;
          command = 1;
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
    case 'm':
      command = 1;
      break;
    default:
      break;
  }

}

//gets command of either quitting game or going to barn
int ParkUI::getCommand() {
  return command;

}


