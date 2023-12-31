#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReversed, float playRate)
	: clipName(clipName), frameCount(frameCount), playRate(playRate), bReversed(bReversed)
{
	srv = srcTex->GetSRV();

	// 텍스처의 너비와 높이
	float imageWidth = srcTex->GetWidth();
	float imageHeight = srcTex->GetHeight();

	// 클립 사이즈 (애니메이션이 그려져있는 텍스처의 길이)
	Vector2 clipSize = endPos - startPos;

	// 프레임 사이즈 (애니메이션 그림 중 하나)
	Vector2 frameSize;
	frameSize.x = clipSize.x / frameCount;
	frameSize.y = clipSize.y;

	// 텍셀 프레임 계산
	texelFrameSize.x = frameSize.x / imageWidth;
	texelFrameSize.y = frameSize.y / imageHeight;

	// 텍셀 시작 위치
	Vector2 texelStartPos;
	texelStartPos.x = startPos.x / imageWidth;
	texelStartPos.y = startPos.y / imageHeight;

	Vector2 keyframe;

	for (UINT i = 0; i < frameCount; i++)
	{
		keyframe.x = texelStartPos.x + (texelFrameSize.x * i);
		keyframe.y = texelStartPos.y;

		keyFrames.push_back(keyframe);
	}
}

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, std::vector<Vector2> Pos, bool bReversed, float playRate)
	: clipName(clipName), frameCount(frameCount), playRate(playRate), bReversed(bReversed)
{
	srv = srcTex->GetSRV();

	// 텍스처의 너비와 높이
	float imageWidth = srcTex->GetWidth();
	float imageHeight = srcTex->GetHeight();

	// 클립 사이즈 (애니메이션이 그려져있는 텍스처의 길이)
	Vector2 clipSize = Pos[1] - Pos[0];

	// 프레임 사이즈 (애니메이션 그림 중 하나)
	Vector2 frameSize;
	frameSize.x = clipSize.x / frameCount;
	frameSize.y = clipSize.y;

	// 텍셀 프레임 계산
	texelFrameSize.x = frameSize.x / imageWidth;
	texelFrameSize.y = frameSize.y / imageHeight;

	// 텍셀 시작 위치
	Vector2 texelStartPos;
	texelStartPos.x = Pos[0].x / imageWidth;
	texelStartPos.y = Pos[0].y / imageHeight;

	Vector2 keyframe;

	for (UINT i = 0; i < frameCount; i++)
	{
		keyframe.x = texelStartPos.x + (texelFrameSize.x * i);
		keyframe.y = texelStartPos.y;

		keyFrames.push_back(keyframe);
	}
}

Animator::Animator()
{
}

Animator::~Animator()
{
	for (auto clip : animClips)
		SAFE_DELETE(clip.second);
}

void Animator::Update()
{
	if (deltaTime > currentClip->playRate)
	{
		if (currentClip->bReversed == false)
		{
			currentFrameIndex++;

			if (currentFrameIndex == currentClip->frameCount)
				currentFrameIndex = 0;

			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}
		else
		{
			currentFrameIndex--;

			if (currentFrameIndex == -1)
				currentFrameIndex = currentClip->frameCount - 1;

			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}
		deltaTime = 0.f;
	}
	else
		deltaTime += Time::Delta();
}

void Animator::AddAnimClip(AnimationClip* animClip)
{
	animClips.insert(make_pair(animClip->clipName, animClip));
}

void Animator::SetCurrentAnimClip(wstring clipName)
{
	if (currentClip == nullptr && CheckExist(clipName) == true)
		currentClip = animClips.find(clipName)->second;
	else if (currentClip != nullptr && currentClip->clipName == clipName)
		return;

	if (CheckExist(clipName))
	{
		currentClip = animClips.find(clipName)->second;
		deltaTime = .0f;

		// 역재생이 활성화 되어있는 경우
		if (currentClip->bReversed == true)
			currentFrameIndex = currentClip->frameCount - 1;
		else
			currentFrameIndex = 0;

		// 현재 프레임 업데이트
		currentFrame = currentClip->keyFrames[currentFrameIndex];
	}
}
