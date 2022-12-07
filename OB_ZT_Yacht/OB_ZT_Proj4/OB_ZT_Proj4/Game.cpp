#include "yatch_chart.h"



GameManage::GameManage()
{
	int round, turn, roll;
	ChartFactory factory;
	vector<Chart>player;
	player[0] = factory.GetChart();
	player[1] = factory.GetChart();

	vector<int>dice; // �ֻ��� �� �ӽð�
	int winner;

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; i < 2; j++)
		{
			for (int x = 0; x < 3; x++)
			{
				//RoundTurnRollDraw()
				while (1)
				{
					int command = 0;
					switch (command)
					{
					case 1: //�ֻ��� ����
						player[i].SetDiceValue(dice);
						player[i].SetDefaultValue();
						player[i].CalSet();
						//DiceValueDraw();
						//TableValueDraw(player[i].GetChartValue());

					case 2:
						//���� �ڵ�� ���� �����,,,��Ф�..
						/*
						Ŀ���� �����̽��� ������ ��->�갡 �� ��° �ֻ������� ���� ������
						�Է¹޴� �ְ� ��ȯ���ָ� ����
						�ֻ��� ��ȣ�� �ٱ� ?
						�ش� ���̽�.Toggle()
						DiceKeepDraw(int �� ��° �ֻ���)-- > �׵θ��� ���� �׷����� Keep ������ �� �˾ƾ� ��
						DiceActivateDraw(int �� ��° �ֻ���)-- > �׵θ��� �ƹ��͵� ���� #�⺻ ����
						*/

					case 3:
						int getreturn = 0;
						player[i].PushValue(getreturn);
						player[i].SetSubTotal();
						player[i].SetBonus();
						player[i].SetTotalSum();
						// player[i].GetRoundResult();
						//draw
					}
				}
			}
		}
		winner = player[0].Winner(player[1]);
	}
}
