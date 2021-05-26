#pragma once
#include <string>
#include <vector>
#include "Card.h"
#include "Score.h"

class Player
{
public:
  Player(std::string name, int id);
  void TakeACard(Card* card);
  void ShowMyCard();
  Card* DrawMyCard(int i);
  bool pibak();
  bool gwangbak();

  void PutACardOnFloor(Card* card);
  void ShowMyCardOnFloor();

  Card* SubPi();
  int CurrentScore();

  std::string name();
  std::vector<Card*>& cards();
  std::vector<Card*>& floorcards();

  int MaxScore();
  void SetMaxScore(int score);

  int FinalScore();

  int pi_score();
  int gwang_score();

  int go();
  void setGo();
  int money_rate(bool pibak, bool gwangbak);

  int id();

private:
  std::vector<Card*> cards_;
  std::vector<Card*> floorcards_;
  std::string name_;
  Score* score = new Score();
  int go_;
  bool pibak_;
  bool gwangbak_;
  int max_score_;
  int id_;

};