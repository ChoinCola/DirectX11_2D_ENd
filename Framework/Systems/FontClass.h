#pragma once

enum STRINGPOSITION
{
	LEFT,
	RIGHT,
	MIDDLE,
};

struct D3DXSTRING
{
	D3DXVECTOR3 Startposition;			// ���� ������ ������, ���ڴ� ���ϴ��� ����.
	D3DXVECTOR3 Endposition;			// ���� ������ ������
	Color color;						// ���� ����
	Vector3 size;						// ���� ũ��
	std::vector<TextureRect*> string;	// ���� ����

public:
	void Update() { for (auto def : string) def->Update(); } // STRING ��ġ��ǥ ����
	void Render() { for (auto def : string) def->Render(); } // STRING ���
};

class FontClass : public SingletonBase<FontClass>
{
public:
	friend SingletonBase<FontClass>;

private:
	struct CharFont // xml���Ͽ��� �ܾ���� �����͵�.
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
	void SetSize(Vector3 size) { this->StringSize = size; }							// ���� ������ ����.
	void Setoffset(float offset)  { this->StringOffset = offset; }					// �� �Ʒ� ������ ����
	bool SetFont(char* fntfile);								// ��Ʈ���� �缳��

	std::vector<Vector2>* uvInit(float x, float y, float xoffset, float yoffset);	// uv��ǥ �����.
	std::vector<Vector3>* RectInit(float x, float y, float xwidth, float ywidth, float size);	// Rect���� �����.

	D3DXSTRING MakeString															// ���� �����Լ�
	(const std::wstring string, const Vector3 position,
	const Color color, const Vector3 stringsize, const int sorting = 0, const int outline = 0);

private:
							
	std::map<int, CharFont*> charators;												// xml���� �ܾ�� ������ ���� map
	
	Texture2D* Fontpng = nullptr;
	ID3D11ShaderResourceView* srv;
	Vector2 fontImagesize;
	Vector3 StringSize;
	int charCount;
	int fontsinglesize;
	float StringOffset;
};
/*
	Font�����͸� �� ���ΰ���� �ܾ�ͼ� ���������ִ� Class
*/