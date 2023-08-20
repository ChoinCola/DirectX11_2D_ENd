#pragma once

class Ready_Ui : public IGame_Master
{
public:
	Ready_Ui();
	~Ready_Ui();
	void Update();

private:
	int moneycount;
	int money_Max;
	std::vector<Texture2D*> Gold;

	int Levelcount;
	int Level_Max;
	std::vector<Texture2D*> Level;

	Vector3 Buttonoffset;
	Vector3 BaseButtonposition;
	Vector3 Buttonsize;

	// ���� ���ΰ�ħ ��ư
	Button* ReButton = nullptr;

	// �����غ� ��ư
	Button* ReadyButton = nullptr;

	// �����ܰ� ���׷��̵� ��ư
	Button* UpgradeButton = nullptr;

	// ���� ��� ��ư
	Button* LockButton = nullptr;

	// ī�޶� �������� Texture2D�� position�� ��������
	Vector3 GetCMPosition(const Vector3 Basepositon, const Vector3 size, const Vector3 offset, const float x, const float y);

	// ������ Level�ִ밪�� �������� Level�� ��½�Ŵ.
	void LevelUP(const bool Press);
	
	// ������ Gold�ִ밪�� �������� Gold�� ��½�Ŵ
	void GoldUP(const bool Press);
};

