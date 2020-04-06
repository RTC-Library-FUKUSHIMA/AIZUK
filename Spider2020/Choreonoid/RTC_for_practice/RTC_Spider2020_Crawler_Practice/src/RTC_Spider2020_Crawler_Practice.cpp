// -*- C++ -*-
/*!
 * @file  RTC_Spider2020_Crawler_Practice.cpp
 * @brief Spider2020 コレオノイドモデルの台車制御RTC
 * @date $Date$
 *
 * $Id$
 */

#include "RTC_Spider2020_Crawler_Practice.h"

#define VELOCITY_MAX		(0.15)	/*!< クローラ最大速度		*/
#define FLIPPER_PWM_MIN		(10)	/*!< PWM指令最小値			*/
#define FLIPPER_PWM_MAX		(90)	/*!< PWM指令最大値			*/

// timeval構造体の差を計算する(x1-x2)
#define TIMEVAL_DIFF(x1,x2)	(((double)x1.tv_sec + (double)x1.tv_usec/1000000.0) - ((double)x2.tv_sec + (double)x2.tv_usec/1000000.0))

// Module specification
// <rtc-template block="module_spec">
static const char* rtc_spider2020_crawler_practice_spec[] =
{
	"implementation_id", "RTC_Spider2020_Crawler_Practice",
	"type_name",         "RTC_Spider2020_Crawler_Practice",
	"description",       "Spider2020 コレオノイドモデルの台車制御RTC",
	"version",           "1.0.0",
	"vendor",            "AIZUK",
	"category",          "Controller",
	"activity_type",     "PERIODIC",
	"kind",              "DataFlowComponent",
	"max_instance",      "1",
	"language",          "C++",
	"lang_type",         "compile",

	// Configuration variables
	"conf.default.WHEEL_RADIUS", "0.0769",
	"conf.default.TURNING_RADIUS", "0.0938",
	"conf.default.MAIN_MOTOR_TORQUE", "405e-3",
	"conf.default.MAIN_MOTOR_RPM", "5950",
	"conf.default.MAIN_MOTOR_GRADIENT", "0.668e+3",
	"conf.default.MAIN_MOTOR_GEAR_RATIO", "243",
	"conf.default.SUB_MOTOR_TORQUE", "105e-3",
	"conf.default.SUB_MOTOR_RPM", "7750",
	"conf.default.SUB_MOTOR_GRADIENT", "6.54e+3",
	"conf.default.SUB_MOTOR_GEAR_RATIO", "1080",
	"conf.default.FAILSAFE_SEC", "1.0",

	// Widget
	"conf.__widget__.WHEEL_RADIUS", "text",
	"conf.__widget__.TURNING_RADIUS", "text",
	"conf.__widget__.MAIN_MOTOR_TORQUE", "text",
	"conf.__widget__.MAIN_MOTOR_RPM", "text",
	"conf.__widget__.MAIN_MOTOR_GRADIENT", "text",
	"conf.__widget__.MAIN_MOTOR_GEAR_RATIO", "text",
	"conf.__widget__.SUB_MOTOR_TORQUE", "text",
	"conf.__widget__.SUB_MOTOR_RPM", "text",
	"conf.__widget__.SUB_MOTOR_GRADIENT", "text",
	"conf.__widget__.SUB_MOTOR_GEAR_RATIO", "text",
	"conf.__widget__.FAILSAFE_SEC", "text",

	// Constraints
	"conf.__type__.WHEEL_RADIUS", "double",
	"conf.__type__.TURNING_RADIUS", "double",
	"conf.__type__.MAIN_MOTOR_TORQUE", "double",
	"conf.__type__.MAIN_MOTOR_RPM", "long",
	"conf.__type__.MAIN_MOTOR_GRADIENT", "double",
	"conf.__type__.MAIN_MOTOR_GEAR_RATIO", "double",
	"conf.__type__.SUB_MOTOR_TORQUE", "double",
	"conf.__type__.SUB_MOTOR_RPM", "long",
	"conf.__type__.SUB_MOTOR_GRADIENT", "double",
	"conf.__type__.SUB_MOTOR_GEAR_RATIO", "double",
	"conf.__type__.FAILSAFE_SEC", "double",

	""
};
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RTC_Spider2020_Crawler_Practice::RTC_Spider2020_Crawler_Practice(RTC::Manager* manager)
	// <rtc-template block="initializer">
	: BodyIoRTC(manager)
	, m_Velocity2D_InIn("Velocity2D_In", m_Velocity2D_In)
	, m_FlipperPwm_InIn("FlipperPwm_In", m_FlipperPwm_In)

	// </rtc-template>
	, m_FlipperPwm_InWrap(m_FlipperPwm_In)
	, m_stVelocity2DReadTime({0})
	, m_stFlipperPwmReadTime({0})
{
}

