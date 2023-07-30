#include "Framework.h"
#include "AnimationRect.h"

#include "Utilities/Animator.h"

AnimationRect::AnimationRect(Vector3 position, Vector3 size)
	: TextureRect(position, size, .0f)
{
	SetShader(ShaderPath + L"Animation.hlsl");
	speed = 100;
	animator = new Animator();
	moveP = { 1,0,0 };

	{
		Texture2D* srcTex = new Texture2D(TexturePath + L"player.png");
		AnimationClip* RunR = new AnimationClip(L"RunR", srcTex, 10, Values::ZeroVec2, { srcTex->GetWidth(), srcTex->GetHeight() * .5f });
		AnimationClip* RunL = new AnimationClip(L"RunL", srcTex, 10, { 0, srcTex->GetHeight() * 0.5f }, { srcTex->GetWidth(), srcTex->GetHeight() }, true);
		animator->AddAnimClip(RunR);
		animator->AddAnimClip(RunL);
		animator->SetCurrentAnimClip(L"RunL");
		SAFE_DELETE(srcTex);
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
}

AnimationRect::~AnimationRect()
{
	
}

void AnimationRect::Update()
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

	__super::Update();
	// __super = 부모함수를 수행시키겠다.
}

void AnimationRect::Render()
{
	srv = animator->GetCurrentSRV();

	DC->PSSetSamplers(0, 1, &point[1]);
	DC->OMSetBlendState(bPoint[1], nullptr, (UINT)0xFFFFFFFF);

	__super::Render();
}

void AnimationRect::SetNormalize(D3DXVECTOR2 move, const int speed, const float delta)
{
	D3DXVec2Normalize(&move, &move);
	SetPosition(move.x * speed * delta, move.y * speed * delta);
}


void AnimationRect::Follow(const Vector3 st, const Vector3 direc)
{
	SetPosition(st.x + direc.x, st.y + direc.y);
	if (moveP.x) { animator->SetCurrentAnimClip(L"RunR"); }
	else { animator->SetCurrentAnimClip(L"RunL"); }
}

void AnimationRect::Move()
{
	auto key = Keyboard::Get();
	auto delta = Time::Delta();
	

	// 방향판별
	if (key->Press('D')) { moveP = { 1,0,0 }; }
	else if (key->Press('A')) { moveP = { 0,1,0 }; }

	// 이동판별
	if (key->Press('W') && key->Press('D'))
	{
		SetNormalize({ 1, 1 }, speed, delta);
		animator->SetCurrentAnimClip(L"RunR");
	}
	else if (key->Press('W') && key->Press('A'))
	{
		SetNormalize({ -1, 1 }, speed, delta);
		animator->SetCurrentAnimClip(L"RunL");
	}
	else if (key->Press('S') && key->Press('D'))
	{
		SetNormalize({ 1, -1 }, speed, delta);
		animator->SetCurrentAnimClip(L"RunR");
	}
	else if (key->Press('S') && key->Press('A'))
	{
		SetNormalize({ -1, -1 }, speed, delta);
		animator->SetCurrentAnimClip(L"RunL");
	}
	else if (key->Press('A'))
	{
		SetNormalize({ -1, 0 }, speed, delta);
		animator->SetCurrentAnimClip(L"RunL");
	}
	else if (key->Press('D'))
	{
		SetNormalize({ 1, 0 }, speed, delta);
		animator->SetCurrentAnimClip(L"RunR");
	}
	else if (key->Press('W'))
	{
		SetNormalize({ 0, 1 }, speed, delta);
		if (moveP.x) { animator->SetCurrentAnimClip(L"RunR"); }
		else { animator->SetCurrentAnimClip(L"RunL"); }
	}
	else if (key->Press('S'))
	{
		SetNormalize({ 0, -1 }, speed, delta);
		if (moveP.x) { animator->SetCurrentAnimClip(L"RunR"); }
		else { animator->SetCurrentAnimClip(L"RunL"); }
	}
	else {
		if (moveP.x) { animator->SetCurrentAnimClip(L"IdleR"); }
		else { animator->SetCurrentAnimClip(L"IdleL"); }
	}
}
