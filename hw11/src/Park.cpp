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

#include "../include/Park.hpp"

std::map< std::string, Critter>::iterator ite;

//constructor
Park::Park(GameStats & s)
  : stats(s)
{
}


//buy one display
void Park::buyDisplay() {
  //cost of display is $50
  //check there is enough money
  if (stats.money < 50 ) {
    std::cout << "Not enough money to buy display";
    return;
  }

  stats.numDisplays++;
  stats.money -= 50;

}

//moves a critter to barn
void Park::critterToBarn(std::string name) {
  if (stats.parkCritters.size() == 1) {
    std::cout << "At least 1 critter must stay in park!\n";
  } else if (stats.contains(name, stats.parkCritters)) {
    stats.allCritters[name] = stats.parkCritters[name];
    stats.parkCritters.erase(name);
  } else {
    std::cout << "Sorry, this Critter doesn't exist in Park.\n";
  }
}

//moves a critter to park
void Park::critterToPark(std::string name) {
  if (stats.contains(name, stats.allCritters)) {
    if (hasEmptyDisplay() == 1) {
    stats.parkCritters[name] = stats.allCritters[name];
    stats.allCritters.erase(name);
    } else {
    std::cout << "Sorry, you don't have an empty display.\n";
    }
  } else {
    std::cout << "Sorry, this Critter doesn't exist in Park.\n";
  }
}


void Park::buyCritter() {
}

//set admission fee
void Park::setAdmission(double fee) {

  stats.overallRep -= ((fee - stats.admissionFee) * 10);
  stats.admissionFee = fee;
}

//sells a Critter
void Park::sellCritter(std::string name) {
  if (stats.contains(name, stats.allCritters)) {
    Critter critter = stats.allCritters[name];
    //get price
    int price = critter.getCuteRep() + critter.getScaryRep()
      + critter.getWeirdRep();
    price = price * 2;
    stats.money += price;
    //remove from map
    stats.allCritters.erase(name);
    std::cout << "You sold " <<name<< " for $" << price << ".\n";
  } else {
    std::cout << "Sorry, this Critter doesn't exist in Farm.\n";
  }
}


//checks that there is at least one empty display
int Park::hasEmptyDisplay() {
  if ((int)stats.parkCritters.size() < stats.numDisplays ) {
    return 1;
  } else {
    return 0;
  }
}

//runs effect phase
void Park::effectPhase() {
  setNumVisitors();
  setMoney();
  setNewRep();
}

//sets the number of visitors
void Park::setNumVisitors() {
  srand(time(NULL));
  double randNum  = (rand()/(2.0 * RAND_MAX)) +.75;
  stats.numVisitors = randNum * stats.overallRep;

}
//set all reputations for effectPhase
void Park:: setNewRep() {
  //get number of types of visitors
  int cuteVisitors = (stats.numVisitors * stats.cuteRep/100.0) + .5;
  int scaryVisitors = (stats.numVisitors * stats.scaryRep/100.0) + .5;
  int weirdVisitors = (stats.numVisitors * stats.weirdRep/100.0) + .5;
  //make sure number of visitors add up
  while (cuteVisitors + scaryVisitors + weirdVisitors != stats.numVisitors) {
    if (weirdVisitors != 0) {
      weirdVisitors--;
    } else if (scaryVisitors != 0) {
      scaryVisitors--;
    } else {
      cuteVisitors--;
    }
  }


  setSatisfaction();


  //get the raw new reps
  int newOverallRep = stats.cuteSatisfaction + stats.scarySatisfaction + stats.weirdSatisfaction;
  int newCuteRep = stats.cuteSatisfaction/(double)newOverallRep * 100 + .5;
  int newScaryRep = stats.scarySatisfaction/(double)newOverallRep * 100 + .5;
  int newWeirdRep = stats.weirdSatisfaction/(double)newOverallRep * 100 + .5;


  //set the actual new reps

  stats.cuteRep = (0.7 * stats.cuteRep) + (.3 *newCuteRep) +.5;
  stats.scaryRep = (0.7 * stats.scaryRep) + (.3 *newScaryRep) + .5;
  stats.weirdRep = (0.7 * stats.weirdRep) + (.3 *newWeirdRep) + .5;
  stats.overallRep = (0.7 * stats.overallRep) + (.3 *newOverallRep) + .5;



}

//sets satisfaction based on critters
void Park::setSatisfaction () {
  for (ite = stats.parkCritters.begin();
    ite != stats.parkCritters.end(); ite++) {
    stats.cuteSatisfaction += (ite->second).getCuteRep();
    stats.scarySatisfaction += (ite->second).getScaryRep();
    stats.weirdSatisfaction += (ite->second).getWeirdRep();
    if (stats.cuteSatisfaction < 0) {
      stats.cuteSatisfaction = 0;
    }
    if (stats.scarySatisfaction < 0) {
      stats.scarySatisfaction = 0;
    }
    if (stats.weirdSatisfaction < 0) {
      stats.weirdSatisfaction = 0;
    }
  }

}

//sets money, income, expenses
void Park::setMoney() {
  stats.income = stats.numVisitors * stats.admissionFee;
  //expense is $5 per critter
  stats.expenses = stats.parkCritters.size() * 5;
  stats.money = stats.money + stats.income - stats.expenses;
}

