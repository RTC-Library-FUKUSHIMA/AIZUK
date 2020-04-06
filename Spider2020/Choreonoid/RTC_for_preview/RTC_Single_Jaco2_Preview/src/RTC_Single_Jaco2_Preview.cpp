// -*- C++ -*-
/*!
 * @file  RTC_Single_Jaco2_Preview.cpp
 * @brief Spider2020 コレオノイドモデルのJaco2アームプレビューRTC
 * @date $Date$
 *
 * $Id$
 */

#include "RTC_Single_Jaco2_Preview.h"

#define FINGER_ANGLE_MIN		(radian(0.0))
#define FINGER_ANGLE_MAX		(radian(80.0))
#define FINGER_UNIT_TO_ANGLE(x)	(radian((FINGER_ANGLE_MAX/6800.0)*(x)))
#define FINGER_ANGLE_ADJUST(x)	\
	((x) < FINGER_ANGLE_MIN) ? FINGER_ANGLE_MIN : \
	((FINGER_ANGLE_MAX < (x)) ? FINGER_ANGLE_MAX : (x) )

// Module specification
// <rtc-template block="module_spec">
static const char* rtc_single_jaco2_preview_spec[] =
{
	"implementation_id", "RTC_Single_Jaco2_Preview",
	"type_name",         "RTC_Single_Jaco2_Preview",
	"description",       "Spider2020 コレオノイドモデルのJaco2アームプレビューRTC",
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
RTC_Single_Jaco2_Preview::RTC_Single_Jaco2_Preview(RTC::Manager* manager)
	// <rtc-template block="initializer">
	: BodyIoRTC(manager)
	, m_Angular_InIn("Angular_In", m_Angular_In)
	, m_Finger_InIn("Finger_In", m_Finger_In)

	// </rtc-template>
	, m_Angular_InWrap(m_Angular_In)
	, m_Finger_InWrap(m_Finger_In)
{
}

/*!
 * @brief destructor
 */
RTC_Single_Jaco2_Preview::~RTC_Single_Jaco2_Preview()
{
}

RTC::ReturnCode_t RTC_Single_Jaco2_Preview::onInitialize(Body* body)
{
	// Registration: InPort/OutPort/Service
	// <rtc-template block="registration">
	// Set InPort buffers
	addInPort("Angular_In", m_Angular_InIn);
	addInPort("Finger_In", m_Finger_InIn);

	// Set OutPort buffer

	// Set service provider to Ports

	// Set service consumers to Ports

	// Set CORBA Service Ports

	// </rtc-template>

	// <rtc-template block="bind_config">
	// </rtc-template>

	// 腕の角度の入力を初期化する
	m_Angular_InWrap.InitData();

	// 指の開閉具合の入力を初期化する
	m_Finger_InWrap.InitData();

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Preview::onFinalize()
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Preview::onStartup(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Preview::onShutdown(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Preview::onActivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Preview::onDeactivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Preview::onExecute(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Preview::onAborting(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Preview::onError(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Preview::onReset(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Preview::onStateUpdate(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2_Preview::onRateChanged(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

bool RTC_Single_Jaco2_Preview::initializeSimulation(ControllerIO* io)
{
	int i = 0;

	if( io != NULL )
	{
		Body* body = io->body();
		if( body != NULL )
		{
			// コレオノイドモデルのリンクを取得
			m_cnoid_Link[LINK_SHOULDER]	= body->link( "SHOULDER" );
			m_cnoid_Link[LINK_ARM]		= body->link( "ARM" );
			m_cnoid_Link[LINK_FOREARM]	= body->link( "FOREARM" );
			m_cnoid_Link[LINK_WRIST1]	= body->link( "WRIST1" );
			m_cnoid_Link[LINK_WRIST2]	= body->link( "WRIST2" );
			m_cnoid_Link[LINK_HAND]		= body->link( "HAND" );
			m_cnoid_Link[LINK_FINGER1]	= body->link( "FINGER1" );
			m_cnoid_Link[LINK_FINGER2]	= body->link( "FINGER2" );
			m_cnoid_Link[LINK_FINGER3]	= body->link( "FINGER3" );
			for( i = 0; i < LINK_NUM; i++ )
			{
				if( m_cnoid_Link[i] == NULL )
				{
					return false;
				}
			}

			// 作動モードを設定
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
	}

	return true;
}

void RTC_Single_Jaco2_Preview::inputFromSimulator()
{
}

void RTC_Single_Jaco2_Preview::outputToSimulator()
{
	// 腕の角度の入力を処理する
	if(m_Angular_InIn.isNew())
	{
		// 次のデータを読み込む
		m_Angular_InIn.read();

		// 腕の各リンクに角度を設定する
		m_cnoid_Link[LINK_SHOULDER]->q_target() = m_Angular_InWrap.GetShoulderAngular();
		m_cnoid_Link[LINK_ARM]->q_target()		= m_Angular_InWrap.GetArmAngular();
		m_cnoid_Link[LINK_FOREARM]->q_target()	= m_Angular_InWrap.GetForearmAngular();
		m_cnoid_Link[LINK_WRIST1]->q_target()	= m_Angular_InWrap.GetWrist1Angular();
		m_cnoid_Link[LINK_WRIST2]->q_target()	= m_Angular_InWrap.GetWrist2Angular();
		m_cnoid_Link[LINK_HAND]->q_target()	 	= m_Angular_InWrap.GetHandAngular();
	}

	// 指の開閉具合の入力を処理する
	if(m_Finger_InIn.isNew())
	{
		// 次のデータを読み込む
		m_Finger_InIn.read();

		// 指の各リンクに角度を設定する
		m_cnoid_Link[LINK_FINGER1]->q_target() = FINGER_ANGLE_ADJUST(FINGER_UNIT_TO_ANGLE(m_Finger_InWrap.GetThumbStatus()));
		m_cnoid_Link[LINK_FINGER2]->q_target() = FINGER_ANGLE_ADJUST(FINGER_UNIT_TO_ANGLE(m_Finger_InWrap.GetIndexFingerStatus()));
		m_cnoid_Link[LINK_FINGER3]->q_target() = FINGER_ANGLE_ADJUST(FINGER_UNIT_TO_ANGLE(m_Finger_InWrap.GetMiddleFingerStatus()));
	}
}

void RTC_Single_Jaco2_Preview::stopSimulation()
{
}


extern "C"
{

	void RTC_Single_Jaco2_PreviewInit(RTC::Manager* manager)
	{
		coil::Properties profile(rtc_single_jaco2_preview_spec);
		manager->registerFactory(
			profile, RTC::Create<RTC_Single_Jaco2_Preview>, RTC::Delete<RTC_Single_Jaco2_Preview>);
	}

};
