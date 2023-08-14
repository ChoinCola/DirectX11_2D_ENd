#pragma once

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

//미리 컴파일된 헤더.
//pch pre compiled header

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <map>
#include <unordered_map>
#include <assert.h>
#include <fstream>

using namespace std;

//DirectX
#include <DirectXTex/DirectXTex.h>
#pragma comment(lib, "DirectXTex/DirectXTex.lib")

#include <d3dcompiler.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dcompiler.lib")
//////////////////////////////////////////
#include <d2d1_2.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
//////////////////////////////////////////
//ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#pragma comment(lib, "ImGui/ImGui.lib")
//////////////////////////////////////////
//FMOD
#include "FMOD/inc/fmod.hpp"
#ifdef _WIN64
#pragma comment(lib, "FMOD/lib/x64/fmod_vc.lib")
#else
#pragma comment(lib, "FMOD/lib/x86/fmod_vc.lib")
#endif
/////////////////////////////////////////
typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR2 Vector2;
typedef D3DXMATRIX  Matrix;
typedef D3DXCOLOR   Color;
typedef UINT		uint;

#include "Interfaces/IObject.h"

#include "Utilities/SingletonBase.h"

#include "Systems/Graphics.h"
#include "Systems/Keyboard.h"
#include "Systems/Mouse.h"
#include "Systems/Time.h"
#include "Systems/Sounds.h"
#include "Systems/SRV.h"
#include "Systems/Text.h"

#include "Utilities/Gui.h"


#define DEVICE Graphics::Get()->GetDevice()
#define DC     Graphics::Get()->GetDC()

#define CHECK(p) assert(SUCCEEDED(p))
#define Zero(p)  ZeroMemory(&p, sizeof(p))

#define SAFE_DELETE(p)		 { if(p) { delete(p);	   (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[](p);	   (p) = nullptr; } }
#define SAFE_RELEASE(p)		 { if(p) { (p)->Release(); (p) = nullptr; } }

#include "Utilities/DirectHelper.h"

#include "Renders/IA/IndexBuffer.h"
#include "Renders/IA/VertexBuffer.h"
#include "Renders/IA/InputLayout.h"
#include "Renders/Resources/VertexTypes.h"
#include "Renders/Resources/ShaderBuffer.h"
#include "Renders/Resources/GlobalBuffer.h"
#include "Renders/Resources/Texture2D.h"

#include "Renders/Shaders/IShader.h"
#include "Renders/Shaders/VertexShader.h"
#include "Renders/Shaders/PixelShader.h"

#include "Utilities/Animator.h"

#include "Geomatries/ShadedTexture.h"
#include "Geomatries/TextureRect.h"
#include "Geomatries/AnimationRect.h"


#include "Renders/IA/VertexBuffer.h"
#include "Renders/IA/IndexBuffer.h"
#include "Renders/IA/InputLayout.h"
#include "Renders/States.h"

#include "Renders/Shaders/VertexShader.h"
#include "Renders/Shaders/PixelShader.h"

#include "Utilities/BoundingBox.h"
#include "Utilities/String.h"
#include "Utilities/Path.h"

#include "Systems/Camera.h"

#include "Game/UI/ProgressBar.h"
#include "Game/HPBar.h"

#include "Game/Item.h"
#include "Game/Character.h"
#include "Game/Button.h"
#include "Game/MousePointer.h"

#define WinMaxWidth 1280
#define WinMaxHeight 720

const wstring LUI = L"../Framework/GameAsset/UI/";
const wstring LButton = L"../Framework/GameAsset/UI/button/";
const wstring HPPath = L"../Framework/GameAsset/UI/HP/";
const wstring ShaderPath  = L"../_Shaders/";
const wstring TexturePath = L"../_Resources/_Textures/";
const wstring LCharacter =  L"../Framework/GameAsset/Character/";
const wstring Effects = L"../Framework/GameAsset/Effects/";
const wstring LItem = L"../Framework/GameAsset/Item/";
const wstring SoundPath   = L"../_Resources/_Sounds/";
const string  TilePath    =  "../_Resources/_TileData/";

extern HWND handle;