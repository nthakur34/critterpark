HW11 for 600.120.02, Fall 2015

Navjyoth Thakur
2015-11-29

This program allows the player to manage a farm and a critter-themed park. Instructions
are available in game, at any time for the player to access. The goal is to reach $10,000.

Source Files:
hw11.cpp - The main function, where the player can decide whether or not to play the game
eyes.cpp - The eyes feature, which contains color and amount
GamePlay.cpp - The actual game play
FarmUI.cpp - Game interface for user to manage the critter farm.
Park.cpp - runs functions which are mostly used in ParkUI.cpp
ParkUI.cpp - game interface for user to handle critter park.
trait.cpp - handles the traits of each critter
limbs.cpp - the limbs feature, which contains thickness and number
skin.cpp - the skin feature, which contains color and type
unitTest.cpp - Runs the test which is capable of running all unit tests
critter.cpp - Critter object which contains all the features
Encoding.cpp - Handles the bitstring genome used for breeding
gameStats.cpp - Carries values to be used in the farm and park such as a list of critters.
Makefile - contains commands to compile and run unitTest.c through create the hw11
executable.


To run the test, run "make".
To run the actual program, run "make all", and then "../bin/hw11"
To run a test run of the main game play, run "../data/testGame.sh"
  -It simulates all the bad inputs and correct inputs and checks that the
    functions in the classes work as they should. Make sure to scroll up 
    to see what each input does.

Chose .03 as the mutation factor, and .1 for the crossover factor.

Warning: FarmUI does not have a unitTest since it doesnt act as an object, but
rather it simply acts upon a map of critters passed onto it. it also uses its
functions by passing on the map, so creating a test would just be playing around
int the barn, and not automated. The same case applies for GamePlay and ParkUI.

GAMEPLAY: the game is made to be a little more difficult so reading instructions
would really make it a lot simpler to understand. they can also be called up at any time
during the game by pressing 'i'.


