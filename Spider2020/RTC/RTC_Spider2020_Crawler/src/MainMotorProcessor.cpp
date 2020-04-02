#include "MainMotorProcessor.h"
#include <math.h>
#include <stdio.h>
#include <Eigen/Geometry>

MainMotorProcessor::MainMotorProcessor()
	: m_dTurningRadius(1.0)
	, m_dKP(1.0)
	, m_dKI(1.0)
	, m_dKD(1.0)
	, m_dVxGain(1.0)
	, m_dVaGain(1.0)
	, m_dVx(0.0)
	, m_dVy(0.0)
	, m_dVa(0.0)
	, m_dPositionX(0.0)
	, m_dPositionY(0.0)
	, m_dPositionZ(0.0)
	, m_dOrientationR(0.0)
	, m_dOrientationP(0.0)
	, m_dOrientationY(0.0)
	, m_dIntegralR(0.0)
	, m_dIntegralL(0.0)
{
}

MainMotorProcessor::~MainMotorProcessor()
{
}

void MainMotorProcessor::InitData(void)
{
	// 旋回半径を初期化する
	SetTurningRadius(1.0);

	// PID速度制御の比例ゲインを初期化する
	SetKP(1.0);

	// PID速度制御の積分ゲインを初期化する
	SetKI(1.0);

	// PID速度制御の微分ゲインを初期化する
	SetKD(1.0);

	// オドメトリの並進速度(X)のゲインを初期化する
	SetVxGain(1.0);

	// オドメトリの回転速度のゲインを初期化する
	SetVaGain(1.0);

	// ３次元の位置(X)を初期化する
	SetPositionX(0.0);

	// ３次元の位置(Y)を初期化する
	SetPositionY(0.0);

	// ３次元の位置(Z)を初期化する
	SetPositionZ(0.0);

	// ３次元の姿勢(Roll)を初期化する
	SetOrientationR(0.0);

	// ３次元の姿勢(Pitch)を初期化する
	SetOrientationP(0.0);

	// ３次元の姿勢(Yaw)を初期化する
	SetOrientationY(0.0);

	// モータのデータを初期化する
	m_MotorR.InitData();
	m_MotorL.InitData();

	// フィードバックデータを初期化する
	InitFeedbackData();
}

void MainMotorProcessor::InitFeedbackData(void)
{
	// ２次元の並進速度(X)を初期化する
	SetVx(0.0);

	// ２次元の並進速度(Y)を初期化する
	SetVy(0.0);

	// ２次元の回転速度を初期化する
	SetVa(0.0);

	// 右モータのPID速度制御の積分項を初期化する
	SetIntegralR(0.0);

	// 左モータのPID速度制御の積分項を初期化する
	SetIntegralL(0.0);

	// モータのフィードバックデータを初期化する
	m_MotorR.InitFeedbackData();
	m_MotorL.InitFeedbackData();
}

std::string MainMotorProcessor::GenMoveCommand(double dVx, double dVy, double dVa)
{
	char sCommand[256 + 1] = {0};
	double dVelocityR = 0.0;
	double dVelocityL = 0.0;
	double dPwmR = 0.0;
	double dPwmL = 0.0;

	// ２次元の速度から右モータの速度を求める
	dVelocityR = dVx + dVa*GetTurningRadius();

	// PID速度制御で右モータのPWMを求める
	if(dVelocityR < 0.0)
	{
		dPwmR = m_dKP*(dVelocityR - m_MotorR.GetVelocity()*GetVxGain())*100.0
			  + m_dKI*GetIntegralR()*100.0
			  + m_dKD*(0.0 - m_MotorR.GetAcceleration()*GetVxGain())*100.0
			  - 10.0;
	}
	else if(0.0 < dVelocityR)
	{
		dPwmR = m_dKP*(dVelocityR - m_MotorR.GetVelocity()*GetVxGain())*100.0
			  + m_dKI*GetIntegralR()*100.0
			  + m_dKD*(0.0 - m_MotorR.GetAcceleration()*GetVxGain())*100.0
			  + 10.0;
	}
	else
	{
		dPwmR = 10.0;
		SetIntegralR(0.0);
	}

	// 右モータのPWMを有効範囲に収める
	if(0.0 < dPwmR)
	{
		if(dPwmR < 10.0)
		{
			dPwmR = 10.0;
		}
		else if(90.0 < dPwmR)
		{
			dPwmR = 90.0;
		}
	}
	else
	{
		if(-10.0 < dPwmR)
		{
			dPwmR = -10.0;
		}
		else if(dPwmR < -90.0)
		{
			dPwmR = -90.0;
		}
	}

	// ２次元の速度から左モータの速度を求める
	dVelocityL = dVx - dVa*GetTurningRadius();

	// PID速度制御で左モータのPWMを求める
	if(dVelocityL < 0.0)
	{
		dPwmL = m_dKP*(dVelocityL - m_MotorL.GetVelocity()*GetVxGain())*100.0
			  + m_dKI*GetIntegralL()*100.0
			  + m_dKD*(0.0 - m_MotorL.GetAcceleration()*GetVxGain())*100.0
			  - 10.0;
	}
	else if(0.0 < dVelocityL)
	{
		dPwmL = m_dKP*(dVelocityL - m_MotorL.GetVelocity()*GetVxGain())*100.0
			  + m_dKI*GetIntegralL()*100.0
			  + m_dKD*(0.0 - m_MotorL.GetAcceleration()*GetVxGain())*100.0
			  + 10.0;
	}
	else
	{
		dPwmL = 10.0;
		SetIntegralL(0.0);
	}

	// 左モータのPWMを有効範囲に収める
	if(0.0 < dPwmL)
	{
		if(dPwmL < 10.0)
		{
			dPwmL = 10.0;
		}
		else if(90.0 < dPwmL)
		{
			dPwmL = 90.0;
		}
	}
	else
	{
		if(-10.0 < dPwmL)
		{
			dPwmL = -10.0;
		}
		else if(dPwmL < -90.0)
		{
			dPwmL = -90.0;
		}
	}

	// 動作コマンド書式の文字列を生成する(モータの回転方向に合わせて正負を反転して要求する)
	snprintf(sCommand, (sizeof(sCommand)/sizeof(sCommand[0])) - 1, "s[%.2f:%.2f]e", dPwmR*m_MotorR.GetDirection(), dPwmL*m_MotorL.GetDirection());

	return sCommand;
}

