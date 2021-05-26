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
    str += "��";
    break;
  case 1:
    str += "��";
    break;
  case 2:
    str += "��";
    break;
  case 3:
    str += "����";
    break;
  case 4:
    str += "�ʴ�";
    break;
  case 5:
    str += "û��";
    break;
  case 6:
    str += "ȫ��";
    break;
  case 7:
    str += "��";
    break;
  case 8:
    str += "����";
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