void Park::unitTest() {
  std::cout << "Starting tests for Park!\n";
  std::map<std::string, Critter> parkCritters;
  std::map<std::string, Critter> allCritters;
  Critter crit1("Crit1");
  Critter crit2("Crit2");
  Critter crit3("Crit3");
  Critter crit5("Crit5");
  crit1.setGenome(999, -1);
  crit2.setGenome(444, -1);
  crit3.setGenome(222, -1);
  crit5.setGenome(984, -1);
  parkCritters["Crit1"] = crit1;
  parkCritters["Crit2"] = crit2;
  parkCritters["Crit3"] = crit3;
  allCritters["Crit5"] = crit5;
  GameStats stats(parkCritters, allCritters);
  Park park(stats);

  //test admissionFee
  stats.overallRep = 150;
  park.setAdmission(10.50);
  if (stats.admissionFee == 10.50) {
    std::cout << "passed setAdmission \n";
  } else {
    std::cout << "failed setAdmission \n";
  }

  //test buyDisplay
  park.buyDisplay();
  //std::cout << stats.numDisplays << " " << stats.money << "\n";
  if (stats.numDisplays == 6 && stats.money == 50) {
    std::cout << "passed buyDisplay\n";
  } else {
    std::cout << "failed buyDisplay\n";
  }

  //test set NumVisitors
  //int temp = stats.overallRep;
  //stats.overallRep = 100;
  park.setNumVisitors();
 // std::cout << "numVisitors: " << stats.numVisitors << "\n";
  //std::cout << "overallRep: " << stats.overallRep << "\n";
  if (stats.numVisitors <= stats.overallRep * 1.25 &&
      stats.numVisitors >= stats.overallRep *.75) {
    std::cout << "passed setNumVisitors \n";
  } else {
    std::cout << "failed setNumVisitors \n";
  }

  //stats.overallRep = temp;
  //test setMoney
  stats.numVisitors = 50;
  park.setMoney();
  //std::cout << stats.income << " " << stats.expenses << " " << stats.money << "\n";
  if (stats.income == 525 && stats.expenses ==  15 &&
      stats.money == 50 + 50 * 10.50 - 15) {
    std::cout << "passed setMoney \n";
  } else {
    std::cout << "failed setMoney \n";
  }

  //test setRep
  stats.cuteRep = 25;
  stats.scaryRep = 25;
  stats.weirdRep = 50;
  //std::cout << stats <<"\n";
  park.setNewRep();
  //std::cout << stats <<"\n";
  if (stats.cuteRep == 18 && stats.scaryRep == 39 && stats.weirdRep == 43) {
    std::cout << "passed setRep \n";
  } else {
    std::cout << "failed setRep \n";
  }

  //test effectPhase
  GameStats stats2(parkCritters, allCritters);
  Park park2(stats2);
  //std::cout <<"OG " << stats2 << "\n";
  Critter crit4("Crit4");
  crit4.setGenome(342);
  stats2.parkCritters["Crit4"] = crit4;


  park2.setAdmission(10);
  park2.effectPhase();
  //std::cout << "After " <<stats2 << "\n";

  //stats2.displayParkCritters();
  if (stats2.parkCritters.size() == 4
      && stats2.expenses == 20.00 && stats2.cuteRep == 7
      && stats2.scaryRep == 73 && stats2.weirdRep == 21
      && stats2.overallRep == -36) {
    std::cout << "passed effectPhase \n";
  } else {
    std::cout << "failed effectPhase \n";
  }

  /*std::cout << stats2.parkCritters.size() << " "<<
      stats2.expenses << " " << stats2.cuteRep << " " <<
      stats2.scaryRep << " " <<stats2.weirdRep << " " <<
      stats.overallRep << "\n";*/

  //test sellCritter
  park2.sellCritter("Crit1");
  park2.sellCritter("Crit5");
  //stats2.displayParkCritters();
  //std::cout <<"\n";
  //stats2.displayAllCritters();

  if ( stats2.allCritters.size() == 0 ) {
    std::cout << "passed sellCritter \n";
  } else {
    std::cout << "failed sellCritter \n";
  }

  //test critterToBarn
  park2.critterToBarn("Crit9");
  //stats2.displayAllCritters();
  //std::cout << "^allCritters afterCrit 5 \n";
  park2.critterToBarn("Crit3");
  //stats2.displayParkCritters();
  //std::cout << "^parkCrit crit 3\n";
  //stats2.displayAllCritters();
  //std::cout << "^allCrit crit 3\n";
  if ( stats2.contains("Crit3", stats2.parkCritters) ==  0
      && stats2.contains("Crit3", stats2.allCritters) == 1)
  {
    std::cout << "passed critterToBarn \n";
  } else {
    std::cout << "failed critterToBarn \n";
  }

  //test critterToPark
  park2.critterToPark("Crit9");
  //stats2.displayAllCritters();
  //std::cout << "^allCritters afterCrit 5 \n";
  park2.critterToPark("Crit3");
  //stats2.displayParkCritters();
  //std::cout << "^parkCrit crit 3\n";
  //std::cout << "^allCrit crit 3\n";
  if ( stats2.contains("Crit3", stats2.parkCritters) ==  1
      && stats2.contains("Crit3", stats.allCritters) == 0)
  {
    std::cout << "passed critterToPark \n";
  } else {
    std::cout << "failed critterToPark \n";
  }

  std::cout << "Tests finished for Park!\n";

}