std::string MainMotorProcessor::GenStopCommand(void)
{
	return GenMoveCommand(0.0, 0.0, 0.0);
}

bool MainMotorProcessor::AnalyzeFeedback(double dFrequency, double dVx, double dVy, double dVa, std::string sFeedback)
{
	int iPulseCountR = 0;
	int iPulseCountL = 0;
	double dVelocityR = 0.0;
	double dVelocityL = 0.0;
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

			// ２次元の速度からモータの速度を求める
			dVelocityR = dVx + dVa*GetTurningRadius();
			dVelocityL = dVx - dVa*GetTurningRadius();

			// PID速度制御の積分項を求める
			SetIntegralR(GetIntegralR() + (dVelocityR - m_MotorR.GetVelocity()*GetVxGain())*dFrequency);
			SetIntegralL(GetIntegralL() + (dVelocityL - m_MotorL.GetVelocity()*GetVxGain())*dFrequency);

			// 解析成功
			return true;
		}
	}

	// 解析失敗
	return false;
}

void MainMotorProcessor::CalcOdometry(double dFrequency)
{
	// モータの回転から２次元の並進速度及び回転速度を求める
	SetVx(((m_MotorR.GetVelocity() + m_MotorL.GetVelocity())/2.0)*GetVxGain());
	SetVa(((m_MotorR.GetVelocity() - m_MotorL.GetVelocity())/(2.0*GetTurningRadius()))*GetVaGain());

	// ２次元の並進速度及び回転速度から３次元の位置姿勢を求める
	SetPositionX(GetPositionX() + (GetVx()*dFrequency)*cos(GetOrientationY() + (GetVa()*dFrequency/2.0)));
	SetPositionY(GetPositionY() + (GetVx()*dFrequency)*sin(GetOrientationY() + (GetVa()*dFrequency/2.0)));
	SetOrientationY(GetOrientationY() + GetVa()*dFrequency);
}

void MainMotorProcessor::CalcOdometry(double dRoll, double dPitch, double dYaw, double dFrequency)
{
	Eigen::Matrix3d rot(3,3);
	Eigen::Vector3d vec(3);

	// モータの回転及びIMUの姿勢から２次元の並進速度及び回転速度を求める
	SetVx(((m_MotorR.GetVelocity() + m_MotorL.GetVelocity())/2.0)*GetVxGain());
	SetVa((dYaw - GetOrientationY())/dFrequency);

	// オイラー角から回転行列を求める
	rot = Eigen::AngleAxisd((GetOrientationY() + dYaw)/2.0, Eigen::Vector3d::UnitZ())
		* Eigen::AngleAxisd((GetOrientationP() + dPitch)/2.0, Eigen::Vector3d::UnitY())
		* Eigen::AngleAxisd((GetOrientationR() + dRoll)/2.0, Eigen::Vector3d::UnitX());

	// 並進成分を求める
	vec(0) = GetVx()*dFrequency;
	vec(1) = 0.0;
	vec(2) = 0.0;

	// ロボットの姿勢方向の並進成分を求める
	vec = rot*vec;

	// ２次元の並進速度及び回転速度から３次元の位置姿勢を求める
	SetPositionX(GetPositionX() + vec(0));
	SetPositionY(GetPositionY() + vec(1));
	SetPositionZ(GetPositionZ() + vec(2));
	SetOrientationR(dRoll);
	SetOrientationP(dPitch);
	SetOrientationY(dYaw);
}

