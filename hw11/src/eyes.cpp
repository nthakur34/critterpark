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

#include "../include/eyes.hpp"
std::map<std::string, unsigned int> Eyes::eyeColorK;
std::map<unsigned int, Trait> Eyes::eyeColorM;
std::map<unsigned int, Trait> Eyes::numEyesM;

Eyes::Eyes(Encoding &g)
    :genome(g)
{
  //createTraits
  Trait blue(3, -3, 0, "Blue");
  Trait red(-3, 3, 1, "Red");
  Trait green(2, 1, 1, "Green");
  Trait rainbow(1, -3, 3, "Rainbow");

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
  if(eyeColorK.empty() ) {
    eyeColorK["Blue"] = 0;
    eyeColorK["Red"] = 1;
    eyeColorK["Green"] = 2;
    eyeColorK["Rainbow"] = 3;

    eyeColorM[0] = blue;
    eyeColorM[1] = red;
    eyeColorM[2] = green;
    eyeColorM[3] = rainbow;

    numEyesM[0] = zero;
    numEyesM[1] = one;
    numEyesM[2] = two;
    numEyesM[3] = three;
    numEyesM[4] = four;
    numEyesM[5] = five;
    numEyesM[6] = six;
    numEyesM[7] = seven;
    numEyesM[8] = eight;
    numEyesM[9] = nine;
    numEyesM[10] = ten;
    numEyesM[11] = eleven;
    numEyesM[12] = twelve;
    numEyesM[13] = thirteen;
    numEyesM[14] = fourteen;
    numEyesM[15] = fifteen;


  }


  //get the number of eyes, while making sure
  //only a non-zero even number
  numEyes = decodeNumEyes();
  int numValue = std::stoi(numEyes);
  if (numValue % 2 != 0) {
    encodeNumEyes(numValue + 1);
    numEyes = decodeNumEyes();
  }
  if (numValue == 0) {
    encodeNumEyes(2);
    numEyes = decodeNumEyes();
  }
  color = decodeEyeColor();
}


//Encode every descriptor of the eyes
void Eyes::encodeEyes(unsigned int number, std::string eyeColor) {
  //use array to encode numerical value

  encodeEyeColor(eyeColor);
  encodeNumEyes(number);

}
//encode the color of the eyes
void Eyes::encodeEyeColor(std::string eyeColor) {
  genome.setBitField(10, 2, eyeColorK[eyeColor]);
}
//encode the number of eyes
void Eyes::encodeNumEyes(unsigned int number) {
   genome.setBitField(6, 4, number);
}
//Decode the eyes into a readable text
std::string Eyes::decodeEyes() {
  string answer = "It has "+ decodeNumEyes() + " "
    + decodeEyeColor() + " eyes.";
  return answer;

}

//decode the color of the eye
std::string Eyes::decodeEyeColor() {
  return eyeColorM[genome.getBitField(10, 2)].getDescription();

}
//decode the number of eyes
std::string Eyes::decodeNumEyes() {
  return numEyesM[genome.getBitField(6, 4)].getDescription();
}
//get numEyes trait
Trait& Eyes::numEyesTrait() {
  return numEyesM[genome.getBitField(6, 4)];
}

//get eyeColor Trait
Trait& Eyes::eyeColorTrait() {
  return eyeColorM[genome.getBitField(10, 2)];
}

//add all eye traits
Trait Eyes::addTraits() {
  return eyeColorTrait() + numEyesTrait();
}

//start the unit test for Eyes
void Eyes::unitTest() {
  std::cout << "Starting unit tests for Eyes...\n";

  Encoding genome;
  genome.setGenome(1230);

  //decodeNumber Test

  Eyes myEyes (genome);
  std:: string number = myEyes.decodeNumEyes();
  if (number.compare("4") == 0) {
    std::cout << "\tpassed decodeNumEyes \n";
  } else {
    std::cout << "\tfailed decodeNumEyes \n";
  }

  //encodeNumber Test

  myEyes.encodeNumEyes(5);
  number = myEyes.decodeNumEyes();
  if (number.compare("5") == 0) {
    std::cout << "\tpassed encodeNumEyes \n";
  } else {
    std::cout << "\tfailed encodeNumEyes \n";
  }


  //decodeColor test

  string colorOfEye = myEyes.decodeEyeColor();
  if (colorOfEye.compare("Red") == 0) {
    std::cout << "\tpassed decodeEyeColor \n";
  } else {
    std::cout << "\tfailed decodeEyeColor \n";
  }

  //encodeColor Test

  myEyes.encodeEyeColor("Rainbow");
  colorOfEye = myEyes.decodeEyeColor();
  if (colorOfEye.compare("Rainbow") == 0) {
    std::cout << "\tpassed encodeEyeColor \n";
  } else {
    std::cout << "\tfailed encodeEyeColor \n";
  }

 //decode eyes test

  string eyeTest = myEyes.decodeEyes();
  string eyeString = "It has 5 Rainbow eyes.";
  if (eyeTest.compare(eyeString) == 0) {
    std::cout << "\tpassed decodeEyes \n";
  } else {
    std::cout << "\tfailed decodeEyes \n";
  }

  //encode eyes test

  myEyes.encodeEyes(8,"Blue");
  eyeTest = myEyes.decodeEyes();
  eyeString = "It has 8 Blue eyes.";
  if (eyeTest.compare(eyeString) == 0) {
    std::cout << "\tpassed decodeEyes \n";
  } else {
    std::cout << "\tfailed decodeEyes \n";
  }

  //addTrait test
  eyeTest = myEyes.addTraits().toString();
  std::cout << myEyes.decodeEyes();
  std::cout <<eyeTest<<"\n";
  eyeString  = "cuteness: 3, scariness: 0, weirdness: 2";
  if (eyeTest.compare(eyeString) == 0) {
    std::cout << "\tpassed addTrait \n";
  } else {
    std::cout << "\tfailed addTrait \n";
  }


}
