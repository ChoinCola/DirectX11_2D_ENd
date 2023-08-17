#include "Framework.h"
#include "FontClass.h"


FontClass::FontClass()
{
	//�⺻ ����
	StringSize = Vector3{ 11.f,11.f,0 };
	StringOffset = 2.f;
	assert(SetFont(
		L"../Framework/GameAsset/Fontfile/Font_0.png", // WSTRING���� �ؾ���,Texture2D�̱� ����,
		"..\\Framework\\GameAsset\\Fontfile\\Font.fnt")); // string���� �ؾ���, ���̺귯���� string���� �б⶧��,
}

FontClass::~FontClass()
{
}

bool FontClass::SetFont(std::wstring pngFile, char* fntfile)
{
	SAFE_DELETE(Fontpng);
	Fontpng = new Texture2D(pngFile);

	tinyxml2::XMLDocument doc;

	//�̹��� ������ �̸��� �޾Ƽ� �ش� �̹��� �ε�
	if (tinyxml2::XMLError eRsult = doc.LoadFile(fntfile))	//xml �ε� ����
	{
		MessageBox(NULL, L"Can't find font file", L"Error", MB_OK);
		return false;
	}
	else
	{
		tinyxml2::XMLElement *pNode = doc.FirstChildElement("font")->FirstChildElement("chars");
		tinyxml2::XMLElement *Imagesize = doc.FirstChildElement("font")->FirstChildElement("common");
		if (pNode == nullptr || Imagesize == nullptr) {
			std::cerr << "Error finding chars element." << std::endl;
			return false;
		}
		fontImagesize = { (float)Imagesize->IntAttribute("scaleW"), (float)Imagesize->IntAttribute("scaleH") };

		//���� ���� �޾ƿ�

		//�ƽ�Ű�ڵ� �ѱ� ��ü �޾ƿ�
		for (tinyxml2::XMLElement* element = pNode->FirstChildElement("char"); 
			element != nullptr; element = element->NextSiblingElement("char")) {
			CharFont* def = new CharFont();
			int id = element->IntAttribute("id");
			def->x = element->IntAttribute("x");
			def->y = element->IntAttribute("y");
			def->width = element->IntAttribute("width");
			def->height = element->IntAttribute("height");
			def->xoffset = element->IntAttribute("xoffset");
			def->yoffset = element->IntAttribute("yoffset");
			def->xadvance = element->IntAttribute("xadvance");
			charators.insert(std::make_pair(id, def));
		}
	}
	return true;
}

std::vector<Vector3>* FontClass::SizeInit(float width, float height)
{

	std::vector<Vector3>* result = new std::vector<Vector3>;
	result->push_back(Vector3(+0.0f, +0.0f, 1));
	result->push_back(Vector3(+width, +height, 1));
	result->push_back(Vector3(+width, +0.0f, 1));
	result->push_back(Vector3(+0.0f, +height, 1));

	return result;
}

std::vector<Vector2>* FontClass::uvInit(float x, float y, float xoffset, float yoffset)
{

	std::vector<Vector2>* result = new std::vector<Vector2>();
	result->push_back(Vector2(x				/ fontImagesize.x,	(y + yoffset) / fontImagesize.y));
	result->push_back(Vector2((x + xoffset) / fontImagesize.x,	y			  / fontImagesize.y));
	result->push_back(Vector2((x + xoffset) / fontImagesize.x,	(y + yoffset) / fontImagesize.y));
	result->push_back(Vector2(x				/ fontImagesize.x,	y			  / fontImagesize.y));

	return result;
}

D3DXSTRING FontClass::MakeString(const std::wstring string, const Vector3 position, const Color color, const Vector3 stringsize)
{
	//StringSize = Vector3{ 11.f,11.f,0 };
	D3DXSTRING* result = new D3DXSTRING();

	if (Fontpng == nullptr) { 
	SetFont(L"../Framework/GameAsset/Fontfile/Font_0.png", // WSTRING���� �ؾ���,Texture2D�̱� ����,
			"..\\Framework\\GameAsset\\Fontfile\\Font.fnt");
	}
	result->Startposition = result->Endposition = position;
	result->size = stringsize * 100;
	result->color = color;

	for (auto def : string) {
		if (def != NULL) {

			// �����̽���
			if ((int)def == 0) {
				result->Endposition.x += result->size.x;
				continue;
			}

			// ���๮��. ����
			if (def == '\n') {
				result->Endposition.y += result->size.y + StringOffset;
				continue;
			}

			auto value = charators.find((int)def);

			std::vector<Vector3>* terticespos = SizeInit(value->second->width, value->second->height);
			std::vector<Vector2>* uv = uvInit(value->second->x / fontImagesize.x, value->second->y / fontImagesize.y,
				value->second->xoffset / fontImagesize.x, value->second->yoffset / fontImagesize.y);

			result->string.push_back(
				new TextureRect(result->Endposition, terticespos, uv, result->size, 0.0f,result->color, Fontpng));

			int beforeX = value->second->width;
			int beforeXOffset = value->second->xoffset;

			result->Endposition.x += beforeX + beforeXOffset;
		}
	}
	return *result;
}
