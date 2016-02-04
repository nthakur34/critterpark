#ifndef EYES_HPP
#define EYES_HPP
#include <iostream>
#include <string>
#include <map>
#include "Encoding.hpp"
#include "trait.hpp"

using std::string;

class Eyes {
  public:

    Eyes();
    Eyes(Encoding &g);
    string printEyeColor();
    unsigned int printNumEyes();
    void encodeEyes(unsigned int number, string eyeColor);
    void encodeEyeColor(string eyeColor);
    void encodeNumEyes(unsigned int number);

    string decodeEyes();
    string decodeEyeColor();
    string decodeNumEyes();
    string getEyeColor();
    void getNumEyes();
    Trait& numEyesTrait();
    Trait& eyeColorTrait();
    Trait addTraits();
    static void unitTest();



  private:
    static std::map<unsigned int, Trait> eyeColorM;
    static std::map<string, unsigned int> eyeColorK;
    static std::map<unsigned int, Trait> numEyesM;
    Encoding &genome;
    string numEyes;//4 bits
    string color;//2 bits
};

#endif

