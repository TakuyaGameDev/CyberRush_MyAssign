#pragma once
#include "Geometory.h"
#include "ActorType.h"

constexpr int size = 100;

// �G��AI�����̂��߂̺ײ�ް�׽
// �G���m���Ԃ����AI�N��
class Enemy;

class AICollider
{
public:
	AICollider();
	~AICollider();
	// �߼޼�ݱ����ް�
	void SetPos(const Vector2I& pos,const int& z);
	// �ײ�ް�ޯ���`��
	void Draw(void);

	// �߼޼�ݎ擾�֐�
	const Vector2I& GetPos(void)
	{
		return pos_;
	}
	const int& GetZPos(void)
	{
		return z_;
	}

private:
	Vector2I pos_;
	int z_;

};

