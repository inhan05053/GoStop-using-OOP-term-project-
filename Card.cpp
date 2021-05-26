#include "Card.h"

int Card::month() {
  return this->month_;
}

int Card::type() {
  return this->type_;
}

int Card::id() {
  return this->id_;
}

std::string Card::ToString() {
  std::string str = "[" + std::to_string(this->month());
  switch (this->type())
  {
  case 0:
    str += "±¤";
    break;
  case 1:
    str += "ºñ±¤";
    break;
  case 2:
    str += "²ý";
    break;
  case 3:
    str += "°íµµ¸®";
    break;
  case 4:
    str += "ÃÊ´Ü";
    break;
  case 5:
    str += "Ã»´Ü";
    break;
  case 6:
    str += "È«´Ü";
    break;
  case 7:
    str += "ÇÇ";
    break;
  case 8:
    str += "½ÖÇÇ";
    break;
  default:
    break;
  }
  str += "]";
  return str;
}

Card::Card(int month, int type, int id) {
  this->month_ = month;
  this->type_ = type;
  this->id_ = id;
}

bool Card::operator<(Card& card) {
  return this->id() < card.id();
}