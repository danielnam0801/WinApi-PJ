#pragma once
#include "Object.h"
#include "Texture.h"
#include<functional>
class Btn : public Object
{
public:
	Btn(void(*_action)(),wstring _text,Texture _tex);
	virtual ~Btn();

	virtual void Update() override;
	virtual void Render(HDC _dc) override;
private:
	void (*m_Action)();
	wstring m_Text;
	Texture m_Tex;
;};

