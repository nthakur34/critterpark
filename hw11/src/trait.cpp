/*
Navjyoth Thakur
2015-11-29
*/

#include "../include/trait.hpp"

Trait::Trait(int c, int s, int w, std::string d)
  : cuteness(c), scariness(s), weirdness(w), description(d)
{
}

Trait::Trait()
  : cuteness(0), scariness(0), weirdness(0), description("")
{
}


std::string Trait::getDescription() {
  return description;
}

void Trait::setCuteness(int c) {
  cuteness = c;
}

void Trait::setScariness(int s) {
  scariness = s;
}

void Trait::setWeirdness(int w) {
  weirdness = w;
}

void Trait::setDescription(std::string d) {
  description =d;
}

//string with description
std::string Trait::toStringD() {
  std::string str = "cuteness: " + std::to_string(cuteness) + ", "
    + "scariness: " + std::to_string(scariness) + ", "
    + "weirdness: " + std::to_string(weirdness) + ", "
    + "description: " + description;
  return str;
}

//string without description
std::string Trait::toString() {
  std::string str = "cuteness: " + std::to_string(cuteness) + ", "
    + "scariness: " + std::to_string(scariness) + ", "
    + "weirdness: " + std::to_string(weirdness);
  return str;
}


void Trait::unitTest() {
  std::cout << "Starting unit tests for Trait...\n";

  //create a test map
  std::map<unsigned int, Trait> testMap;
  Trait spindly(1, -2, 3, "spindly");
  Trait thin(1, -1, 0, "thin");
  Trait thick(-2, 3, 0, "thick");
  Trait round(3, -2, 1, "round");
  testMap[0] = spindly;
  testMap[1] = thin;
  testMap[2] = thick;
  testMap[3] = round;

  //test toStringD
  //std::cout << testMap[0].toString() << "\n";
  if (testMap[0].toStringD() == "cuteness: 1, scariness: -2, weirdness: 3, description: spindly" ) {
    std::cout << "\tpassed toString \n";
  } else {
    std::cout << "\tfailed toString \n";
  }

  //test toString
  if (testMap[0].toString() == "cuteness: 1, scariness: -2, weirdness: 3" ) {
    std::cout << "\tpassed toString \n";
  } else {
    std::cout << "\tfailed toString \n";
  }



  //test operator+=
  Trait newTrait;
  newTrait += testMap[0];
  newTrait += testMap[1];
  //std::cout << newTrait.toString() + "\n";
  if (newTrait.toStringD() == "cuteness: 2, scariness: -3, weirdness: 3, description: ") {
    std::cout << "\tpassed operator+= \n";
  } else {
    std::cout << "\tfailed operator+= \n";
  }

  //test operator+
  newTrait = testMap[2] + testMap[3];
  //std::cout << newTrait.toString() + "\n";
  if (newTrait.toStringD() == "cuteness: 1, scariness: 1, weirdness: 1, description: ") {
    std::cout << "\tpassed operator+ \n";
  } else {
    std::cout << "\tfailed operator+ \n";
  }




  std::cout << "Done with unit tests for Critter.\n";


}



Trait & operator+= (Trait & thisTrait, const Trait & other) {
  thisTrait.setCuteness(thisTrait.cuteness + other.cuteness);
  thisTrait.setScariness(thisTrait.scariness + other.scariness);
  thisTrait.setWeirdness(thisTrait.weirdness + other.weirdness);
  thisTrait.setDescription("");
  return thisTrait;
}



Trait operator+ (const Trait & traitA, const Trait & traitB) {
  Trait thisTrait;
  thisTrait.setCuteness(traitA.cuteness + traitB.cuteness);
  thisTrait.setScariness(traitA.scariness + traitB.scariness);
  thisTrait.setWeirdness(traitA.weirdness+ traitB.weirdness);
  thisTrait.setDescription("");

  return thisTrait;

}
