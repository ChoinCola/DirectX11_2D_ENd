#include "Framework.h"
#include "Character_Demo.h"

#include "Utilities/Animator.h"

Character_Demo::Character_Demo(Vector3 position, Vector3 size, float rotation)
	: position(position), size(size), rotation(rotation)
{
	SetShader(ShaderPath + L"Animation.hlsl");
	animator = new Animator();

	#pragma region Animation
	{
		Texture2D* idle = new Texture2D(Character + L"Goblin/goblin_idle_spritesheet.png");
		Texture2D* MoveR = new Texture2D(Character + L"Goblin/goblin_run_spritesheet.png");

		AnimationClip* RunR = new AnimationClip(L"RunR", MoveR, 6, Values::ZeroVec2, { MoveR->GetWidth(), MoveR->GetHeight()});
		AnimationClip* RunL = new AnimationClip(L"RunL", MoveR, 6, Values::ZeroVec2, { MoveR->GetWidth(), MoveR->GetHeight() }, true);
		AnimationClip* Idle = new AnimationClip(L"Idle", idle, 6, Values::ZeroVec2, { MoveR->GetWidth(), MoveR->GetHeight() });

		animator->AddAnimClip(RunR);
		animator->AddAnimClip(RunL);
		animator->AddAnimClip(Idle);

		animator->SetCurrentAnimClip(L"Idle");

		SAFE_DELETE(idle);
		SAFE_DELETE(MoveR);
	}

	// Sampler
	{
		// 선형 보간
		D3D11_SAMPLER_DESC desc;
		States::GetSamplerDesc(&desc);
		States::CreateSampler(&desc, &point[0]);

		// point sampling
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		States::CreateSampler(&desc, &point[1]);
	}

	// Blend
	{
		// 블랜드 비활성화
		D3D11_BLEND_DESC desc;
		States::GetBlendDesc(&desc);
		States::CreateBlend(&desc, &bPoint[0]);

		// 블랜드 활성화
		desc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&desc, &bPoint[1]);
	}
	#pragma endregion

	#pragma region Vertex
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
	#pragma endregion
}

Character_Demo::~Character_Demo()
{
	SAFE_DELETE(vb);
	SAFE_DELETE(ib);
	SAFE_DELETE(vs);
	SAFE_DELETE(ps);
	SAFE_DELETE(il);
	SAFE_DELETE(wb);
	//SAFE_RELEASE(srv);
}

void Character_Demo::Move()
{
	auto key = Keyboard::Get();
	auto delta = Time::Delta();

	if (key->Press('W') && key->Press('D'))
	{
		position.y += 25 * delta;
		position.x += 100 * delta;
		animator->SetCurrentAnimClip(L"RunR");
	}
	else if (key->Press('W') && key->Press('A'))
	{
		position.y += 25 * delta;
		position.x -= 100 * delta;
		animator->SetCurrentAnimClip(L"RunL");
	}
	else if (key->Press('S') && key->Press('D'))
	{
		position.y -= 25 * delta;
		position.x += 100 * delta;
		animator->SetCurrentAnimClip(L"RunR");
	}
	else if (key->Press('S') && key->Press('A'))
	{
		position.y -= 25 * delta;
		position.x -= 100 * delta;
		animator->SetCurrentAnimClip(L"RunL");
	}
	else if (key->Press('A'))
	{
		position.x -= 128 * delta;
		animator->SetCurrentAnimClip(L"RunL");
	}
	else if (key->Press('D'))
	{
		position.x += 128 * delta;
		animator->SetCurrentAnimClip(L"RunR");
	}

	if (key->Press('W'))
	{
		position.y += 72 * delta;
		animator->SetCurrentAnimClip(L"RunU");
	}
	else if (key->Press('S'))
	{
		position.y -= 72 * delta;
		animator->SetCurrentAnimClip(L"RunD");
	}
}

void Character_Demo::MapVertexBuffer()
{
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
}

void Character_Demo::UnmapVertexBuffer()
{
	memcpy(subResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
	DC->Unmap(vb->GetResource(), 0);
}

void Character_Demo::SetShader(wstring shaderpath)
{
	vs->Clear();
	ps->Clear();

	vs->Create(shaderpath, "VS");
	ps->Create(shaderpath, "PS");
}

void Character_Demo::Update()
{
	animator->Update();
	MapVertexBuffer();
	{
		vertices[0].uv.x = animator->GetCurrentFrame().x;
		vertices[0].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		vertices[1].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[1].uv.y = animator->GetCurrentFrame().y;

		vertices[2].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[2].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		vertices[3].uv.x = animator->GetCurrentFrame().x;
		vertices[3].uv.y = animator->GetCurrentFrame().y;
	}
	UnmapVertexBuffer();

	UpdateWorld();
	Move();
}

void Character_Demo::UpdateWorld()
{
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(rotation));

	world = S * R * T;
	wb->SetWorld(world);
}

void Character_Demo::Render()
{
	srv = animator->GetCurrentSRV();

	DC->PSSetSamplers(0, 1, &point[1]);
	DC->OMSetBlendState(bPoint[1], nullptr, (UINT)0xFFFFFFFF);
#pragma region Vertex
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();
	ps->SetShader();
	wb->SetVSBuffer(0);

	DC->PSSetShaderResources(0, 1, &srv);

	DC->DrawIndexed(ib->GetCount(), 0, 0);
#pragma endregion
}

void Character_Demo::GUI()
{

}
