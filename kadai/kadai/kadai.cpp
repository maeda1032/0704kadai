
#include <iostream>

class Charactor {
public:
	int AttackFase(int attack,bool playerCheck);

	int Death(int enemyDeathCount)
	{
		enemyDeathCount++;
		return enemyDeathCount;
	}
	
	//クラスの中に構造体を入れる手段が見つかりませんでした。
	struct CharaStatus {
	public:

	};
		int HP;
		int Attack;
	
};

int Charactor::AttackFase(int attack,bool playerCheck)
{
	if (playerCheck == true)
	{
		attack = rand() % 20;

		std::cout << "player攻撃" << attack << "ダメージ" << std::endl;
	}
	else
	{
		attack = rand() % 10;

		std::cout << "敵の攻撃" << attack << "ダメージ" << std::endl;
	}
	return attack;
}

int Turn(int turn)
{
	turn++;

	std::cout << "" << std::endl;
	std::cout << "turn開始" << turn << "ターン目" << std::endl;

	return turn;
}

void Result(int turn,int playerMaxDamage,int enemyMaxDamage)
{
	std::cout << "決着までのターン数:" << turn << std::endl;
	std::cout << "プレイヤーが与えた最大ダメージ:" << playerMaxDamage << std::endl;
	std::cout << "敵が与えた最大ダメージ" << enemyMaxDamage << std::endl;
}

int main()
{
	bool enemyBreak = false;
	//enemyDeathCountが２になったらゲーム終了
	int enemyDeathCount = 0;

	//インスタンスの宣言
	std::unique_ptr<Charactor> player(new Charactor);
	std::unique_ptr<Charactor> slime(new Charactor);
	std::unique_ptr<Charactor> goblin(new Charactor);

	//ランダムに生成するために使用
	srand(time(NULL));

	//それぞれをランダムに設定50~100いない
	player->HP = rand() % 51 + 50;
	slime->HP = rand() % 51 + 50;
	goblin->HP = rand() % 51 + 50;



	//初期体力の記載
	std::cout << "PlayerHP" << player->HP << std::endl;
	std::cout << "SlimeHP" << slime->HP << std::endl;
	std::cout << "GoblinHP" << goblin->HP << std::endl;

	//変数の初期値を0に
	int turn = 0;
	int playerMaxAttack = 0;
	int enemyMaxAttack = 0;

	//ターンの処理を開始
	while (player->HP >= 0)
	{
		turn += Turn(turn);

		//攻撃力の決定
		int a;
		std::cout << "攻撃する対象を選択してください1:slime,2:goblin" << std::endl;
		std::cin >> a;

		//プレイヤーの攻撃ターン
		player->AttackFase(player->Attack, true);
		if (player->Attack >= playerMaxAttack)
		{
			playerMaxAttack = player->Attack;
		}

		//1はすらいむのHPを減らす処理
		if (a == 1)
		{
			slime->HP -= player->Attack;
			if (slime->HP <= 0)
			{
				enemyDeathCount++;
			}
		}
		//2はごぶりんのHPを減らす処理
		else
		{
			goblin->HP -= player->Attack;
			if (goblin->HP <= 0)
			{
				enemyDeathCount++;
			}
		}


		//敵キャラクターの攻撃ターン

		if (slime->HP > 0)
		{
			slime->AttackFase(slime->Attack,false);

			//playerの体力を減らす
			player->HP -= slime->Attack;

			//hp0以下なら死亡
			if (player->HP <= 0)
			{
				std::cout << "playerが死亡しました" << std::endl;
				break;
			}
			
			//最大攻撃力の更新
			if (slime->Attack >= enemyMaxAttack)
			{
				enemyMaxAttack = slime->Attack;
			}
		}

		if (goblin->HP > 0)
		{
			//攻撃力の決定
			goblin->AttackFase(goblin->Attack, false);

			//playerの体力を減らす
			player->HP -= goblin->Attack;

			//hp0以下なら死亡
			if (player->HP <= 0)
			{
				std::cout << "playerが死亡しました" << std::endl;
				break;
			}
			//最大攻撃力の更新
			if (goblin->Attack >= enemyMaxAttack)
			{
				enemyMaxAttack = goblin->Attack;
			}
		}

		//敵を2体倒したらゲーム終了
		if (enemyDeathCount >= 2)
		{
			break;
		}
		std::cout << "slimeの残りHP" << slime->HP << std::endl;
		std::cout << "goblinの残りHP" << goblin->HP << std::endl;
		std::cout <<"playerの残りhp" << player->HP << std::endl;

	}

	Result(turn,playerMaxAttack,enemyMaxAttack);

	return 0;
}
