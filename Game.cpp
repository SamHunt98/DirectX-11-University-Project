#include "Game.h"

//class that contains all of the code for the gameplay. 

Game::Game()
{
}


Game::~Game()
{
}

bool Game::LoadContent()
{
	//compile the vertex shader
	ID3DBlob* vsBuffer = 0;

	bool compileResult = CompileD3DShader((char*)"Game.fx", (char*)"VS", (char*)"vs_4_0", &vsBuffer);

	if (compileResult == false)
	{
		DXTRACE_MSG("Error compiling the vertex shader!");
		return false;
	}

	HRESULT d3dResult;
	//creates the vertex shader
	d3dResult = d3dDevice_->CreateVertexShader(vsBuffer->GetBufferPointer(),
		vsBuffer->GetBufferSize(), 0, &solidColourVS_);
	if (FAILED(d3dResult))
	{
		vsBuffer->Release();
		return d3dResult;
	}
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	d3dResult = d3dDevice_->CreateInputLayout(layout, numElements, vsBuffer->GetBufferPointer(),
		vsBuffer->GetBufferSize(), &inputLayout_);
	vsBuffer->Release();
	if (FAILED(d3dResult))
		return d3dResult;
	// Set the input layout
	d3dContext_->IASetInputLayout(inputLayout_);

	// Compile the pixel shader
	ID3DBlob* psBuffer = nullptr;
	d3dResult = CompileD3DShader((char*)"Game.fx", (char*)"PS", (char*)"ps_4_0", &psBuffer);
	if (FAILED(d3dResult))
	{
		MessageBox(nullptr,
			"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
		return d3dResult;
	}
	// Create the pixel shader
	d3dResult = d3dDevice_->CreatePixelShader(psBuffer->GetBufferPointer(), psBuffer->GetBufferSize(), nullptr, &ColourPS_);
	psBuffer->Release();
	if (FAILED(d3dResult))
		return d3dResult;

	// Compile the pixel shader
	psBuffer= nullptr;
	d3dResult = CompileD3DShader((char*)"Game.fx", (char*)"PSSolid", (char*)"ps_4_0", &psBuffer);
	if (FAILED(d3dResult))
	{
		MessageBox(nullptr,
		"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
		return d3dResult;
	}
	// Create the pixel shader
	d3dResult = d3dDevice_->CreatePixelShader(psBuffer->GetBufferPointer(), psBuffer->GetBufferSize(), nullptr, &solidColourPS_);
	psBuffer->Release();
	if (FAILED(d3dResult))
		return d3dResult;

	
	// Create vertex buffer
	SimpleVertex vertices[] = //vertices of the cubes
	{
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) },

		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
	};
	//buffer description for vertex buffer
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 24;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData = {};
	InitData.pSysMem = vertices;
	d3dResult = d3dDevice_->CreateBuffer(&bd, &InitData, &vertexBuffer_);
	if (FAILED(d3dResult))
		return d3dResult;
	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	//set the vertex buffer values
	d3dContext_->IASetVertexBuffers(0, 1, &vertexBuffer_, &stride, &offset);
	//Create index buffer
	
	WORD indices[] =
	{
		3,1,0,
		2,1,3,

		6,4,5,
		7,4,6,

		11,9,8,
		10,9,11,

		14,12,13,
		15,12,14,

		19,17,16,
		18,17,19,

		22,20,21,
		23,20,22
	};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 36;        // 36 vertices needed for 12 triangles in a triangle list
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = indices;
	d3dResult = d3dDevice_->CreateBuffer(&bd, &InitData, &indexBuffer_);
	if (FAILED(d3dResult))
		return d3dResult;
	// Set index buffer
	d3dContext_->IASetIndexBuffer(indexBuffer_, DXGI_FORMAT_R16_UINT, 0);

	// Set primitive topology
	d3dContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	
	// Create the constant buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	d3dResult = d3dDevice_->CreateBuffer(&bd, nullptr, &constantBuffer_);
	if (FAILED(d3dResult))
		return d3dResult;

	// Initialize the world matrices
	world_ = XMMatrixIdentity();

	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 4.0f, -20.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	view_ = XMMatrixLookAtLH(Eye, At, Up);
	// Initialize the projection matrix
	projection_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);
	return true;
}

