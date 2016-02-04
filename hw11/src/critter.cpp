/*
Navjyoth Thakur
nthakur2
nthakur2@jhu.edu
2019236387
2015-11-29

Sherry Chiu
schiu9
schiu9@jhu.edu
7329476211
2015-11-29
*/

#include "../include/critter.hpp"

Critter::Critter(std::string n) //constructor
  : name(n)
{
  //  Encoding genome;
  srand(time(NULL));

  int r; //random genome value to set as encoding
  temp = 0;
  for (int i=0; i < 16; i++) {
  r = rand() % 2;
      temp <<= 1;
      temp += r;
  }
  genome.setGenome(temp);
  //create limbs
  Limbs limbs(genome);
  //store string representing limbs
  limbString = limbs.decodeLimbs();
  //create eye
  Eyes eyes(genome);
  //store string representing eyes
  eyeString = eyes.decodeEyes();
  Skin skin(genome);
  skinString = skin.decodeSkin();
  //store string representing traits
  totalTrait = traitString(limbs, eyes, skin);
  allTrait =  limbs.addTraits() + eyes.addTraits() + skin.addTraits(); //added this line
  cuteRep = allTrait.cuteness;
  scaryRep = allTrait.scariness;
  weirdRep = allTrait.weirdness;

}

//Change Encoding, with temp, while m is mutation factor
//redo constructor operations to get new feature values
void Critter::setGenome(unsigned long temp, double m) {
  genome.setGenome(temp);
  genome.mutate(m);
  Limbs limbs(genome);
  limbString = limbs.decodeLimbs();
  Eyes eyes(genome);
  eyeString = eyes.decodeEyes();
  Skin skin(genome);
  skinString = skin.decodeSkin();

  totalTrait = traitString(limbs, eyes, skin);
  allTrait =  limbs.addTraits() + eyes.addTraits() + skin.addTraits(); //added this line
  cuteRep = allTrait.cuteness;
  scaryRep = allTrait.scariness;
  weirdRep = allTrait.weirdness;



}

//get name of critter
std::string Critter::getName() {
  return name;

}
//set name of critter
void Critter::setName(std::string n) {
  name = n;
}
//get the genome from critter
unsigned long Critter::getGenome() {
  return temp;
}
//get string representation of traits
std::string Critter::getTraits() {
  return totalTrait + "\n";
}
//Get the actual encoding of Critter
Encoding Critter::getEncoding() {
  return genome;
}
//overload << operator to return string representation of critter
std::ostream & operator<< (std::ostream& os, Critter &critter) {

  os << critter.toString() << "\n" << critter.getTraits() << std::endl; //add on traits
  return os;
}

//overload == operator to compare critters
int operator== (Critter &critterA, Critter &critterB) {

  if (critterA.getName().compare(critterB.getName()) == 0) {
    return 1;
  }

  return 0;
}
//overload < operator to compare critters
inline int operator< (Critter &critterA, Critter &critterB) {

  if (critterA.getName().compare(critterB.getName()) < 0) {
    return 1;
  }

  return 0;
}
//get string representation of features of critter
std::string Critter::toString() {
  std::string output = "Critter: " + getName() + " " + limbString + " " +
    eyeString + " " + skinString + "\n";

  return output;
}
//get string representation of traits of critter
std::string Critter::traitString(Limbs & limbs, Eyes & eyes, Skin & skin) {
  Trait totalTrait =  limbs.addTraits() + eyes.addTraits() + skin.addTraits();
  return totalTrait.toString();
}

int Critter::getCuteRep() {//added
  return cuteRep;
}

int Critter::getScaryRep() {//added
  return scaryRep;
}

int Critter::getWeirdRep() {//added
  return weirdRep;
}


void Critter::unitTest() {
  std::cout << "Starting unit tests for Critter...\n";

  //getName
  Critter c;
  if ((c.getName()).compare("") == 0) {
    std::cout << "\tpassed getName1\n";
  } else {
    std::cout << "\tfailed getName1\n";
  }

  //setName
  std::string name = "fluffy";
  c.setName(name);
  if ((c.getName()).compare("fluffy") == 0) {
    std::cout << "\tpassed setName1\n";
  } else {
    std::cout << "\tfailed setName1\n";
  }
  name = "Shadow";
  //Critter(name)
  Critter f(name);
  if ((f.getName()).compare("Shadow") == 0) {
    std::cout << "\tpassed Critter(name)\n";
  } else {
    std::cout << "\tfailed Critter(name)\n";
  }

  //test traitsToString (getTraits)

  f.setGenome(53919);

  std::string testString = "cuteness: 3, scariness: -2, weirdness: 3\n";

  if ((f.getTraits()).compare(testString) == 0) {
    std::cout << "\tpassed getTraits\n";
  } else {
    std::cout << "\tfailed getTraits\n";
  }

  //test toString

  testString = "Critter: Shadow has 0 thin limbs. It has 10 Blue eyes."
               " The Critter also has Fuzzy, Green skin.\n";

  if ((f.toString()).compare(testString) == 0) {
    std::cout << "\tpassed toString\n";
  } else {
    std::cout << "\tfailed toString\n";
  }

  //test == operator

  Critter g(name);

  if ((f == g)) {
    std::cout << "\tpassed operator==\n";
  } else {
    std::cout << "\tfailed operator==\n";
  }

   //test < operator

  Critter m("Patrick");

  if ((m < f)) {
    std::cout << "\tpassed operator<\n";
  } else {
    std::cout << "\tfailed operator<\n";
  }



  std::cout << "Done with unit tests for Critter...\n";


}


