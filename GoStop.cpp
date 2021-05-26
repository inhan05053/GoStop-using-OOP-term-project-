#include "GoStop.h"
#include <Windows.h>

void GoStop::Play() {

  std::cout << "<<���� ������ �����մϴ�>>\n" << std::endl;

  InitGame(); // �� �ʱ�ȭ (�ٴڿ� 6��, ���� 7�徿 �й�)

  while (1) {
    if (card_stack.empty()) break;

    if (TurnOf(player1)) {
      VictoryOf(player1);
      break;
    }

    if (TurnOf(player2)) {
      VictoryOf(player2);
      break;
    }

    if (TurnOf(player3)) {
      VictoryOf(player3);
      break;
    }

  }

  if (nagari) {
    system("cls");
    ShowTable();
    std::cout << "�������Դϴ�." << std::endl;
  }

  std::cout << "<<���� ������ �����մϴ� >>" << std::endl;

}

void GoStop::InitGame() {

  std::cout << "1�� ������ �̸��� �Է��ϼ��� : ";
  player1 = InputPlayerName(1);

  std::cout << "2�� ������ �̸��� �Է��ϼ��� : ";
  player2 = InputPlayerName(2);

  std::cout << "3�� ������ �̸��� �Է��ϼ��� : ";
  player3 = InputPlayerName(3);

  std::cout << std::endl;
  std::cout << "1���� ������ �Է��ϼ��� : ";
  std::cin >> price;

  std::sort(card, card + 48); // ī�� ����

  for (int i = 0; i < 48; i++) {
    card_stack.push(&card[i]);
  }

  for (int i = 0; i < 6; i++) {   // �ٴڿ� ī�� 6�� ���
    floor.push_back(card_stack.top());
    card_stack.pop();
  }

  for (int i = 0; i < 7; i++) { // player1 ī�� 7��
    player1->TakeACard(card_stack.top());
    card_stack.pop();
  }

  for (int i = 0; i < 7; i++) { // player2 ī�� 7��
    player2->TakeACard(card_stack.top());
    card_stack.pop();
  }

  for (int i = 0; i < 7; i++) { // player3 ī�� 7��
    player3->TakeACard(card_stack.top());
    card_stack.pop();
  }
}

Player* GoStop::InputPlayerName(int id) {
  std::string str;
  std::cin >> str;
  Player* player = new Player(str, id);
  return player;
}

void GoStop::ShowTable() {
  std::cout << "===[�ٴ�]=====================================================================" << std::endl;
  ShowCardsOf(floor);
  std::cout << std::endl;
  std::cout << "===[" << player1->name() << "]===================================================================" << std::endl;
  player1->ShowMyCardOnFloor();
  std::cout << std::endl;
  std::cout << "===[" << player2->name() << "]===================================================================" << std::endl;
  player2->ShowMyCardOnFloor();
  std::cout << std::endl;
  std::cout << "===[" << player3->name() << "]===================================================================" << std::endl;
  player3->ShowMyCardOnFloor();
  std::cout << std::endl;
  std::cout << "==============================================================================" << std::endl;
}

int GoStop::TurnOf(Player* player) {

  system("cls");
  ShowTable();

  std::cout << player->name() << "���� �����Դϴ�. ���� �Ͻ÷��� �ƹ� ���ڳ� �Է��ϼ��� : ";
  std::string str;
  std::cin >> str;

  std::cout << std::endl;
  player->ShowMyCard();

  std::cout << "�� ī�带 �����ϼ��� : ";
  int i;
  std::cin >> i;
  Card* drawed_card = player->DrawMyCard(i);
  std::cout << "���� ī�带 �����Ͽ����ϴ� : " << drawed_card->ToString() << std::endl;
  std::cout << "==============================================================================" << std::endl;

  DrawCard(drawed_card, player);

  if (player->CurrentScore() >= 3 && player->MaxScore() < player->CurrentScore()) { // ������ �Ǵ�
    system("cls");
    ShowTable();
    std::cout << player->name() << "���� " << player->CurrentScore() << "������ �����ϴ�." << std::endl;
    if (player->cards().size() == 0) {
      std::cout << "���̻� ī�尡 �������� �ʾ� �ڵ����� �����մϴ�." << std::endl; // �¸�
      Sleep(5000);
      nagari = false;
      return player->CurrentScore();
    }
    std::cout << "��(1) or ����(0) : ";
    int choice;
    std::cin >> choice;
    if (choice) {
      player->setGo();
      player->SetMaxScore(player->CurrentScore());
    }
    else {
      nagari = false;
      return player->CurrentScore(); // �¸�
    }
  }
  return 0;
}

