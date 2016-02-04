#ifndef _BEN_120_LIMBS_HPP
#define _BEN_120_LIMBS_HPP
#include <iostream>
#include <string>
#include <map>
#include "Encoding.hpp"
#include "trait.hpp"

using std::string;


class Limbs
{
  public:

    Limbs(Encoding &g);

    void encodeLimbs(unsigned int number, string thickness);
    void encodeNumber(unsigned int number);
    void encodeThickness(unsigned int number);
    string decodeLimbs();
    string decodeNumber();
    string decodeThickness();
    Trait& numTrait();
    Trait& thicknessTrait();
    Trait addTraits();
    static void unitTest();




  private:
    static std::map<std::string, unsigned int> thicknessK;
    static std::map<unsigned int, Trait> thicknessM;
    static std::map<std::string, unsigned int> numK;
    static std::map<unsigned int, Trait> numM;
    
    Encoding &genome;
    string number; //4 bits
    string thickness;//2 bits
};

#endif

