#ifndef _BEN120_gameStats_HPP
#define _BEN120_gameStats_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../include/critter.hpp"
#include <iomanip>

class GameStats {
  friend std::ostream & operator<< (std::ostream & os, GameStats & stats);
  public:
    GameStats(std::map<std::string, Critter> & pC, std::map<std::string, Critter> & aC);
    static void unitTest();

    void setRep();
    int contains(std::string name, const std::map<std::string, Critter> &Critters);

    //Variables

    std::map<std::string, Critter> parkCritters;
    std::map<std::string, Critter> allCritters;
    void displayParkCritters ();
    int numVisitors;
    int cuteRep;
    int scaryRep;
    int weirdRep;
    int overallRep;
    double income;
    double expenses;
    int cuteSatisfaction;
    int scarySatisfaction;
    int weirdSatisfaction;
    double money;
    double admissionFee;
    int numDisplays;
    int numCritters;
    int gameWon;
    std::string instructions;
  private:



};

#endif

