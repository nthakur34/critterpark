/*
Navjyoth Thakur
2015-11-29

*/

#include "../include/hw11.hpp"
#include "GamePlay.hpp"

int main() {

  std::cout << "\x1b[2J";
  std::cout << "----------------------------------------------------------------\n";
  std::cout << "\x1b[36m";
  std::string intro = "Welcome to the wonderfully wondermazing Critter Park!\n";
  std::cout << intro;
  std::cout << "\x1b[0m";
  std::cout << "----------------------------------------------------------------\n";
  std::cout << "\x1b[36m";
  std::cout << "The option to display instructions will occur during the game.\n"
    "The instructions will display the rules and hints which can be very important!\n"
    "For example, ";
  std::cout << "\x1b[31m";
  std::cout << "STARTING OFF WITH AN ADMISSION FEE GREATER THAN $1 IS AN IMMEDIATE LOSS!\n";
    std::cout << "\x1b[0m";
  std::cout << "----------------------------------------------------------------\n";
  std::cout << "\x1b[36m";
  std::cout << "Our game will begin with four randomly generated critters!\n"
      "Give them names, and they'll be stuck with them for the rest of their \n"
      "short and meaningless lives!\n" << "Would you like to start (y or n): ";
  std::cout << "\x1b[0m";
  std::string reply;
  std::cin >> reply;
  while (reply.compare("y") != 0 && reply.compare("n") != 0) {
    std::cout << "\x1b[31m";
    std::cout << "\n What? just say y or n: ";
    std::cout << "\x1b[0m";
    std::cin >> reply;
  }
  std::cout << "\x1b[2J";

  if (reply.compare("n") == 0) {
    std::cout << "Well peace out then bruh. See you next time! Or not. w.e.\n";
  } else {
    GamePlay gamePlay;

  }
}
