#include "stdafx.h"
#include "Card_UI.h"

Card_UI::Card_UI(Vector3 position, std::wstring CardName, int CardBrood, int CardUnitCount, std::list<int>* Card_Upgrade, std::wstring Cardstring, int* unitalldamage)
	: ICard_UI()
{
	FontClass::Create();
	float CornerSize = 30;
	float CCorrection = 9;

	this->position = position;
	this->CardName = CardName;
	this->CardBrood = CardBrood;
	this->CardUnitCount = CardUnitCount;
	this->Card_Upgrade = Card_Upgrade;
	this->Cardstring = Cardstring;
	this->unitalldamage = unitalldamage;
#pragma region Card_base
	Card.push_back( new TextureRect(	// Base
	this->position,						// position
	{250,50,1},						// size
	0.0f,								// rotation	
	D3DXCOLOR(0.09f, 0.07f, 0.14f, 0.35f)	// Color
	));
	Card.push_back(new TextureRect( // UP
		{ this->position.x,
		  this->position.y + Card[0]->GetSize().y / 2 + CCorrection,
		  this->position.z
		},
		{ Card[0]->GetSize().x - CornerSize, CornerSize, 1 },
		0.0f,
		LUI + L"TextBox/Side_X.png",		// srv
		{ 0,1 }
	));
	Card.push_back(new TextureRect( // Down
		{ this->position.x,
		  this->position.y - Card[0]->GetSize().y / 2 - CCorrection,
		  this->position.z
		},
		{ Card[0]->GetSize().x - CornerSize , CornerSize,1 },
		0.0f,
		LUI + L"TextBox/Side_X.png",
		{ 0,0 }
	));
	Card.push_back(new TextureRect( // Left
		{ this->position.x - Card[0]->GetSize().x / 2 - CCorrection,
		  this->position.y,
		  this->position.z
		},
		{ CornerSize, Card[0]->GetSize().y - CornerSize , 1 },
		0.0f,
		LUI + L"TextBox/Side_Y.png",
		{ 1,0 }
	));
	Card.push_back(new TextureRect( // Right
		{ this->position.x + Card[0]->GetSize().x / 2 + CCorrection,
		  this->position.y,
		  this->position.z
		},
		{ CornerSize, Card[0]->GetSize().y - CornerSize , 1 },
		0.0f,
		LUI + L"TextBox/Side_Y.png",
		{ 0,0 }
	));

	Card.push_back(new TextureRect( // LeftUP
		{ this->position.x - Card[0]->GetSize().x / 2 + CCorrection,
		  this->position.y + Card[0]->GetSize().y / 2 - CCorrection,
		  this->position.z
		},
		{ CornerSize, CornerSize, 1 },
		0.0f,
		LUI + L"TextBox/Corner.png",
		{ 0,0 }
	));
	Card.push_back(new TextureRect( // RightUP
		{ this->position.x + Card[0]->GetSize().x / 2 - CCorrection,
		  this->position.y + Card[0]->GetSize().y / 2 - CCorrection,
		  this->position.z
		},
		{ CornerSize, CornerSize, 1 },
		0.0f,
		LUI + L"TextBox/Corner.png",
		{ 1,0 }
	));
	Card.push_back(new TextureRect( // LeftDown
		{ this->position.x - Card[0]->GetSize().x / 2 + CCorrection,
		  this->position.y - Card[0]->GetSize().y / 2 + CCorrection,
		  this->position.z
		},
		{ CornerSize, CornerSize, 1 },
		0.0f,
		LUI + L"TextBox/Corner.png",
		{ 0,1 }
	));
	Card.push_back(new TextureRect( // RightDown
		{ this->position.x + Card[0]->GetSize().x / 2 - CCorrection,
		  this->position.y - Card[0]->GetSize().y / 2 + CCorrection,
		  this->position.z
		},
		{ CornerSize, CornerSize, 1 },
		0.0f,
		LUI + L"TextBox/Corner.png",
		{ 1,1 }
	));
#pragma endregion

#pragma region Card_Info
	Vector3 Card_Info_Base_Size = { 250, 400, 1 };

	CardInfo.push_back(new TextureRect(	// Base
		Card[0]->GetPosition() + Vector3( // position
		Card[0]->GetSize().x + CCorrection, 
		- Card_Info_Base_Size.y / 2 + CornerSize,
		0), 
		Card_Info_Base_Size ,						// size
		0.0f,								// rotation	
		D3DXCOLOR(0.09f, 0.07f, 0.14f, 0.35f)	// Color
	));
	CardInfo.push_back(new TextureRect( // UP
		CardInfo[0]->GetPosition() + Vector3(0, + CardInfo[0]->GetSize().y / 2 + CCorrection, 0),
		{ CardInfo[0]->GetSize().x - CornerSize, CornerSize, 1 },
		0.0f,
		LUI + L"TextBox/Side_X.png",		// srv
		{ 0,1 }
	));
	CardInfo.push_back(new TextureRect( // Down
		CardInfo[0]->GetPosition() + Vector3(0, - CardInfo[0]->GetSize().y / 2 - CCorrection, 0),
		{ CardInfo[0]->GetSize().x - CornerSize , CornerSize,1 },
		0.0f,
		LUI + L"TextBox/Side_X.png",
		{ 0,0 }
	));
	CardInfo.push_back(new TextureRect( // Left
		CardInfo[0]->GetPosition() + Vector3(-CardInfo[0]->GetSize().x / 2 - CCorrection, 0, 0),
		{ CornerSize, CardInfo[0]->GetSize().y - CornerSize , 1 },
		0.0f,
		LUI + L"TextBox/Side_Y.png",
		{ 1,0 }
	));
	CardInfo.push_back(new TextureRect( // Right
		CardInfo[0]->GetPosition() + Vector3(+ CardInfo[0]->GetSize().x / 2 + CCorrection, 0, 0),
		{ CornerSize, CardInfo[0]->GetSize().y - CornerSize , 1 },
		0.0f,
		LUI + L"TextBox/Side_Y.png",
		{ 0,0 }
	));

	CardInfo.push_back(new TextureRect( // LeftUP
		CardInfo[0]->GetPosition() + Vector3(- CardInfo[0]->GetSize().x / 2 + CCorrection, 
											 + CardInfo[0]->GetSize().y / 2 - CCorrection, 0),
		{ CornerSize, CornerSize, 1 },
		0.0f,
		LUI + L"TextBox/Corner.png",
		{ 0,0 }
	));
	CardInfo.push_back(new TextureRect( // RightUP
		CardInfo[0]->GetPosition() + Vector3(+ CardInfo[0]->GetSize().x / 2 - CCorrection,
											 + CardInfo[0]->GetSize().y / 2 - CCorrection, 0),
		{ CornerSize, CornerSize, 1 },
		0.0f,
		LUI + L"TextBox/Corner.png",
		{ 1,0 }
	));
	CardInfo.push_back(new TextureRect( // LeftDown
		CardInfo[0]->GetPosition() + Vector3(- CardInfo[0]->GetSize().x / 2 + CCorrection,
											 - CardInfo[0]->GetSize().y / 2 + CCorrection, 0),
		{ CornerSize, CornerSize, 1 },
		0.0f,
		LUI + L"TextBox/Corner.png",
		{ 0,1 }
	));
	CardInfo.push_back(new TextureRect( // RightDown
		CardInfo[0]->GetPosition() + Vector3(+CardInfo[0]->GetSize().x / 2 - CCorrection,
											 -CardInfo[0]->GetSize().y / 2 + CCorrection, 0),
		{ CornerSize, CornerSize, 1 },
		0.0f,
		LUI + L"TextBox/Corner.png",
		{ 1,1 }
	));
#pragma endregion

#pragma region Button

	
	Vector3 ButtonSize = { 100, 40, 1 };
	float BCorrectionX = ButtonSize.x / 2 + ButtonSize.x / 10;
	float BCorrectionY = 25;

	Close_Button = new Button(
		{ CardInfo[0]->GetPosition() + 
		Vector3(+CardInfo[0]->GetSize().x / 2 - 20, CardInfo[0]->GetSize().y / 2 - 20, 0),
		},
		{ 40, 40 , 1 },
		L"UI_Close_Button",
		L"One_Button.png",
		L"One_Button_press.png",
		L"XCross_pattern.png"
	);
	Buy_Button = new Button(
		{ CardInfo[0]->GetPosition() + 
		Vector3(-CardInfo[0]->GetSize().x / 2 + BCorrectionX ,- CardInfo[0]->GetSize().y / 2 + BCorrectionY, 0),
		},
		ButtonSize,
		L"UI_Buy_Button",
		L"Small_Button.png",
		L"Small_Button_press.png",
		L"Buy_pattern.png"
	);
	Sell_Button = new Button(
		{ CardInfo[0]->GetPosition() + 
		Vector3(+CardInfo[0]->GetSize().x / 2 - BCorrectionX, - CardInfo[0]->GetSize().y / 2 + BCorrectionY, 0),
		},
		ButtonSize,
		L"UI_Sell_Button",
		L"Small_Button.png",
		L"Small_Button_press.png",
		L"Sell_pattern.png"
	);

	Button_list.Get()->push_back(Close_Button);
	Button_list.Get()->push_back(Buy_Button);
	Button_list.Get()->push_back(Sell_Button);
#pragma endregion
	
	{
		Color TextColor{ 0.86, 0.68, 0.85, 1 };
		float textsize = 50.0f;
		Vector3 pos = Vector3(
			Card[0]->GetPosition().x,
			Card[0]->GetPosition().y, 1);

		D3DCardstring = 
		new D3DXSTRING(FontClass::Get()->MakeString(CardName, pos, TextColor, { textsize, textsize, 1 }, MIDDLE, 5));
	}


	{
		Color TextColor{ 0.86, 0.68, 0.85, 1 };
		float textsize = 50.0f;
		Vector3 pos = Vector3(
			CardInfo[0]->GetPosition().x - CardInfo[0]->GetSize().x / 2 + Close_Button->GetSize().x / 2,
			CardInfo[0]->GetPosition().y + CardInfo[0]->GetSize().y / 2 - Close_Button->GetSize().y / 2 - textsize, 1);
		D3DCardInfostring = 
		new D3DXSTRING(FontClass::Get()->MakeString(Cardstring, pos, TextColor, { textsize, textsize, 1 },LEFT, 5));

	}

	{
		Color TextColor{ 0.86, 0.68, 0.85, 1 };
		float textsize = 50.0f;
		Vector3 pos = Vector3(
			CardInfo[0]->GetPosition().x - CardInfo[0]->GetSize().x / 2,
			CardInfo[0]->GetPosition().y + CardInfo[0]->GetSize().y / 2 - Close_Button->GetSize().y / 2 - textsize, 1);
		D3DCardDamage =
			new D3DXNUMBER(FontClass::Get()->Makenumberbord(12030, pos, TextColor, { textsize, textsize, 1 }, LEFT, 5));
	}
}

Card_UI::~Card_UI()
{
	UI_list.Get()->remove(this);
	for(auto def : Card)
		SAFE_DELETE(def);
	SAFE_DELETE(Close_Button);
	SAFE_DELETE(Buy_Button);
	SAFE_DELETE(Sell_Button);
}

void Card_UI::Render()
{
#pragma region CardInfo
	if (Closenow == false) {
		for (auto def : CardInfo)
			def->Render();

		D3DCardInfostring->Render();
		D3DCardDamage->Render();
	}
#pragma endregion

#pragma region Card_base
	for(auto def: Card) {
		def->Render();

		D3DCardstring->Render();
	}
#pragma endregion
}

void Card_UI::Update()
{
	if(Close_Button->GetPush()) {
		SetOPEN();
		SetRenderButton();
	}

	for (auto def : Card)
		def->Update();

	for (auto def : CardInfo)
		def->Update();

	D3DCardInfostring->Update();
	D3DCardstring->Update();

	//D3DCardDamage->Changer_Number(*unitalldamage);
}
