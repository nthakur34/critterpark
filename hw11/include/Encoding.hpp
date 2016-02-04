#ifndef _BEN_120_ENCODING_HPP
#define _BEN_120_ENCODING_HPP
#include <iostream>
#include <cstdlib>

typedef unsigned long encoding_t;

class Encoding {
  public:
    Encoding();
    void setGenome(encoding_t number);

    unsigned int getBitField (int offset, int width);
    void setBitField (int offset, int width,
        unsigned int value);
    
    void mutate(double mutationRate);
    encoding_t crossover(const encoding_t &other, double crossoverRate);
    static void unitTest();
    void print(encoding_t bits);
    encoding_t getGenome();

  private:
    encoding_t genome;

};
#endif
