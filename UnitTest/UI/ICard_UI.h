#pragma once

#include "Game/Button.h"

class ICard_UI
{
public:
	ICard_UI();
	~ICard_UI();

	virtual void Update() = 0;
	virtual void Render() = 0;

	bool GetOPEN() { return Closenow; };

	Button* GetCloseButton() { return Close_Button; };
	Button* GetBuyButton() { return Buy_Button; };
	Button* GetSellButton() { return Sell_Button; };

	Vector3 GetPosition() { return Card[0]->GetPosition(); };
	Vector3 GetSize() { return Card[0]->GetSize(); };

	Vector3 GetPositionInfo() { return CardInfo[0]->GetPosition(); };
	Vector3 GetSizeInfo() { return CardInfo[0]->GetSize(); };

	std::wstring GetName() { return CardName; };

	void SetOPEN() { Closenow ? Closenow = false : Closenow = true; };
	void SetPosition(Vector3 Position) { position = Position; };

	void SetRenderButton() {
		Close_Button->SetRender();
		Buy_Button->SetRender();
		Sell_Button->SetRender();
	}

protected:
	std::wstring CardName;
	std::list<int>* Card_Upgrade;
	std::wstring Cardstring;

	Vector3 position;

	int CardBrood;
	int CardUnitCount;

	bool Closenow;

	std::vector<TextureRect*> Card;
	D3DXSTRING* D3DCardstring;
	std::vector<TextureRect*> CardInfo;
	D3DXSTRING* D3DCardInfostring;
	Button* Close_Button;
	Button* Buy_Button;
	Button* Sell_Button;
};

