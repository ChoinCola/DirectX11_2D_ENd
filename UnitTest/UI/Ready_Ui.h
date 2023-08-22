#pragma once

class Ready_Ui : public IGame_Master
{
public:
	Ready_Ui();
	~Ready_Ui();
	void Update();

private:
	int Goldhavenow;
	int Gold_Now_Max;
	int Gold_Defalt_Max;
	std::vector<UI_Obejct*> Gold;

	int LevelUpCost;
	int Levelcount;
	int Level_Max;
	std::vector<UI_Obejct*> Level;

	Vector3 Buttonoffset;
	Vector3 LBaseposition;
	Vector3 RBaseposition;

	Vector3 Buttonsize;
	Vector3 Leveloffset;
	Vector3 Level_UI_size;
	Vector3 Gold_UI_size;

	D3DXSTRING upcostp;

	// �ӽ� ���� ���� ��ư
	Button* defRoundButton = nullptr;

	// ���� ���ΰ�ħ ��ư
	Button* ReButton = nullptr;

	// �����غ� ��ư
	Button* ReadyButton = nullptr;

	// �����ܰ� ���׷��̵� ��ư
	Button* UpgradeButton = nullptr;

	// ���� ��� ��ư
	Button* LockButton = nullptr;

	// ī�޶� �������� Texture2D�� position�� ��������
	Vector3 GetCMPosition(const Vector3 Basepositon, const Vector3 size, const Vector3 offset, const float x, const float y, bool flipx = false);

	// ������ Level�ִ밪�� �������� Level�� ��½�Ŵ.
	void LevelUP();
	void LevelChack(); // ���� ������ �����ִºκ��� ������ ������ Ȯ��ó���Ѵ�.
	// ������ Gold�ִ밪�� �������� Gold�� ��½�Ŵ
	void GoldUP();
	void GoldChack(); // ���� ������ �����ִ� �κ�, �����Ǵ� �κ��� ������ ������ Ȯ��ó���Ѵ�.

	// ������ Gold��ŭ ����ϰ�, �����Ұ��, false�� ��ȯ ������� true ��ȯ
	bool UseGold(const int cost);
};

