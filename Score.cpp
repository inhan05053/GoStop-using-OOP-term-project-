#include<iostream>
#include "Score.h"
#include "Player.h"


int Score::getScore(std::vector<Card*>& vector) {
  total_score_ = 0;
  scoreofpi_ = 0;
  scoreofgwang_ = 0;
  for (int i = 0; i < 9; i++) {
    numoftype[i] = 0;
  }
  for (int i = 0; i < vector.size(); i++) {
    numoftype[vector.at(i)->type()]++;
  }
  if (numoftype[0] + numoftype[1] == 5) {   //���� �� ���� �հ�
    total_score_ += 15;
    scoreofgwang_ += 15;
  }
  else if (numoftype[0] + numoftype[1] == 4) {
    total_score_ += 4;
    scoreofgwang_ += 4;
  }
  else if (numoftype[0] == 2 && numoftype[1] == 1) {
    total_score_ += 2;
    scoreofgwang_ += 2;
  }
  else if (numoftype[0] == 3) {
    total_score_ += 3;
    scoreofgwang_ += 3;
  }

  if (numoftype[3] == 3) { //����
    total_score_ += 5;
  }
  if (numoftype[2] >= 5) {  //���� (���� - 4 = ����)
    total_score_ += (numoftype[2] - 4);
  }


  if (numoftype[4] == 3) { //�ʴ�
    total_score_ += 3;
  }
  if (numoftype[5] == 3) {  //û��
    total_score_ += 3;
  }
  if (numoftype[6] == 3) {  //ȫ��
    total_score_ += 3;
  }

  if (numoftype[4] + numoftype[5] + numoftype[6] >= 5) {  //ûȫ�� ���� �հ���
    total_score_ += (numoftype[4] + numoftype[5] + numoftype[6] - 4);
  }

  if (numoftype[7] + (2 * numoftype[8]) >= 10) {  //��
    total_score_ += (numoftype[7] + (2 * numoftype[8]) - 9);
    scoreofpi_ += (numoftype[7] + (2 * numoftype[8]) - 9);
  }

  if (scoreofpi_ < 0) {
    scoreofpi_ = 0;
  }

  numofgwang_ = numoftype[0] + numoftype[1];
  numofpi_ = numoftype[7] + (2 * numoftype[8]);

  return total_score_;
}