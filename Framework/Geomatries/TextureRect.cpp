#include "Framework.h"
#include "TextureRect.h"

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation, wstring path)
	: position(position), size(size), rotation(rotation)
{
	// vertices
	{
		vertices.assign(4, VertexTexture());

		vertices[0].position = verticesLocalPosition[0] = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[1].position = verticesLocalPosition[1] = Vector3(0.5f, 0.5f, 0.0f);
		vertices[2].position = verticesLocalPosition[2] = Vector3(0.5f, -0.5f, 0.0f);
		vertices[3].position = verticesLocalPosition[3] = Vector3(-0.5f, 0.5f, 0.0f);

		vertices[0].uv = Vector2(0, 1);
		vertices[1].uv = Vector2(1, 0);
		vertices[2].uv = Vector2(1, 1);
		vertices[3].uv = Vector2(0, 0);
	}

	// Vertex Buffer
	{
		vb = new VertexBuffer();
		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
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

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation)
	: position(position), size(size), rotation(rotation)
{
	// vertices
	{
		vertices.assign(4, VertexTexture());

		vertices[0].position = verticesLocalPosition[0] = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[1].position = verticesLocalPosition[1] = Vector3(0.5f, 0.5f, 0.0f);
		vertices[2].position = verticesLocalPosition[2] = Vector3(0.5f, -0.5f, 0.0f);
		vertices[3].position = verticesLocalPosition[3] = Vector3(-0.5f, 0.5f, 0.0f);

		vertices[0].uv = Vector2(0, 1);
		vertices[1].uv = Vector2(1, 0);
		vertices[2].uv = Vector2(1, 1);
		vertices[3].uv = Vector2(0, 0);
	}

	// Vertex Buffer
	{
		vb = new VertexBuffer();
		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
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

void TextureRect::Move()
{
	//if (Keyboard::Get()->Press('W'))
	//	position.y += 100 * Time::Delta();
	//if (Keyboard::Get()->Press('S'))
	//	position.y -= 100 * Time::Delta();

	//if (Keyboard::Get()->Press('D'))
	//	position.x += 100 * Time::Delta();
	//if (Keyboard::Get()->Press('A'))
	//	position.x -= 100 * Time::Delta();

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
	Move();
}

void TextureRect::UpdateWorld()
{
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(rotation));

	world = S * R * T;
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
	wb->SetVSBuffer(0);

	DC->PSSetShaderResources(0, 1, &srv);

	DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void TextureRect::GUI()
{

}
