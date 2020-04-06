// -*- C++ -*-
/*!
 * @file  RTC_Single_Jaco2_Practice.cpp
 * @brief Spider2020 コレオノイドモデルのJaco2アーム制御RTC
 * @date $Date$
 *
 * $Id$
 */

#include "RTC_Single_Jaco2_Practice.h"

// 手先位置姿勢の変位ゲイン ※AGX Dynamics 200Hz環境においてJaco2実機と似た速度になる値に調整(仕様値ではない)
#define TRANSLATION_X_GAIN	(0.05)
#define TRANSLATION_Y_GAIN	(0.05)
#define TRANSLATION_Z_GAIN	(0.05)
#define ROTATION_R_GAIN		(0.05)
#define ROTATION_P_GAIN		(0.05)
#define ROTATION_Y_GAIN		(0.05)
#define FINGER1_GAIN		(0.1)
#define FINGER2_GAIN		(0.1)
#define FINGER3_GAIN		(0.1)
#define ARM_GAIN			(0.05)

#define FINGER_ANGLE_MIN		(radian(0.0))
#define FINGER_ANGLE_MAX		(radian(80.0))
#define FINGER_UNIT_TO_ANGLE(x)	(radian((FINGER_ANGLE_MAX/6800.0)*(x)))
#define FINGER_ANGLE_ADJUST(x)	\
	((x) < FINGER_ANGLE_MIN) ? FINGER_ANGLE_MIN : \
	((FINGER_ANGLE_MAX < (x)) ? FINGER_ANGLE_MAX : (x) )

// timeval構造体の差を計算する(x1-x2)
#define TIMEVAL_DIFF(x1,x2)	(((double)x1.tv_sec + (double)x1.tv_usec/1000000.0) - ((double)x2.tv_sec + (double)x2.tv_usec/1000000.0))

// Module specification
// <rtc-template block="module_spec">
static const char* rtc_single_jaco2_practice_spec[] =
{
	"implementation_id", "RTC_Single_Jaco2_Practice",
	"type_name",         "RTC_Single_Jaco2_Practice",
	"description",       "Spider2020 コレオノイドモデルのJaco2アーム制御RTC",
	"version",           "1.0.0",
	"vendor",            "AIZUK",
	"category",          "Controller",
	"activity_type",     "PERIODIC",
	"kind",              "DataFlowComponent",
	"max_instance",      "1",
	"language",          "C++",
	"lang_type",         "compile",
	""
};
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RTC_Single_Jaco2_Practice::RTC_Single_Jaco2_Practice(RTC::Manager* manager)
	// <rtc-template block="initializer">
	: BodyIoRTC(manager)
	, m_PoseDelta_InIn("PoseDelta_In", m_PoseDelta_In)
	, m_FingerDelta_InIn("FingerDelta_In", m_FingerDelta_In)
	, m_Home_InIn("Home_In", m_Home_In)

	// </rtc-template>
	, m_FingerDelta_InWrap(m_FingerDelta_In)
	, m_stPoseDeltaReadTime({0})
	, m_stFingerDeltaReadTime({0})
{
}

/*!
 * @brief destructor
 */
RTC_Single_Jaco2_Practice::~RTC_Single_Jaco2_Practice()
{
}

