#pragma once

class IFontClass : public SingletonBase<IFontClass>
{
	friend SingletonBase<IFontClass>;
protected:
	struct FontType
	{
		float left, right;
		int size;
	};

	struct CharFont
	{
		int id;
		int x;
		int y;
		int width;
		int height;
		int xoffset;
		int yoffset;
		int xadvance;
	};

	std::wstring Fontfile;
	FontType* m_Font = nullptr;

	TiXmlDocument fontXml;

	CharFont* charators;
	Texture2D* m_Texture = nullptr;
	int charCount;

public:
	IFontClass() {
		
		m_Texture = new 
		Texture2D(L"../Framework/GameAsset/Fontfile/Font_0.png");

		TiXmlNode* pNode;
		//이미지 파일의 이름을 받아서 해당 이미지 로딩
		pNode = fontXml.FirstChild("font")->FirstChild("pages")->FirstChild("page");
		const char* fontImage = pNode->ToElement()->Attribute("file");

		//글자 갯수 받아옴
		pNode = fontXml.FirstChild("font")->FirstChild("chars");
		pNode->ToElement()->Attribute("count", &charCount);
		charators = new CharFont[charCount];
		pNode = pNode->FirstChild("char");

		int cnt = 0;
		//아스키코드 한글 전체 받아옴
		while (pNode != NULL)
		{
			pNode->ToElement()->Attribute("id", &charators[cnt].id);
			pNode->ToElement()->Attribute("x", &charators[cnt].x);
			pNode->ToElement()->Attribute("y", &charators[cnt].y);
			pNode->ToElement()->Attribute("width", &charators[cnt].width);
			pNode->ToElement()->Attribute("height", &charators[cnt].height);
			pNode->ToElement()->Attribute("xoffset", &charators[cnt].xoffset);
			pNode->ToElement()->Attribute("yoffset", &charators[cnt].yoffset);
			pNode->ToElement()->Attribute("xadvance", &charators[cnt].xadvance);
			//테스트

			std::cout << charCount << charators[cnt].id << charators[cnt].x << charators[cnt].y <<
				charators[cnt].width << charators[cnt].height << charators[cnt].xoffset << charators[cnt].yoffset <<
				charators[cnt].xadvance << std::endl;

			pNode = pNode->NextSibling();
			cnt++;
		}
		fontXml.Clear();
	}

	std::vector<TextureRect>& printString(const std::wstring string, const Vector2 position)
	{
		std::vector<TextureRect> result;
		for (auto def : string) {
			if (def != NULL) {
				int charNum = (int)def;
				charNum -= 32;

				if (charNum == 0) {
					
				}
			}
		}
	}

	TextureRect& Make_char(wchar_t def, Vector2 position, Vector2 uv)
	{
		if (def == 0)
		{
			return TextureRect()
		}
	}
};


class FontClass : public IFontClass
{
private:
	std::wstring string;

public:
	FontClass();
	~FontClass();
	void Render();
	void SetFontfile();
};

/*
	Font데이터를 각 맵핑값대로 긁어와서 렌더링해주는 Class
*/