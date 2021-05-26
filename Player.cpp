#include <iostream>
#include "Player.h"

std::string Player::name() {
  return this->name_;
}
std::vector<Card*>& Player::cards() {
  return this->cards_;
}
std::vector<Card*>& Player::floorcards() {
  return this->floorcards_;
}

bool Player::pibak() { return this->pibak_; }
bool Player::gwangbak() { return this->gwangbak_; }

Player::Player(std::string name, int id) {
  this->name_ = name;
  this->id_ = id;
  this->pibak_ = false;
  this->gwangbak_ = false;
}

void Player::TakeACard(Card* card) {
  this->cards_.push_back(card);
}

void Player::ShowMyCard() {
  std::cout << name() << "님이 현재 손에 쥐고 있는 카드 : " << std::endl;
  for (int i = 0; i < cards().size(); i++) {
    std::cout << "[" << i << "] : " << cards().at(i)->ToString()
      << std::endl;
  }
}

Card* Player::DrawMyCard(int i) {
  Card* card = cards().at(i);
  cards().erase(cards().begin() + i);
  return card;
}

void Player::PutACardOnFloor(Card* card) {
  floorcards().push_back(card);
}

void Player::ShowMyCardOnFloor() {
  int count = 0;
  for (int i = 0; i < floorcards().size(); i++) {
    if (floorcards().at(i)->type() == 0 || floorcards().at(i)->type() == 1) {
      std::cout << floorcards().at(i)->ToString();
      count++;
    }
  }
  if (count != 0) {
    std::cout << "    ";
    count = 0;
  }
  for (int i = 0; i < floorcards().size(); i++) {
    if (floorcards().at(i)->type() == 2 || floorcards().at(i)->type() == 3) {
      std::cout << floorcards().at(i)->ToString();
      count++;
    }
  }
  if (count != 0) {
    std::cout << "    ";
    count = 0;
  }
  for (int i = 0; i < floorcards().size(); i++) {
    if (floorcards().at(i)->type() == 4 || floorcards().at(i)->type() == 5 ||
      floorcards().at(i)->type() == 6) {
      std::cout << floorcards().at(i)->ToString();
      count++;
    }
  }
  if (count != 0) {
    std::cout << "    ";
    count = 0;
  }
  for (int i = 0; i < floorcards().size(); i++) {
    if (floorcards().at(i)->type() == 7 || floorcards().at(i)->type() == 8) {
      std::cout << floorcards().at(i)->ToString();
      count++;
    }
  }
  if (count != 0) {
    std::cout << "    ";
    count = 0;
  }
  std::cout << std::endl;
}

Card* Player::SubPi() {
  Card* pi = NULL;
  for (int i = 0; i < floorcards().size(); i++) {
    if (floorcards().at(i)->type() == 7 || floorcards().at(i)->type() == 8) {
      pi = floorcards().at(i);
      floorcards().erase(floorcards().begin() + i);
      return pi;
    }
  }
  return pi;
}


int Player::CurrentScore() {
  int current_score = score->getScore(floorcards());
  this->pibak_ = (score->numofpi() <= 5);
  this->gwangbak_ = (score->numofgwang() == 0);

  return current_score;
}

int Player::go() { return this->go_; }
void Player::setGo() { this->go_++; }

int Player::MaxScore() {
  return this->max_score_;
}

void Player::SetMaxScore(int score) {
  this->max_score_ = score;
}

int Player::FinalScore() {
  int score = CurrentScore();
  if (this->go() < 3) {
    score += this->go();
  }
  else {
    for (int i = 0; i < this->go() - 2; i++) {
      score *= 2;
    }
  }
  return score;
}

int Player::money_rate(bool pibak, bool gwangbak) {
  int rate = 1;
  if (this->pibak() && pibak) {
    rate *= 2;
  }
  if (this->gwangbak() && gwangbak) {
    rate *= 2;
  }
  return rate;
}

int Player::id() {
  return this->id_;
}
int Player::pi_score() {
  return this->score->scoreofpi();
}
int Player::gwang_score() {
  return this->score->scoreofgwang();
}