RTC::ReturnCode_t RTC_Single_Jaco2_Practice::onInitialize(Body* body)
{
	// Registration: InPort/OutPort/Service
	// <rtc-template block="registration">
	// Set InPort buffers
	addInPort("PoseDelta_In", m_PoseDelta_InIn);
	addInPort("FingerDelta_In", m_FingerDelta_InIn);
	addInPort("Home_In", m_Home_InIn);

	// Set OutPort buffer

	// Set service provider to Ports

	// Set service consumers to Ports

	// Set CORBA Service Ports

	// </rtc-template>

	// <rtc-template block="bind_config">
	// </rtc-template>

	// 手先位置姿勢の変位速度の入力を初期化する
	m_PoseDelta_In.data.position.x = 0.0;
	m_PoseDelta_In.data.position.y = 0.0;
	m_PoseDelta_In.data.position.z = 0.0;
	m_PoseDelta_In.data.orientation.r = 0.0;
	m_PoseDelta_In.data.orientation.p = 0.0;
	m_PoseDelta_In.data.orientation.y = 0.0;

	// 指の開閉具合の変位速度の入力を初期化する
	m_FingerDelta_InWrap.InitData();

	// 初期姿勢遷移指令の入力を初期化する
	m_Home_In.data = 0;

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Practice::onFinalize()
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Practice::onStartup(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Practice::onShutdown(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Practice::onActivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Practice::onDeactivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Practice::onExecute(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Practice::onAborting(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Practice::onError(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Practice::onReset(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Practice::onStateUpdate(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Practice::onRateChanged(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

bool RTC_Single_Jaco2_Practice::initializeSimulation(ControllerIO* io)
{
	int i = 0;

	if( io != NULL )
	{
		Body* body = io->body();
		if( body != NULL )
		{
			// リンクを取得する
			m_cnoid_Link[LINK_BASE]			= body->link( "BASE" );
			m_cnoid_Link[LINK_SHOULDER]		= body->link( "SHOULDER" );
			m_cnoid_Link[LINK_ARM]			= body->link( "ARM" );
			m_cnoid_Link[LINK_FOREARM]		= body->link( "FOREARM" );
			m_cnoid_Link[LINK_WRIST1]		= body->link( "WRIST1" );
			m_cnoid_Link[LINK_WRIST2]		= body->link( "WRIST2" );
			m_cnoid_Link[LINK_HAND]			= body->link( "HAND" );
			m_cnoid_Link[LINK_END_EFFECTOR]	= body->link( "END_EFFECTOR" );
			m_cnoid_Link[LINK_FINGER1]		= body->link( "FINGER1" );
			m_cnoid_Link[LINK_FINGER2]		= body->link( "FINGER2" );
			m_cnoid_Link[LINK_FINGER3]		= body->link( "FINGER3" );
			for( i = 0; i < LINK_NUM; i++ )
			{
				if( m_cnoid_Link[i] == NULL )
				{
					return false;
				}
			}

			// 逆キネの処理クラスを生成する
			m_BaseToEndEffector = getCustomJointPath(body, m_cnoid_Link[LINK_BASE], m_cnoid_Link[LINK_END_EFFECTOR]);
			if( m_BaseToEndEffector == NULL )
			{
				return false;
			}

			// set actuation mode
			m_cnoid_Link[LINK_SHOULDER]->setActuationMode( Link::JOINT_ANGLE );
			m_cnoid_Link[LINK_ARM]->setActuationMode( Link::JOINT_ANGLE );
			m_cnoid_Link[LINK_FOREARM]->setActuationMode( Link::JOINT_ANGLE );
			m_cnoid_Link[LINK_WRIST1]->setActuationMode( Link::JOINT_ANGLE );
			m_cnoid_Link[LINK_WRIST2]->setActuationMode( Link::JOINT_ANGLE );
			m_cnoid_Link[LINK_HAND]->setActuationMode( Link::JOINT_ANGLE );
			m_cnoid_Link[LINK_FINGER1]->setActuationMode( Link::JOINT_ANGLE );
			m_cnoid_Link[LINK_FINGER2]->setActuationMode( Link::JOINT_ANGLE );
			m_cnoid_Link[LINK_FINGER3]->setActuationMode( Link::JOINT_ANGLE );
		}

		// 実行周期を取得する
		m_cnoid_TimeStep = io->timeStep();
	}

	return true;
}

void RTC_Single_Jaco2_Practice::inputFromSimulator()
{
}

void RTC_Single_Jaco2_Practice::outputToSimulator()
{
	int i = 0;

	// 手先位置姿勢の変位速度をポートから読み込む
	ReadPoseDelta();

	// 指の開閉具合の変位速度をポートから読み込む
	ReadFingerDelta();

	// 初期姿勢遷移指令をポートから読み込む
	ReadHome();

	// ホーム姿勢指令ありならば、ホーム姿勢に移行する
	if(m_Home_In.data == 1)
	{
		// 腕をホーム位置に移動する
		setArmAngle(m_cnoid_Link[LINK_SHOULDER], radian(276));
		setArmAngle(m_cnoid_Link[LINK_ARM],		 radian(168));
		setArmAngle(m_cnoid_Link[LINK_FOREARM],	 radian(58));
		setArmAngle(m_cnoid_Link[LINK_WRIST1],	 radian(241));
		setArmAngle(m_cnoid_Link[LINK_WRIST2],	 radian(83));
		setArmAngle(m_cnoid_Link[LINK_HAND],	 radian(76));
	}
	// ホーム姿勢指令なしならば、変位指令を処理する
	else
	{
		Vector3d DeltaP = Vector3d(
			m_PoseDelta_In.data.position.x*TRANSLATION_X_GAIN,
			m_PoseDelta_In.data.position.y*TRANSLATION_Y_GAIN,
			m_PoseDelta_In.data.position.z*TRANSLATION_Z_GAIN
		);
		Vector3d DeltaR = Vector3d(
			m_PoseDelta_In.data.orientation.r*ROTATION_R_GAIN,
			m_PoseDelta_In.data.orientation.p*ROTATION_P_GAIN,
			m_PoseDelta_In.data.orientation.y*ROTATION_Y_GAIN
		);
		Vector3d EndEffectorP = m_cnoid_Link[LINK_END_EFFECTOR]->p();
		Matrix3d EndEffectorR = m_cnoid_Link[LINK_END_EFFECTOR]->R();

		// Jaco2アームのローカル座標系のXYZの変位をワールド座標系のXYZの変位に変換する
		DeltaP = m_cnoid_Link[LINK_BASE]->attitude()*DeltaP;

		// ワールド座標系のXYZの変位を目標座標としてEND EFFECTORの位置に加える
		EndEffectorP += DeltaP;

		// Jaco2アームのローカル座標系のRPYの変位をワールド座標系のRPYの変位に変換する
		DeltaR = m_cnoid_Link[LINK_END_EFFECTOR]->attitude()*DeltaR;

		// ワールド座標系のRPYの変位を目標姿勢としてEND EFFECTORの姿勢に加える
		EndEffectorR = rotFromRpy(DeltaR)*EndEffectorR;

		// HANDリンクを目標位置姿勢にするための各関節の角度を計算する
		if(m_BaseToEndEffector->calcInverseKinematics(EndEffectorP, EndEffectorR))
		{
			// 計算角を目標角に設定する
			for(i = 0; i < m_BaseToEndEffector->numJoints(); i++)
			{
				m_BaseToEndEffector->joint(i)->q_target() = m_BaseToEndEffector->joint(i)->q();
			}
		}
		else
		{
			std::cout << "IK failed" << std::endl;
		}

		// 親指の目標角度を設定する
		m_cnoid_Link[LINK_FINGER1]->q_target()	= FINGER_ANGLE_ADJUST(m_cnoid_Link[LINK_FINGER1]->q()
												+ FINGER_UNIT_TO_ANGLE(m_FingerDelta_InWrap.GetThumbDelta())
												* FINGER1_GAIN);
		// 差指の目標角度を設定する
		m_cnoid_Link[LINK_FINGER2]->q_target()	= FINGER_ANGLE_ADJUST(m_cnoid_Link[LINK_FINGER2]->q()
												+ FINGER_UNIT_TO_ANGLE(m_FingerDelta_InWrap.GetIndexFingerDelta())
												* FINGER2_GAIN);
		// 中指の目標角度を設定する
		m_cnoid_Link[LINK_FINGER3]->q_target()	= FINGER_ANGLE_ADJUST(m_cnoid_Link[LINK_FINGER3]->q()
												+ FINGER_UNIT_TO_ANGLE(m_FingerDelta_InWrap.GetMiddleFingerDelta())
												* FINGER3_GAIN);
	}
}

void RTC_Single_Jaco2_Practice::stopSimulation()
{
}

void RTC_Single_Jaco2_Practice::setArmAngle(Link* link, double angle)
{
	double dDiff = angle - link->q();
	double dTarget = 0.0;

	// 1周期の変位をリンクの最大角速度に収める
	if(0 < dDiff)
	{
		if((link->dq_upper()*ARM_GAIN) < dDiff)
		{
			dDiff = link->dq_upper()*ARM_GAIN;
		}
	}
	else
	{
		if(dDiff < (link->dq_lower()*ARM_GAIN))
		{
			dDiff = link->dq_lower()*ARM_GAIN;
		}
	}

	// 目標角を算出する
	dTarget = link->q() + dDiff;

	// 目標角を最大最小角に収める
	if(link->q_upper() < dTarget)
	{
		dTarget = link->q_upper();
	}
	else if(dTarget < link->q_lower())
	{
		dTarget = link->q_lower();
	}

	// 目標角を設定する
	link->q_target() = dTarget;
}

void RTC_Single_Jaco2_Practice::setFingerAngle(Link* link, long delta)
{
	double dDiff = FINGER_UNIT_TO_ANGLE(delta);

	// 1周期の変位をリンクの最大角速度に収める
	if(0 < dDiff)
	{
		if((link->dq_upper()*m_cnoid_TimeStep) < dDiff)
		{
			dDiff = link->dq_upper()*m_cnoid_TimeStep;
		}
	}
	else
	{
		if(dDiff < (link->dq_lower()*m_cnoid_TimeStep))
		{
			dDiff = link->dq_lower()*m_cnoid_TimeStep;
		}
	}

	// 目標角を設定する
	link->q_target() = FINGER_ANGLE_ADJUST(link->q() + dDiff);
}

void RTC_Single_Jaco2_Practice::ReadPoseDelta(void)
{
	struct timeval ti = {0};

	// 現在の時刻を取得する
	gettimeofday(&ti, NULL);

	// 手先位置姿勢の変位速度を更新する
	if(m_PoseDelta_InIn.isNew())
	{
		// 読み込み時刻を更新する
		m_stPoseDeltaReadTime = ti;

		// 次のデータを読み込む
		m_PoseDelta_InIn.read();
	}
	else
	{
		if(m_FAILSAFE_SEC <= TIMEVAL_DIFF(ti,m_stPoseDeltaReadTime))
		{
			// 手先位置姿勢の変位速度の入力を初期化する(暴走回避)
			m_PoseDelta_In.data.position.x = 0.0;
			m_PoseDelta_In.data.position.y = 0.0;
			m_PoseDelta_In.data.position.z = 0.0;
			m_PoseDelta_In.data.orientation.r = 0.0;
			m_PoseDelta_In.data.orientation.p = 0.0;
			m_PoseDelta_In.data.orientation.y = 0.0;
		}
	}
}

void RTC_Single_Jaco2_Practice::ReadFingerDelta(void)
{
	struct timeval ti = {0};

	// 現在の時刻を取得する
	gettimeofday(&ti, NULL);

	// 指の開閉具合の変位速度を更新する
	if(m_FingerDelta_InIn.isNew())
	{
		// 読み込み時刻を更新する
		m_stFingerDeltaReadTime = ti;

		// 次のデータを読み込む
		m_FingerDelta_InIn.read();
	}
	else
	{
		if(m_FAILSAFE_SEC <= TIMEVAL_DIFF(ti,m_stFingerDeltaReadTime))
		{
			// 指の開閉具合の変位速度の入力を初期化する(暴走回避)
			m_FingerDelta_InWrap.InitData();
		}
	}
}

void RTC_Single_Jaco2_Practice::ReadHome(void)
{
	// 初期姿勢遷移指令を更新する
	if(m_Home_InIn.isNew())
	{
		// 次のデータを読み込む
		m_Home_InIn.read();
	}
}


extern "C"
{
	void RTC_Single_Jaco2_PracticeInit(RTC::Manager* manager)
	{
		coil::Properties profile(rtc_single_jaco2_practice_spec);
		manager->registerFactory(
			profile, RTC::Create<RTC_Single_Jaco2_Practice>, RTC::Delete<RTC_Single_Jaco2_Practice>);
	}
};