void GoStop::ShowCardsOf(std::vector<Card*> vec) {

  for (int i = 0; i < vec.size(); i++) {
    std::cout << vec.at(i)->ToString() << " ";
  }
  std::cout << std::endl;
}

void GoStop::DrawCard(Card* card, Player* player) {

  std::cout << "�ٴ� Ȯ�� ��...";
  Sleep(1000);

  int month = card->month();
  std::vector<Card*> same_month_cards = GetSameMonthCards(card, floor);

  Card* poped_card;

  if (same_month_cards.size() == 0) {
    std::cout << "��ġ�ϴ� ī�尡 ���� �ٴڿ� �����ϴ�." << std::endl;
    std::cout << "==============================================================================" << std::endl;
    poped_card = PopACard();
    if (card->month() == poped_card->month()) {
      // ��
      std::cout << "���Դϴ�! �� ī�带 �Խ��ϴ�." << std::endl;
      player->PutACardOnFloor(card);
      player->PutACardOnFloor(poped_card);
      std::cout << "�ٸ� �����ڵ��� �Ǹ� �� �徿 ����ɴϴ�." << std::endl;
      GetOnePiFromOther(player);
    }
    else {
      floor.push_back(card);
      DrawForPoppedCard(poped_card, player);
    }
  }
  else if (same_month_cards.size() == 1) {
    std::cout << "�ٴڿ� ��ġ�ϴ� ī�尡 �ϳ� �ֽ��ϴ� : " << same_month_cards.at(0)->ToString() << std::endl;
    std::cout << "==============================================================================" << std::endl;
    poped_card = PopACard();
    if (card->month() == poped_card->month()) {
      // ��
      std::cout << "�����ϴ�. ī�带 ���� �� �Ͽ����ϴ�." << std::endl;
      floor.push_back(card);
      floor.push_back(same_month_cards.at(0));
      floor.push_back(poped_card);
    }
    else {
      player->PutACardOnFloor(card);
      player->PutACardOnFloor(same_month_cards.at(0));
      DrawForPoppedCard(poped_card, player);
      std::cout << "���� ī�带 �Ծ����ϴ� : " << same_month_cards.at(0)->ToString() << std::endl;
    }
  }
  else if (same_month_cards.size() == 2) {

    std::cout << std::endl;
    for (int i = 0; i < same_month_cards.size(); i++) {
      std::cout << i << " : " << same_month_cards.at(i)->ToString() << std::endl;
    }
    std::cout << "�� ī�� �� �ϳ��� �����Ͽ� ���� �� �ֽ��ϴ� : ";
    int choice;
    std::cin >> choice;
    std::cout << "���� ī�带 �����Ͽ����ϴ� : " << same_month_cards.at(choice)->ToString() << std::endl;
    std::cout << "==============================================================================" << std::endl;
    poped_card = PopACard();
    if (card->month() == poped_card->month()) {
      // ����
      std::cout << "�����Դϴ�! ���� ī�带 �߰��� �Խ��ϴ� : " << same_month_cards.at(!choice)->ToString() << std::endl;
      player->PutACardOnFloor(card);
      player->PutACardOnFloor(same_month_cards.at(0));
      player->PutACardOnFloor(same_month_cards.at(1));
      player->PutACardOnFloor(poped_card);
      std::cout << "�ٸ� �����ڵ��� �Ǹ� �� �徿 ����ɴϴ�." << std::endl;
      GetOnePiFromOther(player);
    }
    else {
      floor.push_back(same_month_cards.at(!choice));
      player->PutACardOnFloor(same_month_cards.at(choice));
      player->PutACardOnFloor(card);
      DrawForPoppedCard(poped_card, player);
      std::cout << "���� ī�带 �Ծ����ϴ� : " << same_month_cards.at(choice)->ToString() << std::endl;
    }
  }
  else {
    // �Ѱ� ���� ó��
    std::cout << "���� �Ծ����ϴ�! ���� ī����� ��� �Խ��ϴ� : " << same_month_cards.at(0)->ToString() << " " <<
      same_month_cards.at(1)->ToString() << " " << same_month_cards.at(2)->ToString() << std::endl;
    std::cout << "==============================================================================" << std::endl;
    std::cout << "�ٸ� �����ڵ��� �Ǹ� �� �徿 ����ɴϴ�." << std::endl;
    GetOnePiFromOther(player);
    poped_card = PopACard();
    player->PutACardOnFloor(card);
    player->PutACardOnFloor(same_month_cards.at(0));
    player->PutACardOnFloor(same_month_cards.at(1));
    player->PutACardOnFloor(same_month_cards.at(2));
    DrawForPoppedCard(poped_card, player);
  }
  std::cout << "���� ������ �Ѿ���� �ƹ� ���ڳ� �Է��ϼ��� : ";
  std::string str;
  std::cin >> str;
}

