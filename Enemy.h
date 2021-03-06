#pragma once
#include <memory>
#include <vector>
#include <functional>
#include "Actor.h"

class ControlledPlayer;
class BulletBase;
class AIBase;
class AICollider;

// 敵のAIｽﾃｰﾄ
enum class AIState
{
	// 歩く
	Walk,
	// ﾌﾟﾚｲﾔｰの背後に走り抜ける
	Run,
	// 攻撃
	Attack,
	// ﾌﾟﾚｲﾔｰのZ軸と合わせる
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

	// ﾌﾟﾚｲﾔｰの銃弾との当たり判定
	virtual bool CheckHitPlayerBullet(const std::vector<std::shared_ptr<BulletBase>>& playerBullets);
	// ﾌﾟﾚｲﾔｰに自分の弾が当たったかの当たり判定
	virtual bool CheckHitMyBulletToPlayer(std::vector<std::shared_ptr<BulletBase>>& bullets);
	// 自分に一番近いプレイヤーを距離を計算してからの取得
	virtual std::shared_ptr<ControlledPlayer> SearchNearestPlayer(void);
	// 自分に一番近いプレイヤーを計算なしで取得
	// いちいち計算負荷をかけたくないため
	virtual std::shared_ptr<ControlledPlayer> GetNearestPlayer(void);
	// AIｺﾗｲﾀﾞｰ取得関数
	virtual const std::unique_ptr<AICollider>& GetAICollider(void);
	// 敵1体のAIｼｽﾃﾑ取得関数
	virtual const std::shared_ptr<AIBase>& GetAISystem(void)
	{
		return aiSystem_;
	}
	// 自身の固有識別番号の取得
	virtual const int& GetId(void)
	{
		return id_;
	}

	// AIstate取得関数
	virtual AIState& GetAIState(void)
	{
		return AIstate_;
	}

	// 仲間のAIｺﾗｲﾀﾞｰと当たったかのﾌﾗｸﾞ取得
	virtual bool& GetisHitAICollider(void)
	{
		return isHitAICollider_;
	}

	// 銃弾の追加
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
	// 敵の固有識別番号(生成されると1加算)
	static int enemyNo_;
	// 自分自身の固有識別番号
	int id_;
	// ﾀｲﾌﾟ別のﾀﾞﾒｰｼﾞ率
	// 敵皆はHPを同じ100にしておいて、ﾀﾞﾒｰｼﾞ率で食らうﾀﾞﾒｰｼﾞの割合を計算する
	float damageRate_;
	// 各敵の弾の攻撃力
	float attackRate_;
	// AIｽﾃｰﾄ変数
	AIState AIstate_;
	// 仲間のAIｺﾗｲﾀﾞｰに当たったかのﾌﾗｸﾞ
	bool isHitAICollider_;
	// ﾌﾟﾚｲﾔｰの背後にいるﾌﾗｸﾞ
	bool isBehindPlayer_;

	// 自分が味方に当たったﾌﾗｸﾞ(Exoskeletonのみに対してしか使用しない)
	bool friendlyFireFlag_;

	std::vector<std::shared_ptr<ControlledPlayer>>& player_;
	std::shared_ptr<ControlledPlayer> nearestPlayer_;

	std::unique_ptr<AICollider> aiCollider_;
	// 敵のﾀｲﾌﾟに応じたAIｼｽﾃﾑ
	std::shared_ptr<AIBase> aiSystem_;
	// muzzleFlashのﾎﾟｼﾞｼｮﾝ
	Vector2I muzzleFlashPos_;
	// 銃口から出るmuzzleFlashのｱﾆﾒｰｼｮﾝｶｳﾝﾄ
	float muzzleFlashAnimationCount_;

	std::string name_;
};

