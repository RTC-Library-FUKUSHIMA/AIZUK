/*!
 * @file FingerDeltaWrapper.cpp
 * @brief Jaco2アームの指の開閉具合の変位速度入出力のラッパークラス
 * @author C.Saito
 * @date 2019/04/18
 */
#include "FingerDeltaWrapper.h"

/*!
 * @enum 列挙子
 * データのインデクサ
 */
enum DATA_INDEX_t
{
	DATA_INDEX_THUMB,				/*!< 親指		*/
	DATA_INDEX_INDEX_FINGER,		/*!< 差指		*/
	DATA_INDEX_MIDDLE_FINGER,		/*!< 中指		*/
	DATA_INDEX_NUM,					/*!< データの数	*/
};

FingerDeltaWrapper::FingerDeltaWrapper(RTC::TimedLongSeq& Port)
	: m_Port(Port)
{
}

FingerDeltaWrapper::~FingerDeltaWrapper()
{
}

FingerDeltaWrapper& FingerDeltaWrapper::operator=(const FingerDeltaWrapper& rhs)
{
	m_Port = rhs.m_Port;
	return *this;
};

void FingerDeltaWrapper::SetTimestamp(void)
{
	// タイムスタンプを設定する
	setTimestamp(m_Port);
}

void FingerDeltaWrapper::InitData(void)
{
	int i = 0;

	// フリッパーのPWM指令の入出力の配列数を初期化する
	m_Port.data.length(DATA_INDEX_NUM);

	// フリッパーのPWM指令の入出力の配列値を初期化する
	for(i = 0; i < static_cast<int>(m_Port.data.length()); i++)
	{
		m_Port.data[i] = 0;
	}
	SetThumbDelta(0);
	SetIndexFingerDelta(0);
	SetMiddleFingerDelta(0);
}

uint8_t FingerDeltaWrapper::GetNumber(void)
{
	return DATA_INDEX_NUM;
}

int32_t FingerDeltaWrapper::GetThumbDelta(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_THUMB];
}

void FingerDeltaWrapper::SetThumbDelta(const int32_t iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_THUMB] = iValue;
}

int32_t FingerDeltaWrapper::GetIndexFingerDelta(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_INDEX_FINGER];
}

void FingerDeltaWrapper::SetIndexFingerDelta(const int32_t iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_INDEX_FINGER] = iValue;
}

int32_t FingerDeltaWrapper::GetMiddleFingerDelta(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_MIDDLE_FINGER];
}

void FingerDeltaWrapper::SetMiddleFingerDelta(const int32_t iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_MIDDLE_FINGER] = iValue;
}
