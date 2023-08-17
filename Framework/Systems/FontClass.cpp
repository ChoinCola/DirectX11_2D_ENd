#include "Framework.h"
#include "FontClass.h"


FontClass::FontClass()
{
	//기본 설정
	StringSize = { 11.f,11.f,0 };
	StringOffset = 2.f;
	assert(SetFont(
		L"../Framework/GameAsset/Fontfile/Font_0.png", // WSTRING으로 해야함,Texture2D이기 때문,
		"Framework\\GameAsset\\Fontfile\\Font.fnt")); // string으로 해야함, 라이브러리가 string으로 읽기때문,
}

FontClass::~FontClass()
{
}

bool FontClass::SetFont(std::wstring pngFile, char* fntfile)
{
	m_Texture = new Texture2D(pngFile);
	XMLDocument doc;
	
	//이미지 파일의 이름을 받아서 해당 이미지 로딩
	if (tinyxml2::XMLError eRsult = doc.LoadFile(fntfile))	//xml 로드 실패
	{
		MessageBox(NULL, L"Can't find font file", L"Error", MB_OK);
		return false;
	}
	else
	{
		tinyxml2::XMLElement *pNode = doc.FirstChildElement("font")->FirstChildElement("chars");
		if (pNode == nullptr) {
			std::cerr << "Error finding chars element." << std::endl;
			return false;
		}
		//const char* fontImage = pNode->ToElement()->Attribute("file");

		//글자 갯수 받아옴

		//아스키코드 한글 전체 받아옴
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

std::vector<Vector3>* FontClass::SizeInit(int width, int height)
{
	//colorVertices[0].position = Vector3(-0.0f, -0.0f, 0.0f); 좌하단
	//colorVertices[1].position = Vector3(+1.0f, +1.0f, 0.0f); 우상단
	//colorVertices[2].position = Vector3(+1.0f, -0.0f, 0.0f); 우하단
	//colorVertices[3].position = Vector3(+0.0f, +1.0f, 0.0f); 좌상단

	std::vector<Vector3>* result = new std::vector<Vector3>();
	result->push_back(Vector3(+0.0f, +0.0f, 1));
	result->push_back(Vector3(+(width / 10), +(height / 10), 1));
	result->push_back(Vector3(+(width / 10), +0.0f, 1));
	result->push_back(Vector3(+0.0f, +(height / 10), 1));

	return result;
}

std::vector<Vector2>* FontClass::uvInit(float x, float y, float xoffset, float yoffset)
{

	//vertices[0].uv = Vector2(flip.x, !flip.y); 0, 1
	//vertices[1].uv = Vector2(!flip.x, flip.y); 1, 0
	//vertices[2].uv = Vector2(!flip.x, !flip.y);1, 1
	//vertices[3].uv = Vector2(flip.x, flip.y);  0, 0

	std::vector<Vector2>* result = new std::vector<Vector2>();
	result->push_back(Vector2(x, y + yoffset));
	result->push_back(Vector2(x + xoffset, y));
	result->push_back(Vector2(x + xoffset, y + yoffset));
	result->push_back(Vector2(x, y));

	return result;
}

D3DXSTRING* FontClass::printString(const std::wstring string, const Vector3 position, const Color color)
{
	D3DXSTRING* result = new D3DXSTRING();
	result->Startposition = result->Endposition = position;
	result->size = StringSize;
	result->color = color;

	for (auto def : string) {
		if (def != NULL) {

			// 스페이스바
			if ((int)def == 0) {
				result->Endposition.x += StringSize.x;
				continue;
			}

			// 개행문자. 엔터
			if (def == '\n') {
				result->Endposition.y += StringSize.y + StringOffset;
				continue;
			}

			auto value = charators.find((int)def);
			result->string->push_back(
				new TextureRect(
					result->Endposition,
					SizeInit(value->second->width, value->second->height),
					uvInit(value->second->x, value->second->y, value->second->xoffset, value->second->yoffset),
					result->size,
					0.0f,
					result->color,
					m_Texture->GetSRV())
			);
			int beforeX = value->second->width;
			int beforeXOffset = value->second->xoffset;

			result->Endposition.x += beforeX + beforeXOffset;
		}
	}
	return result;
}
