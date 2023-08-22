#include "stdafx.h"
//#include "Ready_Ui.h"

Ready_Ui::Ready_Ui()
	: Gold_Defalt_Max(10), Levelcount(0)
{
	LBaseposition = Vector3(50, 50, 0);
	RBaseposition = Vector3(WinMaxWidth - 50, 50, 0);
	Buttonsize = Vector3(50, 50, 0);
	Buttonoffset = Buttonsize * 0.1;

	Level_UI_size = Vector3(28, 50, 0);
	Gold_UI_size = Vector3(30, 30, 0);
	Gold_Now_Max = Goldhavenow = 9;

	LevelUpCost = 0;
	Level_Max = 6;

	defRoundButton = new Button(
		Vector3(0, 0, 0),
		Buttonsize,
		L"RoundButton",
		L"Small_Button.png",
		L"Small_Button_press.png",
		L"Head_pattern.png"
	);
	defRoundButton->SetRender();
	Button_list.Get()->push_back(defRoundButton);

// ��ư ���� ������
#pragma region Button
	{
		UpgradeButton = new Button(
		Vector3(0,0,0),
		Buttonsize,
		L"UI_ResetButton",
		L"Small_Button.png",
		L"Small_Button_press.png",
		L"Upgrade_pattern.png"
		);
		UpgradeButton->SetRender();

		LockButton = new Button(
		Vector3(0, 0, 0),
		Buttonsize,
		L"UI_ResetButton",
		L"Small_Button.png",
		L"Small_Button_press.png",
		L"Lock_pattern.png"
		);
		LockButton->SetRender();

		ReButton = new Button(
		Vector3(0, 0, 0),
		Buttonsize,
		L"UI_ResetButton",
		L"Small_Button.png",
		L"Small_Button_press.png",
		L"Re_pattern.png"
		);
		ReButton->SetRender();

		ReadyButton = new Button(
		Vector3(0, 0, 0),
		Buttonsize,
		L"UI_ResetButton",
		L"Small_Button.png",
		L"Small_Button_press.png",
		L"Right_arrow_pattern.png"
		);
		ReadyButton->SetRender();
	}

	{
		Button_list.Get()->push_back(ReButton);
		Button_list.Get()->push_back(ReadyButton);
		Button_list.Get()->push_back(UpgradeButton);
		Button_list.Get()->push_back(LockButton);
	}
#pragma endregion

// �� ���� ������
#pragma region GoldUI
	for (int def = 0; def < Gold_Defalt_Max; def++) {

		UI_Obejct* gold = new UI_Obejct(
		Vector3(0, 0, 0),
		Gold_UI_size, 0.0,
		L"Gold_UI_" +std::to_wstring(def + 1),
		L"Gold_on_patten.png",
		L"Gold_off_patten.png");

		gold->SetRender();  // ��ȭ�� ������ ������ ���� �ʰ� �ؾ��Ѵ�.
							// ���븶�� ��ȭ�� �ö�� �ϱ� ����.
							// ���ÿ��� offó�� �ؾ��Ѵ�.
		Gold.push_back(gold);
	}

	for (auto def : Gold) {
		Ready_UI_list.Get()->push_back(def);
	}

#pragma endregion

// Level ���� ������
#pragma region Level
	for(int def = 0; def < Level_Max; def++) {
			// Level�� ������ �̸� �ִ밪�� ǥ���ϰ� �۾��Ѵ�.
			// Level�� ����ؼ� �������� ��찡 ���� ����.
		Level.push_back( 
		new UI_Obejct(
		Vector3(0,0,0),
		Level_UI_size,0.0,
		L"Level_UI_" + std::to_wstring(def+1), 
		L"Level_on_patten.png",
		L"Level_off_patten.png"));
	}

	for (auto def : Level) {
		Ready_UI_list.Get()->push_back(def); 
	}
	
	

#pragma endregion
}

