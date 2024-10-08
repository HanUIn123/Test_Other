#include "FontManager.h"

IMPLEMENT_SINGLETON(CFontManager)

CFontManager::CFontManager()
{
}

CFontManager::~CFontManager()
{
    Free();
}

HRESULT CFontManager::Ready_Font(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* pFontTag, const _tchar* pFontType, const _uint& iWidth, const _uint& iHeight, const _uint& iWeight)
{
    CFont* pFont = Find_Font(pFontTag);

    if (nullptr != pFont)
        return E_FAIL;

    pFont = CFont::Create(pGraphicDev, pFontType, iWidth, iHeight, iWeight);

    NULL_CHECK_RETURN(pFont, E_FAIL);

    m_mapFont.insert({ pFontTag, pFont });

    return S_OK;
}

void CFontManager::Render_Font(const _tchar* pFontTag, const _tchar* pString, const _vec2* pPos, D3DXCOLOR Color)
{
    CFont* pFont = Find_Font(pFontTag);

    NULL_CHECK(pFont);

    pFont->Render_Font(pString, pPos, Color);
}

CFont* CFontManager::Find_Font(const _tchar* pFontTag)
{
    auto iter = find_if(m_mapFont.begin(), m_mapFont.end(), CTag_Finder(pFontTag));

    if (iter == m_mapFont.end())
        return nullptr;

    return iter->second;
}

void CFontManager::Free()
{
    for_each(m_mapFont.begin(), m_mapFont.end(), CDeleteMap());
    m_mapFont.clear();
}
