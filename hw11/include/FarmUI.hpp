#ifndef FARMUI_HPP
#define FARMUI_HPP

#include <iostream>
#include <string>
#include <map>
#include "gameStats.hpp"
#include "Park.hpp"

class FarmUI {

    public:
        FarmUI(GameStats & stats, Park & park);
        void barn();
        std::string setName(int i);
        int contains(std::string name, const std::map<std::string, Critter> &allCritters);
        int buyCritter();
        void endTurn();

    private:
      std::map< std::string, Critter> outForTurn;
      GameStats & stats;
      Park & park;
      int count; //counter for default names, e.g., default<1>, default<2>...
      int breed;
};

#endif
