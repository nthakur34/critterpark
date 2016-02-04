/*
Navjyoth Thakur
2015-11-29
*/

#include "../include/limbs.hpp"

std::map<std::string, unsigned int> Limbs::thicknessK;
std::map<unsigned int, Trait> Limbs::thicknessM;
std::map<unsigned int, Trait> Limbs::numM;


Limbs::Limbs(Encoding &g)
  :genome(g)
{
  //create Traits
  Trait spindly(1, -3, 3, "spindly");
  Trait thin(1, -2, 1, "thin");
  Trait thick(-2, 3, 0, "thick");
  Trait round(3, -1, -1, "round");

  Trait zero(0, 0, 3, "0");
  Trait one(1, 1, 3, "1");
  Trait two(3, 1, -3, "2");
  Trait three(-1, 1, 3, "3");
  Trait four(3, 1, -3, "4");
  Trait five(-1, 1, 3, "5");
  Trait six(2, 1, -3, "6");
  Trait seven(-2, 2, 3, "7");
  Trait eight(0, 3, 2, "8");
  Trait nine(-3, 2, 3, "9");
  Trait ten(-2, 3, 2, "10");
  Trait eleven(-3, 2, 3, "11");
  Trait twelve(-3, 3, 2, "12");
  Trait thirteen(-3, 2, 3, "13");
  Trait fourteen(-3, 3, 3, "14");
  Trait fifteen(-3, 2, 3, "15");



  //create all maps
  if (thicknessK.empty() ) {

    thicknessK["spindly"] = 0;
    thicknessK["thin"] = 1;
    thicknessK["thick"] = 2;
    thicknessK["round"] = 3;

    thicknessM[0] = spindly;
    thicknessM[1] = thin;
    thicknessM[2] = thick;
    thicknessM[3] = round;

    numM[0] = zero;
    numM[1] = one;
    numM[2] = two;
    numM[3] = three;
    numM[4] = four;
    numM[5] = five;
    numM[6] = six;
    numM[7] = seven;
    numM[8] = eight;
    numM[9] = nine;
    numM[10] = ten;
    numM[11] = eleven;
    numM[12] = twelve;
    numM[13] = thirteen;
    numM[14] = fourteen;
    numM[15] = fifteen;
  }

  //decode the number of limbs so that there can
  //only be a non-zero even number of them
  number = decodeNumber();
  int numValue = std::stoi(number);
  if (numValue % 2 != 0) {
    encodeNumber(numValue + 1);
    number = decodeNumber();
  }
  if (numValue == 0) {
    encodeNumber(2);
    number = decodeNumber();
  }

  thickness = decodeThickness();


}

//encode all descriptors of the limbs
void Limbs::encodeLimbs(unsigned int number, std :: string thickness) {
  //get numerical value per descriptor to encode
  encodeNumber(number);
  encodeThickness(thicknessK[thickness]);

}
//encode the number of limbs
void Limbs::encodeNumber(unsigned int number) {
  genome.setBitField (0, 4, number);

}
//encode the thickness of the limbs
void Limbs::encodeThickness(unsigned int number) {
  genome.setBitField(4, 2, number);

}
//decode the limbs into readable strings
string Limbs::decodeLimbs() {
  string answer = "has "+ decodeNumber()
    + " " + decodeThickness() + " limbs.";
  return answer;
}
//decode the number of limbs..
string Limbs::decodeNumber() {
  return numM[genome.getBitField(0,4)].getDescription();
}
//decode the thickness of the limbs
string Limbs::decodeThickness() {

  return thicknessM[genome.getBitField(4,2)].getDescription();
 }

//get number of Limbs trait
Trait& Limbs::numTrait() {
  return numM[genome.getBitField(0,4)];
}

//get thickness trait
Trait& Limbs::thicknessTrait() {
  return thicknessM[genome.getBitField(4,2)];
}

//add all limbs trait together
Trait Limbs::addTraits() {
  return numTrait() + thicknessTrait();
}

void Limbs::unitTest() {

  std::cout << "Starting unit tests for Limbs...\n";

  Encoding genome;
  genome.setGenome(21);

  //decodeNumber test
  //
  Limbs myLimbs (genome);
  string number = myLimbs.decodeNumber();
  if (number == "6") {
    std::cout << "\tpassed decodeNumber \n";
   } else {
    std::cout << "\tfailed decodeNumber \n";
  }

  //encodeNumber test

  myLimbs.encodeNumber(8);
  number = myLimbs.decodeNumber();
  if (number == "8") {
    std::cout << "\tpassed encodeNumber \n";
   } else {
    std::cout << "\tfailed encodeNumber \n";
  }

  //decodeThickness test

  string thickness = myLimbs.decodeThickness();
  if (thickness.compare("thin") == 0) {
    std::cout << "\tpassed decodeThickness \n";
   } else {
    std::cout << "\tfailed decodeThickness \n";
  }

  //encodeThickness test

  myLimbs.encodeThickness(3);
  thickness = myLimbs.decodeThickness();
  if (thickness.compare("thick")) {
    std::cout << "\tpassed encodeThickness \n";
   } else {
    std::cout << "\tfailed encodeThickness \n";
  }

 //decodeLimbs test

  string limbTest = myLimbs.decodeLimbs();
  string limbString = "has 8 round limbs.";
  if (limbTest.compare(limbString) == 0) {
    std::cout << "\tpassed decodeLimbs \n";
  } else {
    std::cout << "\tfailed decodeLimbs \n";
  }

  //encodeLimbs test

  myLimbs.encodeLimbs(9,"thick");
  limbTest = myLimbs.decodeLimbs();
  limbString = "has 9 thick limbs.";
  if (limbTest.compare(limbString) == 0) {
    std::cout << "\tpassed decodeLimbs \n";
  } else {
    std::cout << "\tfailed decodeLimbs \n";
  }

  //addTrait test
  limbTest = myLimbs.addTraits().toString();
  //std::cout << myLimbs.decodeLimbs();
  //std::cout <<limbTest<<"\n";
  limbString  = "cuteness: -5, scariness: 5, weirdness: 3";
  if (limbTest.compare(limbString) == 0) {
    std::cout << "\tpassed addTrait \n";
  } else {
    std::cout << "\tfailed addTrait \n";
  }


}
