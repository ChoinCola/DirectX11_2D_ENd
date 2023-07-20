#include "Framework.h"
#include "BlurTexture.h"

BlurTexture::BlurTexture(Vector3 position, Vector3 size, float rotation, wstring path)
	: Dmd(position, size, rotation, path)
{
	buffer = new BlurBuffer();
	buffer->SetTextureSize({ size.x, size.y });
	SetShader(ShaderPath + L"TextureBlur.hlsl");
	//SetShader(ShaderPath + L"TextureFilter_2.hlsl");
}

BlurTexture::~BlurTexture()
{
	SAFE_DELETE(buffer);
}

void BlurTexture::Update()
{
	Dmd::Update();
}

void BlurTexture::Render()
{
	buffer->SetPSBuffer(1);
	__super::Render();
}

void BlurTexture::GUI()
{
	ImGui::Begin("BlurCount");
	{
		ImGui::SliderInt("BlurCount", buffer->GetBlurCountPtr(), 1, 20);
	}
	ImGui::End();
}
