#include "ArmCurrentWrapper.h"

/*!
 * @enum 列挙子
 * データのインデクサ
 */
enum DATA_INDEX_t
{
	DATA_INDEX_SHOULDER,		/*!< Shoulde	r	*/
	DATA_INDEX_ARM,				/*!< Arm			*/
	DATA_INDEX_FOREARM,			/*!< Forearm		*/
	DATA_INDEX_WRIST1,			/*!< Wrist1			*/
	DATA_INDEX_WRIST2,			/*!< Wrist2			*/
	DATA_INDEX_HAND,			/*!< Hand			*/
	DATA_INDEX_THUMB,			/*!< Thumb			*/
	DATA_INDEX_INDEX_FINGER,	/*!< Index Finger	*/
	DATA_INDEX_MIDDLE_FINGER,	/*!< Middle Finger	*/
	DATA_INDEX_NUM,				/*!< データの数		*/
};

ArmCurrentWrapper::ArmCurrentWrapper(RTC::TimedDoubleSeq& Port)
	: m_Port(Port)
{
}

ArmCurrentWrapper::~ArmCurrentWrapper()
{
}

ArmCurrentWrapper& ArmCurrentWrapper::operator=(const ArmCurrentWrapper& rhs)
{
	m_Port = rhs.m_Port;
	return *this;
};

void ArmCurrentWrapper::SetTimestamp(void)
{
	// タイムスタンプを設定する
	setTimestamp(m_Port);
}

void ArmCurrentWrapper::InitData(void)
{
	// モータ負荷の入出力の配列数を初期化する
	m_Port.data.length(DATA_INDEX_NUM);

	// モータ負荷の入出力の配列値を初期化する
	SetShoulderCurrent(0.0);
	SetArmCurrent(0.0);
	SetForearmCurrent(0.0);
	SetWrist1Current(0.0);
	SetWrist2Current(0.0);
	SetHandCurrent(0.0);
	SetThumbCurrent(0.0);
	SetIndexFingerCurrent(0.0);
	SetMiddleFingerCurrent(0.0);
}

uint8_t ArmCurrentWrapper::GetNumber(void)
{
	return DATA_INDEX_NUM;
}

double ArmCurrentWrapper::GetShoulderCurrent(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_SHOULDER];
}

void ArmCurrentWrapper::SetShoulderCurrent(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_SHOULDER] = dValue;
}

double ArmCurrentWrapper::GetArmCurrent(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_ARM];
}

void ArmCurrentWrapper::SetArmCurrent(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_ARM] = dValue;
}

double ArmCurrentWrapper::GetForearmCurrent(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_FOREARM];
}

void ArmCurrentWrapper::SetForearmCurrent(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_FOREARM] = dValue;
}

double ArmCurrentWrapper::GetWrist1Current(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_WRIST1];
}

void ArmCurrentWrapper::SetWrist1Current(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_WRIST1] = dValue;
}

double ArmCurrentWrapper::GetWrist2Current(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_WRIST2];
}

void ArmCurrentWrapper::SetWrist2Current(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_WRIST2] = dValue;
}

double ArmCurrentWrapper::GetHandCurrent(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_HAND];
}

void ArmCurrentWrapper::SetHandCurrent(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_HAND] = dValue;
}

double ArmCurrentWrapper::GetThumbCurrent(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_THUMB];
}

void ArmCurrentWrapper::SetThumbCurrent(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_THUMB] = dValue;
}

double ArmCurrentWrapper::GetIndexFingerCurrent(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_INDEX_FINGER];
}

void ArmCurrentWrapper::SetIndexFingerCurrent(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_INDEX_FINGER] = dValue;
}

double ArmCurrentWrapper::GetMiddleFingerCurrent(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_MIDDLE_FINGER];
}

void ArmCurrentWrapper::SetMiddleFingerCurrent(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_MIDDLE_FINGER] = dValue;
}
