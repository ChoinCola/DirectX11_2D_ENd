#include "Framework.h"
#include "AnimationRect.h"

#include "Utilities/Animator.h"

AnimationRect::AnimationRect(Vector3 position, Vector3 size)
	: TextureRect(position, size, .0f)
{
	SetShader(ShaderPath + L"Animation.hlsl");

	animator = new Animator();

	{
		//Texture2D* srcTex = new Texture2D(TexturePath + L"player.png");
		//AnimationClip* RunR = new AnimationClip(L"RunR", srcTex, 10, Values::ZeroVec2, { srcTex->GetWidth(), srcTex->GetHeight() * .5f });
		//AnimationClip* RunL = new AnimationClip(L"RunL", srcTex, 10, { 0, srcTex->GetHeight() * 0.5f }, { srcTex->GetWidth(), srcTex->GetHeight() }, true);
		//animator->AddAnimClip(RunR);
		//animator->AddAnimClip(RunL);
		//animator->SetCurrentAnimClip(L"RunL");
		//SAFE_DELETE(srcTex);
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
}

void AnimationRect::Render()
{
	srv = animator->GetCurrentSRV();

	DC->PSSetSamplers(0, 1, &point[1]);
	DC->OMSetBlendState(bPoint[1], nullptr, (UINT)0xFFFFFFFF);

	__super::Render();
}

void AnimationRect::Move()
{
	auto key = Keyboard::Get();
	auto delta = Time::Delta();

	if (key->Press('W') && key->Press('D'))
	{
		position.y += 25 * delta;
		position.x += 100 * delta;
		animator->SetCurrentAnimClip(L"RunU");
	}
	else if (key->Press('W') && key->Press('A'))
	{
		position.y += 25 * delta;
		position.x -= 100 * delta;
		animator->SetCurrentAnimClip(L"RunU");
	}
	else if (key->Press('S') && key->Press('D'))
	{
		position.y -= 25 * delta;
		position.x += 100 * delta;
		animator->SetCurrentAnimClip(L"RunD");
	}
	else if (key->Press('S') && key->Press('A'))
	{
		position.y -= 25 * delta;
		position.x -= 100 * delta;
		animator->SetCurrentAnimClip(L"RunD");
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

	if(key->Press('W'))
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
