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
	Font�����͸� �� ���ΰ���� �ܾ�ͼ� ���������ִ� Class
*/