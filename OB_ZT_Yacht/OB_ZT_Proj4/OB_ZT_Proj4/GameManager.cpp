#include "yatch_chart.h"
#include "Scene.h"



vector<Chart> StartScene::setChart()
{
	ChartFactory factory;
	vector<Chart>playerchart;
	playerchart[0] = factory.GetChart();
	playerchart[1] = factory.GetChart("me");
	return playerchart;
}

/*
void GameScene::SetGameRound(int& game_round)
{
	game_round--;
}*/
/*
vector<int> GameScene::DrawScene(Chart& player)
{
	return player.GetRoundResult();
}*/
int GameScene::GetGameRound(vector<Chart>& player, int& game_round)
{
	GameScenePrev prev;
	GameSceneCal cal;
	GameSceneResult result;

	while (game_round > 0) //12���� �ݺ�
	{
		for (int i = 0; i < player.size(); i++) //chart ���� player�� �� ��ŭ , �� �÷��̾��� �� ��ŭ �ݺ�
		{
			int roll_count = 3;
			prev.DrawScene(player[i]); 			//�� ó�� ���� �Ѿ���� ���� �� ���� �����Ͽ� ���

			//�ִ� 3ȸ �ݺ�
			while (roll_count > 3)
			{
				//1 .dice ���� , �ֻ��� �� ��������
				vector<int>dice;  //���� �ʿ� ..... �ֻ��� ������

				//2. chart_value �� �ʱ�ȭ �� ���� ����
				player[i].SetDefaultValue(); //chart_value �� �ʱ�ȭ
				player[i].SetDiceValue(dice); //�ֻ��� �� �����ͼ� dice_num �ʱ�ȭ
				cal.DrawScene(player[i]); //���� ����� ����
				roll_count--;

				//�����ʿ�, UI���� select ���� �� select�� ĭ ��ȣ �о�ͼ� ������
				if (1)  //UI���� ������ ���� ǥ ���� ���
				{
					player[i].PushValue(1); //���ð�
					break;
				}
				else continue;
			}
			result.DrawScene(player[i]);
		}
		/*
			 // ���꿡 �̿��� vector<int> chart_value �ʱ�ȭ
			 // �ֻ��� �� vector<int> dice_num �� ����

			cal.DrawScene(player[i]);
			DrawScene(player[i].chart_value); //���� �� ��� �� �����ֱ�


			display���� ������ ��ġ �Է¹޾Ƽ� ���� �Է°� ������ �����س���
			player[i].PushValue();

			player[i].GetRoundResult();
			DrawScene(player[i].GetRoundResult());
		}*/
	}
	return 0;
}


vector<int>GameScenePrev::DrawScene(Chart& player)
{
	player.SetDefaultValue();
	return player.GetRoundResult(); //vector<int>Result �� ����
}

vector<int>GameSceneCal::DrawScene(Chart& player)
{
	player.SetDefaultValue();
	SetUpValue upvalue(&player);
	//SetUpValue upvalue(&player);
	CheckFOK fok(&player);
	CheckFH fh(&player);
	CheckSS ss(&player);
	CheckBS bs(&player);
	CheckYacht yatcht(&player);
	CheckChoice choice(&player);
	for (int i = 0; i < 6; i++)
	{
		if (upvalue.IsNullptr(&player.chart_value[i]))
			player.chart_value[i] = upvalue.SetValue(player.dice_num, i);
	} //���� ǥ �� ���

		//for of kind ���� choice ���� null ���� Ȯ�� �� �� ���� ����(chart_value�� �����Ѵ�)
	if (fok.IsNullptr(&player.chart_value[6])) //�Ʒ��� ǥ �� ���
		player.chart_value[6] = fok.SetValue(player.dice_num);

	if (fh.IsNullptr(&player.chart_value[7]))
		player.chart_value[7] = fh.SetValue(player.dice_num);

	if (ss.IsNullptr(&player.chart_value[8]))
		player.chart_value[8] = ss.SetValue(player.dice_num);

	if (bs.IsNullptr(&player.chart_value[9]))
		player.chart_value[9] = bs.SetValue(player.dice_num);

	if (yatcht.IsNullptr(&player.chart_value[10]))
		player.chart_value[10] = yatcht.SetValue(player.dice_num);

	if (choice.IsNullptr(&player.chart_value[11]))
		player.chart_value[11] = choice.SetValue(player.dice_num);
	return player.chart_value; //vector<int>chart_value �� ����
}

vector<int>GameSceneResult::DrawScene(Chart& player)
{
	player.SetSubTotal(); //�� ǥ �� ���
	player.SetBonus(); //
	player.SetTotalSum();
	return player.GetRoundResult();
}






