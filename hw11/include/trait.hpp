#ifndef _BEN120_TRAIT_HPP
#define _BEN120_TRAIT_HPP
#include <string>
#include <iostream>
#include <map>


class Trait {
  public:
    Trait(int c, int s, int w, std::string d);
    Trait();
    static void unitTest();
    std::string getDescription();
    void setCuteness(int c);
    void setScariness(int s);
    void setWeirdness(int w);
    void setDescription(std::string d);
    std::string toString();
    std::string toStringD();


    int cuteness;
    int scariness;
    int weirdness;
    std::string description;
    
};

Trait & operator+= (Trait & thisTrait, const Trait & other);
Trait operator+ (const Trait & traitA, const Trait & traitB);
#endif
