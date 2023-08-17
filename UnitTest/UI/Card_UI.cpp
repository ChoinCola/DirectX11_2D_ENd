#include "stdafx.h"
#include "Card_UI.h"

Card_UI::Card_UI(Vector3 position, std::wstring CardName, int CardBrood, int CardUnitCount, std::list<int>* Card_Upgrade, std::wstring Cardstring)
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

		//Text::Get()->BeginDraw();
		//{
		//	float textsize = 4.0f;
		//	float size = (float)Text::Get()->GetStringWidth(Cardstring, textsize);
		//	Vector2 pos = Vector2(
		//	CardInfo[0]->GetPosition().x - CardInfo[0]->GetSize().x / 2 + Close_Button->GetSize().x / 2,
		//	CardInfo[0]->GetPosition().y + CardInfo[0]->GetSize().y / 2 - Close_Button->GetSize().y);
		//	Text::Get()->RenderText(Cardstring, pos + Vector2(textsize / 4, textsize / 4), Color(38, 43, 68, 1), size, true);
		//	Text::Get()->RenderText(Cardstring, pos, Color(255, 255, 255, 1), size, true);
		//}
		//Text::Get()->EndDraw();

		//FontClass* def;
		//def->Create();

		//Vector3 pos = Vector3(
		//	CardInfo[0]->GetPosition().x + CardInfo[0]->GetSize().x / 2 - Close_Button->GetSize().x / 2,
		//	CardInfo[0]->GetPosition().y - CardInfo[0]->GetSize().y / 2 + Close_Button->GetSize().y, 1);

		D3DCardstring = new D3DXSTRING(FontClass::Get()->MakeString(Cardstring, { 600,300,0 }, { 255,255,255,1 }, { 11.f,11.f,1 }));
		D3DCardstring->Update();
		D3DCardstring->Render();
	}
#pragma endregion

#pragma region Card_base
	for(auto def: Card)
		def->Render();

	Text::Get()->BeginDraw();
	{
		float textsize = 10.0f;
		float size = (float)Text::Get()->GetStringWidth(CardName, textsize);
		Vector2 pos = Vector2(
		Card[0]->GetPosition().x - Card[0]->GetSize().x / 2 + textsize * CardName.length() / 2,
		Card[0]->GetPosition().y + Card[0]->GetSize().y / 2);
		Text::Get()->RenderText(CardName, pos + Vector2(textsize / 4, textsize / 4), Color(38, 43, 68, 1), size, true);
		Text::Get()->RenderText(CardName, pos, Color(255, 255, 255, 1), size, true);
	}
	Text::Get()->EndDraw();
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
}
