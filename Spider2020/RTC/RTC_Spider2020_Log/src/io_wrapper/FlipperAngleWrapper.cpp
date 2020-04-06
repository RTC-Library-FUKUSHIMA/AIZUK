/*!
 * @file FlipperAngleWrapper.cpp
 * @brief フリッパーのPWM指令入出力のラッパークラス
 * @author C.Saito
 * @date 2019/04/18
 */
#include "FlipperAngleWrapper.h"

/*!
 * @enum 列挙子
 * データのインデクサ
 */
enum DATA_INDEX_t
{
	DATA_INDEX_FR,		/* 右前方フリッパー		*/
	DATA_INDEX_FL,		/* 左前方フリッパー		*/
	DATA_INDEX_BR,		/* 右後方フリッパー		*/
	DATA_INDEX_BL,		/* 左後方フリッパー		*/
	DATA_INDEX_NUM,		/* データの数			*/
};

FlipperAngleWrapper::FlipperAngleWrapper(RTC::TimedDoubleSeq& Port)
	: m_Port(Port)
{
}

FlipperAngleWrapper::~FlipperAngleWrapper()
{
}

FlipperAngleWrapper& FlipperAngleWrapper::operator=(const FlipperAngleWrapper& rhs)
{
	m_Port = rhs.m_Port;
	return *this;
};

void FlipperAngleWrapper::SetTimestamp(void)
{
	// タイムスタンプを設定する
	setTimestamp(m_Port);
}

void FlipperAngleWrapper::InitData(void)
{
	// フリッパーのPWM指令の入出力の配列数を初期化する
	m_Port.data.length(DATA_INDEX_NUM);

	// フリッパーのPWM指令の入出力の配列値を初期化する
	SetFrontRightAngle(0);
	SetFrontLeftAngle(0);
	SetBackRightAngle(0);
	SetBackLeftAngle(0);
}

uint8_t FlipperAngleWrapper::GetNumber(void)
{
	return DATA_INDEX_NUM;
}

double FlipperAngleWrapper::GetFrontRightAngle(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_FR];
}

void FlipperAngleWrapper::SetFrontRightAngle(const double iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_FR] = iValue;
}

double FlipperAngleWrapper::GetFrontLeftAngle(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_FL];
}

void FlipperAngleWrapper::SetFrontLeftAngle(const double iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_FL] = iValue;
}

double FlipperAngleWrapper::GetBackRightAngle(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_BR];
}

void FlipperAngleWrapper::SetBackRightAngle(const double iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_BR] = iValue;
}

double FlipperAngleWrapper::GetBackLeftAngle(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_BL];
}

void FlipperAngleWrapper::SetBackLeftAngle(const double iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_BL] = iValue;
}
