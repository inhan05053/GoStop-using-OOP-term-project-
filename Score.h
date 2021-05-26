#pragma once
#include <vector>
#include "Card.h"

class Score {
public:
  int getScore(std::vector<Card*>& vector);
  int numoftype[9] = {
      0,
  };

  int numofgwang() { return this->numofgwang_; }
  int numofpi() { return this->numofpi_; }
  int scoreofpi() { return this->scoreofpi_; }
  int scoreofgwang() { return this->scoreofgwang_; }

private:
  int total_score_ = 0;
  int numofgwang_ = 0;
  int numofpi_ = 0;
  int scoreofpi_ = 0;
  int scoreofgwang_ = 0;
};