//free up the memory used by the pointers and reset their values to zero
void Game::UnloadContent()
{
	if (solidColourVS_) solidColourVS_->Release();
	if (solidColourPS_) solidColourPS_->Release();
	if (vertexBuffer_) vertexBuffer_->Release();
	if (indexBuffer_) indexBuffer_->Release();
	if (ColourPS_) ColourPS_->Release();
	if (constantBuffer_) constantBuffer_->Release();
	if (inputLayout_) inputLayout_->Release();

	solidColourVS_ = 0;
	solidColourPS_ = 0;
	vertexBuffer_ = 0;
	indexBuffer_ = 0;
	ColourPS_ = 0;
	constantBuffer_ = 0;
	inputLayout_ = 0;

}



void Game::Render()
{
	//gets the state of the keyboard, allowing us to access which keys have been pressed.
	keyboardDevice_->GetDeviceState(sizeof(keyboardKeys_), (LPVOID)&keyboardKeys_);
	//if player presses escape game closes
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}
	//if the player runs out of lives the game closes
	if (livesLeft <= 0)
	{
		PostQuitMessage(0); 
	}
	// time variable used in order to make the cube move.
	static float t = 0.0f;
	static ULONGLONG timeStart = 0;
	ULONGLONG timeCur = GetTickCount64();
	if (timeStart == 0)
		timeStart = timeCur;
	t = (timeCur - timeStart) / 1000.0f;
	xDistance = 13.5f - moveMultiplier * t;
	
	//if the cube moves off of the screen it resets and player loses a life
	if (xDistance <= -13.0f)
	{
		xDistance = 13.5f;
		t = 0;
		timeStart = 0;
		livesLeft -= 1;
		//moveMultiplier = moveMultiplier + 1.0f;
	}
	//when the cube is at a certain point on the screen it will turn green, indicating you need to press space
	if (xDistance <= 3.0f && xDistance >= -3.0f)
	{
		greenTime = true;
	}
	else
	{
		greenTime = false;
	}
	//checks to see if the space key has been pressed
	if (KEYDOWN(prevkeyboardKeys_, DIK_SPACE) && !KEYDOWN(keyboardKeys_, DIK_SPACE))
	{
		//if in the red, takes a life away and resets
		if (greenTime == false)
		{
			livesLeft -= 1;
			xDistance = 13.5f;
			t = 0;
			timeStart = 0;
			OutputDebugString("Player Miss");
		}
		//if in the green, adds to score and resets with the movement multiplier made faster
		if (greenTime == true)
		{
			score += 100;
			xDistance = 13.5f;
			t = 0;
			timeStart = 0;
			moveMultiplier += 1.0f;
			OutputDebugString("Player Hit");
		}

	}
	// Rotate cube around the origin
	rotationMat_ = XMMatrixRotationY(0.0f);
	//moves the cube across the screen each frame
	translationMat_ = XMMatrixTranslation(xDistance, 0.0f, 0.0f);
	world_ = translationMat_ * rotationMat_;

	

	//the location of the two light sources
	XMFLOAT4 vLightDirs[2] =
	{
		XMFLOAT4(-5.0f, 1.0f, -0.577f, 1.0f),
		XMFLOAT4(5.0f, 1.0f, -1.5f, 1.0f),
	};

	//array containing the float4 values for Red, used for both of the lights
	XMFLOAT4 vRedLightColors[2] =
	{
		Red, //red
		Red

		//XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f), //green
		//XMFLOAT4(0.0f, 0.9f, 0.0f, 0.5f)

	};
	//array containing the float4 values for Red, used for both of the lights
	XMFLOAT4 vGreenLightColors[2] =
	{
		Green,
		Green
	};

	//rotate is set to 0 since it is going to stay in place

	XMMATRIX mRotate = XMMatrixRotationY(0.0f);
	XMVECTOR vLightDir = XMLoadFloat4(&vLightDirs[1]);
	vLightDir = XMVector3Transform(vLightDir, mRotate);
	XMStoreFloat4(&vLightDirs[1], vLightDir);

	//
	// Clear the back buffer
	//
	float clearColor[4] = { 0.0f, 0.0f, 0.25f, 1.0f };
	d3dContext_->ClearRenderTargetView(backBufferTarget_, clearColor);
	
	//
	// Clear the depth buffer to 1.0 (max depth)
	//
	d3dContext_->ClearDepthStencilView(depthStencilView_, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//
	// Update matrix variables and lighting variables. A default value of red is set here to avoid a crash
	//
	ConstantBuffer cb1;
	cb1.mWorld = XMMatrixTranspose(world_);
	cb1.mView = XMMatrixTranspose(view_);
	cb1.mProjection = XMMatrixTranspose(projection_);
	cb1.vLightDir[0] = vLightDirs[0];
	cb1.vLightDir[1] = vLightDirs[1];
	cb1.vLightColor[0] = vRedLightColors[0];
	cb1.vLightColor[1] = vRedLightColors[1];
	cb1.vOutputColor = XMFLOAT4(0, 0, 0, 0);
	d3dContext_->UpdateSubresource(constantBuffer_, 0, nullptr, &cb1, 0, 0);
	//sets the lights to be green when they are meant to be
	if (greenTime == true)
	{
		ConstantBuffer cb1;
		cb1.mWorld = XMMatrixTranspose(world_);
		cb1.mView = XMMatrixTranspose(view_);
		cb1.mProjection = XMMatrixTranspose(projection_);
		cb1.vLightDir[0] = vLightDirs[0];
		cb1.vLightDir[1] = vLightDirs[1];
		cb1.vLightColor[0] = vGreenLightColors[0];
		cb1.vLightColor[1] = vGreenLightColors[1];
		cb1.vOutputColor = XMFLOAT4(0, 0, 0, 0);
		d3dContext_->UpdateSubresource(constantBuffer_, 0, nullptr, &cb1, 0, 0);
	}
	else //sets the lights to be red when they are meant to be
	{
		ConstantBuffer cb1;
		cb1.mWorld = XMMatrixTranspose(world_);
		cb1.mView = XMMatrixTranspose(view_);
		cb1.mProjection = XMMatrixTranspose(projection_);
		cb1.vLightDir[0] = vLightDirs[0];
		cb1.vLightDir[1] = vLightDirs[1];
		cb1.vLightColor[0] = vRedLightColors[0];
		cb1.vLightColor[1] = vRedLightColors[1];
		cb1.vOutputColor = XMFLOAT4(0, 0, 0, 0);
		d3dContext_->UpdateSubresource(constantBuffer_, 0, nullptr, &cb1, 0, 0);
	}


	//
	// Render the cube
	//
	d3dContext_->VSSetShader(solidColourVS_, nullptr, 0);
	d3dContext_->VSSetConstantBuffers(0, 1, &constantBuffer_);
	d3dContext_->PSSetShader(ColourPS_, nullptr, 0);
	d3dContext_->PSSetConstantBuffers(0, 1, &constantBuffer_);
	

	d3dContext_->DrawIndexed(36, 0, 0);

	
	// Render each light
	
	for (int m = 0; m < 2; m++)
	{
		//renders the green light
		if (greenTime == true)
		{
			XMMATRIX mLight = XMMatrixTranslationFromVector(5.0f * XMLoadFloat4(&vLightDirs[m]));
			XMMATRIX mLightScale = XMMatrixScaling(0.2f, 0.2f, 0.2f);
			mLight = mLightScale * mLight;

			// Update the world variable to reflect the current light
			cb1.mWorld = XMMatrixTranspose(mLight);
			cb1.vOutputColor = vGreenLightColors[m];
			d3dContext_->UpdateSubresource(constantBuffer_, 0, nullptr, &cb1, 0, 0);

			d3dContext_->PSSetShader(solidColourPS_, nullptr, 0);
			d3dContext_->DrawIndexed(36, 0, 0);
		}
		else //renders the red light
		{
			XMMATRIX mLight = XMMatrixTranslationFromVector(5.0f * XMLoadFloat4(&vLightDirs[m]));
			XMMATRIX mLightScale = XMMatrixScaling(0.2f, 0.2f, 0.2f);
			mLight = mLightScale * mLight;

			// Update the world variable to reflect the current light
			cb1.mWorld = XMMatrixTranspose(mLight);
			cb1.vOutputColor = vRedLightColors[m];
			d3dContext_->UpdateSubresource(constantBuffer_, 0, nullptr, &cb1, 0, 0);

			d3dContext_->PSSetShader(solidColourPS_, nullptr, 0);
			d3dContext_->DrawIndexed(36, 0, 0);
		}
	
	}

	//
	// Present our back buffer to our front buffer
	//
	memcpy(prevkeyboardKeys_, keyboardKeys_, sizeof(keyboardKeys_));
	swapChain_->Present(0, 0);
	
} 