Card* GoStop::PopACard() {

  if (!floor.empty()) {
    Card* poped_card = card_stack.top();
    card_stack.pop();
    std::string str;
    std::cout << "ī�� �� ���� �����÷��� �ƹ� ���ڳ� �Է��ϼ��� : ";
    std::cin >> str;
    std::cout << "==============================================================================" << std::endl;
    std::cout << "ī�� �� ���� �������ϴ�...";
    Sleep(1000);
    std::cout << "������ ī�尡 ���Խ��ϴ� : " << poped_card->ToString() << std::endl;
    Sleep(1000);
    std::cout << "�ٴ� Ȯ�� ��...";
    Sleep(1000);
    return poped_card;
  }
  return NULL;
}

std::vector<Card*> GoStop::GetSameMonthCards(Card* card, std::vector<Card*>& vector) {

  std::vector<Card*> same_month_cards;

  for (int i = 0; i < vector.size(); i++) {
    if (vector.at(i)->month() == card->month()) {
      same_month_cards.push_back(vector.at(i));
      vector.erase(vector.begin() + i);
      i--;
    }
  }
  return same_month_cards;
}

void GoStop::DrawForPoppedCard(Card* poped_card, Player* player) {
  std::vector<Card*> same_month_cards = GetSameMonthCards(poped_card, floor);
  if (same_month_cards.size() == 0) {
    std::cout << "��ġ�ϴ� ī�尡 ���� �ٴڿ� �����ϴ�." << std::endl;
    floor.push_back(poped_card);
  }
  else if (same_month_cards.size() == 1) {
    std::cout << "���� ī�带 �߰��� �Խ��ϴ� : " << same_month_cards.at(0)->ToString() << std::endl;
    player->PutACardOnFloor(same_month_cards.at(0));
    player->PutACardOnFloor(poped_card);
  }
  else if (same_month_cards.size() == 2) {
    std::cout << std::endl;
    for (int i = 0; i < same_month_cards.size(); i++) {
      std::cout << i << " : " << same_month_cards.at(i)->ToString() << std::endl;
    }
    std::cout << "�� ī�� �� �ϳ��� �߰��� �����Ͽ� ���� �� �ֽ��ϴ� : ";
    int choice;
    std::cin >> choice;
    std::cout << "���� ī�带 �Խ��ϴ� : " << same_month_cards.at(choice)->ToString() << std::endl;
    player->PutACardOnFloor(poped_card);
    player->PutACardOnFloor(same_month_cards.at(choice));
    floor.push_back(same_month_cards.at(!choice));
  }
  else {
    // �Ѱ� ���� ó��
    std::cout << "���� �Ծ����ϴ�! ���� ī����� ��� �Խ��ϴ� : " << same_month_cards.at(0)->ToString() << " " <<
      same_month_cards.at(1)->ToString() << " " << same_month_cards.at(2)->ToString() << std::endl;
    player->PutACardOnFloor(poped_card);
    player->PutACardOnFloor(same_month_cards.at(0));
    player->PutACardOnFloor(same_month_cards.at(1));
    player->PutACardOnFloor(same_month_cards.at(2));
    std::cout << "�ٸ� �����ڵ��� �Ǹ� �� �徿 ����ɴϴ�." << std::endl;
    GetOnePiFromOther(player);
  }
}

