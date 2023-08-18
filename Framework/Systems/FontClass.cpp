#include "Framework.h"
#include "FontClass.h"


FontClass::FontClass()
{
	// �⺻ ����
	StringSize = Vector3{ 11.f,11.f,0 };	// �⺻ ���� ������
	StringOffset = 2.f;						// �⺻ ���� ����

	assert(SetFont(
		L"../Framework/GameAsset/Fontfile/Font2_0.png", // WSTRING���� �ؾ���,Texture2D�̱� ����,
		"..\\Framework\\GameAsset\\Fontfile\\Font2.fnt")); // string���� �ؾ���, ���̺귯���� string���� �б⶧��,
}

FontClass::~FontClass()
{
}

bool FontClass::SetFont(std::wstring pngFile, char* fntfile)
{
	// ��Ʈ ���� ���� �� �����ؾ��� �����͹迭 ���� �ʱ�ȭ
	{
		SAFE_DELETE(Fontpng);
		charators.clear();
	}

	// ��Ʈ png���� �ε�
	Fontpng = new Texture2D(pngFile);
	
	// xml���� ������ �������� ����
	tinyxml2::XMLDocument doc;

	//�̹��� ������ �̸��� �޾Ƽ� �ش� �̹��� �ε�
	if (tinyxml2::XMLError eRsult = doc.LoadFile(fntfile))	//xml �ε� ���� �˻�
	{
		MessageBox(NULL, L"Can't find font file", L"Error", MB_OK);
		return false; // ���н� ��Ʈ��
	}
	else
	{
		// xml������ font ���� chars�� ������ ����� pNode�� ����. ( �� �����ʹ� �� ������ ���Ե����͸� �����Ѵ�. )
		tinyxml2::XMLElement *pNode = doc.FirstChildElement("font")->FirstChildElement("chars");
		// xml������ font ���� common�� ������ ����� Imagesize�� ����. ( �� �����ʹ� �̹����� ������ �� �����Ѵ�. )
		tinyxml2::XMLElement *Imagesize = doc.FirstChildElement("font")->FirstChildElement("common");

		// �� �Ѱ��� �ܾ���� ������ ���, �ڵ������ �Ұ��ϱ⿡ ��Ʈ����.
		if (pNode == nullptr || Imagesize == nullptr) {
			std::cerr << "Error finding chars element." << std::endl;
			return false;
		}
		// png������ ��ü ����� �޾ƿ´�. ( Texture2D�����͸� �����ϴ� Fontpng������ �ܾ�ü� ����. ���� )
		fontImagesize = { (float)Imagesize->IntAttribute("scaleW"), (float)Imagesize->IntAttribute("scaleH") };

		// �ԷµǾ��ִ� ��� ���ڿ��� �˻��Ͽ� ���� map�� �־��ش�.
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
	//maxx 18, maxy 18 ����ū �ѱ� ��Ʈ�� ����� �ƽ� 18�� ��� ����� offset�� ��´�.
	std::vector<Vector3>* result = new std::vector<Vector3>;

	 //TextureRect�� ���� ���� Vector�� �����Ͽ� ������� �Ѵ�.
	result->push_back(Vector3(+0.0f			, +0.0f			, 0));
	result->push_back(Vector3(+width / 18	, +height / 18	, 0));
	result->push_back(Vector3(+width / 18	, +0.0f			, 0));
	result->push_back(Vector3(+0.0f			, +height / 18	, 0));

	return result;
}

std::vector<Vector2>* FontClass::uvInit(float x, float y, float xoffset, float yoffset)
{
	// uv��ǥ�� ��Ƽ�, ��ü ���� png�� �ʿ��� ���� �Ѱ��� uv��ǥ�� �����Ѵ�.
	std::vector<Vector2>* result = new std::vector<Vector2>();

	// TextureRect�� ���� ���� Vector�� �����Ͽ� ������� �Ѵ�.
	result->push_back(Vector2(x				,	(y + yoffset)));	// ���ϴ�
	result->push_back(Vector2((x + xoffset),	y			 ));	// ����
	result->push_back(Vector2((x + xoffset),	(y + yoffset)));	// ���ϴ�
	result->push_back(Vector2(x				,	y			 ));	// �»��

	return result;
}

D3DXSTRING FontClass::MakeString
(const std::wstring string, const Vector3 position, const Color color, const Vector3 stringsize, const int sorting, const int outline)
{
	D3DXSTRING* result = new D3DXSTRING;
	
	// ����üũ, ���� Fontpng�� ������� �ʾ��� ���,
	if (Fontpng == nullptr) { 
	// ��Ʈ �� �ٽ� ����ش�.
	SetFont(L"../Framework/GameAsset/Fontfile/Font2_0.png", // WSTRING���� �ؾ���,Texture2D�̱� ����,
			"..\\Framework\\GameAsset\\Fontfile\\Font2.fnt");
	}

	// ��ȯ���� ������ ���� �����͸� ����.
	result->Startposition = result->Endposition = position;
	result->size = stringsize;
	result->color = color;

	for (auto def : string) {
		if (def != NULL) {

			// �����̽��� �Է½� ����
			if ((int)def == 0) {
				result->Endposition.x += result->size.x;
				continue;
			}

			// ���๮��. �����Է½� ������
			if (def == '\n') {
				result->Endposition.y -= result->size.y * 1.8;
				result->Endposition.x = result->Startposition.x;
				continue;
			}

			// map�迭���� �ش�Ǵ� ������ ASCII �ڵ带 ã�ƿ´�. 
			auto value = charators.find((int)def);

			// offset�� ���� ��ġ��.
			std::vector<Vector3>* terticespos;
			terticespos = SizeInit(value->second->width, value->second->height);

			// uv�� ���ذ�. ������ x��ġ�� ��ü �̹����� �����־� ��ü�̹����� 1�ϰ�� x�� ���� ���Ѵ�. ���μ��α���, y�� ���� ������� ����
			std::vector<Vector2>* uv = 
			uvInit(value->second->x / fontImagesize.x, value->second->y / fontImagesize.y,
					value->second->width / fontImagesize.x, value->second->height / fontImagesize.y);

			// �ѱ۰� ������ Offset��ġ�� �ٸ��� ������ �ѱ��ϰ��, �߰� offset�� �ش�.
			Vector3 Offset;
			if(value->first >= 40000)
				Offset = Vector3(0,value->second->yoffset,0);
			else
				Offset = Vector3(0, 0, 0);

			// ���°������ ���� �� �����Ѵ�.
			result->string.push_back(
				new TextureRect(result->Endposition + Offset, 
				terticespos, uv, result->size, 0.0f,result->color, Fontpng, outline));

			result->Endposition.x += value->second->width / 18 * result->size.x + StringOffset;
		}
	}

	
	switch (sorting)
	{
		case RIGHT : // �� ������ ������ġ ���� �������� �߻��մϴ�.
		{
			float sortvectorsizex = (result->Endposition.x - result->Startposition.x); // ��ü ���� ����
			Vector3 sortvector = { sortvectorsizex, 0, 0 };
			for (auto def : result->string) {
				if (def->GetPosition().y < result->Startposition.y) // ���Ͱ� �ԷµǾ��� ���,
					sortvector.x = sortvectorsizex; // x�� ������� �⺻ ���� �ʱ�ȭ

				Vector3 charX = Vector3(def->GetRect().x / 4 - StringOffset, 0, 0);

				def->SetPosition(def->GetPosition() - sortvector); // ���� ��ġ�� �ܾ� ���̸�ŭ�� �� �о����.
				sortvector -= charX;
				// ������ �������� �̴� ���� ��� �� ������ x������ ��ŭ �پ���� �Ѵ�.
			}
			break;
		}
		case MIDDLE : 	// �� ������ ������ġ �� ������ �߾��Դϴ�.
		{
			float sortvectorsizex = (result->Endposition.x - result->Startposition.x) / 2; // ��ü ���� ������ ��
			Vector3 sortvector = { sortvectorsizex, 0, 0 };
			for (auto def : result->string) {
				if (def->GetPosition().y < result->Startposition.y) // ���Ͱ� �ԷµǾ��� ���,
					sortvector.x = sortvectorsizex; // x�� ��������� �⺻�� ���� �� �ʱ�ȭ

				Vector3 charX = Vector3(def->GetRect().x / 4 - StringOffset, 0, 0);
			
				def->SetPosition(def->GetPosition() - sortvector); // ���� ��ġ�� �ܾ� ���̸�ŭ�� �� �о����.
				sortvector -= charX;
				 // ������ �������� �̴� ���� ��� �� ������ x������ ��ŭ �پ���� �Ѵ�.
			}
			break;
		}
		default: // �� ������ ������ġ ���� ���������� �߻��մϴ�.
			break;
	}
	return *result;
}
