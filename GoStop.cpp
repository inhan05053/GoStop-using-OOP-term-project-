#include "GoStop.h"
#include <Windows.h>

void GoStop::Play() {

  std::cout << "<<고스톱 게임을 시작합니다>>\n" << std::endl;

  InitGame(); // 판 초기화 (바닥에 6장, 각각 7장씩 분배)

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
    std::cout << "나가리입니다." << std::endl;
  }

  std::cout << "<<고스톱 게임을 종료합니다 >>" << std::endl;

}

void GoStop::InitGame() {

  std::cout << "1번 참가자 이름을 입력하세요 : ";
  player1 = InputPlayerName(1);

  std::cout << "2번 참가자 이름을 입력하세요 : ";
  player2 = InputPlayerName(2);

  std::cout << "3번 참가자 이름을 입력하세요 : ";
  player3 = InputPlayerName(3);

  std::cout << std::endl;
  std::cout << "1점당 가격을 입력하세요 : ";
  std::cin >> price;

  std::sort(card, card + 48); // 카드 섞기

  for (int i = 0; i < 48; i++) {
    card_stack.push(&card[i]);
  }

  for (int i = 0; i < 6; i++) {   // 바닥에 카드 6장 깔기
    floor.push_back(card_stack.top());
    card_stack.pop();
  }

  for (int i = 0; i < 7; i++) { // player1 카드 7장
    player1->TakeACard(card_stack.top());
    card_stack.pop();
  }

  for (int i = 0; i < 7; i++) { // player2 카드 7장
    player2->TakeACard(card_stack.top());
    card_stack.pop();
  }

  for (int i = 0; i < 7; i++) { // player3 카드 7장
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
  std::cout << "===[바닥]=====================================================================" << std::endl;
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

  std::cout << player->name() << "님의 차례입니다. 진행 하시려면 아무 글자나 입력하세요 : ";
  std::string str;
  std::cin >> str;

  std::cout << std::endl;
  player->ShowMyCard();

  std::cout << "낼 카드를 선택하세요 : ";
  int i;
  std::cin >> i;
  Card* drawed_card = player->DrawMyCard(i);
  std::cout << "다음 카드를 선택하였습니다 : " << drawed_card->ToString() << std::endl;
  std::cout << "==============================================================================" << std::endl;

  DrawCard(drawed_card, player);

  if (player->CurrentScore() >= 3 && player->MaxScore() < player->CurrentScore()) { // 낫는지 판단
    system("cls");
    ShowTable();
    std::cout << player->name() << "님이 " << player->CurrentScore() << "점으로 낫습니다." << std::endl;
    if (player->cards().size() == 0) {
      std::cout << "더이상 카드가 남아있지 않아 자동으로 스톱합니다." << std::endl; // 승리
      Sleep(5000);
      nagari = false;
      return player->CurrentScore();
    }
    std::cout << "고(1) or 스톱(0) : ";
    int choice;
    std::cin >> choice;
    if (choice) {
      player->setGo();
      player->SetMaxScore(player->CurrentScore());
    }
    else {
      nagari = false;
      return player->CurrentScore(); // 승리
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

  std::cout << "바닥 확인 중...";
  Sleep(1000);

  int month = card->month();
  std::vector<Card*> same_month_cards = GetSameMonthCards(card, floor);

  Card* poped_card;

  if (same_month_cards.size() == 0) {
    std::cout << "일치하는 카드가 없어 바닥에 놓습니다." << std::endl;
    std::cout << "==============================================================================" << std::endl;
    poped_card = PopACard();
    if (card->month() == poped_card->month()) {
      // 쪽
      std::cout << "쪽입니다! 두 카드를 먹습니다." << std::endl;
      player->PutACardOnFloor(card);
      player->PutACardOnFloor(poped_card);
      std::cout << "다른 참가자들의 피를 한 장씩 뺏어옵니다." << std::endl;
      GetOnePiFromOther(player);
    }
    else {
      floor.push_back(card);
      DrawForPoppedCard(poped_card, player);
    }
  }
  else if (same_month_cards.size() == 1) {
    std::cout << "바닥에 일치하는 카드가 하나 있습니다 : " << same_month_cards.at(0)->ToString() << std::endl;
    std::cout << "==============================================================================" << std::endl;
    poped_card = PopACard();
    if (card->month() == poped_card->month()) {
      // 뻑
      std::cout << "쌋습니다. 카드를 먹지 못 하였습니다." << std::endl;
      floor.push_back(card);
      floor.push_back(same_month_cards.at(0));
      floor.push_back(poped_card);
    }
    else {
      player->PutACardOnFloor(card);
      player->PutACardOnFloor(same_month_cards.at(0));
      DrawForPoppedCard(poped_card, player);
      std::cout << "다음 카드를 먹었습니다 : " << same_month_cards.at(0)->ToString() << std::endl;
    }
  }
  else if (same_month_cards.size() == 2) {

    std::cout << std::endl;
    for (int i = 0; i < same_month_cards.size(); i++) {
      std::cout << i << " : " << same_month_cards.at(i)->ToString() << std::endl;
    }
    std::cout << "두 카드 중 하나를 선택하여 먹을 수 있습니다 : ";
    int choice;
    std::cin >> choice;
    std::cout << "다음 카드를 선택하였습니다 : " << same_month_cards.at(choice)->ToString() << std::endl;
    std::cout << "==============================================================================" << std::endl;
    poped_card = PopACard();
    if (card->month() == poped_card->month()) {
      // 따닥
      std::cout << "따닥입니다! 다음 카드를 추가로 먹습니다 : " << same_month_cards.at(!choice)->ToString() << std::endl;
      player->PutACardOnFloor(card);
      player->PutACardOnFloor(same_month_cards.at(0));
      player->PutACardOnFloor(same_month_cards.at(1));
      player->PutACardOnFloor(poped_card);
      std::cout << "다른 참가자들의 피를 한 장씩 뺏어옵니다." << std::endl;
      GetOnePiFromOther(player);
    }
    else {
      floor.push_back(same_month_cards.at(!choice));
      player->PutACardOnFloor(same_month_cards.at(choice));
      player->PutACardOnFloor(card);
      DrawForPoppedCard(poped_card, player);
      std::cout << "다음 카드를 먹었습니다 : " << same_month_cards.at(choice)->ToString() << std::endl;
    }
  }
  else {
    // 싼거 먹음 처리
    std::cout << "뻑을 먹었습니다! 다음 카드들을 모두 먹습니다 : " << same_month_cards.at(0)->ToString() << " " <<
      same_month_cards.at(1)->ToString() << " " << same_month_cards.at(2)->ToString() << std::endl;
    std::cout << "==============================================================================" << std::endl;
    std::cout << "다른 참가자들의 피를 한 장씩 뺏어옵니다." << std::endl;
    GetOnePiFromOther(player);
    poped_card = PopACard();
    player->PutACardOnFloor(card);
    player->PutACardOnFloor(same_month_cards.at(0));
    player->PutACardOnFloor(same_month_cards.at(1));
    player->PutACardOnFloor(same_month_cards.at(2));
    DrawForPoppedCard(poped_card, player);
  }
  std::cout << "다음 순서로 넘어가려면 아무 글자나 입력하세요 : ";
  std::string str;
  std::cin >> str;
}

Card* GoStop::PopACard() {

  if (!floor.empty()) {
    Card* poped_card = card_stack.top();
    card_stack.pop();
    std::string str;
    std::cout << "카드 한 장을 뽑으시려면 아무 글자나 입력하세요 : ";
    std::cin >> str;
    std::cout << "==============================================================================" << std::endl;
    std::cout << "카드 한 장을 뒤집습니다...";
    Sleep(1000);
    std::cout << "다음의 카드가 나왔습니다 : " << poped_card->ToString() << std::endl;
    Sleep(1000);
    std::cout << "바닥 확인 중...";
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
    std::cout << "일치하는 카드가 없어 바닥에 놓습니다." << std::endl;
    floor.push_back(poped_card);
  }
  else if (same_month_cards.size() == 1) {
    std::cout << "다음 카드를 추가로 먹습니다 : " << same_month_cards.at(0)->ToString() << std::endl;
    player->PutACardOnFloor(same_month_cards.at(0));
    player->PutACardOnFloor(poped_card);
  }
  else if (same_month_cards.size() == 2) {
    std::cout << std::endl;
    for (int i = 0; i < same_month_cards.size(); i++) {
      std::cout << i << " : " << same_month_cards.at(i)->ToString() << std::endl;
    }
    std::cout << "두 카드 중 하나를 추가로 선택하여 먹을 수 있습니다 : ";
    int choice;
    std::cin >> choice;
    std::cout << "다음 카드를 먹습니다 : " << same_month_cards.at(choice)->ToString() << std::endl;
    player->PutACardOnFloor(poped_card);
    player->PutACardOnFloor(same_month_cards.at(choice));
    floor.push_back(same_month_cards.at(!choice));
  }
  else {
    // 싼거 먹음 처리
    std::cout << "뻑을 먹었습니다! 다음 카드들을 모두 먹습니다 : " << same_month_cards.at(0)->ToString() << " " <<
      same_month_cards.at(1)->ToString() << " " << same_month_cards.at(2)->ToString() << std::endl;
    player->PutACardOnFloor(poped_card);
    player->PutACardOnFloor(same_month_cards.at(0));
    player->PutACardOnFloor(same_month_cards.at(1));
    player->PutACardOnFloor(same_month_cards.at(2));
    std::cout << "다른 참가자들의 피를 한 장씩 뺏어옵니다." << std::endl;
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
  std::cout << player->name() << "님이 " << winner_score << "점으로 승리하셨습니다!!" << std::endl;
  std::cout << "적용 가능한 페널티 : ";
  if (pibak) std::cout << "피박 ";
  if (gwangbak)  std::cout << "광박";
  std::cout << std::endl << std::endl;

  if (player->id() != player1->id()) {
    if (player1->pibak() && pibak) {
      std::cout << player1->name() << "님은 피박입니다." << std::endl;
    }
    if (player1->gwangbak() && gwangbak) {
      std::cout << player1->name() << "님은 광박입니다." << std::endl;
    }
    std::cout << player1->name() << "님이 내셔야 할 돈 : " << winner_score << " x " << player1->money_rate(pibak, gwangbak) <<
      " x " << price << " = " << winner_score * player1->money_rate(pibak, gwangbak) * price << " 입니다." << std::endl;
    std::cout << std::endl;
  }

  if (player->id() != player2->id()) {
    if (player2->pibak() && pibak) {
      std::cout << player2->name() << "님은 피박입니다." << std::endl;
    }
    if (player2->gwangbak() && gwangbak) {
      std::cout << player2->name() << "님은 광박입니다." << std::endl;
    }
    std::cout << player2->name() << "님이 내셔야 할 돈 : " << winner_score << " x " << player2->money_rate(pibak, gwangbak) <<
      " x " << price << " = " << winner_score * player2->money_rate(pibak, gwangbak) * price << " 입니다." << std::endl;
    std::cout << std::endl;
  }

  if (player->id() != player3->id()) {
    if (player3->pibak() && pibak) {
      std::cout << player3->name() << "님은 피박입니다." << std::endl;
    }
    if (player3->gwangbak() && gwangbak) {
      std::cout << player3->name() << "님은 광박입니다." << std::endl;
    }
    std::cout << player3->name() << "님이 내셔야 할 돈 : " << winner_score << " x " << player3->money_rate(pibak, gwangbak) <<
      " x " << price << " = " << winner_score * player3->money_rate(pibak, gwangbak) * price << " 입니다." << std::endl;
    std::cout << std::endl;
  }

}

void GoStop::GetOnePiFromOther(Player* player) {
  int id = player->id();

  if (player1->id() != id) {
    Card* one_pi = player1->SubPi();
    if (one_pi != NULL) {
      std::cout << player1->name() << "님으로부터 다음 피 한장을 뺏어옵니다 : " << one_pi->ToString() << std::endl;
      player->PutACardOnFloor(one_pi);
    }
    else {
      std::cout << player1->name() << "님은 피가 없어서 빼앗지 못 하였습니다." << std::endl;
    }
  }

  if (player2->id() != id) {
    Card* one_pi = player2->SubPi();
    if (one_pi != NULL) {
      std::cout << player2->name() << "님으로부터 다음 피 한장을 뺏어옵니다 : " << one_pi->ToString() << std::endl;
      player->PutACardOnFloor(one_pi);
    }
    else {
      std::cout << player2->name() << "님은 피가 없어서 빼앗지 못 하였습니다." << std::endl;
    }
  }

  if (player3->id() != id) {
    Card* one_pi = player3->SubPi();
    if (one_pi != NULL) {
      std::cout << player3->name() << "님으로부터 다음 피 한장을 뺏어옵니다 : " << one_pi->ToString() << std::endl;
      player->PutACardOnFloor(one_pi);
    }
    else {
      std::cout << player3->name() << "님은 피가 없어서 빼앗지 못 하였습니다." << std::endl;
    }
  }
}