void MainMotorProcessor::SetConfig(double dTurningRadius, double dKP, double dKI, double dKD, double dVxGain, double dVaGain)
{
	// 旋回半径を設定する
	SetTurningRadius(dTurningRadius);

	// PID速度制御の比例ゲインを設定する
	SetKP(dKP);

	// PID速度制御の積分ゲインを設定する
	SetKI(dKI);

	// PID速度制御の微分ゲインを設定する
	SetKD(dKD);

	// オドメトリの並進速度(X)のゲインを設定する
	SetVxGain(dVxGain);

	// オドメトリの回転速度のゲインを設定する
	SetVaGain(dVaGain);
}

void MainMotorProcessor::SetConfigR(int8_t iDirection, int32_t iPulseNumber, double dRadius, double dGearRatio, double dLoadGain, double dLoadBase)
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

void MainMotorProcessor::SetConfigL(int8_t iDirection, int32_t iPulseNumber, double dRadius, double dGearRatio, double dLoadGain, double dLoadBase)
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

double MainMotorProcessor::GetLoadR(void)
{
	return m_MotorR.GetLoad();
}

double MainMotorProcessor::GetLoadL(void)
{
	return m_MotorL.GetLoad();
}

double MainMotorProcessor::GetTurningRadius(void)
{
	return m_dTurningRadius;
}

void MainMotorProcessor::SetTurningRadius(double dValue)
{
	m_dTurningRadius = dValue;
}

double MainMotorProcessor::GetKP(void)
{
	return m_dKP;
}

void MainMotorProcessor::SetKP(double dValue)
{
	m_dKP = dValue;
}

double MainMotorProcessor::GetKI(void)
{
	return m_dKI;
}

void MainMotorProcessor::SetKI(double dValue)
{
	m_dKI = dValue;
}

double MainMotorProcessor::GetKD(void)
{
	return m_dKD;
}

void MainMotorProcessor::SetKD(double dValue)
{
	m_dKD = dValue;
}

double MainMotorProcessor::GetVxGain(void)
{
	return m_dVxGain;
}

void MainMotorProcessor::SetVxGain(double dValue)
{
	m_dVxGain = dValue;
}

double MainMotorProcessor::GetVaGain(void)
{
	return m_dVaGain;
}

void MainMotorProcessor::SetVaGain(double dValue)
{
	m_dVaGain = dValue;
}

double MainMotorProcessor::GetVx(void)
{
	return m_dVx;
}

void MainMotorProcessor::SetVx(double dValue)
{
	m_dVx = dValue;
}

double MainMotorProcessor::GetVy(void)
{
	return m_dVy;
}

void MainMotorProcessor::SetVy(double dValue)
{
	m_dVy = dValue;
}

double MainMotorProcessor::GetVa(void)
{
	return m_dVa;
}

void MainMotorProcessor::SetVa(double dValue)
{
	m_dVa = dValue;
}

double MainMotorProcessor::GetPositionX(void)
{
	return m_dPositionX;
}

void MainMotorProcessor::SetPositionX(double dValue)
{
	m_dPositionX = dValue;
}

double MainMotorProcessor::GetPositionY(void)
{
	return m_dPositionY;
}

void MainMotorProcessor::SetPositionY(double dValue)
{
	m_dPositionY = dValue;
}

double MainMotorProcessor::GetPositionZ(void)
{
	return m_dPositionZ;
}

void MainMotorProcessor::SetPositionZ(double dValue)
{
	m_dPositionZ = dValue;
}

double MainMotorProcessor::GetOrientationR(void)
{
	return m_dOrientationR;
}

void MainMotorProcessor::SetOrientationR(double dValue)
{
	m_dOrientationR = dValue;
}

double MainMotorProcessor::GetOrientationP(void)
{
	return m_dOrientationP;
}

void MainMotorProcessor::SetOrientationP(double dValue)
{
	m_dOrientationP = dValue;
}

double MainMotorProcessor::GetOrientationY(void)
{
	return m_dOrientationY;
}

void MainMotorProcessor::SetOrientationY(double dValue)
{
	m_dOrientationY = dValue;
}

double MainMotorProcessor::GetIntegralR(void)
{
	return m_dIntegralR;
}

void MainMotorProcessor::SetIntegralR(double dValue)
{
	m_dIntegralR = dValue;
}

double MainMotorProcessor::GetIntegralL(void)
{
	return m_dIntegralL;
}

void MainMotorProcessor::SetIntegralL(double dValue)
{
	m_dIntegralL = dValue;
}
