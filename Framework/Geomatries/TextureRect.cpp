#include "Framework.h"
#include "TextureRect.h"

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation, Color path, Vector2 flip)
	: position(position), size(size), rotation(rotation)
{
	flip.x ? flip.x = 1 : flip.x = 0;
	flip.y ? flip.y = 1 : flip.y = 0;

	{
		D3DXMatrixTranslation(&X, 0, 0, 0);
	}

	// vertices
	{
		colorVertices.assign(4, VertexColor());
		for (VertexColor& v : colorVertices)
			v.color = path;

		colorVertices[0].position = Vector3(-0.5f, -0.5f, 0.0f); // 좌하단
		colorVertices[1].position = Vector3(+0.5f, +0.5f, 0.0f); // 우상단
		colorVertices[2].position = Vector3(+0.5f, -0.5f, 0.0f); // 우하단
		colorVertices[3].position = Vector3(-0.5f, +0.5f, 0.0f); // 좌상단
	}

	// Vertex Buffer
	{
		vb = new VertexBuffer();
		vb->Create(colorVertices, D3D11_USAGE_DYNAMIC);
	}

	// Index Buffer
	{
		indices = { 0,1,2,0,3,1 };

		ib = new IndexBuffer();
		ib->Create(indices, D3D11_USAGE_IMMUTABLE);
	}

	// Vertex Shader
	{
		vs = new VertexShader();
		vs->Create(ShaderPath + L"UI/ColorUI.hlsl", "VS");
	}

	// Pixel Shader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"UI/ColorUI.hlsl", "PS");
	}

	// InputLayout
	{
		il = new InputLayout();
		il->Create(VertexColor::descs, VertexColor::count, vs->GetBlob());
	}

	// World Buffer
	{
		wb = new WorldBuffer();
	}
}

TextureRect::TextureRect
(Vector3 position, std::vector<Vector2>* uv,Vector3 size, float rotation, 
Color path, ID3D11ShaderResourceView* Fontpng, Vector2 Imagesize)
	: position(position), size(size), rotation(rotation)
{	// 텍스트 출력용
	{
		D3DXMatrixTranslation(&X, 0, 0, 0);
	}

	// vertices
	{	// 텍스트 출력용 VertexTexture형식
		Textvertices.assign(4, TextureVertexTexture());

		Textvertices[0].position = Vector3(-0.5f, -0.5f, 0.0f); // 좌하단
		Textvertices[1].position = Vector3(+0.5f, +0.5f, 0.0f); // 우상단
		Textvertices[2].position = Vector3(+0.5f, -0.5f, 0.0f); // 우하단
		Textvertices[3].position = Vector3(-0.5f, +0.5f, 0.0f); // 좌상단

		Textvertices[0].uv = (*uv)[0];
		Textvertices[1].uv = (*uv)[1];
		Textvertices[2].uv = (*uv)[2];
		Textvertices[3].uv = (*uv)[3];

		for(auto& def : Textvertices) {
			def.color = path;
		}
	}

	// Vertex Buffer
	{
		vb = new VertexBuffer();
		vb->Create(Textvertices, D3D11_USAGE_DYNAMIC);
	}

	// Index Buffer
	{
		indices = { 0,1,2,0,3,1 };
		ib = new IndexBuffer();
		ib->Create(indices, D3D11_USAGE_IMMUTABLE);
	}

	// Vertex Shader
	{
		vs = new VertexShader();
		vs->Create(ShaderPath + L"FontVertexTexture.hlsl", "VS");
	}

	// Pixel Shader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"FontVertexTexture.hlsl", "PS");
	}

	{
		ot = new OutlineBuffer();
		ot->SetTextureSize(Imagesize);
		ot->SetOutlineCount(2);
	}

	// InputLayout
	{
		il = new InputLayout();
		il->Create(TextureVertexTexture::descs, TextureVertexTexture::count, vs->GetBlob());
	}

	// World Buffer
	{
		wb = new WorldBuffer();
	}
	// srv
	{
		srv = Fontpng;
	}
}

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation, wstring path, Vector2 flip)
	: position(position), size(size), rotation(rotation)
{
	{
		D3DXMatrixTranslation(&X, 0, 0, 0);
	}

	buff(flip);

	// Vertex Buffer
	{
		vb = new VertexBuffer();
		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
	}

	// Shader Resource View
	{
		HRESULT hr = D3DX11CreateShaderResourceViewFromFile
		(
			DEVICE,
			path.c_str(),
			nullptr,
			nullptr,
			&srv,
			nullptr
		);
		CHECK(hr);
		SRV::Get()->AddSRV(String::ToString(path), srv);
	}
}

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation, Vector2 flip)
	: position(position), size(size), rotation(rotation)
{

	{
		D3DXMatrixTranslation(&X, 0, 0, 0);
	}

	buff(flip);

	// Vertex Buffer
	{
		vb = new VertexBuffer();
		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
	}
}


TextureRect::~TextureRect()
{
	SAFE_DELETE(vb);
	SAFE_DELETE(ib);
	SAFE_DELETE(vs);
	SAFE_DELETE(ps);
	SAFE_DELETE(il);
	SAFE_DELETE(wb);
	//SAFE_RELEASE(srv);
}

void TextureRect::MapVertexBuffer()
{
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
}

void TextureRect::UnmapVertexBuffer()
{
	memcpy(subResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
	DC->Unmap(vb->GetResource(), 0);
}

void TextureRect::SetShader(wstring shaderpath)
{
	vs->Clear();
	ps->Clear();

	vs->Create(shaderpath, "VS");
	ps->Create(shaderpath, "PS");
}

void TextureRect::Update()
{
	UpdateWorld();
}

void TextureRect::Update(Vector3 position)
{
	this->position = position;
	UpdateWorld();
}


void TextureRect::UpdateWorld()
{
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(rotation));

	world = S * X * R * T ;
	wb->SetWorld(world);
}

void TextureRect::Render()
{
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();
	ps->SetShader();	

	if(ot)
		ot->SetPSBuffer(2);

	wb->SetVSBuffer(0);



	if (srv)
		DC->PSSetShaderResources(0, 1, &srv);

	DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void TextureRect::GUI()
{

}

void TextureRect::buff(Vector2 flip = {0,0})
{
	flip.x ? flip.x = 1 : flip.x = 0;
	flip.y ? flip.y = 1 : flip.y = 0;

	{
		D3DXMatrixTranslation(&X, 0, 0, 0);
	}

	// vertices
	{
		vertices.assign(4, VertexTexture());

		vertices[0].position = verticesLocalPosition[0] = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[1].position = verticesLocalPosition[1] = Vector3(0.5f, 0.5f, 0.0f);
		vertices[2].position = verticesLocalPosition[2] = Vector3(0.5f, -0.5f, 0.0f);
		vertices[3].position = verticesLocalPosition[3] = Vector3(-0.5f, 0.5f, 0.0f);

		vertices[0].uv = Vector2(flip.x, !flip.y);
		vertices[1].uv = Vector2(!flip.x, flip.y);
		vertices[2].uv = Vector2(!flip.x, !flip.y);
		vertices[3].uv = Vector2(flip.x, flip.y);
	}

	// Index Buffer
	{
		indices = { 0,1,2,0,3,1 };
		ib = new IndexBuffer();
		ib->Create(indices, D3D11_USAGE_IMMUTABLE);
	}

	// Vertex Shader
	{
		vs = new VertexShader();
		vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");
	}

	// Pixel Shader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");
	}

	// InputLayout
	{
		il = new InputLayout();
		il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());
	}

	// World Buffer
	{
		wb = new WorldBuffer();
	}
}
