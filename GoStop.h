#pragma once
#include "Card.h"
#include "Player.h"
#include <stack>
#include <iostream>
#include <algorithm>

class GoStop
{
public:
  void Play();
private:
  // ī�� ��ü �迭
  Card card[48] = {
      Card(1, 0, std::rand()), Card(1, 6, std::rand()), Card(1, 7, std::rand()), Card(1, 7, std::rand()),
      Card(2, 2, std::rand()), Card(2, 6, std::rand()), Card(2, 7, std::rand()), Card(2, 7, std::rand()),
      Card(3, 0, std::rand()), Card(3, 6, std::rand()), Card(3, 7, std::rand()), Card(3, 7, std::rand()),
      Card(4, 3, std::rand()), Card(4, 4, std::rand()), Card(4, 7, std::rand()), Card(4, 7, std::rand()),
      Card(5, 2, std::rand()), Card(5, 4, std::rand()), Card(5, 7, std::rand()), Card(5, 7, std::rand()),
      Card(6, 2, std::rand()), Card(6, 5, std::rand()), Card(6, 7, std::rand()), Card(6, 7, std::rand()),
      Card(7, 2, std::rand()), Card(7, 4, std::rand()), Card(7, 7, std::rand()), Card(7, 7, std::rand()),
      Card(8, 0, std::rand()), Card(8, 3, std::rand()), Card(8, 7, std::rand()), Card(8, 7, std::rand()),
      Card(9, 8, std::rand()), Card(9, 5, std::rand()), Card(9, 7, std::rand()), Card(9, 7, std::rand()),
      Card(10, 2, std::rand()), Card(10, 5, std::rand()), Card(10, 7, std::rand()), Card(10, 7, std::rand()),
      Card(11, 0, std::rand()), Card(11, 8, std::rand()), Card(11, 7, std::rand()), Card(11, 7, std::rand()),
      Card(12, 1, std::rand()), Card(12, 2, std::rand()), Card(12, 4, std::rand()), Card(12, 8, std::rand())
  };

  // �÷��̾�
  Player* player1;
  Player* player2;
  Player* player3;

  // ���� ��
  int price;

  // �� ����
  bool pibak = false;
  bool gwangbak = false;

  // ī�� ��
  std::stack<Card*> card_stack;

  // �ٴڿ� �� ī��
  std::vector<Card*> floor;

  // ������ ����
  bool nagari = true;

  // �Լ�
  void InitGame();
  Player* InputPlayerName(int id);
  int TurnOf(Player* player);
  void ShowCardsOf(std::vector<Card*> vec);
  void ShowTable();
  void DrawCard(Card* card, Player* player);
  Card* PopACard();
  std::vector<Card*> GetSameMonthCards(Card* card, std::vector<Card*>& vector);
  void DrawForPoppedCard(Card* poped_card, Player* player);
  void GetOnePiFromOther(Player* player);
  void VictoryOf(Player* player);
};
