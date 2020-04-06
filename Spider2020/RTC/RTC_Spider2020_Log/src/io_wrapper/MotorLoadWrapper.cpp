#include "MotorLoadWrapper.h"

/*!
 * @enum 列挙子
 * データのインデクサ
 */
enum DATA_INDEX_t
{
	DATA_INDEX_R,		/*!< 右メインモータ		*/
	DATA_INDEX_L,		/*!< 左メインモータ		*/
	DATA_INDEX_FR,		/*!< 右前方サブモータ	*/
	DATA_INDEX_FL,		/*!< 左前方サブモータ	*/
	DATA_INDEX_BR,		/*!< 右後方サブモータ	*/
	DATA_INDEX_BL,		/*!< 左後方サブモータ	*/
	DATA_INDEX_NUM,		/*!< データの数			*/
};

MotorLoadWrapper::MotorLoadWrapper(RTC::TimedDoubleSeq& Port)
	: m_Port(Port)
{
}

MotorLoadWrapper::~MotorLoadWrapper()
{
}

MotorLoadWrapper& MotorLoadWrapper::operator=(const MotorLoadWrapper& rhs)
{
	m_Port = rhs.m_Port;
	return *this;
};

void MotorLoadWrapper::SetTimestamp(void)
{
	// タイムスタンプを設定する
	setTimestamp(m_Port);
}

void MotorLoadWrapper::InitData(void)
{
	// モータの負荷の入出力の配列数を初期化する
	m_Port.data.length(DATA_INDEX_NUM);

	// モータの負荷の入出力の配列値を初期化する
	SetRightMotorLoad(0.0);
	SetLeftMotorLoad(0.0);
	SetFrontRightMotorLoad(0.0);
	SetFrontLeftMotorLoad(0.0);
	SetBackRightMotorLoad(0.0);
	SetBackLeftMotorLoad(0.0);
}

uint8_t MotorLoadWrapper::GetNumber(void)
{
	return DATA_INDEX_NUM;
}

double MotorLoadWrapper::GetRightMotorLoad(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_R];
}

void MotorLoadWrapper::SetRightMotorLoad(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_R] = dValue;
}

double MotorLoadWrapper::GetLeftMotorLoad(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_L];
}

void MotorLoadWrapper::SetLeftMotorLoad(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_L] = dValue;
}

double MotorLoadWrapper::GetFrontRightMotorLoad(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_FR];
}

void MotorLoadWrapper::SetFrontRightMotorLoad(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_FR] = dValue;
}

double MotorLoadWrapper::GetFrontLeftMotorLoad(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_FL];
}

void MotorLoadWrapper::SetFrontLeftMotorLoad(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_FL] = dValue;
}

double MotorLoadWrapper::GetBackRightMotorLoad(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_BR];
}

void MotorLoadWrapper::SetBackRightMotorLoad(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_BR] = dValue;
}

double MotorLoadWrapper::GetBackLeftMotorLoad(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_BL];
}

void MotorLoadWrapper::SetBackLeftMotorLoad(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_BL] = dValue;
}
