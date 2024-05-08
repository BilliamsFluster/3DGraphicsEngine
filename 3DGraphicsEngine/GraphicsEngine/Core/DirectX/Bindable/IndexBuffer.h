#pragma once
#include "Bindable.h"
class IndexBuffer: public Bindable
{
public:
	IndexBuffer(Graphics& gfx, const std::vector<unsigned short>& indicies);
	void Bind(Graphics& gfx) override;
	UINT GetCount() const;
protected:
	UINT count;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
};

