#include "Motor.h"
#include <math.h>

Motor::Motor()
	: m_iDirection(1)
	, m_iPulseNumber(1)
	, m_dRadius(1.0)
	, m_dGearRatio(1.0)
	, m_dLoadGain(1.0)
	, m_dLoadBase(1.0)
	, m_iPulseCount(0)
	, m_dLoad(0.0)
	, m_dAngle(0.0)
	, m_dAngularVelocity(0.0)
	, m_dAngularAcceleration(0.0)
	, m_dVelocity(0.0)
	, m_dAcceleration(0.0)
{
}

Motor::~Motor()
{
}

void Motor::InitData(void)
{
	// モータの回転方向を初期化する
	SetDirection(1);

	// モータのパルス数を初期化する
	SetPulseNumber(1);

	// 車輪の半径を初期化する
	SetRadius(1.0);

	// モータと車輪の減速比を初期化する
	SetGearRatio(1.0);

	// 電圧値をモータ負荷に変換するゲインを初期化する
	SetLoadGain(1.0);

	// モータ負荷の基準電圧を初期化する
	SetLoadBase(1.0);

	// 車輪の角度を初期化する
	SetAngle(0.0);

	// モータのフィードバックデータを初期化する
	InitFeedbackData();
}

void Motor::InitFeedbackData(void)
{
	// モータのパルスカウントを初期化する
	SetPulseCount(0);

	// モータの負荷を初期化する
	SetLoad(0.0);

	// 車輪の角速度を初期化する
	SetAngularVelocity(0.0);

	// 車輪の角加速度を初期化する
	SetAngularAcceleration(0.0);

	// 車輪の速度を初期化する
	SetVelocity(0.0);

	// 車輪の加速度を初期化する
	SetAcceleration(0.0);
}

void Motor::CalcFeedback(double dFrequency, int32_t iPulseCount, double dVelocityMD, double dLoad)
{
	int iOldPulseCount = 0;
	int iDiffPulseCount = 0;
	double dDiffAngle = 0;
	double dOldAngularVelocity = 0.0;

	// 前回のパルスカウントを退避する
	iOldPulseCount = GetPulseCount();

	// 前回の車輪の角加速度を退避する
	dOldAngularVelocity = GetAngularVelocity();

	// パルスカウントを更新する
	SetPulseCount(iPulseCount);

	// モータの負荷を更新する(モータの回転方向に合わせて正負を反転する)
	SetLoad(((dLoad - GetLoadBase())*GetLoadGain())*GetDirection());

	// パルスカウントの差分を求める(65535 - 40000 >= 5000[パルス/周期] * RTCの実行が4周期遅れるぐらいまで想定)
	iDiffPulseCount = GetPulseCount() - iOldPulseCount;
	if(iDiffPulseCount <= -40000)
	{
		iDiffPulseCount = GetPulseCount() + 65535 + 1 - iOldPulseCount;
	}
	else if(40000 <= iDiffPulseCount)
	{
		iDiffPulseCount = GetPulseCount() - 65535 - 1 - iOldPulseCount;
	}

	// 車輪の角度の差分を求める(モータの回転方向に合わせて正負を反転する)
	dDiffAngle = (((2.0*M_PI)/(GetPulseNumber()*GetGearRatio()))*iDiffPulseCount)*GetDirection();

	// 車輪の角度を更新する
	SetAngle(GetAngle() + dDiffAngle);

	// 車輪の角速度を更新する
	SetAngularVelocity(dDiffAngle/dFrequency);

	// 車輪の角加速度を更新する
	SetAngularAcceleration((GetAngularVelocity() - dOldAngularVelocity)/dFrequency);

	// 車輪の速度を更新する
	SetVelocity(GetAngularVelocity()*GetRadius());

	// 車輪の加速度を更新する
	SetAcceleration(GetAngularAcceleration()*GetRadius());
}

int8_t Motor::GetDirection(void)
{
	return m_iDirection;
}

void Motor::SetDirection(int8_t iValue)
{
	m_iDirection = iValue;
}

int32_t Motor::GetPulseNumber(void)
{
	return m_iPulseNumber;
}

void Motor::SetPulseNumber(int32_t iValue)
{
	m_iPulseNumber = iValue;
}

double Motor::GetRadius(void)
{
	return m_dRadius;
}

void Motor::SetRadius(double dValue)
{
	m_dRadius = dValue;
}

double Motor::GetGearRatio(void)
{
	return m_dGearRatio;
}

void Motor::SetGearRatio(double dValue)
{
	m_dGearRatio = dValue;
}

double Motor::GetLoadGain(void)
{
	return m_dLoadGain;
}

void Motor::SetLoadGain(double dValue)
{
	m_dLoadGain = dValue;
}

double Motor::GetLoadBase(void)
{
	return m_dLoadBase;
}

void Motor::SetLoadBase(double dValue)
{
	m_dLoadBase = dValue;
}

int32_t Motor::GetPulseCount(void)
{
	return m_iPulseCount;
}

void Motor::SetPulseCount(int32_t iValue)
{
	m_iPulseCount = iValue;
}

double Motor::GetLoad(void)
{
	return m_dLoad;
}

void Motor::SetLoad(double dValue)
{
	m_dLoad = dValue;
}

double Motor::GetAngle(void)
{
	return m_dAngle;
}

void Motor::SetAngle(double dValue)
{
	m_dAngle = dValue;
}

double Motor::GetAngularVelocity(void)
{
	return m_dAngularVelocity;
}

void Motor::SetAngularVelocity(double dValue)
{
	m_dAngularVelocity = dValue;
}

double Motor::GetAngularAcceleration(void)
{
	return m_dAngularAcceleration;
}

void Motor::SetAngularAcceleration(double dValue)
{
	m_dAngularAcceleration = dValue;
}

double Motor::GetVelocity(void)
{
	return m_dVelocity;
}

void Motor::SetVelocity(double dValue)
{
	m_dVelocity = dValue;
}

double Motor::GetAcceleration(void)
{
	return m_dAcceleration;
}

void Motor::SetAcceleration(double dValue)
{
	m_dAcceleration = dValue;
}
