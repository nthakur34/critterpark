/*
Navjyoth Thakur
nthakur2
nthakur2@jhu.edu
2019236387
2015-11-29

Sherry Chiu
schiu9
schiu9@jhu.edu
7329476211
2015-11-29
*/

#include "../include/FarmUI.hpp"

FarmUI::FarmUI(GameStats & stats, Park & park)
  :stats(stats), park(park)
{
  std::map< std::string, Critter> outForTurn;
  count = 0; //counter for default names, e.g., default<1>, default<2>...
  breed = 0; //0 if not yet bred for turn, else 1
}

void FarmUI::barn() {
  //create all variables to be used in switch statement
  std::map< std::string, Critter>::iterator iter;
  double crossOverFactor = .1;
  double mutationFactor = .03;
  Critter critter;
  std::string name;
  std::string newName;
  std::string child;
  int random; //0 if no user picks, else 1

  unsigned long temp; //value used to setGenome
  //Menu items to display
  std::string choices = "FARM - Make a decision:\n\
                         b: type 'b' to buy a random critter\n\
                         a: display all critters.\n\
                         d: display one critter's description\n\
                         n: change name of critter.\n\
                         x: breed new critter.\n\
                         r: sell a critter.\n\
                         s: send a critter to a display.\n\
                         i: instructions.\n\
                         m: go to main menu\n→ ";
  std::cout << "\x1b[36m"; //changes color to cyan
  std::cout << stats << "\n" << choices;
  std::cout << "\x1b[0m"; //sets back to default color
  char userChoice;
  std::cin >> userChoice;

  //continue until user wants to quit
  while (userChoice != 'm') {
    switch (userChoice) {
          //create the critter with valid name
      case 'b':
        buyCritter();
        break;
          //display a;; critters
      case 'a':
        std::cout << "\x1b[2J"; //clears screen
        std::cout << "\x1b[32m"; // set foreground to green

        for (iter = stats.allCritters.begin();
          iter != stats.allCritters.end(); iter++) {
          //display traits of all critters
          std::cout << (iter->first) << ": " << (iter->second).getTraits() << "\n";

        }
        std::cout << "\x1b[0m"; // reset to defaults
        break;
          //rename a critter
      case 'd':

        std::cout << "Which critter would you like to see the details of?\n(q to cancel)\n→ ";
        std::cin >> name;
        //check that critter exists and that user wants to continue with choice
        while (stats.contains(name, stats.allCritters) == 0 && name.compare("q") != 0) {

          std::cin.clear();
          std::cin.ignore();
          std::cout << "\x1b[31m";
          std::cout << "Please enter valid name\n(q to cancel)\n→ ";
          std::cout << "\x1b[0m";
          std::cin >> name;
        }
        //if user selects q, user quits action
        if (name.compare("q") == 0) {
             break;
        }

        std::cout << "\x1b[35m"; // set foreground to
        std::cout << stats.allCritters[name]; //overloaded operator <<
        std::cout << "\x1b[0m"; // reset to defaults

        break;

      case 'n':
        //renames critter
        std::cout << "What is the name of the critter you want to rename?\n(q to cancel)\n→ ";
        std::cin >> name;
        //critter must exist
        while (stats.contains(name, stats.allCritters) == 0
            && stats.contains(name, stats.allCritters) == 0 && name.compare("q") != 0) {

          std::cin.clear();
          std::cin.ignore();
          std::cout << "\x1b[31m";
          std::cout << "Please enter valid name\n(q to cancel)\n→ ";
          std::cout << "\x1b[0m";
          std::cin >> name;
        }
        //if user prompts q, exit function
        if (name.compare("q") == 0) {
          break;
        }
        //set new name
        newName = setName(0); //calls setName function of FarmUI
        stats.allCritters[name].setName(newName);
        stats.allCritters[newName] = stats.allCritters[name];
        stats.allCritters.erase(stats.allCritters.find(name));

        break;
      //breed two critters
      case 'x':

        if (breed == 1) {
          std::cout << "Can only breed critters once per turn\n";
          break;
        }
        //choose a valid critter to breed
        std::cout << "What is the name of the first critter you want to breed?\n(q to cancel)\n→ ";
        std::cin >> name;
        //check for existing critter
        while (stats.contains(name, stats.allCritters) == 0 && name.compare("q") != 0) {

          std::cin.clear();
          std::cin.ignore();
          std::cout << "\x1b[31m";
          std::cout << "Please enter valid name\n(q to cancel)\n→ ";
          std::cout << "\x1b[0m";
          std::cin >> name;

        }


        if (name.compare("q") == 0) {
             break;
          }
        //choose another valid critter to breed
        std::cout << "What is the name of the second critter you want to breed?\n(q to cancel)\n→ ";
        std::cin >> newName;

        while (stats.contains(newName, stats.allCritters) == 0 && name.compare("q") != 0) {

          std::cin.clear();
          std::cin.ignore();
          std::cout << "\x1b[31m";
          std::cout << "Please enter valid name\n(q to cancel)\n→ ";
          std::cout << "\x1b[0m";
          std::cin >> newName;

        }
        if (newName.compare("q") == 0) {
             break;
        }
              //CREATE new critter with crossover and mutation
        temp =  stats.allCritters[name].getEncoding().crossover(
        stats.allCritters[newName].getGenome(), crossOverFactor); // crossover factor here as .1

        critter.setGenome(temp, mutationFactor); //mutation factor here as .03
        std::cout << "Would you like to name the child? (y/n)\n→ ";
        std::cin >> child;
        //decide if user wants to name child
        while (child != "n" && child != "y") {
          std::cout << "\x1b[31m";
          std::cout << "please enter y or n\n→ ";
          std::cout << "\x1b[0m";
          std::cin >> child;
        }
        if (child.compare("y") == 0) {
          random = 0;
        } else {
          count++;
          random = 1;
        }
        //set critter
        child = setName(random);
        critter.setName(child);
        stats.allCritters[child] = critter;
        std::cout << "\x1b[33m";
        std::cout << "Congratulations! You made " << child << "!\n";
        std::cout << "\x1b[0m";

        outForTurn[name] = stats.allCritters[name];
        stats.allCritters.erase(name);
        outForTurn[newName] = stats.allCritters[newName];
        stats.allCritters.erase(newName);
        outForTurn[child] = stats.allCritters[child];
        stats.allCritters.erase(child);

        breed = 1;

        break;

      case 'r':
        //choose a valid critter to remove
        std::cout << "What is the name of the critter to sell?\n(q to cancel)\n→ ";
        std::cin >> name;
        park.sellCritter(name);

        break;
      case 's':

        std::cout << "What is the name of the critter to sell?\n→ ";
        std::cin >> name;
        if (stats.contains(name, stats.allCritters) == 0) {
          std::cout << "Sorry, this Critter doesn't exist in Park.\n";
          break;
        }
        park.critterToPark(name);
        break;
      case 'i': //display instructions
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
      //repeat until user picks "q"
    std::cout << "\x1b[36m";
    std::cout << stats << "\n" << choices;
    std::cout << "\x1b[0m";
    std::cin >> userChoice;
    //checks for valid input. Not sure if needed, so just to be safe here
  }

}
//end the turn for farm by moving all critters into allCritters
void FarmUI :: endTurn() {
 std::map< std::string, Critter>::iterator iter;
 for (iter = outForTurn.begin();
        iter != outForTurn.end(); iter++) {
        stats.allCritters[iter->first] = (iter->second);
      }
  breed = 0;
  outForTurn.clear();

}

//Sets the name of the critter. i represents if random or not(1 or 0).
//count represents the nth default name
std::string FarmUI::setName(int i) {

  std::string child;
  std::string unknown = "default";
  //let the user make the name
  if(i == 0) {
    std::cout << "What is the new name you want?\n→ ";
    std::cin >> child;
    while (stats.contains(child, stats.allCritters) == 1
        || stats.contains(child, stats.parkCritters) == 1) {
      std::cout << "\x1b[31m";
      std::cout << "Please enter a name that is not currently in use.\n→ ";
      std::cout << "\x1b[0m";
      std::cin >> child;
    }
  //make default name
  } else {
    unknown.append("<");
    unknown.append(std::to_string(count));
    unknown.append(">");
    child = unknown;
  }
  return child;
}

//buying of critter which is also used by Park
int FarmUI :: buyCritter() {

  std::string name;
  int random;
  Critter critter;
  int bought = 0;
  //check if player wants to buy
  std::cout << "Are you sure you want to buy a new Critter? (y/n)\n→ ";
  std::cin >> name;
  while (name != "n" && name != "y") {
    std::cout << "\x1b[31m";
    std::cout << "please enter y or n\n→ ";
    std::cout << "\x1b[0m";
    std::cin >> name;
  }
  if (name.compare("n") == 0) {
    return bought;
  }
  bought = 1;
  //check if user wants to name critter
  std::cout << "Would you like to name the new Critter? (y/n)\n→ ";
  std::cin >> name;
  //make sure y or n is selected
  while (name != "n" && name != "y") {
    std::cout << "\x1b[31m";
    std::cout << "please enter y or n\n→ ";
    std::cout << "\x1b[0m";
    std::cin >> name;
  }
  //check if user wants to select name or not
  if (name.compare("y") == 0) {
    random = 0;
  } else {
    count++;
    random = 1;
  }
  //set new name to new critter
  name = setName(random);
  critter.setName(name);
  stats.allCritters[name] = critter;
  std::cout << "\x1b[33m"; //yellow
  std::cout << "Congratulations! You bought " << name << "!\n";
  std::cout << "\x1b[0m";

  return bought;

}

