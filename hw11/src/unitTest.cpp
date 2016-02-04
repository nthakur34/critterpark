/*
HW11 for 600.120.02, Fall 2015

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

#include "../include/unitTest.hpp"

int main() {
  string paragraph = "UnitTest Driver: \n"
            "1 Quit\n"
            "2 All Unit Tests \n"
            "3 Final test \n"
            "4 Encoding \n"
            "5 Critter \n"
            "6 Limbs\n"
            "7 Eyes\n"
            "8 Skin\n"
            "9 Trait\n"
            "10 GameStats\n"
            "11 Park\n"
            "Run this test: ";
  std::cout << paragraph;
  int testNumber;
  std::cin >> testNumber;
  while (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Please Enter valid input\n";
    std::cin >> testNumber;
    }
  while (testNumber!= 1 ) {
    switch (testNumber) {
      case 4:
        Encoding::unitTest();
        break;
      case 5:
        Critter::unitTest();
        break;
      case 6:
        Limbs::unitTest();
        break;
      case 7:
        Eyes::unitTest();
        break;
      case 8:
        Skin::unitTest();
        break;
      case 2:
        Encoding::unitTest();
        Critter::unitTest();
        Limbs::unitTest();
        Eyes::unitTest();
        Skin::unitTest();
        Trait::unitTest();
        GameStats::unitTest();
        Park::unitTest();
        break;
      case 9:
        Trait::unitTest();
        break;
      case 10:
        GameStats::unitTest();
        break;
      case 11:
        Park::unitTest();
        break;
      default:
        break;
      }
    std::cout << paragraph;
    std::cin >> testNumber;
    while (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore();
      std::cout << "Please Enter valid input\n";
      std::cin >> testNumber;
    }
  }
  std::cout << "Quiting UnitTest Driver\n";
  return 0;
}
