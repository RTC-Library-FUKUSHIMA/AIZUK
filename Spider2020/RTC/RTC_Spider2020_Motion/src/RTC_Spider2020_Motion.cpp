// -*- C++ -*-
/*!
 * @file  RTC_Spider2020_Motion.cpp
 * @brief ロボットの動作指令を生成する
 * @date $Date$
 *
 * $Id$
 */

#include "RTC_Spider2020_Motion.h"
#include <math.h>

// timeval構造体の差を計算する(x1-x2)
#define TIMEVAL_DIFF(x1,x2)	(((double)x1.tv_sec + (double)x1.tv_usec/1000000.0) - ((double)x2.tv_sec + (double)x2.tv_usec/1000000.0))

// Module specification
// <rtc-template block="module_spec">
static const char* rtc_spider2020_motion_spec[] =
{
	"implementation_id", "RTC_Spider2020_Motion",
	"type_name",         "RTC_Spider2020_Motion",
	"description",       "ロボットの動作指令を生成する",
	"version",           "2.0.0",
	"vendor",            "AIZUK",
	"category",          "Controller",
	"activity_type",     "PERIODIC",
	"kind",              "DataFlowComponent",
	"max_instance",      "1",
	"language",          "C++",
	"lang_type",         "compile",

	// Configuration variables
	"conf.default.VELOCITY_GAIN", "0.15",
	"conf.default.OMEGA_GAIN", "0.785",
	"conf.default.FAILSAFE_SEC", "1.0",

	// Widget
	"conf.__widget__.VELOCITY_GAIN", "text",
	"conf.__widget__.OMEGA_GAIN", "text",
	"conf.__widget__.FAILSAFE_SEC", "text",

	// Constraints
	"conf.__type__.VELOCITY_GAIN", "double",
	"conf.__type__.OMEGA_GAIN", "double",
	"conf.__type__.FAILSAFE_SEC", "double",

	""
};
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RTC_Spider2020_Motion::RTC_Spider2020_Motion(RTC::Manager* manager)
	// <rtc-template block="initializer">
	: RTC::DataFlowComponentBase(manager)
	, m_Axis_InIn("Axis_In", m_Axis_In)
	, m_Button_InIn("Button_In", m_Button_In)
	, m_Mode_OutOut("Mode_Out", m_Mode_Out)
	, m_Velocity2D_OutOut("Velocity2D_Out", m_Velocity2D_Out)
	, m_FlipperPwm_OutOut("FlipperPwm_Out", m_FlipperPwm_Out)
	, m_ResetIMU_OutOut("ResetIMU_Out", m_ResetIMU_Out)
	, m_Arm1PoseDelta_OutOut("Arm1PoseDelta_Out", m_Arm1PoseDelta_Out)
	, m_Arm1FingerDelta_OutOut("Arm1FingerDelta_Out", m_Arm1FingerDelta_Out)
	, m_Arm1Home_OutOut("Arm1Home_Out", m_Arm1Home_Out)

	// </rtc-template>
	, m_Axis_InWrap(m_Axis_In)
	, m_OldAxis_InWrap(m_OldAxis_In)
	, m_Button_InWrap(m_Button_In)
	, m_OldButton_InWrap(m_OldButton_In)
	, m_Mode_OutWrap(m_Mode_Out)
	, m_FlipperPwm_OutWrap(m_FlipperPwm_Out)
	, m_Arm1FingerDelta_OutWrap(m_Arm1FingerDelta_Out)
	, m_stAxisReadTime({0})
	, m_stButtonReadTime({0})
{
}

/*!
 * @brief destructor
 */
RTC_Spider2020_Motion::~RTC_Spider2020_Motion()
{
}

