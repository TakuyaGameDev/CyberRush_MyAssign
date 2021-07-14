#include <DxLib.h>
#include "SoundManager.h"
#include "AIBase.h"
#include "Enemy.h"
#include "PodAI.h"
#include "AICollider.h"
#include "ControlledPlayer.h"
#include "Floor.h"

AIBase::AIBase(Enemy& enemy):
	me_(enemy)
{
	createBulletFlag_ = false;
}

AIBase::~AIBase()
{
}

void AIBase::AIAction(std::list<std::shared_ptr<Enemy>>& enemies)
{
	// ������������ڲ԰�̍��ɂ��邩���׸�
	auto playerIsLeft = me_.SearchNearestPlayer()->GetisTurnFlag();
	// ��ڲ԰���߼޼�ݎ擾
	auto playerPos = me_.SearchNearestPlayer()->GetPos();
	// ��ڲ԰�����ɂ��邩���׸�(���݂����true���Ȃ����false)
	auto isBehind = false;
	// ��ڲ԰�����ɑ��݂�
	if (playerIsLeft)
	{
		// ��ڲ԰�������̌��ɑ��݂����
		if (me_.GetPos().x > playerPos.x)
		{
			// �׸ނ�true��
			isBehind = true;
		}
	}
	// ��ڲ԰���E�ɑ��݂�
	else
	{
		// ��ڲ԰�������̌��ɑ��݂����
		if (me_.GetPos().x < playerPos.x)
		{
			// �׸ނ�true��
			isBehind = true;
		}
	}
	// ��Ұ�ނ����������
	if (me_.GetOnDamaged())
	{
		// HP��0�ȉ��ɂȂ��
		if (me_.GetHp() <= 0)
		{
			// ��������炷
			lpSound.Play("explosion",DX_PLAYTYPE_BACK);
		}
	}
	// �G���m������������
	if (me_.GetFriendlyFireFlag())
	{
		// ��������炷
		lpSound.Play("explosion", DX_PLAYTYPE_BACK);
	}

	// �G��̨���ވړ�����----------------------------
	// x���W�̐���
	if (me_.GetPos().x <= 50)
	{
		me_.GetPos().x = 50;
	}
	if (me_.GetPos().x >= floorX - 40)
	{
		me_.GetPos().x = floorX - 40;
	}
	// z���W�̐���
	if (me_.GetZPos() <= -floorZ)
	{
		me_.GetZPos() = -floorZ;
	}
	// �G���޽�̏ꍇ��z���ړ�����
	if (me_.GetType() == ActorType::Bigboy)
	{
		if (me_.GetZPos() >= -120)
		{
			me_.GetZPos() = -120;
		}
	}
	else
	{
		if (me_.GetZPos() >= 0)
		{
			me_.GetZPos() = 0;
		}
	}
	// --------------------------------------------

	// �G����ڲ԰�̔w��ɂ��邩���Ȃ����׸ނ��
	me_.SetisBehindPlayer(isBehind);
	// �G�̍s���X�V
	Update(enemies);
}

bool AIBase::IsHitFriends(std::list<std::shared_ptr<Enemy>>& enemies)
{
	// ��ڲ԰�̌��ɓG�����݂��邩���׸�
	auto isBehindPlayer = false;
	// ��ڲ԰�̌��ɓG�����݂��邩������
	for (auto e1 : enemies)
	{
		isBehindPlayer = e1->GetisBehindPlayer();
	}
	// �G�̎������g��AICollider�߼޼��(X,Y��)
	auto myColPos = me_.GetAICollider()->GetPos();
	// �G�̎������g��AICollider�߼޼��(Z���F���s)
	auto myColPosZ = me_.GetAICollider()->GetZPos();
	// ��ڲ԰�̌��ɉ������Ȃ����
	if (!isBehindPlayer)
	{
		for (auto e2 : enemies)
		{
			if (me_.GetId() != e2->GetId())
			{
				if (!e2->GetisHitAICollider() &&
					!me_.GetisHitAICollider())
				{
					// �����Ɠ�������������AICollider���߼޼��
					auto otherColPos
						= Vector2I(e2->GetAICollider()->GetPos().x,
							e2->GetAICollider()->GetPos().y +
							(e2->GetAICollider()->GetZPos() / 2));

					// �����Ǝ�����AI Collider���������Ă�����AI�N��
					if (abs(otherColPos.x - myColPos.x) <= (size / 2) &&
						abs(otherColPos.y - myColPos.y) <= (size / 2))
					{
						// �����ł͂Ȃ�������AICollider�̓����蔻���true��
						e2->GetisHitAICollider() = true;
						// ������AICollider�̓����蔻���true��
						me_.GetisHitAICollider() = true;
						return true;
					}
					else
					{
						// �������Ă��Ȃ���
						return false;
					}
				}
			}
		}
	}
	return false;
}
