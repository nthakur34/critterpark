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

#include "../include/skin.hpp"
std::map<std::string, unsigned int> Skin::skinColorK;
std::map<unsigned int, Trait> Skin::skinColorM;
std::map<std::string, unsigned int> Skin::skinTypeK;
std::map<unsigned int, Trait> Skin::skinTypeM;



Skin::Skin(Encoding &g)
    :genome(g)
{
  //create traits
  Trait brown(-1, 2, 0, "Brown");
  Trait green(-2, 3, 0, "Green");
  Trait purple(3,-2, 1, "Purple");
  Trait transparent(-1, 1, 3, "Transparent");

  Trait scaly(-3, 3, 1, "Scaly");
  Trait slimy(-3, 2, 2, "Slimly");
  Trait hairless(-2, 2, 3, "Hairless");
  Trait fuzzy(3, -3, -3, "Fuzzy");

  //create all maps
  if ( skinColorM.empty()) {
    skinColorK["Brown"] = 0;
    skinColorK["Green"] = 1;
    skinColorK["Purple"] = 2;
    skinColorK["Transparent"] = 3;

    skinTypeK["Scaly"] = 0;
    skinTypeK["Slimy"] = 1;
    skinTypeK["Hairless"] = 2;
    skinTypeK["Fuzzy"] = 3;

    skinColorM[0] = brown;
    skinColorM[1] = green;
    skinColorM[2] = purple;
    skinColorM[3] = transparent;

    skinTypeM[0] = scaly;
    skinTypeM[1] = slimy;
    skinTypeM[2] = hairless;
    skinTypeM[3] = fuzzy;
}

  color = decodeSkinColor();
  skinType = decodeSkinType();
}
//encode the skin's descriptors
void Skin::encodeSkin(std::string skinColor, std::string skinType) {

  encodeSkinColor(skinColorK[skinColor]);
  encodeSkinType(skinTypeK[skinType]);

}

void Skin::encodeSkinColor(unsigned int number) {
  genome.setBitField(12, 2, number);
}

void Skin::encodeSkinType(unsigned int number) {
  genome.setBitField(14, 2, number);
}

std::string Skin::decodeSkin() {
  string answer = "The Critter also has " + decodeSkinType() + ", "
    + decodeSkinColor() + " skin.";

  return answer;

}


std::string Skin::decodeSkinColor() {
  colorNum = genome.getBitField(12, 2);
  color = skinColorM[colorNum].getDescription();
  return color;

}

std::string Skin::decodeSkinType() {
  typeNum = genome.getBitField(14, 2);
  skinType = skinTypeM[typeNum].getDescription();
  return skinType;

}
//get skinColor trait
Trait& Skin::skinColorTrait() {
  return skinColorM[genome.getBitField(12, 2)];
}
//get skinType trait
Trait& Skin::skinTypeTrait() {
  return skinTypeM[genome.getBitField(14, 2)];
}


//add all skin traits together
Trait Skin::addTraits() {
  return skinColorTrait() + skinTypeTrait();
}



void Skin::unitTest() {
  std::cout << "Starting unit tests for Skin...\n";

  Encoding genome;
  genome.setGenome(53919);

  Skin mySkin (genome);

  //decodeColor Test

  string colorOfSkin = mySkin.decodeSkinColor();
  if (colorOfSkin.compare("Green") == 0) {
    std::cout << "\tpassed decodeSkinColor \n";
  } else {
    std::cout << "\tfailed decodeSkinColor \n";
  }

  //encodeColor Test

  mySkin.encodeSkinColor(3);
  colorOfSkin = mySkin.decodeSkinColor();
  if (colorOfSkin.compare("Transparent") == 0) {
    std::cout << "\tpassed encodeSkinColor \n";
  } else {
    std::cout << "\tfailed encodeSkinColor \n";
  }

   //decodeType Test

  string typeOfSkin = mySkin.decodeSkinType();
  if (typeOfSkin.compare("Fuzzy") == 0) {
    std::cout << "\tpassed decodeSkinType \n";
  } else {
    std::cout << "\tfailed decodeSkinType \n";
  }

  //encodeType Test

  mySkin.encodeSkinType(0);
  typeOfSkin = mySkin.decodeSkinType();
  if (typeOfSkin.compare("Scaly") == 0) {
    std::cout << "\tpassed encodeSkinType \n";
  } else {
    std::cout << "\tfailed encodeSkinType \n";
  }

 //decodeSkin Test

  string skinTest = mySkin.decodeSkin();
  //std::cout<< limbTest <<"\n";
  string skinString = "The Critter also has Scaly, Transparent skin.";
  if (skinTest.compare(skinString) == 0) {
    std::cout << "\tpassed decodeSkin \n";
  } else {
    std::cout << "\tfailed decodeSkin \n";
  }

  //encodeSkin Test
  //
  mySkin.encodeSkin("Purple", "Hairless");
  skinTest = mySkin.decodeSkin();
  skinString = "The Critter also has Hairless, Purple skin.";
  if (skinTest.compare(skinString) == 0) {
    std::cout << "\tpassed decodeSkin \n";
  } else {
    std::cout << "\tfailed decodeSkin \n";
  }

  //addTrait test
  skinTest = mySkin.addTraits().toString();
  skinString ="cuteness: 1, scariness: 0, weirdness: 4";
  if (skinTest.compare(skinString) == 0) {
    std::cout << "\tpassed addTrait \n";
  } else {
    std::cout << "\tfailed addTrait \n";
  }

}
