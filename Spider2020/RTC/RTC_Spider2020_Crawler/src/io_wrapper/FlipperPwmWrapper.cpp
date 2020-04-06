/*!
 * @file FlipperPwmWrapper.cpp
 * @brief フリッパーのPWM指令入出力のラッパークラス
 * @author C.Saito
 * @date 2019/04/18
 */
#include "FlipperPwmWrapper.h"

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

FlipperPwmWrapper::FlipperPwmWrapper(RTC::TimedLongSeq& Port)
	: m_Port(Port)
{
}

FlipperPwmWrapper::~FlipperPwmWrapper()
{
}

FlipperPwmWrapper& FlipperPwmWrapper::operator=(const FlipperPwmWrapper& rhs)
{
	m_Port = rhs.m_Port;
	return *this;
};

void FlipperPwmWrapper::SetTimestamp(void)
{
	// タイムスタンプを設定する
	setTimestamp(m_Port);
}

void FlipperPwmWrapper::InitData(void)
{
	// フリッパーのPWM指令の入出力の配列数を初期化する
	m_Port.data.length(DATA_INDEX_NUM);

	// フリッパーのPWM指令の入出力の配列値を初期化する
	SetFrontRightPwm(0);
	SetFrontLeftPwm(0);
	SetBackRightPwm(0);
	SetBackLeftPwm(0);
}

uint8_t FlipperPwmWrapper::GetNumber(void)
{
	return DATA_INDEX_NUM;
}

int32_t FlipperPwmWrapper::GetFrontRightPwm(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_FR];
}

void FlipperPwmWrapper::SetFrontRightPwm(const int32_t iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_FR] = iValue;
}

int32_t FlipperPwmWrapper::GetFrontLeftPwm(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_FL];
}

void FlipperPwmWrapper::SetFrontLeftPwm(const int32_t iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_FL] = iValue;
}

int32_t FlipperPwmWrapper::GetBackRightPwm(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_BR];
}

void FlipperPwmWrapper::SetBackRightPwm(const int32_t iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_BR] = iValue;
}

int32_t FlipperPwmWrapper::GetBackLeftPwm(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0;
	}

	return m_Port.data[DATA_INDEX_BL];
}

void FlipperPwmWrapper::SetBackLeftPwm(const int32_t iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_BL] = iValue;
}
