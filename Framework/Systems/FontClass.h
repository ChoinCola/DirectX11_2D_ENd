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

struct D3DXNUMBER
{
	D3DXVECTOR3 Startposition;					// ������
	D3DXVECTOR3 Endposition;					// ������ ���� ������
	Color color;								// ���� ����
	Vector3 size;								// ���� ũ��
	int nvectorsize;							// ��ȣ�� ������ ( ������ �Ѿ�� ǥ�úҰ� )
	int sortType;								// ���ı����� ���� �߾� ��������
	int num;									// ����ִ� ����

	Vector2 srvsize;
	ID3D11ShaderResourceView* srv;				// �̹�����
	std::vector<TextureRect*> numstring;		// ���� ����
	std::map<wchar_t, std::vector<Vector2>*> numberpad;	// �ѹ���� ����

public:
	void Update() { for (auto def : numstring) def->Update(); } // ���� ��ġ��ǥ ����
	void Render() { for (auto def : numstring) def->Render(); } // ���� ���

	void Changer_Number(int num) {
		std::wstring numdef = std::to_wstring(num);

		while (true) {
			if (numstring.size() > numdef.size()) { // ����� ũ�� �ڷ� ��������.
				Endposition.x -= (*numstring.end())->GetSize().x;	//Endposition�� ������ش�.
				TextureRect* back = *numstring.end();
				numstring.pop_back();
			}

			break;
		}

		for (uint i = 0; i < numdef.size(); i++)
		{
			if(i >= numstring.size()) { // ������ ��ġ�� ������ �����ͼ� �ھ���.
				TextureRect* numberdef = new TextureRect(Endposition, numberpad.find(numdef[i])->second,
					size, 0.0, color, srv, srvsize);
				numstring.push_back(numberdef);
				Endposition += Vector3(size.x, 0, 0);
			}
			else {					// ������ ����.
				numstring[i]->SetTextvertices(*numberpad.find(numdef[i])->second);
			}
		}
	}
private:
	template<typename T>
	D3DXNUMBER operator+ (T x) {
		num += x;
		Changer_Number(num);
	}

	template<typename T>
	D3DXNUMBER operator- (T x) {
		num -= x;
		Changer_Number(num);
	}

	template<typename T>
	D3DXNUMBER operator* (T x) {
		num *= x;
		Changer_Number(num);
	}

	template<typename T>
	D3DXNUMBER operator/ (T x) {
		num /= x;
		Changer_Number(num);
	}
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

	D3DXSTRING MakeString															// ���� �����Լ�
	(const std::wstring string, const Vector3 position,
	const Color color, const Vector3 stringsize, const int sorting = 0, const int outline = 0);

	D3DXNUMBER Makenumberbord															// ������ �����Լ�
	(const int number, const Vector3 position,
		const Color color, const Vector3 stringsize, const int sorting = 0, const int outline = 0);

private:
							
	std::map<int, CharFont*> charators;												// xml���� �ܾ�� ������ ���� ma

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