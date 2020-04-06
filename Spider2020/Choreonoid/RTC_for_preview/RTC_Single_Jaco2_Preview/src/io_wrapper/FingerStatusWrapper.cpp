/*!
 * @file FingerStatusWrapper.cpp
 * @brief Jaco2アームの指の開閉具合の変位速度入出力のラッパークラス
 * @author C.Saito
 * @date 2019/12/27
 */
#include "FingerStatusWrapper.h"

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

FingerStatusWrapper::FingerStatusWrapper(RTC::TimedLongSeq& Port)
	: m_Port(Port)
{
}

FingerStatusWrapper::~FingerStatusWrapper()
{
}

FingerStatusWrapper& FingerStatusWrapper::operator=(const FingerStatusWrapper& rhs)
{
	m_Port = rhs.m_Port;
	return *this;
};

void FingerStatusWrapper::SetTimestamp(void)
{
	// タイムスタンプを設定する
	setTimestamp(m_Port);
}

void FingerStatusWrapper::InitData(void)
{
	// Jaco2アームの指の開閉具合の入出力の配列数を初期化する
	m_Port.data.length(DATA_INDEX_NUM);

	// Jaco2アームの指の開閉具合の入出力の配列値を初期化する
	SetThumbStatus(0);
	SetIndexFingerStatus(0);
	SetMiddleFingerStatus(0);
}

uint8_t FingerStatusWrapper::GetNumber(void)
{
	return DATA_INDEX_NUM;
}

int32_t FingerStatusWrapper::GetThumbStatus(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_THUMB];
}

void FingerStatusWrapper::SetThumbStatus(const int32_t iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_THUMB] = iValue;
}

int32_t FingerStatusWrapper::GetIndexFingerStatus(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_INDEX_FINGER];
}

void FingerStatusWrapper::SetIndexFingerStatus(const int32_t iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_INDEX_FINGER] = iValue;
}

int32_t FingerStatusWrapper::GetMiddleFingerStatus(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_MIDDLE_FINGER];
}

void FingerStatusWrapper::SetMiddleFingerStatus(const int32_t iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_MIDDLE_FINGER] = iValue;
}
