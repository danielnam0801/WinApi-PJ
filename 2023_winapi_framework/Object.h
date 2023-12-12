#pragma once
class Collider;
class Animator;
class Rigidbody;
class Gravity;
class Texture;
class Object
{
public:
	Object();
	virtual ~Object();
//public:	// 크기, 위치
	//POINT m_ptPos;
	//POINT m_ptScale;
public:
	virtual void Update();
	virtual void FinalUpdate() final;
	virtual void Render(HDC _dc);
	virtual void EnterCollision(Collider* _pOther);
	virtual void ExitCollision(Collider* _pOther);
	virtual void StayCollision(Collider* _pOther);
	void Component_Render(HDC _dc);
public:
	void SetTexture(std::shared_ptr<Texture> _Tex) { m_tex = _Tex; }
	void SetTextureRect(RECT _rect) { m_texRect = _rect; }
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	const Vec2& GetPos() const { return m_vPos; }
	const Vec2& GetScale() const { return m_vScale; }
	const RECT& GetTextureRect() const { return m_texRect; }
	Collider* GetCollider() const 
	{ 
		return m_pCollider;
	}
	Animator* GetAnimator()
	{
		return m_pAnimator;
	}
	Rigidbody* GetRigidbody()
	{
		return m_pRigidbody;
	}
	Gravity* GetGravity()
	{
		return m_pGravity;
	}
	const wstring& GetName() const { return m_strName; }
	void SetName(wstring _name) { m_strName = _name; }
	void SetIsClicked(bool value) { m_IsClicked = value; }
	bool GetIsDead() const { return !m_IsAlive; }
	bool GetIsClicked() const { return !m_IsClicked; }
	bool GetIsCanRender() const { return m_iscanRender; }
private:
	void SetDead() { m_IsAlive = false; }
	friend class EventMgr;
public:
	void CreateCollider();
	void CreateRigidbody();
	void CreateAnimator();
	void CreateGravity();
protected:
	RECT m_texRect;
	std::shared_ptr<Texture> m_tex;
	Vec2 m_vPos; // 위치
	Vec2 m_vScale; // 크기
	wstring m_strName; // 이름.
	bool m_IsAlive;
	bool m_IsClicked;
	bool m_iscanRender;
	Collider* m_pCollider;
	Rigidbody* m_pRigidbody;
	Animator* m_pAnimator;
	Gravity* m_pGravity;
};

