#pragma once
#include "Res.h"
#include <string>
class Texture :
    public Res
{
public:
    Texture();
    ~Texture();
    friend class ResMgr;
public:
    void Load(const wstring& _strFilePath);
    bool LoadFromFile(const wstring& _strFilePath);
    const LONG& GetWidth() const { return (m_bitInfo.bmWidth); }
    const LONG& GetHeight() const { return (m_bitInfo.bmHeight); }
    const HDC& GetDC() const { return m_hDC; }
private:
    HBITMAP m_hBit;
    HDC     m_hDC;
    BITMAP  m_bitInfo;
};

