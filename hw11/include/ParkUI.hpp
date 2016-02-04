#ifndef ParkUI_HPP
#define ParkUI_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Park.hpp"
#include "FarmUI.hpp"


class ParkUI {

    public:
    ParkUI(GameStats & s, Park & p, FarmUI & f);
    void runPark();
    int getCommand(); //used to decide whether to stay in park or not
  private:
    int command;
    void printMenu();
    char getValidInput();
    void decision(char input);
    Park & park;
    GameStats & stats;
    FarmUI & farm;



};

#endif