void Ready_Ui::Update()
{
	defRoundButton->SetPosition (GetCMPosition(LBaseposition, Buttonsize, Buttonoffset, 2.0, 2));
	ReButton->SetPosition		(GetCMPosition(LBaseposition, Buttonsize, Buttonoffset, 0.0, 2));
	ReadyButton->SetPosition	(GetCMPosition(LBaseposition, Buttonsize, Buttonoffset, 1.0, 2));
	UpgradeButton->SetPosition	(GetCMPosition(LBaseposition, Buttonsize, Buttonoffset, 0.0, 0));
	LockButton->SetPosition		(GetCMPosition(LBaseposition, Buttonsize, Buttonoffset, 0.5, 1));

	for (int i = 0; i < Gold.size(); i++) {
		Gold[i]->SetPosition	(GetCMPosition(RBaseposition, Gold_UI_size, Gold_UI_size * 0.1, i + 1, -0.5, true));
	};

	int levelLastpos =  0;
	for (levelLastpos = 0; levelLastpos < Level.size(); levelLastpos++) {
		Level[levelLastpos]->SetPosition	(GetCMPosition(LBaseposition, Level_UI_size, Vector3(0, 0, 0), levelLastpos + 2, -0.1));
	};

	//upcostp = FontClass::Get()->MakeString(std::to_wstring(LevelUpCost), 
	//GetCMPosition(LBaseposition, Level_UI_size, Vector3(0, 0, 0), levelLastpos + 3, -0.1),
	//Color(0,0,0,1),
	//Buttonsize,
	//LEFT,
	//1);

	upcostp.Render();

	LevelChack();
	GoldChack();
}

Vector3 Ready_Ui::GetCMPosition(const Vector3 Basepositon, const Vector3 size, const Vector3 offset, const float x, const float y, bool flipx)
{
	Vector3 result;

	float flip;
	flipx ? flip = -1 : flip = 1;
	result = Basepositon + Camera::Get()->GetPosition() +
	(Vector3(size.x * x * flip, size.y * y, 0) +
	Vector3(offset.x * (x-1) * flip, offset.y * (y-1), 0)) ;

	return result;
}

void Ready_Ui::LevelUP()
{
	if( Levelcount < Level_Max &&  // ������ ������ �ƴϰ�
		Goldhavenow >= LevelUpCost) { // ���� ���� ���� �ڽ�Ʈ���� ũ�ų� �������,

		Goldhavenow -= LevelUpCost;		// �����ڽ�Ʈ ��ŭ ��������.
		Levelcount++; // ���� �ø���.

		switch (Levelcount)
	{
		case 1:
		{
			LevelUpCost = 5;
			break;
		}

		case 2:
		{
			LevelUpCost = 6;
			break;
		}

		case 3:
		{
			LevelUpCost = 7;
			break;
		}

		case 4:
		{
			LevelUpCost = 8;
			break;
		}

		case 5:
		{
			LevelUpCost = 11;
			break;
		}

		case 6:
		{
			LevelUpCost = 0;
			break;
		}

		default:
			break;
	}
	}

}

void Ready_Ui::LevelChack()
{
	for (int i = 0; i < Level.size(); i++) // Level ���͸� ��ü ��ȸ�Ѵ�.
	{
		if (!Level[i]->GetONOFF() && i <= Levelcount)
			// ����, Level�� Off�̰�, Levelcount���� �۰ų� ������,
			Level[i]->SetONOFF(); //�ش�Ǵ� ������ ����
		else if (Level[i]->GetONOFF() && i > Levelcount)
			// ����, Level�� ON�̰�, Levelcount���� ũ��,
			Level[i]->SetONOFF(); // �ش�Ǵ� ������ ����.
	}
}

void Ready_Ui::GoldUP()
{
	if(Gold_Now_Max < Gold_Defalt_Max) // ��� �ִ�ġ�� �ƴҰ��, �ִ�ġ���� 1�� �����Ѵ�.
		Gold_Now_Max += 1;
}

void Ready_Ui::GoldChack()
{
	for (int i = Gold.size()-1; i >= 0; i--) // Gold ���͸� ��ü ��ȸ�Ѵ�.
	{
		if (!Gold[i]->GetONOFF() && i <= Goldhavenow)
			// ����, Gold�� Off�̰�, Goldhavenow���� �۰ų� ������,
			Gold[i]->SetONOFF(); //�ش�Ǵ� ������ ����
		else if (Gold[i]->GetONOFF() && i > Goldhavenow)
			// ����, GOld�� ON�̰�, Goldhavenow���� ũ��,
			Gold[i]->SetONOFF(); // �ش�Ǵ� ������ ����.

		if (!Gold[i]->GetRender() && i <= Gold_Now_Max)
			// ����, Gold�� Render�� Off�̰�, Gold_Now_Max���� �۰ų� ������,
			Gold[i]->SetRender(); //�ش�Ǵ� ��带 ������Ŵ
		else if (Gold[i]->GetRender() && i > Gold_Now_Max)
			// ����, GOld�� Render�� ON�̰�, Gold_Now_Max���� ũ��,
			Gold[i]->SetRender(); // �ش�Ǵ� ��带 ������Ű�� ����.
	}
}

bool Ready_Ui::UseGold(const int cost)
{
	if (Goldhavenow >= cost) {
		Goldhavenow -= cost;
		return true;
	}

	return false;
}
