#pragma once
struct D3DXSTRING
{
	D3DXVECTOR3 Startposition;	// ���� ������ ������, ���ڴ� ���ϴ��� ����.
	D3DXVECTOR3 Endposition;	// ���� ������ ������
	Color color;				// ���� ����
	Vector3 size;				// ���� ũ��
	std::vector<TextureRect*> string; // ���� ����

public:
	void Render() { for(auto def : string) def->Render(); } // STRING�� ���
};

class FontClass : public SingletonBase<FontClass>
{
public:
	friend SingletonBase<FontClass>;

private:
	struct CharFont // ���� ���� ��ü
	{
		float x;
		float y;
		float width;
		float height;
		float xoffset;
		float yoffset;
		float xadvance;
	};
private:
	FontClass();
	~FontClass();

public:
	void SetSize(Vector3 size) { this->StringSize = size; } // ���� ������ ����.
	void Setoffset(float offset)  { this->StringOffset = offset; } // �� �Ʒ� ������ ����
	bool SetFont(std::wstring pngFile, char* fntfile); // ��Ʈ���� �缳��
	std::vector<Vector3>* SizeInit(float width, float height);
	std::vector<Vector2>* uvInit(float x, float y, float xoffset, float yoffset);
	D3DXSTRING printString(const std::wstring string, const Vector3 position, const Color color, const Vector3 stringsize);

private:
	std::wstring Fontfile;
	std::map<int, CharFont*> charators;
	
	Texture2D* m_Texture = nullptr;

	Vector2 fontImagesize;
	Vector3 StringSize;
	int charCount;
	float StringOffset;
};
/*
	Font�����͸� �� ���ΰ���� �ܾ�ͼ� ���������ִ� Class
*/