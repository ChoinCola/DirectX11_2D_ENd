#pragma once

class IFontClass : public SingletonBase<IFontClass>
{
	friend SingletonBase<IFontClass>;
public:
	IFontClass() {
		m_Texture = new 
		Texture2D(L"../Framework/GameAsset/Fontfile/Font_0.png");
	}
protected:
	Texture2D* m_Texture = nullptr;
};


class FontClass : public IFontClass
{
private:
	struct FontType
	{
		float left, right;
		int size;
	};

	struct CharFont
	{
		int x;
		int y;
		int width;
		int height;
		int xoffset;
		int yoffset;
		int xadvance;
	};

public:
	FontClass();
	~FontClass();
	void Render();
	void SetFontfile(std::wstring);
	bool SetString();
private:
	std::wstring string;
	std::wstring Fontfile;
	FontType* m_Font = nullptr;

	TiXmlDocument fontXml;

	std::map<int, CharFont*> charactors;
};

/*
	Font데이터를 각 맵핑값대로 긁어와서 렌더링해주는 Class
*/