#ifndef SKIN_HPP
#define SKIN_HPP
#include <iostream>
#include <string>
#include <map>
#include "Encoding.hpp"
#include "trait.hpp"
using std::string;

class Skin {
  public:

    Skin();
    Skin(Encoding &g);
    void encodeSkin(string skinColor, string skinType);
    void encodeSkinColor(unsigned int number);
    void encodeSkinType(unsigned int number);
    string decodeSkin();
    string decodeSkinColor();
    Trait& skinColorTrait();
    Trait& skinTypeTrait();
    string decodeSkinType();
    Trait addTraits();
    static void unitTest();



  private:
    static std::map<unsigned int, Trait> skinColorM;
    static std::map<string, unsigned int> skinColorK;
    static std::map<unsigned int, Trait> skinTypeM;
    static std::map<string, unsigned int> skinTypeK;


    Encoding &genome;
    unsigned int colorNum;
    string color;//2 bits
    string skinType;
    unsigned int typeNum;
};

#endif

