#ifndef _BEN120_Park_HPP
#define _BEN120_Park_HPP

#include <iostream>
#include <string>
#include <vector>
#include "../include/gameStats.hpp"
#include <cstdlib>


class Park {
  public:
    Park(GameStats & s);
    //Decision Phase
    void buyDisplay();
    void critterToBarn(std::string name);
    void critterToPark(std::string name);
    void buyCritter();
    void setAdmission(double fee); 
    void sellCritter(std::string critter);
    int hasEmptyDisplay();
    //Effective Phase
    void effectPhase();
    void setNumVisitors();
    void setSatisfaction();
    void setNewRep();
    void setMoney();
    static void unitTest();


  private:
    GameStats & stats;


};


#endif