void GoStop::VictoryOf(Player* player) {
  system("cls");
  ShowTable();
  int winner_score = player->FinalScore();
  if (player->pi_score() > 0) {
    pibak = true;
  }
  if (player->gwang_score() > 0) {
    gwangbak = true;
  }
  std::cout << player->name() << "���� " << winner_score << "������ �¸��ϼ̽��ϴ�!!" << std::endl;
  std::cout << "���� ������ ���Ƽ : ";
  if (pibak) std::cout << "�ǹ� ";
  if (gwangbak)  std::cout << "����";
  std::cout << std::endl << std::endl;

  if (player->id() != player1->id()) {
    if (player1->pibak() && pibak) {
      std::cout << player1->name() << "���� �ǹ��Դϴ�." << std::endl;
    }
    if (player1->gwangbak() && gwangbak) {
      std::cout << player1->name() << "���� �����Դϴ�." << std::endl;
    }
    std::cout << player1->name() << "���� ���ž� �� �� : " << winner_score << " x " << player1->money_rate(pibak, gwangbak) <<
      " x " << price << " = " << winner_score * player1->money_rate(pibak, gwangbak) * price << " �Դϴ�." << std::endl;
    std::cout << std::endl;
  }

  if (player->id() != player2->id()) {
    if (player2->pibak() && pibak) {
      std::cout << player2->name() << "���� �ǹ��Դϴ�." << std::endl;
    }
    if (player2->gwangbak() && gwangbak) {
      std::cout << player2->name() << "���� �����Դϴ�." << std::endl;
    }
    std::cout << player2->name() << "���� ���ž� �� �� : " << winner_score << " x " << player2->money_rate(pibak, gwangbak) <<
      " x " << price << " = " << winner_score * player2->money_rate(pibak, gwangbak) * price << " �Դϴ�." << std::endl;
    std::cout << std::endl;
  }

  if (player->id() != player3->id()) {
    if (player3->pibak() && pibak) {
      std::cout << player3->name() << "���� �ǹ��Դϴ�." << std::endl;
    }
    if (player3->gwangbak() && gwangbak) {
      std::cout << player3->name() << "���� �����Դϴ�." << std::endl;
    }
    std::cout << player3->name() << "���� ���ž� �� �� : " << winner_score << " x " << player3->money_rate(pibak, gwangbak) <<
      " x " << price << " = " << winner_score * player3->money_rate(pibak, gwangbak) * price << " �Դϴ�." << std::endl;
    std::cout << std::endl;
  }

}

void GoStop::GetOnePiFromOther(Player* player) {
  int id = player->id();

  if (player1->id() != id) {
    Card* one_pi = player1->SubPi();
    if (one_pi != NULL) {
      std::cout << player1->name() << "�����κ��� ���� �� ������ ����ɴϴ� : " << one_pi->ToString() << std::endl;
      player->PutACardOnFloor(one_pi);
    }
    else {
      std::cout << player1->name() << "���� �ǰ� ��� ������ �� �Ͽ����ϴ�." << std::endl;
    }
  }

  if (player2->id() != id) {
    Card* one_pi = player2->SubPi();
    if (one_pi != NULL) {
      std::cout << player2->name() << "�����κ��� ���� �� ������ ����ɴϴ� : " << one_pi->ToString() << std::endl;
      player->PutACardOnFloor(one_pi);
    }
    else {
      std::cout << player2->name() << "���� �ǰ� ��� ������ �� �Ͽ����ϴ�." << std::endl;
    }
  }

  if (player3->id() != id) {
    Card* one_pi = player3->SubPi();
    if (one_pi != NULL) {
      std::cout << player3->name() << "�����κ��� ���� �� ������ ����ɴϴ� : " << one_pi->ToString() << std::endl;
      player->PutACardOnFloor(one_pi);
    }
    else {
      std::cout << player3->name() << "���� �ǰ� ��� ������ �� �Ͽ����ϴ�." << std::endl;
    }
  }
}