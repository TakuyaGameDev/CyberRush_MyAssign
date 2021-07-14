#pragma once
#include <memory>
#include <vector>
#include <functional>
#include "Actor.h"

class ControlledPlayer;
class BulletBase;
class AIBase;
class AICollider;

// �G��AI�ð�
enum class AIState
{
	// ����
	Walk,
	// ��ڲ԰�̔w��ɑ��蔲����
	Run,
	// �U��
	Attack,
	// ��ڲ԰��Z���ƍ��킹��
	ZArrange,
	Max
};

class Enemy :
	public Actor
{
public:
	Enemy(std::vector<std::shared_ptr<ControlledPlayer>>& player);
	~Enemy();

	virtual void Action(void);
	virtual void UpDate(void) = 0;
	virtual void Draw_(void) = 0;
	virtual bool Initialize(void);
	virtual void SetPos(const Vector2I& pos,int z);

	// ��ڲ԰�̏e�e�Ƃ̓����蔻��
	virtual bool CheckHitPlayerBullet(const std::vector<std::shared_ptr<BulletBase>>& playerBullets);
	// ��ڲ԰�Ɏ����̒e�������������̓����蔻��
	virtual bool CheckHitMyBulletToPlayer(std::vector<std::shared_ptr<BulletBase>>& bullets);
	// �����Ɉ�ԋ߂��v���C���[���������v�Z���Ă���̎擾
	virtual std::shared_ptr<ControlledPlayer> SearchNearestPlayer(void);
	// �����Ɉ�ԋ߂��v���C���[���v�Z�Ȃ��Ŏ擾
	// ���������v�Z���ׂ����������Ȃ�����
	virtual std::shared_ptr<ControlledPlayer> GetNearestPlayer(void);
	// AI�ײ�ް�擾�֐�
	virtual const std::unique_ptr<AICollider>& GetAICollider(void);
	// �G1�̂�AI���ю擾�֐�
	virtual const std::shared_ptr<AIBase>& GetAISystem(void)
	{
		return aiSystem_;
	}
	// ���g�̌ŗL���ʔԍ��̎擾
	virtual const int& GetId(void)
	{
		return id_;
	}

	// AIstate�擾�֐�
	virtual AIState& GetAIState(void)
	{
		return AIstate_;
	}

	// ���Ԃ�AI�ײ�ް�Ɠ������������׸ގ擾
	virtual bool& GetisHitAICollider(void)
	{
		return isHitAICollider_;
	}

	// �e�e�̒ǉ�
	void AddBullet(std::vector<std::shared_ptr<BulletBase>>& bullets);

	void SetisBehindPlayer(bool& flg);
	const bool& GetisBehindPlayer(void)
	{
		return isBehindPlayer_;
	}

	bool& GetFriendlyFireFlag(void)
	{
		return friendlyFireFlag_;
	}

	virtual void AddMuzzleFlashAnimationCount(float cnt)
	{
		muzzleFlashAnimationCount_ += cnt;
	}

	float& GetmuzzleFlashAnimationCount(void)
	{
		return muzzleFlashAnimationCount_;
	}
private:

protected:
	// �G�̌ŗL���ʔԍ�(����������1���Z)
	static int enemyNo_;
	// �������g�̌ŗL���ʔԍ�
	int id_;
	// ���ߕʂ���Ұ�ޗ�
	// �G�F��HP�𓯂�100�ɂ��Ă����āA��Ұ�ޗ��ŐH�炤��Ұ�ނ̊������v�Z����
	float damageRate_;
	// �e�G�̒e�̍U����
	float attackRate_;
	// AI�ðĕϐ�
	AIState AIstate_;
	// ���Ԃ�AI�ײ�ް�ɓ������������׸�
	bool isHitAICollider_;
	// ��ڲ԰�̔w��ɂ����׸�
	bool isBehindPlayer_;

	// �����������ɓ��������׸�(Exoskeleton�݂̂ɑ΂��Ă����g�p���Ȃ�)
	bool friendlyFireFlag_;

	std::vector<std::shared_ptr<ControlledPlayer>>& player_;
	std::shared_ptr<ControlledPlayer> nearestPlayer_;

	std::unique_ptr<AICollider> aiCollider_;
	// �G�����߂ɉ�����AI����
	std::shared_ptr<AIBase> aiSystem_;
	// muzzleFlash���߼޼��
	Vector2I muzzleFlashPos_;
	// �e������o��muzzleFlash�̱�Ұ��ݶ���
	float muzzleFlashAnimationCount_;

	std::string name_;
};

