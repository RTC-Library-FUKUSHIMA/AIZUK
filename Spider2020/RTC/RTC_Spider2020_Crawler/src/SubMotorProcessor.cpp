#include "SubMotorProcessor.h"
#include <stdio.h>

SubMotorProcessor::SubMotorProcessor()
{
}

SubMotorProcessor::~SubMotorProcessor()
{
}

void SubMotorProcessor::InitData(void)
{
	// モータのデータを初期化する
	m_MotorR.InitData();
	m_MotorL.InitData();
}

void SubMotorProcessor::InitFeedbackData(void)
{
	// モータのフィードバックデータを初期化する
	m_MotorR.InitFeedbackData();
	m_MotorL.InitFeedbackData();
}

std::string SubMotorProcessor::GenMoveCommand(int32_t iPwmR, int32_t iPwmL)
{
	char sCommand[256 + 1] = {0};

	// 動作コマンド書式の文字列を生成する(モータの回転方向に合わせて正負を反転して要求する)
	snprintf(sCommand, (sizeof(sCommand)/sizeof(sCommand[0])) - 1, "s[%d:%d]e", iPwmR*m_MotorR.GetDirection(), iPwmL*m_MotorL.GetDirection());

	return sCommand;
}

std::string SubMotorProcessor::GenStopCommand(void)
{
	return GenMoveCommand(0, 0);
}

bool SubMotorProcessor::AnalyzeFeedback(double dFrequency, std::string sFeedback)
{
	int iPulseCountR = 0;
	int iPulseCountL = 0;
	double dVelocityMdR = 0.0;
	double dVelocityMdL = 0.0;
	double dLoadR = 0.0;
	double dLoadL = 0.0;
	int iRet = 0;

	if(0 < sFeedback.length())
	{
		// フィードバック書式通りに６つのパラメータがあるかチェックする
		iRet = sscanf(sFeedback.c_str(), "s[%X:%X][%lf:%lf][%lf:%lf]e", &iPulseCountR, &iPulseCountL, &dVelocityMdR, &dLoadR, &dVelocityMdL, &dLoadL);
		if(iRet == 6)
		{
			// モータのフィードバックを処理する
			m_MotorR.CalcFeedback(dFrequency, iPulseCountR, dVelocityMdR, dLoadR);
			m_MotorL.CalcFeedback(dFrequency, iPulseCountL, dVelocityMdL, dLoadL);

			// 解析成功
			return true;
		}
	}

	// 解析失敗
	return false;
}

void SubMotorProcessor::SetConfigR(int8_t iDirection, int32_t iPulseNumber, double dRadius, double dGearRatio, double dLoadGain, double dLoadBase)
{
	// モータの回転方向を設定する
	m_MotorR.SetDirection(iDirection);

	// モータのパルス数を設定する
	m_MotorR.SetPulseNumber(iPulseNumber);

	// 車輪の半径を設定する
	m_MotorR.SetRadius(dRadius);

	// モータと車輪の減速比を設定する
	m_MotorR.SetGearRatio(dGearRatio);

	// 電圧値をモータ負荷に変換するゲインを設定する
	m_MotorR.SetLoadGain(dLoadGain);

	// モータ負荷の基準電圧を設定する
	m_MotorR.SetLoadBase(dLoadBase);
}

void SubMotorProcessor::SetConfigL(int8_t iDirection, int32_t iPulseNumber, double dRadius, double dGearRatio, double dLoadGain, double dLoadBase)
{
	// モータの回転方向を設定する
	m_MotorL.SetDirection(iDirection);

	// モータのパルス数を設定する
	m_MotorL.SetPulseNumber(iPulseNumber);

	// 車輪の半径を設定する
	m_MotorL.SetRadius(dRadius);

	// モータと車輪の減速比を設定する
	m_MotorL.SetGearRatio(dGearRatio);

	// 電圧値をモータ負荷に変換するゲインを設定する
	m_MotorL.SetLoadGain(dLoadGain);

	// モータ負荷の基準電圧を設定する
	m_MotorL.SetLoadBase(dLoadBase);
}

double SubMotorProcessor::GetAngleR(void)
{
	return m_MotorR.GetAngle();
}

void SubMotorProcessor::SetAngleR(double dValue)
{
	m_MotorR.SetAngle(dValue);
}

double SubMotorProcessor::GetAngleL(void)
{
	return m_MotorL.GetAngle();
}

void SubMotorProcessor::SetAngleL(double dValue)
{
	m_MotorL.SetAngle(dValue);
}

double SubMotorProcessor::GetLoadR(void)
{
	return m_MotorR.GetLoad();
}

double SubMotorProcessor::GetLoadL(void)
{
	return m_MotorL.GetLoad();
}
