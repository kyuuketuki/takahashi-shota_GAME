#include "map.h"
#include "scene3D.h"

CMap::CMap()
{
}

CMap::~CMap()
{
}

HRESULT CMap::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// CScene2DÇÃèâä˙âªèàóù
	CScene3D::Init(pos, fSizeX, fSizeY);

	return S_OK;
}

void CMap::Uninit(void)
{
}

void CMap::Update(void)
{
}

void CMap::Draw(void)
{
}

CMap * CMap::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	return nullptr;
}

HRESULT CMap::Load(void)
{
	return E_NOTIMPL;
}

void CMap::Unload(void)
{
}
