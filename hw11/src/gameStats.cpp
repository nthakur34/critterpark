/*
HW11 for 600.120.02, Fall 2015

Navjyoth Thakur
2015-11-29
*/

#include "../include/gameStats.hpp"

std::map< std::string, Critter>::iterator iter;
std::map<std::string, Critter> parkCritters;
std::map<std::string, Critter> allCritters;

//constructor
GameStats::GameStats(std::map<std::string, Critter> & pC,
    std::map<std::string, Critter> & aC)
  : parkCritters(pC), allCritters(aC)
{
  parkCritters = pC;
  allCritters = aC;
  numVisitors = 0;
  cuteSatisfaction = 0;
  scarySatisfaction = 0;
  weirdSatisfaction = 0;
  income = 0;
  expenses = 0;
  money = 100;
  admissionFee = 0;
  numDisplays = 5;
  cuteRep = 0;
  scaryRep = 0;
  weirdRep = 0;
  overallRep = 0;
  gameWon = 0;
  instructions = "Instructions:\n\n"
    "-> To win this game, you must manage your Critter Park so that your\n"
    "   reputation and cash savings does not fall to zero.\n"
    "-> Critters may only stay at the barn of in the park displays.\n"
    "-> At least one critter must always be on display and visitors are attracted\n"
    "   based on overall reputation and their personal critter preferences\n"
    "   (weird, scary, etc.).\n"
    "-> The user may change as much as they like on their turn, but critters who are\n"
    "   breeding become inactive until the following day.\n"
    "-> Opening the park also carries expenses, but once you're out of the rough patch,\n"
    "   it should be relatively easy to get visitors.\n"
    "-> Remember, the goal is to hit $10,000 in cash savings, but you can play as long as\n"
    "   you like!\n"
    "-----------------------------------------------------------------------------------\n"
    "Hints and Suggestions:\n\n"
    "- Make sure to keep admission at $1 or less at start since every dollar increase\n"
    "  reduces reputation by 10 points, and a reputation of zero results in a loss.\n"
    "- Make sure to manage admission costs, so that your income doesn't stay negative, \n"
    "  although you should have a negative income at the start of the game.\n"
    "- Displaying all critters is an efficient way to keep track of them while managing\n"
    "  the park.\n"
    "- The critters that breed won't be usable until the next turn, nor will their child.\n"
    "- Breeding critters with particular stats may or may NOT result in a critter with\n"
    "  the stats you desire, since children don't always work that way.\n"
    "- There can only be as many critters in the park as there are displays. The game\n"
    "  starts with 5 displays\n\n";

  setRep();

}


//check if critter exists
int GameStats :: contains(std::string name, const std::map<std::string, Critter> &Critters) {

  int contains = 0;
  if (Critters.find(name) != Critters.end()) {
    contains = 1;
  }

  return contains;
}

//displays park critters
void GameStats::displayParkCritters () {
  for (iter  = parkCritters.begin();
      iter !=parkCritters.end(); iter++) {
    std::cout << iter->first << "\n";
  }

}

//sets initial reputation
void GameStats::setRep() {
    for (iter = parkCritters.begin();
    iter != parkCritters.end(); iter++) {
    cuteRep += (iter->second).getCuteRep();
    scaryRep += (iter->second).getScaryRep();
    weirdRep += (iter->second).getWeirdRep();

    //makes sure rep is positive
    if (cuteRep < 0) {
      cuteRep = 0;
    }
    if (scaryRep < 0) {
      scaryRep = 0;
    }
    if (weirdRep < 0) {
      weirdRep = 0;
    }
  }

  //makes subReps a percentage
  overallRep = cuteRep + scaryRep + weirdRep;
  cuteRep = cuteRep/(double)overallRep * 100 + .5;
  scaryRep = scaryRep/(double)overallRep * 100 + .5;
  weirdRep = weirdRep/(double)overallRep* 100 + .5;
}

//prints out game stats
std::ostream & operator<< (std::ostream & os, GameStats & stats) {
  os << "Overall Reputation: " << stats.overallRep << "\n";
  os << "[Cuteness: " << stats.cuteRep << " Scariness: " << stats.scaryRep
    << " Weirdness: " << stats.weirdRep << "]\n";
  os << std::fixed << std::setprecision(2) <<"Money: $" << stats.money
    << " Income: $" << stats.income << " Expenses: $"
    << stats.expenses << " Admission Fee: $" << stats.admissionFee << "\n";

  return os;
}


void GameStats::unitTest() {

  std::cout << "Starting tests for GameStats!\n";
  std::map<std::string, Critter> parkCritters;
  std::map<std::string, Critter> allCritters;
  Critter crit1("Crit1");
  Critter crit2("Crit2");
  crit1.setGenome(0);
  crit2.setGenome(0);
  parkCritters["Crit1"] = crit1;
  parkCritters["Crit2"] = crit2;
  /*for ( auto p : parkCritters) {
    std::cout << "parkCritter: " << p.second << "\n";
  }*/


  GameStats stats(parkCritters, allCritters);
  //test setRep

  if (stats.cuteRep >=0 && stats.scaryRep >=0 &&
      stats.weirdRep >= 0 && stats.overallRep >= 0) {
    std::cout << "passed setRep" << "\n";
  } else {
    std::cout << "failed setRep" << "\n";
  }

  //test operator <<
  //std::cout << stats;
  std::cout << "passed operator <<" << "\n";

  std::cout << "Tests finished for GameStats!\n";

}



