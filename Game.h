#include "DX11BaseClass.h"
#include <xnamath.h>
#include <stdlib.h>
#include <DirectXColors.h>
class Game : public DX11BaseClass //inherits from base class
{
public:
	Game();
	~Game();
	bool LoadContent();
	void UnloadContent();
	void Render();

private:
	
	ID3D11VertexShader*     solidColourVS_ = nullptr; //will be used to store vertex shader

	ID3D11PixelShader*      ColourPS_ = nullptr; //will be used to store one of the pixel shaders
	ID3D11PixelShader*      solidColourPS_= nullptr; //will be used to store a second pixel shader for solid colour

	XMFLOAT4                Green = XMFLOAT4(0.0f, 0.9f, 0.0f, 1.0f); //float4 that stores the RGB values for a green colour so it can be called more easily in the main code
	XMFLOAT4                Red = XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f); //float4 that stores the RGB values for a red colour so it can be called more easily in the main code
	int                     livesLeft = 3; //the amount of lives the player has left. used to decide when the game is over
	int                     score = 0; //shows the amount of times they have successfully pressed space
	float                   StartTime; //used to set the store the starting time for the deltatime calculation
	float                   EndTime; //used to set the store the starting time for the deltatime calculation
	bool                    greenTime = false; //set to true during period where light is green. used to decide whether pressing space is a success or failure
	ID3D11InputLayout*      inputLayout_ = nullptr; //used to store input layout
	ID3D11Buffer*           vertexBuffer_ = nullptr; //used to store vertex buffer
	ID3D11Buffer*           indexBuffer_ = nullptr; //used to store index buffer
	ID3D11Buffer*           constantBuffer_ = nullptr; //used to store constant buffer
	XMMATRIX                world_; //world matrix
	XMMATRIX                view_; //view matrix
	XMMATRIX                projection_; //projection matrix
	XMMATRIX                translationMat_; //translation matrix
	XMMATRIX                rotationMat_; //rotation matrix
	int                     moveMultiplier = 1; //used to set how fast the cube will move. increased on successful space bar presses
	float                   xDistance; //used to record where the cube is on the screen

	struct SimpleVertex //used to store the vertex values of the cube that will be rendered.
	{
		XMFLOAT3 Pos;
		XMFLOAT3 Normal;
	};
	struct ConstantBuffer //used to store various matrix values that are then used in the rendering
	{
		XMMATRIX mWorld;
		XMMATRIX mView;
		XMMATRIX mProjection;
		XMFLOAT4 vLightDir[2];
		XMFLOAT4 vLightColor[2];
		XMFLOAT4 vOutputColor;
	};
};

