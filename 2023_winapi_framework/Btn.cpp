#include "pch.h"
#include "Btn.h"
#include "ResMgr.h"
#include"KeyMgr.h"
#include "Texture.h"



Btn::Btn(void(*_action)(), wstring _text)
{
    m_Action = _action;
    m_Text = _text; 
}
Btn::~Btn()
{

}
void Btn::Update()
{

    if (KEY_UP(KEY_TYPE::LBUTTON))
    {
        Vec2 vPos = GetPos();
        Vec2 vScale = GetScale();
        POINT _pMousePoint;
        GetCursorPos(&_pMousePoint);

        RECT rt = { vPos.x - vScale.x / 2, vPos.y - vScale.y / 2 , vPos.x + vScale.x / 2, vPos.y + vScale.y / 2 };

        if (PtInRect(&rt, KeyMgr::GetInst()->GetMousePos()))
        {
            m_Action();
        }
    }
}
void Btn::Render(HDC _hdc)
{
    Vec2 vPos = GetPos();
    Vec2 vScale = GetScale();
    RECT rt = { vPos.x - vScale.x / 2, vPos.y - vScale.y / 2 , vPos.x + vScale.x / 2, vPos.y + vScale.y / 2 };

    

    RECT_RENDER(vPos.x, vPos.y, vScale.x, vScale.y, _hdc);

    

    DrawText(_hdc, m_Text.c_str(), -1, &rt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}