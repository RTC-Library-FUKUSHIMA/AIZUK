/*!
 * @file ArmAngularWrapper.cpp
 * @brief Jaco2アームの腕の角度のラッパークラス
 * @author C.Saito
 * @date 2019/12/27
 */
#include "ArmAngularWrapper.h"

/*!
 * @enum 列挙子
 * データのインデクサ
 */
enum DATA_INDEX_t
{
	DATA_INDEX_SHOULDER,	/*!< Shoulder	*/
	DATA_INDEX_ARM,			/*!< Arm		*/
	DATA_INDEX_FOREARM,		/*!< Forearm	*/
	DATA_INDEX_WRIST1,		/*!< Wrist1		*/
	DATA_INDEX_WRIST2,		/*!< Wrist2		*/
	DATA_INDEX_HAND,		/*!< Hand 		*/
	DATA_INDEX_NUM,			/*!< データの数 */
};

ArmAngularWrapper::ArmAngularWrapper(RTC::TimedDoubleSeq& Port)
	: m_Port(Port)
{
}

ArmAngularWrapper::~ArmAngularWrapper()
{
}

ArmAngularWrapper& ArmAngularWrapper::operator=(const ArmAngularWrapper& rhs)
{
	m_Port = rhs.m_Port;
	return *this;
};

void ArmAngularWrapper::SetTimestamp(void)
{
	// タイムスタンプを設定する
	setTimestamp(m_Port);
}

void ArmAngularWrapper::InitData(void)
{
	// Jaco2アームの腕の角度の入出力の配列数を初期化する
	m_Port.data.length(DATA_INDEX_NUM);

	// Jaco2アームの腕の入出力の配列値を初期化する
	SetShoulderAngular(0.0);
	SetArmAngular(0.0);
	SetForearmAngular(0.0);
	SetWrist1Angular(0.0);
	SetWrist2Angular(0.0);
	SetHandAngular(0.0);
}

uint8_t ArmAngularWrapper::GetNumber(void)
{
	return DATA_INDEX_NUM;
}

double ArmAngularWrapper::GetShoulderAngular(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_SHOULDER];
}

void ArmAngularWrapper::SetShoulderAngular(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_SHOULDER] = dValue;
}

double ArmAngularWrapper::GetArmAngular(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_ARM];
}

void ArmAngularWrapper::SetArmAngular(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_ARM] = dValue;
}

double ArmAngularWrapper::GetForearmAngular(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_FOREARM];
}

void ArmAngularWrapper::SetForearmAngular(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_FOREARM] = dValue;
}

double ArmAngularWrapper::GetWrist1Angular(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_WRIST1];
}

void ArmAngularWrapper::SetWrist1Angular(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_WRIST1] = dValue;
}

double ArmAngularWrapper::GetWrist2Angular(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_WRIST2];
}

void ArmAngularWrapper::SetWrist2Angular(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_WRIST2] = dValue;
}

double ArmAngularWrapper::GetHandAngular(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_HAND];
}

void ArmAngularWrapper::SetHandAngular(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_HAND] = dValue;
}