RTC::ReturnCode_t RTC_Spider2020_Motion::onInitialize()
{
	// Registration: InPort/OutPort/Service
	// <rtc-template block="registration">
	// Set InPort buffers
	addInPort("Axis_In", m_Axis_InIn);
	addInPort("Button_In", m_Button_InIn);

	// Set OutPort buffer
	addOutPort("Mode_Out", m_Mode_OutOut);
	addOutPort("Velocity2D_Out", m_Velocity2D_OutOut);
	addOutPort("FlipperPwm_Out", m_FlipperPwm_OutOut);
	addOutPort("ResetIMU_Out", m_ResetIMU_OutOut);
	addOutPort("Arm1PoseDelta_Out", m_Arm1PoseDelta_OutOut);
	addOutPort("Arm1FingerDelta_Out", m_Arm1FingerDelta_OutOut);
	addOutPort("Arm1Home_Out", m_Arm1Home_OutOut);

	// Set service provider to Ports

	// Set service consumers to Ports

	// Set CORBA Service Ports

	// </rtc-template>

	// <rtc-template block="bind_config">
	// Bind variables and configuration variable
	bindParameter("VELOCITY_GAIN", m_VELOCITY_GAIN, "0.15");
	bindParameter("OMEGA_GAIN", m_OMEGA_GAIN, "0.785");
	bindParameter("FAILSAFE_SEC", m_FAILSAFE_SEC, "1.0");
	// </rtc-template>

	// 軸キーの出力を初期化する
	m_Axis_InWrap.InitData();

	// 前回の軸キーの出力を初期化する
	m_OldAxis_InWrap.InitData();

	// ボタンの出力を初期化する
	m_Button_InWrap.InitData();

	// 前回のボタンの出力を初期化する
	m_OldButton_InWrap.InitData();

	// 動作指令の状態の出力を初期化する
	m_Mode_OutWrap.InitData();

	// ２次元の速度を初期化する
	m_Velocity2D_Out.data.vx = 0.0;
	m_Velocity2D_Out.data.vy = 0.0;
	m_Velocity2D_Out.data.va = 0.0;

	// フリッパーのPWM指令を初期化する
	m_FlipperPwm_OutWrap.InitData();

	// IMUのフィルタリセット指令を初期化する
	m_ResetIMU_Out.data = 0;

	// Jaco2アーム(１本目)の手先位置姿勢の変位速度を初期化する
	m_Arm1PoseDelta_Out.data.position.x = 0.0;
	m_Arm1PoseDelta_Out.data.position.y = 0.0;
	m_Arm1PoseDelta_Out.data.position.z = 0.0;
	m_Arm1PoseDelta_Out.data.orientation.r = 0.0;
	m_Arm1PoseDelta_Out.data.orientation.p = 0.0;
	m_Arm1PoseDelta_Out.data.orientation.y = 0.0;

	// Jaco2アーム(１本目)の指の開閉具合の変位速度を初期化する
	m_Arm1FingerDelta_OutWrap.InitData();

	// Jaco2アーム(１本目)の初期姿勢遷移指令を初期化する
	m_Arm1Home_Out.data = 0;

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_Spider2020_Motion::onFinalize()
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Motion::onStartup(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Motion::onShutdown(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Motion::onActivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Motion::onDeactivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

RTC::ReturnCode_t RTC_Spider2020_Motion::onExecute(RTC::UniqueId ec_id)
{
	// 軸キーの入力具合をポートから読み込む
	ReadAxis();

	// ボタンの入力具合をポートから読み込む
	ReadButton();

	// 動作指令の状態を更新してポートに出力する
	WriteMode();

	// 走行モードの動作指令を生成してポートに出力する
	WriteCrawlerMotion();

	// IMUのフィルタリセット指令の状態を更新してポートに出力する
	WriteResetIMU();

	// アームモードの動作指令を生成してポートに出力する
	WriteArmMotion();

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_Spider2020_Motion::onAborting(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Motion::onError(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Motion::onReset(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Motion::onStateUpdate(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Motion::onRateChanged(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

void RTC_Spider2020_Motion::ReadAxis(void)
{
	struct timeval ti = {0};

	// 現在の時刻を取得する
	gettimeofday(&ti, NULL);

	// 前回の軸キーの入力具合を更新する
	m_OldAxis_InWrap = m_Axis_InWrap;

	// 軸キーの入力具合を更新する
	if(m_Axis_InIn.isNew())
	{
		// 読み込み時刻を更新する
		m_stAxisReadTime = ti;

		// 次のデータを読み込む
		m_Axis_InIn.read();
	}
	else
	{
		if(m_FAILSAFE_SEC <= TIMEVAL_DIFF(ti,m_stAxisReadTime))
		{
			// 初期化する(暴走回避)
			m_Axis_InWrap.InitData();
		}
	}
}

void RTC_Spider2020_Motion::ReadButton(void)
{
	struct timeval ti = {0};

	// 現在の時刻を取得する
	gettimeofday(&ti, NULL);

	// 前回のボタンの入力具合を更新する
	m_OldButton_InWrap = m_Button_InWrap;

	// ボタンの入力具合を更新する
	if(m_Button_InIn.isNew())
	{
		// 読み込み時刻を更新する
		m_stButtonReadTime = ti;

		// 次のデータを読み込む
		m_Button_InIn.read();
	}
	else
	{
		if(m_FAILSAFE_SEC <= TIMEVAL_DIFF(ti,m_stButtonReadTime))
		{
			// 初期化する(暴走回避)
			m_Button_InWrap.InitData();
		}
	}
}

void RTC_Spider2020_Motion::WriteMode(void)
{
	// TOUCHボタン押下で速度レベルを変更する
	if(m_Button_InWrap.GetTouch() && !m_OldButton_InWrap.GetTouch())
	{
		switch(m_Mode_OutWrap.GetControl())
		{
			// 動作指令の操作モードを台車からアームに変更する
			case ModeWrapper::CONTROL_DRIVE:
				m_Mode_OutWrap.SetControl(ModeWrapper::CONTROL_ARM);
				break;
			// 動作指令の操作モードをアームから台車に変更する
			case ModeWrapper::CONTROL_ARM:
				m_Mode_OutWrap.SetControl(ModeWrapper::CONTROL_DRIVE);
				break;
			default:
				m_Mode_OutWrap.SetControl(ModeWrapper::CONTROL_DRIVE);
				break;
		}
	}

	// 走行モード
	if(m_Mode_OutWrap.GetControl() == ModeWrapper::CONTROL_DRIVE)
	{
		// SHAREボタン及びOPTIONSボタンを同時押しなら台車の位置姿勢のクリアを設定する
		if(m_Button_InWrap.GetShare() && m_Button_InWrap.GetOptions())
		{
			// 台車の位置姿勢のクリアをONする
			m_Mode_OutWrap.SetCrawlerPoseClear(ModeWrapper::CRAWLER_POSE_CLEAR_ON);
		}
		else
		{
			// 台車の位置姿勢のクリアをOFFする
			m_Mode_OutWrap.SetCrawlerPoseClear(ModeWrapper::CRAWLER_POSE_CLEAR_OFF);
		}

		// CIRCLEボタン押下で速度レベルを変更する
		if(m_Button_InWrap.GetCircle() && !m_OldButton_InWrap.GetCircle())
		{
			switch(m_Mode_OutWrap.GetSpeedLevel())
			{
				// 台車の速度を低速から中速に変更する
				case ModeWrapper::SPEED_LEVEL_LOW:
					m_Mode_OutWrap.SetSpeedLevel(ModeWrapper::SPEED_LEVEL_MID);
					break;
				// 台車の速度を中速から高速に変更する
				case ModeWrapper::SPEED_LEVEL_MID:
					m_Mode_OutWrap.SetSpeedLevel(ModeWrapper::SPEED_LEVEL_HIGH);
					break;
				// 台車の速度を高速から低速に変更する
				case ModeWrapper::SPEED_LEVEL_HIGH:
					m_Mode_OutWrap.SetSpeedLevel(ModeWrapper::SPEED_LEVEL_LOW);
					break;
				default:
					m_Mode_OutWrap.SetSpeedLevel(ModeWrapper::SPEED_LEVEL_LOW);
					break;
			}
		}

		// L3ボタン押下で最大速度フラグを変更する
		if(m_Button_InWrap.GetL3())
		{
			// 最大速度フラグをONする
			m_Mode_OutWrap.SetSpeedMax(ModeWrapper::SPEED_MAX_ON);
		}
		else
		{
			// 最大速度フラグをOFFする
			m_Mode_OutWrap.SetSpeedMax(ModeWrapper::SPEED_MAX_OFF);
		}

		// R1ボタン押下で右前方フリッパーの選択状態を変更する
		if(m_Button_InWrap.GetR1())
		{
			// 右前方フリッパーを選択する
			m_Mode_OutWrap.SetFrontRightFlipperSelect(ModeWrapper::FLIPPER_SELECT_ON);
		}
		else
		{
			// 右前方フリッパーを選択解除する
			m_Mode_OutWrap.SetFrontRightFlipperSelect(ModeWrapper::FLIPPER_SELECT_OFF);
		}

		// L1ボタン押下で左前方フリッパーの選択状態を変更する
		if(m_Button_InWrap.GetL1())
		{
			// 左前方フリッパーを選択する
			m_Mode_OutWrap.SetFrontLeftFlipperSelect(ModeWrapper::FLIPPER_SELECT_ON);
		}
		else
		{
			// 左前方フリッパーを選択解除する
			m_Mode_OutWrap.SetFrontLeftFlipperSelect(ModeWrapper::FLIPPER_SELECT_OFF);
		}

		// R2ボタン押下で右後方フリッパーの選択状態を変更する
		if(m_Button_InWrap.GetR2())
		{
			// 右後方フリッパーを選択する
			m_Mode_OutWrap.SetBackRightFlipperSelect(ModeWrapper::FLIPPER_SELECT_ON);
		}
		else
		{
			// 右後方フリッパーを選択解除する
			m_Mode_OutWrap.SetBackRightFlipperSelect(ModeWrapper::FLIPPER_SELECT_OFF);
		}

		// L2ボタン押下で左後方フリッパーの選択状態を変更する
		if(m_Button_InWrap.GetL2())
		{
			// 左後方フリッパーを選択する
			m_Mode_OutWrap.SetBackLeftFlipperSelect(ModeWrapper::FLIPPER_SELECT_ON);
		}
		else
		{
			// 左後方フリッパーを選択解除する
			m_Mode_OutWrap.SetBackLeftFlipperSelect(ModeWrapper::FLIPPER_SELECT_OFF);
		}

		// TRIANGLEボタンまたはCROSSボタン押下でフリッパーの動作状態を変更する
		if(m_Button_InWrap.GetTriangle())
		{
			// 選択フリッパーを上昇する
			m_Mode_OutWrap.SetFlipperStatus(ModeWrapper::FLIPPER_STATUS_UP);
		}
		else if(m_Button_InWrap.GetCross())
		{
			// 選択フリッパーを下降する
			m_Mode_OutWrap.SetFlipperStatus(ModeWrapper::FLIPPER_STATUS_DOWN);
		}
		else
		{
			// 選択フリッパーを現状維持する
			m_Mode_OutWrap.SetFlipperStatus(ModeWrapper::FLIPPER_STATUS_STAY);
		}
	}
	// 上記以外
	else
	{
		// 台車の位置姿勢のクリアをOFFする
		m_Mode_OutWrap.SetCrawlerPoseClear(ModeWrapper::CRAWLER_POSE_CLEAR_OFF);

		// 最大速度フラグをOFFする
		m_Mode_OutWrap.SetSpeedMax(ModeWrapper::SPEED_MAX_OFF);

		// 全てのフリッパーの選択状態を解除する
		m_Mode_OutWrap.SetFrontRightFlipperSelect(ModeWrapper::FLIPPER_SELECT_OFF);
		m_Mode_OutWrap.SetFrontLeftFlipperSelect(ModeWrapper::FLIPPER_SELECT_OFF);
		m_Mode_OutWrap.SetBackRightFlipperSelect(ModeWrapper::FLIPPER_SELECT_OFF);
		m_Mode_OutWrap.SetBackLeftFlipperSelect(ModeWrapper::FLIPPER_SELECT_OFF);

		// 選択フリッパーを現状維持する
		m_Mode_OutWrap.SetFlipperStatus(ModeWrapper::FLIPPER_STATUS_STAY);
	}

	// 動作指令の状態をポートに出力する
	m_Mode_OutWrap.SetTimestamp();
	m_Mode_OutOut.write();
}

void RTC_Spider2020_Motion::WriteCrawlerMotion(void)
{
	double dLStickVertical = 0.0;
	double dLStickHorizontal = 0.0;
	double dLStickLength = 0.0;
	double dOmega = 0.0;

	// 走行モード
	if(m_Mode_OutWrap.GetControl() == ModeWrapper::CONTROL_DRIVE)
	{
		// 左スティック操作を速度に変換する
		dLStickVertical = m_Axis_InWrap.GetLStickVertical()*-1.0;
		dLStickHorizontal = m_Axis_InWrap.GetLStickHorizontal();
		dLStickLength = sqrt(pow(dLStickVertical,2.0) + pow(dLStickHorizontal,2.0));
		dLStickLength = std::min(std::max(dLStickLength, -1.0), 1.0);
		dOmega = atan2(dLStickVertical,dLStickHorizontal);

		// 最大速度フラグがONならば高速で走行する
		if(m_Mode_OutWrap.GetSpeedMax())
		{
			dLStickLength *= 1.00;
		}
		// 上記以外なら速度レベルに合わせて走行する
		else
		{
			switch(m_Mode_OutWrap.GetSpeedLevel())
			{
				case ModeWrapper::SPEED_LEVEL_LOW:
					dLStickLength *= 0.20;
					break;
				case ModeWrapper::SPEED_LEVEL_MID:
					dLStickLength *= 0.60;
					break;
				case ModeWrapper::SPEED_LEVEL_HIGH:
					dLStickLength *= 1.00;
					break;
				default:
					dLStickLength *= 0.20;
					break;
			}
		}

		// ２次元の速度を求める
		m_Velocity2D_Out.data.vx = dLStickLength*sin(dOmega)*m_VELOCITY_GAIN;
		m_Velocity2D_Out.data.vy = 0.0;
		m_Velocity2D_Out.data.va = dLStickLength*cos(dOmega)*m_OMEGA_GAIN*-1.0;

		// フリッパーの動作状態が上昇
		if(m_Mode_OutWrap.GetFlipperStatus() == ModeWrapper::FLIPPER_STATUS_UP)
		{
			// 右前方フリッパー
			if(m_Mode_OutWrap.GetFrontRightFlipperSelect())
			{
				// 右前方フリッパーを上昇する
				m_FlipperPwm_OutWrap.SetFrontRightPwm(90);
			}
			else
			{
				// 右前方フリッパーを現状維持する
				m_FlipperPwm_OutWrap.SetFrontRightPwm(10);
			}

			// 左前方フリッパー
			if(m_Mode_OutWrap.GetFrontLeftFlipperSelect())
			{
				// 左前方フリッパーを上昇する
				m_FlipperPwm_OutWrap.SetFrontLeftPwm(90);
			}
			else
			{
				// 左前方フリッパーを現状維持する
				m_FlipperPwm_OutWrap.SetFrontLeftPwm(10);
			}

			// 右後方フリッパー
			if(m_Mode_OutWrap.GetBackRightFlipperSelect())
			{
				// 右後方フリッパーを上昇する
				m_FlipperPwm_OutWrap.SetBackRightPwm(90);
			}
			else
			{
				// 右後方フリッパーを現状維持する
				m_FlipperPwm_OutWrap.SetBackRightPwm(10);
			}

			// 左後方フリッパー
			if(m_Mode_OutWrap.GetBackLeftFlipperSelect())
			{
				// 左後方フリッパーを上昇する
				m_FlipperPwm_OutWrap.SetBackLeftPwm(90);
			}
			else
			{
				// 左後方フリッパーを現状維持する
				m_FlipperPwm_OutWrap.SetBackLeftPwm(10);
			}
		}
		// フリッパーの動作状態が下降
		else if(m_Mode_OutWrap.GetFlipperStatus() == ModeWrapper::FLIPPER_STATUS_DOWN)
		{
			// 右前方フリッパー
			if(m_Mode_OutWrap.GetFrontRightFlipperSelect())
			{
				// 右前方フリッパーを下降する
				m_FlipperPwm_OutWrap.SetFrontRightPwm(-90);
			}
			else
			{
				// 右前方フリッパーを現状維持する
				m_FlipperPwm_OutWrap.SetFrontRightPwm(-10);
			}

			// 左前方フリッパー
			if(m_Mode_OutWrap.GetFrontLeftFlipperSelect())
			{
				// 左前方フリッパーを下降する
				m_FlipperPwm_OutWrap.SetFrontLeftPwm(-90);
			}
			else
			{
				// 左前方フリッパーを現状維持する
				m_FlipperPwm_OutWrap.SetFrontLeftPwm(-10);
			}

			// 右後方フリッパー
			if(m_Mode_OutWrap.GetBackRightFlipperSelect())
			{
				// 右後方フリッパーを下降する
				m_FlipperPwm_OutWrap.SetBackRightPwm(-90);
			}
			else
			{
				// 右後方フリッパーを現状維持する
				m_FlipperPwm_OutWrap.SetBackRightPwm(-10);
			}

			// 左後方フリッパー
			if(m_Mode_OutWrap.GetBackLeftFlipperSelect())
			{
				// 左後方フリッパーを下降する
				m_FlipperPwm_OutWrap.SetBackLeftPwm(-90);
			}
			else
			{
				// 左後方フリッパーを現状維持する
				m_FlipperPwm_OutWrap.SetBackLeftPwm(-10);
			}
		}
		// 上記以外
		else
		{
			// フリッパーのPWM指令を初期化する
			m_FlipperPwm_OutWrap.InitData();
		}
	}
	// 上記以外
	else
	{
		// ２次元の速度を初期化する
		m_Velocity2D_Out.data.vx = 0.0;
		m_Velocity2D_Out.data.vy = 0.0;
		m_Velocity2D_Out.data.va = 0.0;

		// フリッパーのPWM指令を初期化する
		m_FlipperPwm_OutWrap.InitData();
	}

	// ２次元の速度をポートに出力する
	setTimestamp(m_Velocity2D_Out);
	m_Velocity2D_OutOut.write();

	// フリッパーのPWM指令をポートに出力する
	m_FlipperPwm_OutWrap.SetTimestamp();
	m_FlipperPwm_OutOut.write();
}

void RTC_Spider2020_Motion::WriteResetIMU(void)
{
	// 走行モード
	if(m_Mode_OutWrap.GetControl() == ModeWrapper::CONTROL_DRIVE)
	{
		// SHAREボタン及びOPTIONSボタンを同時押しなら台車の位置姿勢のクリアを設定する
		if(m_Button_InWrap.GetShare() && m_Button_InWrap.GetOptions())
		{
			// IMUのフィルタをリセットをONする
			m_ResetIMU_Out.data = 1;
		}
		else
		{
			// IMUのフィルタをリセットをOFFする
			m_ResetIMU_Out.data = 0;
		}
	}
	// 上記以外
	else
	{
		// IMUのフィルタをリセットをOFFする
		m_ResetIMU_Out.data = 0;
	}

	// IMUのフィルタリセット指令の状態をポートに出力する
	setTimestamp(m_ResetIMU_Out);
	m_ResetIMU_OutOut.write();
}

void RTC_Spider2020_Motion::WriteArmMotion(void)
{
	// アームモード
	if(m_Mode_OutWrap.GetControl() == ModeWrapper::CONTROL_ARM)
	{
		m_Arm1PoseDelta_Out.data.position.x = 0.0;
		m_Arm1PoseDelta_Out.data.position.y = 0.0;
		m_Arm1PoseDelta_Out.data.position.z = 0.0;
		m_Arm1PoseDelta_Out.data.orientation.r = 0.0;
		m_Arm1PoseDelta_Out.data.orientation.p = 0.0;
		m_Arm1PoseDelta_Out.data.orientation.y = 0.0;
		m_Arm1FingerDelta_OutWrap.SetThumbDelta(0);
		m_Arm1FingerDelta_OutWrap.SetIndexFingerDelta(0);
		m_Arm1FingerDelta_OutWrap.SetMiddleFingerDelta(0);

		// 十字ボタン(上)
		if(m_Axis_InWrap.GetDirVertical() == -1.0)
		{
			// 手先をロール軸で回転する
			m_Arm1PoseDelta_Out.data.orientation.r = m_Axis_InWrap.GetLStickVertical()*-1.0;
		}
		// 十字ボタン(下)
		else if(m_Axis_InWrap.GetDirHorizontal() == 1.0)
		{
			// 手先をピッチ軸で回転する
			m_Arm1PoseDelta_Out.data.orientation.p = m_Axis_InWrap.GetLStickVertical();
		}
		// 十字ボタン(右)
		else if(m_Axis_InWrap.GetDirVertical() == 1.0)
		{
			// 手先をヨー軸で回転する
			m_Arm1PoseDelta_Out.data.orientation.y = m_Axis_InWrap.GetLStickVertical();
		}
		// 十字ボタン(左)
		else if(m_Axis_InWrap.GetDirHorizontal() == -1.0)
		{
			if(0.2 < fabs(m_Axis_InWrap.GetLStickVertical()))
			{
				if(0.0 < m_Axis_InWrap.GetLStickVertical())
				{
					// 指を閉じる
					m_Arm1FingerDelta_OutWrap.SetThumbDelta(3000);
					m_Arm1FingerDelta_OutWrap.SetIndexFingerDelta(3000);
					m_Arm1FingerDelta_OutWrap.SetMiddleFingerDelta(3000);
				}
				else
				{
					// 指を放す
					m_Arm1FingerDelta_OutWrap.SetThumbDelta(-3000);
					m_Arm1FingerDelta_OutWrap.SetIndexFingerDelta(-3000);
					m_Arm1FingerDelta_OutWrap.SetMiddleFingerDelta(-3000);
				}
			}
		}
		else
		{
			// 手先をXYZ座標で動かす
			m_Arm1PoseDelta_Out.data.position.x = (m_Axis_InWrap.GetLStickHorizontal()/10.0)*-1.0;
			m_Arm1PoseDelta_Out.data.position.y = (m_Axis_InWrap.GetLStickVertical()/10.0);
			m_Arm1PoseDelta_Out.data.position.z = (m_Button_InWrap.GetL1() - m_Button_InWrap.GetL2())/10.0;
		}

		// SHAREボタン
		if(m_Button_InWrap.GetShare())
		{
			// 初期姿勢遷移ON
			m_Arm1Home_Out.data = 1;
		}
		// 上記以外
		else
		{
			// 初期姿勢遷移OFF
			m_Arm1Home_Out.data = 0;
		}
	}
	// 上記以外
	else
	{
		// Jaco2アーム(１本目)の手先位置姿勢の変位速度を初期化する
		m_Arm1PoseDelta_Out.data.position.x = 0.0;
		m_Arm1PoseDelta_Out.data.position.y = 0.0;
		m_Arm1PoseDelta_Out.data.position.z = 0.0;
		m_Arm1PoseDelta_Out.data.orientation.r = 0.0;
		m_Arm1PoseDelta_Out.data.orientation.p = 0.0;
		m_Arm1PoseDelta_Out.data.orientation.y = 0.0;

		// Jaco2アーム(１本目)の指の開閉具合の変位速度を初期化する
		m_Arm1FingerDelta_OutWrap.SetThumbDelta(0);
		m_Arm1FingerDelta_OutWrap.SetIndexFingerDelta(0);
		m_Arm1FingerDelta_OutWrap.SetMiddleFingerDelta(0);

		// Jaco2アーム(１本目)の初期姿勢遷移指令を初期化する
		m_Arm1Home_Out.data = 0;
	}

	// Jaco2アーム(１本目)の手先位置姿勢の変位速度をポートに出力する
	setTimestamp(m_Arm1PoseDelta_Out);
	m_Arm1PoseDelta_OutOut.write();

	// Jaco2アーム(１本目)の指の開閉具合の変位速度をポートに出力する
	m_Arm1FingerDelta_OutWrap.SetTimestamp();
	m_Arm1FingerDelta_OutOut.write();

	// Jaco2アーム(１本目)の初期姿勢遷移指令をポートに出力する
	setTimestamp(m_Arm1Home_Out);
	m_Arm1Home_OutOut.write();
}


extern "C"
{
	void RTC_Spider2020_MotionInit(RTC::Manager* manager)
	{
		coil::Properties profile(rtc_spider2020_motion_spec);
		manager->registerFactory(profile, RTC::Create<RTC_Spider2020_Motion>, RTC::Delete<RTC_Spider2020_Motion>);
	}
};
