#ifndef _BASE_CLASS_H
#define _BASE_CLASS_H
#define INITGUID

#include<d3d11.h>
#include<d3dx11.h>
#include<DxErr.h> //error handling library
#include <D3DCompiler.h> //for the compiling library
#include <DirectXColors.h> 
#include <dinput.h> //direct input library used for keyboard input

//defines the process for checking if a key has been pressed
#define KEYDOWN( name, key ) ( name[key] & 0x80 )


//this base class is used to initialise directx11 and directinput, and is inherited by the main gameplay class


//forward declarations for the base dx11 class
class DX11BaseClass
{
public:
	DX11BaseClass();
	virtual ~DX11BaseClass();

	bool Initialize(HINSTANCE hInstance, HWND hwnd); //initialize direct3d
	void Shutdown();  //releases all d3d objects when deleted or out of scope
	virtual bool LoadContent(); //load content for d3d
	virtual void UnloadContent(); //unload content
	//virtual void Update(float dt) = 0; //updates once per frame
	virtual void Render() = 0; //the rendering code
	bool CompileD3DShader(char* filePath, char* entry, char* shaderModel, ID3DBlob** buffer);
	
protected:
	HINSTANCE hInstance_;
	HWND hwnd_;

	D3D_DRIVER_TYPE driverType_;
	D3D_FEATURE_LEVEL featureLevel_;

	ID3D11Device* d3dDevice_;
	ID3D11DeviceContext* d3dContext_;
	IDXGISwapChain* swapChain_;
	ID3D11RenderTargetView* backBufferTarget_;
	ID3D11Texture2D* depthTexture_; //stores data for the depth buffer
	ID3D11DepthStencilView* depthStencilView_; //depth/stencil view
	LPDIRECTINPUT8 directInput_; //directinput
	LPDIRECTINPUTDEVICE8 keyboardDevice_; //the keyboard device
	char keyboardKeys_[256];
	char prevkeyboardKeys_[256];
	UINT width;
	UINT height;

};

#endif
