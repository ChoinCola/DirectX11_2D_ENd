#include "stdafx.h"
#include "Card_UI.h"

Card_UI::Card_UI(Vector3 position, std::wstring CardName, int CardBrood, int CardUnitCount, std::list<int>* Card_Upgrade, std::wstring Cardstring)
	: ICard_UI()
{
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
	CardInfo.push_back(new TextureRect(	// Base
		Card[0]->GetPosition() + Vector3(Card[0]->GetSize().x,0,0), // position
		{ 250,400,1 },						// size
		0.0f,								// rotation	
		D3DXCOLOR(0.09f, 0.07f, 0.14f, 0.35f)	// Color
	));
	CardInfo.push_back(new TextureRect( // UP
		{ this->position.x,
		  this->position.y + Card[0]->GetSize().y / 2 + CCorrection,
		  this->position.z
		},
		{ Card[0]->GetSize().x - CornerSize, CornerSize, 1 },
		0.0f,
		LUI + L"TextBox/Side_X.png",		// srv
		{ 0,1 }
	));
	CardInfo.push_back(new TextureRect( // Down
		{ this->position.x,
		  this->position.y - Card[0]->GetSize().y / 2 - CCorrection,
		  this->position.z
		},
		{ Card[0]->GetSize().x - CornerSize , CornerSize,1 },
		0.0f,
		LUI + L"TextBox/Side_X.png",
		{ 0,0 }
	));
	CardInfo.push_back(new TextureRect( // Left
		{ this->position.x - Card[0]->GetSize().x / 2 - CCorrection,
		  this->position.y,
		  this->position.z
		},
		{ CornerSize, Card[0]->GetSize().y - CornerSize , 1 },
		0.0f,
		LUI + L"TextBox/Side_Y.png",
		{ 1,0 }
	));
	CardInfo.push_back(new TextureRect( // Right
		{ this->position.x + Card[0]->GetSize().x / 2 + CCorrection,
		  this->position.y,
		  this->position.z
		},
		{ CornerSize, Card[0]->GetSize().y - CornerSize , 1 },
		0.0f,
		LUI + L"TextBox/Side_Y.png",
		{ 0,0 }
	));

	CardInfo.push_back(new TextureRect( // LeftUP
		{ this->position.x - Card[0]->GetSize().x / 2 + CCorrection,
		  this->position.y + Card[0]->GetSize().y / 2 - CCorrection,
		  this->position.z
		},
		{ CornerSize, CornerSize, 1 },
		0.0f,
		LUI + L"TextBox/Corner.png",
		{ 0,0 }
	));
	CardInfo.push_back(new TextureRect( // RightUP
		{ this->position.x + Card[0]->GetSize().x / 2 - CCorrection,
		  this->position.y + Card[0]->GetSize().y / 2 - CCorrection,
		  this->position.z
		},
		{ CornerSize, CornerSize, 1 },
		0.0f,
		LUI + L"TextBox/Corner.png",
		{ 1,0 }
	));
	CardInfo.push_back(new TextureRect( // LeftDown
		{ this->position.x - Card[0]->GetSize().x / 2 + CCorrection,
		  this->position.y - Card[0]->GetSize().y / 2 + CCorrection,
		  this->position.z
		},
		{ CornerSize, CornerSize, 1 },
		0.0f,
		LUI + L"TextBox/Corner.png",
		{ 0,1 }
	));
	CardInfo.push_back(new TextureRect( // RightDown
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
#pragma region Button
	Close_Button = new Button(
		{ CardInfo[0]->GetPosition() + Vector3(+Card[0]->GetSize().x / 2 , Card[0]->GetSize().y / 2, 0),
		},
		{ 20,20,1 },
		L"UI_Close_Button",
		L"One_Button.png",
		L"One_Button_press.png",
		L"XCross_pattern.png"
	);
	Buy_Button = new Button(
		{ CardInfo[0]->GetPosition() + Vector3(-Card[0]->GetSize().x / 2 ,- Card[0]->GetSize().y / 2, 0),
		},
		{ 20,20,1 },
		L"UI_Buy_Button",
		L"One_Button.png",
		L"One_Button_press.png",
		L"Buy_pattern.png"
	);
	Sell_Button = new Button(
		{ CardInfo[0]->GetPosition() + Vector3(+Card[0]->GetSize().x / 2 ,- Card[0]->GetSize().y / 2, 0),
		},
		{ 20,20,1 },
		L"UI_Sell_Button",
		L"One_Button.png",
		L"One_Button_press.png",
		L"Sell_pattern.png"
	);
#pragma endregion
}

Card_UI::~Card_UI()
{
	for(auto def : Card)
		SAFE_DELETE(def);
	SAFE_DELETE(Close_Button);
}

void Card_UI::Render()
{
#pragma region CardInfo
	if (Closenow == false) {
		for (auto def : CardInfo)
			def->Render();

		Text::Get()->BeginDraw();
		{
			float textsize = 8.0f;
			float size = (float)Text::Get()->GetStringWidth(Cardstring, textsize);
			Vector2 pos = Vector2(Card[0]->GetPosition().x - size * 2, Card[0]->GetPosition().y - textsize * 3);
			Text::Get()->RenderText(Cardstring, pos + Vector2(textsize / 4, textsize / 4), Color(38, 43, 68, 1), size, true);

			Text::Get()->RenderText(Cardstring, pos, Color(255, 255, 255, 1), size, true);
		}
		Text::Get()->EndDraw();

		Close_Button->Render();
		Buy_Button->Render();
		Sell_Button->Render();
	}
#pragma endregion

#pragma region Card_base
	for(auto def: Card)
		def->Render();

	Text::Get()->BeginDraw();
	{
		float textsize = 10.0f;
		float size = (float)Text::Get()->GetStringWidth(CardName, textsize);
		Vector2 pos = Vector2(Card[0]->GetPosition().x - size * 2, Card[0]->GetPosition().y - textsize * 3);
		Text::Get()->RenderText(CardName, pos + Vector2(textsize / 4, textsize / 4), Color(38, 43, 68, 1), size, true);
		Text::Get()->RenderText(CardName, pos, Color(255, 255, 255, 1), size, true);
	}
	Text::Get()->EndDraw();
#pragma endregion


}

void Card_UI::Update()
{
	if (Closenow == false) {
		Close_Button->SetRender();
		Buy_Button->SetRender();
		Sell_Button->SetRender();
	}

	for (auto def : Card)
		def->Update();

	for (auto def : CardInfo)
		def->Update();

	Close_Button->Update();
	Buy_Button->Update();
	Sell_Button->Update();
}
