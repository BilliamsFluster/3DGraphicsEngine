#pragma once
#include "Core/DirectX/Graphics.h"
class Bindable
{
public: 
	virtual void Bind(Graphics& gfx) = 0;
	virtual ~Bindable() = default;
protected:
	static ID3D11DeviceContext* GetContext(Graphics& gfx) noexcept;
	static ID3D11Device* GetDevice(Graphics& gfx) noexcept;
	static DxgiInfoManager& GetInfoManager(Graphics& gfx) noexcept;
};

