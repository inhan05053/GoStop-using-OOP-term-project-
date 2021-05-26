#pragma once
#include <string>

class Card
{
public:
  // getters
  int month();
  int type();
  int id();
  std::string ToString();

  // constructor
  Card(int month, int type, int id);

  // operator
  bool operator <(Card& card);

private:
  int month_;
  int type_;
  int id_;
};