/*!
 * @brief destructor
 */
RTC_Spider2020_Crawler_Practice::~RTC_Spider2020_Crawler_Practice()
{
}

RTC::ReturnCode_t RTC_Spider2020_Crawler_Practice::onInitialize(Body* body)
{
	// Registration: InPort/OutPort/Service
	// <rtc-template block="registration">
	// Set InPort buffers
	addInPort("Velocity2D_In", m_Velocity2D_InIn);
	addInPort("FlipperPwm_In", m_FlipperPwm_InIn);

	// Set OutPort buffer

	// Set service provider to Ports

	// Set service consumers to Ports

	// Set CORBA Service Ports

	// </rtc-template>

	// <rtc-template block="bind_config">
	// Bind variables and configuration variable
	bindParameter("WHEEL_RADIUS", m_WHEEL_RADIUS, "0.0769");
	bindParameter("TURNING_RADIUS", m_TURNING_RADIUS, "0.0938");
	bindParameter("MAIN_MOTOR_TORQUE", m_MAIN_MOTOR_TORQUE, "405e-3");
	bindParameter("MAIN_MOTOR_RPM", m_MAIN_MOTOR_RPM, "5950");
	bindParameter("MAIN_MOTOR_GRADIENT", m_MAIN_MOTOR_GRADIENT, "0.668e+3");
	bindParameter("MAIN_MOTOR_GEAR_RATIO", m_MAIN_MOTOR_GEAR_RATIO, "243");
	bindParameter("SUB_MOTOR_TORQUE", m_SUB_MOTOR_TORQUE, "105e-3");
	bindParameter("SUB_MOTOR_RPM", m_SUB_MOTOR_RPM, "7750");
	bindParameter("SUB_MOTOR_GRADIENT", m_SUB_MOTOR_GRADIENT, "6.54e+3");
	bindParameter("SUB_MOTOR_GEAR_RATIO", m_SUB_MOTOR_GEAR_RATIO, "1080");
	bindParameter("FAILSAFE_SEC", m_FAILSAFE_SEC, "1.0");
	// </rtc-template>

	// ２次元の速度を初期化する
	m_Velocity2D_In.data.vx = 0.0;
	m_Velocity2D_In.data.vy = 0.0;
	m_Velocity2D_In.data.va = 0.0;

	// フリッパーのPWM指令を初期化する
	m_FlipperPwm_InWrap.InitData();

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Practice::onFinalize()
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Practice::onStartup(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Practice::onShutdown(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

RTC::ReturnCode_t RTC_Spider2020_Crawler_Practice::onActivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Practice::onDeactivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Practice::onExecute(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Practice::onAborting(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Practice::onError(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Practice::onReset(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Practice::onStateUpdate(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Practice::onRateChanged(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

bool RTC_Spider2020_Crawler_Practice::initializeSimulation(ControllerIO* io)
{
	int i = 0;

	if(io != nullptr)
	{
		Body* body = io->body();
		if(body != nullptr)
		{
			// リンクを取得する
			m_cnoid_Link[LINK_CHASSIS]			= body->link("CHASSIS");
			m_cnoid_Link[LINK_FR_FLIPPER]		= body->link("FR_FLIPPER");
			m_cnoid_Link[LINK_FL_FLIPPER]		= body->link("FL_FLIPPER");
			m_cnoid_Link[LINK_BR_FLIPPER]		= body->link("BR_FLIPPER");
			m_cnoid_Link[LINK_BL_FLIPPER]		= body->link("BL_FLIPPER");
			m_cnoid_Link[LINK_R_BELT]			= body->link("R_BELT");
			m_cnoid_Link[LINK_L_BELT]			= body->link("L_BELT");
			m_cnoid_Link[LINK_FR_SUB_BELT]		= body->link("FR_SUB_BELT");
			m_cnoid_Link[LINK_FL_SUB_BELT]		= body->link("FL_SUB_BELT");
			m_cnoid_Link[LINK_BR_SUB_BELT]		= body->link("BR_SUB_BELT");
			m_cnoid_Link[LINK_BL_SUB_BELT]		= body->link("BL_SUB_BELT");
			for(i = 0; i <= LINK_BL_FLIPPER; i++)
			{
				if(m_cnoid_Link[i] == nullptr)
				{
					return false;
				}
			}

			// 走行モードを判断する
			if((m_cnoid_Link[LINK_R_BELT] != nullptr) && (m_cnoid_Link[LINK_L_BELT] != nullptr))
			{
				// 無限軌道
				m_bPseudoContinuousTrack = true;

				for(i = LINK_R_BELT_SPROCKET; i <= LINK_BL_SUB_BELT_SPROCKET; i++)
				{
					m_cnoid_Link[i] = nullptr;
				}
			}
			else
			{
				// AGXクローラ
				m_bPseudoContinuousTrack = false;

				m_cnoid_Link[LINK_R_BELT_SPROCKET]			= body->link("R_BELT_SPROCKET");
				m_cnoid_Link[LINK_L_BELT_SPROCKET]			= body->link("L_BELT_SPROCKET");
				m_cnoid_Link[LINK_FR_SUB_BELT_SPROCKET]		= body->link("FR_SUB_BELT_SPROCKET");
				m_cnoid_Link[LINK_FL_SUB_BELT_SPROCKET]		= body->link("FL_SUB_BELT_SPROCKET");
				m_cnoid_Link[LINK_BR_SUB_BELT_SPROCKET]		= body->link("BR_SUB_BELT_SPROCKET");
				m_cnoid_Link[LINK_BL_SUB_BELT_SPROCKET]		= body->link("BL_SUB_BELT_SPROCKET");
				for(i = LINK_R_BELT_SPROCKET; i <= LINK_BL_SUB_BELT_SPROCKET; i++)
				{
					if(m_cnoid_Link[i] == nullptr)
					{
						return false;
					}
				}
			}

			// 作動モードを設定する
			m_cnoid_Link[LINK_FR_FLIPPER]->setActuationMode(Link::JOINT_TORQUE);
			m_cnoid_Link[LINK_FL_FLIPPER]->setActuationMode(Link::JOINT_TORQUE);
			m_cnoid_Link[LINK_BR_FLIPPER]->setActuationMode(Link::JOINT_TORQUE);
			m_cnoid_Link[LINK_BL_FLIPPER]->setActuationMode(Link::JOINT_TORQUE);
			if(m_bPseudoContinuousTrack)
			{
				m_cnoid_Link[LINK_R_BELT]->setActuationMode(Link::JOINT_SURFACE_VELOCITY);
				m_cnoid_Link[LINK_L_BELT]->setActuationMode(Link::JOINT_SURFACE_VELOCITY);
				m_cnoid_Link[LINK_FR_SUB_BELT]->setActuationMode(Link::JOINT_SURFACE_VELOCITY);
				m_cnoid_Link[LINK_FL_SUB_BELT]->setActuationMode(Link::JOINT_SURFACE_VELOCITY);
				m_cnoid_Link[LINK_BR_SUB_BELT]->setActuationMode(Link::JOINT_SURFACE_VELOCITY);
				m_cnoid_Link[LINK_BL_SUB_BELT]->setActuationMode(Link::JOINT_SURFACE_VELOCITY);
			}
			else
			{
				m_cnoid_Link[LINK_R_BELT_SPROCKET]->setActuationMode(Link::JOINT_VELOCITY);
				m_cnoid_Link[LINK_L_BELT_SPROCKET]->setActuationMode(Link::JOINT_VELOCITY);
				m_cnoid_Link[LINK_FR_SUB_BELT_SPROCKET]->setActuationMode(Link::JOINT_VELOCITY);
				m_cnoid_Link[LINK_FL_SUB_BELT_SPROCKET]->setActuationMode(Link::JOINT_VELOCITY);
				m_cnoid_Link[LINK_BR_SUB_BELT_SPROCKET]->setActuationMode(Link::JOINT_VELOCITY);
				m_cnoid_Link[LINK_BL_SUB_BELT_SPROCKET]->setActuationMode(Link::JOINT_VELOCITY);
			}
		}

		// 実行周期を取得する
		m_cnoid_TimeStep = io->timeStep();
	}

	return true;
}

void RTC_Spider2020_Crawler_Practice::inputFromSimulator()
{
}

void RTC_Spider2020_Crawler_Practice::outputToSimulator()
{
	// ２次元の速度をポートから読み込む
	ReadVelocity2D();

	// ２次元の速度をリンクに書き込む
	WriteVelocity2D();

	// フリッパーのPWM指令をポートから読み込む
	ReadFlipperPwm();

	// フリッパーのPWM指令をリンクに書き込む
	WriteFlipperPwm();
}

void RTC_Spider2020_Crawler_Practice::stopSimulation()
{
}

void RTC_Spider2020_Crawler_Practice::ReadVelocity2D(void)
{
	struct timeval ti = {0};

	// 現在の時刻を取得する
	gettimeofday(&ti, NULL);

	// ２次元の速度を処理する
	if(m_Velocity2D_InIn.isNew())
	{
		// 読み込み時刻を更新する
		m_stVelocity2DReadTime = ti;

		// 次のデータを読み込む
		m_Velocity2D_InIn.read();
	}
	else
	{
		if(m_FAILSAFE_SEC <= TIMEVAL_DIFF(ti,m_stVelocity2DReadTime))
		{
			// ２次元の速度の入力を初期化する(暴走回避)
			m_Velocity2D_In.data.vx = 0.0;
			m_Velocity2D_In.data.vy = 0.0;
			m_Velocity2D_In.data.va = 0.0;
		}
	}
}

void RTC_Spider2020_Crawler_Practice::WriteVelocity2D(void)
{
	double dVelocityR = 0.0;
	double dVelocityL = 0.0;

	// 右メインベルトの速度
	dVelocityR = (double)m_Velocity2D_In.data.vx + (m_Velocity2D_In.data.va*m_TURNING_RADIUS)/2.0;
	if(VELOCITY_MAX < fabs(dVelocityR))
	{
		if(0.0 < dVelocityR)
		{
			dVelocityR = VELOCITY_MAX;
		}
		else
		{
			dVelocityR = -VELOCITY_MAX;
		}
	}

	// 左メインベルトの速度
	dVelocityL = (double)m_Velocity2D_In.data.vx - (m_Velocity2D_In.data.va*m_TURNING_RADIUS)/2.0;
	if(VELOCITY_MAX < fabs(dVelocityL))
	{
		if(0.0 < dVelocityL)
		{
			dVelocityL = VELOCITY_MAX;
		}
		else
		{
			dVelocityL = -VELOCITY_MAX;
		}
	}

	if(m_bPseudoContinuousTrack)
	{
		m_cnoid_Link[LINK_R_BELT]->dq_target() = dVelocityR;
		m_cnoid_Link[LINK_L_BELT]->dq_target() = dVelocityL;
		m_cnoid_Link[LINK_FR_SUB_BELT]->dq_target() = dVelocityR;
		m_cnoid_Link[LINK_FL_SUB_BELT]->dq_target() = dVelocityL;
		m_cnoid_Link[LINK_BR_SUB_BELT]->dq_target() = dVelocityR;
		m_cnoid_Link[LINK_BL_SUB_BELT]->dq_target() = dVelocityL;
	}
	else
	{
		m_cnoid_Link[LINK_R_BELT_SPROCKET]->dq_target() = dVelocityR/m_WHEEL_RADIUS;
		m_cnoid_Link[LINK_L_BELT_SPROCKET]->dq_target() = dVelocityL/m_WHEEL_RADIUS;
		m_cnoid_Link[LINK_FR_SUB_BELT_SPROCKET]->dq_target() = dVelocityR/m_WHEEL_RADIUS;
		m_cnoid_Link[LINK_FL_SUB_BELT_SPROCKET]->dq_target() = dVelocityL/m_WHEEL_RADIUS;
		m_cnoid_Link[LINK_BR_SUB_BELT_SPROCKET]->dq_target() = dVelocityR/m_WHEEL_RADIUS;
		m_cnoid_Link[LINK_BL_SUB_BELT_SPROCKET]->dq_target() = dVelocityL/m_WHEEL_RADIUS;
	}
}

void RTC_Spider2020_Crawler_Practice::ReadFlipperPwm(void)
{
	struct timeval ti = {0};

	// 現在の時刻を取得する
	gettimeofday(&ti, NULL);

	// フリッパーのPWM指令を処理する
	if(m_FlipperPwm_InIn.isNew())
	{
		// 読み込み時刻を更新する
		m_stFlipperPwmReadTime = ti;

		// 次のデータを読み込む
		m_FlipperPwm_InIn.read();
	}
	else
	{
		if(m_FAILSAFE_SEC <= TIMEVAL_DIFF(ti,m_stFlipperPwmReadTime))
		{
			// フリッパーのPWM指令を初期化する(暴走回避)
			m_FlipperPwm_InWrap.InitData();
		}
	}
}

void RTC_Spider2020_Crawler_Practice::WriteFlipperPwm(void)
{
	long lFlipperPwmFR = 0;
	long lFlipperPwmFL = 0;
	long lFlipperPwmBR = 0;
	long lFlipperPwmBL = 0;

	// 右前方フリッパーのPWM
	lFlipperPwmFR = m_FlipperPwm_InWrap.GetFrontRightPwm();
	if(FLIPPER_PWM_MAX < labs(lFlipperPwmFR))
	{
		if(0 < lFlipperPwmFR)
		{
			lFlipperPwmFR = FLIPPER_PWM_MAX;
		}
		else
		{
			lFlipperPwmFR = -FLIPPER_PWM_MAX;
		}
	}

	// 左前方フリッパーのPWM
	lFlipperPwmFL = m_FlipperPwm_InWrap.GetFrontLeftPwm();
	if(FLIPPER_PWM_MAX < labs(lFlipperPwmFL))
	{
		if(0 < lFlipperPwmFL)
		{
			lFlipperPwmFL = FLIPPER_PWM_MAX;
		}
		else
		{
			lFlipperPwmFL = -FLIPPER_PWM_MAX;
		}
	}

	// 右後方フリッパーのPWM
	lFlipperPwmBR = m_FlipperPwm_InWrap.GetBackRightPwm();
	if(FLIPPER_PWM_MAX < labs(lFlipperPwmBR))
	{
		if(0 < lFlipperPwmBR)
		{
			lFlipperPwmBR = FLIPPER_PWM_MAX;
		}
		else
		{
			lFlipperPwmBR = -FLIPPER_PWM_MAX;
		}
	}

	// 左後方フリッパーのPWM
	lFlipperPwmBL = m_FlipperPwm_InWrap.GetBackLeftPwm();
	if(FLIPPER_PWM_MAX < labs(lFlipperPwmBL))
	{
		if(0 < lFlipperPwmBL)
		{
			lFlipperPwmBL = FLIPPER_PWM_MAX;
		}
		else
		{
			lFlipperPwmBL = -FLIPPER_PWM_MAX;
		}
	}

	FlipperPwm( JOINT_FR_FLIPPER, lFlipperPwmFR );
	FlipperPwm( JOINT_FL_FLIPPER, lFlipperPwmFL );
	FlipperPwm( JOINT_BR_FLIPPER, lFlipperPwmBR );
	FlipperPwm( JOINT_BL_FLIPPER, lFlipperPwmBL );
}

void RTC_Spider2020_Crawler_Practice::FlipperPwm(int iJointIndex, long lPwm)
{
	double dKp					= 1000.0;
	double dKd					= 10.0;
	double dMotorRpm			= 0.0;
	double dMotorVelocity		= 0.0;
	double dFlipperTorque		= 0.0;
	double q					= 0.0;
	double dq					= 0.0;
	double ref_dq				= 0.0;
	double u					= 0.0;
	Link* link = nullptr;

	if((0 <= iJointIndex) && (iJointIndex < JOINT_NUM))
	{
		link = m_cnoid_Link[LINK_FR_FLIPPER + iJointIndex];
	}
	if(link == nullptr)
	{
		return;
	}

	// モータのトルク勾配からPWM指令値に対応するトルクと回転速度を求め、
	// 回転速度から次の目標角度を計算して目標角度に対してPD制御する
	// モータスペック: RE 35 diameter 35mm, 90 Watt, 24 volt
	dMotorRpm			= (m_SUB_MOTOR_RPM/100.0)*labs(lPwm) - m_SUB_MOTOR_GRADIENT*m_SUB_MOTOR_TORQUE;
	dMotorVelocity		= ((dMotorRpm/60.0)*m_cnoid_TimeStep)*(2.0*M_PI);
	dFlipperTorque		= m_SUB_MOTOR_TORQUE*m_SUB_MOTOR_GEAR_RATIO;
	q					= link->q();
	dq					= link->dq();

	if(labs(lPwm) <= FLIPPER_PWM_MIN)
	{
		// 現状維持
	}
	else
	{
		if(0 < lPwm)
		{
			m_cnoid_MotorAngle[iJointIndex] += dMotorVelocity;
		}
		else
		{
			m_cnoid_MotorAngle[iJointIndex] -= dMotorVelocity;
		}
	}

	// 目標角度を求める
	m_cnoid_RefAngle[iJointIndex] = m_cnoid_MotorAngle[iJointIndex]/m_SUB_MOTOR_GEAR_RATIO;

	// 目標角度に対してPD制御する
	u = (m_cnoid_RefAngle[iJointIndex] - q)*dKp + (ref_dq - dq)*dKd;
	if(dFlipperTorque < fabs(u))
	{
		if(0.0 <= u)
		{
			u = dFlipperTorque;
		}
		else
		{
			u = -dFlipperTorque;
		}
	}

	// リンクにトルクを設定する
	link->u() = u;
}


extern "C"
{
	void RTC_Spider2020_Crawler_PracticeInit(RTC::Manager* manager)
	{
		coil::Properties profile(rtc_spider2020_crawler_practice_spec);
		manager->registerFactory(profile, RTC::Create<RTC_Spider2020_Crawler_Practice>, RTC::Delete<RTC_Spider2020_Crawler_Practice>);
	}
};
