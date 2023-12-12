#pragma once
class Camera;
class CameraMgr
{
	SINGLE(CameraMgr);
private:
    float m_fTime = 2.f; // Ÿ�� ���󰡴µ� �ɸ��� �ð�
    float m_fSpeed = 0.f; // Ÿ�� ���󰡴� �ӵ�
    float m_fAccTime = 0.f; // �����ð�
public:
    void SetLook(Vec2 _vLoot)
    {
        m_vLootAt = _vLoot;
        float fMoveDist = (m_vLootAt - m_vPrevLookAt).Length();
        m_fSpeed = fMoveDist / m_fTime; // �̵��ӵ�
        m_fAccTime = 0.f;
    }
    void SetTarget(Object* _pTargetObj)
    {
        m_pTargetObj = _pTargetObj;
    }
    const Vec2& GetLocalPos(Vec2 _vObjpos) const
    {
        return _vObjpos - m_vDiff;
    }
    const Vec2& GetRealPos(Vec2 _vRenderpos) const
    {
        return _vRenderpos + m_vDiff;
    }
public:
    void Update();
private:
    Vec2 m_vLootAt; // ī�޶� ���� ��ġ
    Vec2 m_vPrevLookAt; // ī�޶� ���� ���� ������ ��ġ
    Vec2 m_vCurLookAt; // Look�� PrevLook ���� ��� �����ϴ���
    // �������ִ� ���� ��� LookAt

    Object* m_pTargetObj; // ī�޶� Ÿ�� ������Ʈ
    Vec2 m_vDiff; // �ػ� �߽���ġ�� ī�޶� Lootat���� ���̰�
private:
    void CalDiff(); // ���� ���
};