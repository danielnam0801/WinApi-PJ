#pragma once
#include "Object.h"
#include<functional>

class Texture;
class Btn : public Object
{
public:
	Btn(void(*_action)(),wstring _text, wstring _key, const wstring& _textureFilePath);
	virtual ~Btn();

	virtual void Update() override;
	virtual void Render(HDC _dc) override;
private:
	void (*m_Action)();
	wstring m_Text;
	std::shared_ptr<Texture> m_Tex;
;};

