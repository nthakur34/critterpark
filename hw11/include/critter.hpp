#ifndef CRITTER_HPP
#define CRITTER_HPP

#include <iostream>
#include <cstdio>
#include <string>
#include "Encoding.hpp"
#include "eyes.hpp"
#include "skin.hpp"
#include "limbs.hpp"

class Critter {
  public:


    Critter(std::string n = "");//constructor
    void setGenome(unsigned long temp, double m=-1);
    ~Critter() { } //destructor
    std::string getName();
    void setName(std::string n);
    friend std::ostream & operator<<  (std::ostream& os, Critter &critter);
    friend int operator== (Critter &critterA, Critter &critterB);
    friend int operator< (Critter &critterA, Critter &critterB);
    void getEyes();
    void getLimbs();
    unsigned long getGenome();
    unsigned long crossOver(Encoding &g);
    std::string getTraits();
    Encoding getEncoding();
    void setGenome(Encoding &g);
    std::string toString();
    std::string traitString(Limbs & limbs, Eyes & eyes, Skin & skin);
    static void unitTest();
    int getCuteRep();
    int getScaryRep();
    int getWeirdRep();

  private:
    Encoding genome;
    std::string name;
    std::string thickness;
    std::string eyeColor;
    std::string limbString;
    std::string eyeString;
    std::string skinString;
    std::string totalTrait;
    unsigned long temp;
    Trait allTrait;
    int cuteRep;
    int scaryRep;
    int weirdRep;




};


#endif

