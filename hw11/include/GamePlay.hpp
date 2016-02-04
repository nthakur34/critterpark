/*
HW9 for 600.120.02, Fall 2015

Navjyoth Thakur
nthakur2
nthakur2@jhu.edu
2019236387
2015-11-09

Sherry Chiu
schiu9
schiu9@jhu.edu
7329476211
2015-11-09
*/

#ifndef _BEN_120_GAMEPLAY_HPP
#define _BEN_120_GAMEPLAY_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "critter.hpp"
#include "FarmUI.hpp"
#include "ParkUI.hpp"

class GamePlay {
    public:
        GamePlay();
        void dialogue(std::map<std::string, Critter> &allCritters);
        int contains(std::string name, std::map<std::string, Critter>
           allCritters);
        void getMenu(GameStats & stats);
       // void setGameStats(GameStats & gameStats);
       // void setDifficulty(std::vector<int> &parkVals, int diff);

    private:

        std::map<std::string, Critter> parkCritters;
        std::map<std::string, Critter> allCritters;
      //  GameStats stats(std::map<std::string, Critter> parkCritters,
        //  std::map<std::string, Critter> allCritters);
};

#endif
