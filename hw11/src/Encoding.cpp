/*
Navjyoth Thakur
2015-11-29

*/

#include "../include/Encoding.hpp"
#include <bitset>

typedef unsigned long encoding_t;



Encoding :: Encoding() {
  genome = 0;
}

void Encoding::setGenome(encoding_t number) {
  genome = number;
}

unsigned int Encoding::getBitField (int offset, int width) {
  //create mask that has ones where there are ones
  //in the place we want to decode
  //print(genome);
  encoding_t mask = 0;
  for (int i=0; i<width; i++) {
    mask <<= 1;
    mask +=1;
  }
  mask <<= offset;
  //print(mask);
  //get just the value
  mask &= genome;
  //print(genome);
  //print(mask);
  mask >>= offset;
  //print(mask);

  return mask;
}

void Encoding::setBitField (int offset, int width,
  unsigned int value) {
   //create mask that has ones where there are zeros in the place we want to encode
  //print(genome);
  encoding_t mask = 0;

  for (int i=0; i< width; i++) {
    mask <<= 1;
    mask += 1;
    //mask <<= 1;
  }
  mask <<= offset;
  mask = ~mask;
  //std::cout << "the mask\n";
  //print(mask);
  //offset value to location in genome
  value <<= offset;
  //std::cout <<"the value\n";
  //print(value);
  //set value in genome
  genome &= mask;
  //std::cout << "mask and genome\n";
  //print(genome);
  genome |= value;
  //std::cout << "final genome\n";
  //print(genome);
}



void Encoding::print(encoding_t bits) {
  std::bitset<sizeof(encoding_t)*8> n (bits);
  std::cout << n << " \n";

}

encoding_t Encoding::getGenome() {
  return genome;
}


void Encoding::mutate(double mutationRate) {
  encoding_t mask = 0;
  double r;
  for (int i=0; i < (int)sizeof(encoding_t) *8 ; i++) {
		r = (double)rand()/(double)RAND_MAX;
    if ( r < mutationRate) {
      mask += 1;
    }
    mask <<= 1;
  }
  //print(mask);
  //print(genome);
  genome ^=mask;
  //print(genome);

}

encoding_t Encoding::crossover(const encoding_t &other, double crossoverRate) {
  encoding_t mask = 0;
  bool p1 = true;
  double r;
  for (int i=0; i < (int)sizeof(encoding_t) *8 ; i++) {
		r = (double)rand()/(double)RAND_MAX;
    //std::cout << r <<" \n";
    //std::cout << crossoverRate<<"\n";
    if ( r < crossoverRate) {
			  p1 = !p1;
        //std::cout <<p1;
    }
		if (p1) {
		  mask += 1;
    }
    mask <<= 1;
  }
  //print(mask);
	mask &= genome;
  //print(mask);
	encoding_t tmp = ~mask && other;
  //print(tmp);
  mask |= tmp;
  //print(mask);
  return mask;
}

void Encoding::unitTest() {
  std::cout << "Starting unit tests for Encoding...\n";

  Encoding c;
  Encoding d;
  Encoding e;
  d.setGenome(4294967295);//all 1's
  //d.print(d.getGenome());
  e.setGenome(2147483647);//random number
  //e.print(e.getGenome());
  unsigned int offset = 2;
  unsigned int width = 4;
  unsigned int value  = 8;

  //test setBitField
  c.setBitField (offset, width, value);
  if (c.getGenome() == (value << offset)) {
    std::cout << "\tpassed setBitField \n";
  } else {
    std::cout << "\tfailed setBitField \n";
  }
  //test getBitField
  unsigned int getBit= c.getBitField (offset, width);
  if (getBit == value) {
    std::cout << "\tpassed getBitField \n";
   } else {
    std::cout << "\tfailed getBitField \n";
  }

  //test crossover
  Encoding f;
  Encoding g;//child
  g.setGenome(d.crossover(f.getGenome(),.2));
  std::cout << "\tcrossover genome: ";
  g.print(g.getGenome());
  std::cout << "\tpassed crossover \n";

  //test mutate
  g.mutate(.2);
  std::cout << "\tmutate genome: ";
  g.print(g.getGenome());
  std::cout << "\tpassed mutate \n";



  std::cout << "Done with unit tests for Encoding.\n";

}


