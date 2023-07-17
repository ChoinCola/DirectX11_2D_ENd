#pragma once
#include "Framework.h"
#include "Star.h"

Star::Star(Vector3 position, Vector3 size, float rotation)
	: position(position), size(size), rotation(rotation)
{
	// vertices
	{
		vertices.assign(6, VertexColor());

		vertices[0].position = Vector3(-1.0f, -0.5f, 0.0f);
		vertices[0].color = color;

		vertices[1].position = Vector3(+0.0f, +1.0f, 0.0f);
		vertices[1].color = color;

		vertices[2].position = Vector3(1.0f, -0.5f, 0.0f);
		vertices[2].color = color;

		vertices[3].position = Vector3(+0.5f, -1.0f, 0.0f);
		vertices[3].color = color;
	
		vertices[4].position = Vector3(-1.0f, +0.5f, 0.0f);
		vertices[4].color = color;

		vertices[5].position = Vector3(0.0f, -1.0f, 0.0f);
		vertices[5].color = color;
	}


	// Vertex Buffer
	{
		vb = new VertexBuffer();
		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
	}

	// Index Buffer
	{
		indices = { 0,1,2,3,4,5 };

		ib = new IndexBuffer();
		ib->Create(indices, D3D11_USAGE_IMMUTABLE);
	}

	// Vertex Shader
	{
		vs = new VertexShader();
		vs->Create(ShaderPath + L"VertexColor.hlsl", "VS");
	}

	// Pixel Shader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"VertexColor.hlsl", "PS");
	}

	// Input Layout
	{
		il = new InputLayout();
		il->Create(VertexColor::descs, VertexColor::count, vs->GetBlob());
	}

	// World
	{
		wb = new WorldBuffer();
	}

}

Star::~Star()
{
	SAFE_DELETE(wb);

	SAFE_DELETE(il);
	SAFE_DELETE(ps);
	SAFE_DELETE(vs);

	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
}

void Star::Update()
{
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, rotation);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;
	wb->SetWorld(world);

	/*UpdateWorld();
	collision->Update(Vector3(100, 100, 0), Vector3(100, 100, 1), 0.f);*/
}

void Star::Render()
{
	// IA
	{
		vb->SetIA();
		ib->SetIA();
		il->SetIA();
		DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	// VS
	{
		vs->SetShader();
		wb->SetVSBuffer(0);
	}

	// PS
	{
		ps->SetShader();
	}

	DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void Star::Move()
{
	if (Keyboard::Get()->Press('W'))
		position.y += 10;
	if (Keyboard::Get()->Press('S'))
		position.y -= 10;

	if (Keyboard::Get()->Press('A'))
		position.x -= 10;
	if (Keyboard::Get()->Press('D'))
		position.x += 10;
}

void Star::UpdateWorld()
{
	// Scale
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	// Rotation
	D3DXMatrixRotationZ(&R, rotation);
	// Translation
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;
	wb->SetWorld(world);
}