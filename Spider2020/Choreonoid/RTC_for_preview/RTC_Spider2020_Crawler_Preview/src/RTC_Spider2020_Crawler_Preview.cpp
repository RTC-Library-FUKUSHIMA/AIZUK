// -*- C++ -*-
/*!
 * @file  RTC_Spider2020_Crawler_Preview.cpp
 * @brief Spider2020 コレオノイドモデルの台車プレビューRTC
 * @date $Date$
 *
 * $Id$
 */

#include "RTC_Spider2020_Crawler_Preview.h"

// Module specification
// <rtc-template block="module_spec">
static const char* rtc_spider2020_crawler_preview_spec[] =
{
	"implementation_id", "RTC_Spider2020_Crawler_Preview",
	"type_name",         "RTC_Spider2020_Crawler_Preview",
	"description",       "Spider2020 コレオノイドモデルの台車プレビューRTC",
	"version",           "1.0.0",
	"vendor",            "AIZUK",
	"category",          "Controller",
	"activity_type",     "PERIODIC",
	"kind",              "DataFlowComponent",
	"max_instance",      "1",
	"language",          "C++",
	"lang_type",         "compile",

	// Configuration variables
	"conf.default.CHASSIS_Z", "0.0081",

	// Widget
	"conf.__widget__.CHASSIS_Z", "text",

	// Constraints
	"conf.__type__.CHASSIS_Z", "double",

	""
};
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RTC_Spider2020_Crawler_Preview::RTC_Spider2020_Crawler_Preview(RTC::Manager* manager)
	// <rtc-template block="initializer">
	: BodyIoRTC(manager)
	, m_Pose3D_InIn("Pose3D_In", m_Pose3D_In)
	, m_FlipperAngle_InIn("FlipperAngle_In", m_FlipperAngle_In)

	// </rtc-template>
	, m_FlipperAngle_InWrap(m_FlipperAngle_In)
{
}

/*!
 * @brief destructor
 */
RTC_Spider2020_Crawler_Preview::~RTC_Spider2020_Crawler_Preview()
{
}

RTC::ReturnCode_t RTC_Spider2020_Crawler_Preview::onInitialize(Body* body)
{
	// Registration: InPort/OutPort/Service
	// <rtc-template block="registration">
	// Set InPort buffers
	addInPort("Pose3D_In", m_Pose3D_InIn);
	addInPort("FlipperAngle_In", m_FlipperAngle_InIn);

	// Set OutPort buffer

	// Set service provider to Ports

	// Set service consumers to Ports

	// Set CORBA Service Ports

	// </rtc-template>

	// <rtc-template block="bind_config">
	// Bind variables and configuration variable
	bindParameter("CHASSIS_Z", m_CHASSIS_Z, "0.0081");
	// </rtc-template>

	// ３次元の位置・姿勢を初期化する
	m_Pose3D_In.data.position.x = 0.0;
	m_Pose3D_In.data.position.y = 0.0;
	m_Pose3D_In.data.position.z = 0.0;
	m_Pose3D_In.data.orientation.r = 0.0;
	m_Pose3D_In.data.orientation.p = 0.0;
	m_Pose3D_In.data.orientation.y = 0.0;

	// フリッパーの角度を初期化する
	m_FlipperAngle_InWrap.InitData();

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Preview::onFinalize()
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Preview::onStartup(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Preview::onShutdown(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Preview::onActivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Preview::onDeactivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Preview::onExecute(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Preview::onAborting(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Preview::onError(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Preview::onReset(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Preview::onStateUpdate(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler_Preview::onRateChanged(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

bool RTC_Spider2020_Crawler_Preview::initializeSimulation(ControllerIO* io)
{
	int i = 0;

	if(io != nullptr)
	{
		Body* body = io->body();
		if(body != nullptr)
		{
			// コレオノイドモデルのリンクを取得
			m_cnoid_Link[LINK_CHASSIS]			= body->link("CHASSIS");
			m_cnoid_Link[LINK_FR_FLIPPER]		= body->link("FR_FLIPPER");
			m_cnoid_Link[LINK_FL_FLIPPER]		= body->link("FL_FLIPPER");
			m_cnoid_Link[LINK_BR_FLIPPER]		= body->link("BR_FLIPPER");
			m_cnoid_Link[LINK_BL_FLIPPER]		= body->link("BL_FLIPPER");
			for(i = 0; i < LINK_NUM; i++)
			{
				if(m_cnoid_Link[i] == nullptr)
				{
					return false;
				}
			}

			// 作動モードを設定
			m_cnoid_Link[LINK_CHASSIS]->setActuationMode(Link::LINK_POSITION);
			m_cnoid_Link[LINK_FR_FLIPPER]->setActuationMode(Link::JOINT_ANGLE);
			m_cnoid_Link[LINK_FL_FLIPPER]->setActuationMode(Link::JOINT_ANGLE);
			m_cnoid_Link[LINK_BR_FLIPPER]->setActuationMode(Link::JOINT_ANGLE);
			m_cnoid_Link[LINK_BL_FLIPPER]->setActuationMode(Link::JOINT_ANGLE);
		}
	}

	return true;
}


void RTC_Spider2020_Crawler_Preview::inputFromSimulator()
{
}

void RTC_Spider2020_Crawler_Preview::outputToSimulator()
{
	// ３次元の位置・姿勢の入力を処理する
	if(m_Pose3D_InIn.isNew())
	{
		// 次のデータを読み込む
		m_Pose3D_InIn.read();

		Vector3 T = Vector3(m_Pose3D_In.data.position.x, m_Pose3D_In.data.position.y, m_Pose3D_In.data.position.z);
		Matrix3 R = rotFromRpy(m_Pose3D_In.data.orientation.r, m_Pose3D_In.data.orientation.p, m_Pose3D_In.data.orientation.y);

		// コレオノイドモデルのシャーシは地面より高い位置にあるので、入力された位置・姿勢にその高さを加味し、表示座標を合わせる
		T += R*Vector3(0, 0, m_CHASSIS_Z);
		m_cnoid_Link[LINK_CHASSIS]->setTranslation(T);
		m_cnoid_Link[LINK_CHASSIS]->setRotation(R);
	}

	// サブクローラの角度の入力を処理する
	if(m_FlipperAngle_InIn.isNew())
	{
		// 次のデータを読み込む
		m_FlipperAngle_InIn.read();

		m_cnoid_Link[LINK_FR_FLIPPER]->q_target() = m_FlipperAngle_InWrap.GetFrontRightAngle();
		m_cnoid_Link[LINK_FL_FLIPPER]->q_target() = m_FlipperAngle_InWrap.GetFrontLeftAngle();
		m_cnoid_Link[LINK_BR_FLIPPER]->q_target() = m_FlipperAngle_InWrap.GetBackRightAngle();
		m_cnoid_Link[LINK_BL_FLIPPER]->q_target() = m_FlipperAngle_InWrap.GetBackLeftAngle();
	}
}

void RTC_Spider2020_Crawler_Preview::stopSimulation()
{
}


extern "C"
{
	void RTC_Spider2020_Crawler_PreviewInit(RTC::Manager* manager)
	{
		coil::Properties profile(rtc_spider2020_crawler_preview_spec);
		manager->registerFactory(profile, RTC::Create<RTC_Spider2020_Crawler_Preview>, RTC::Delete<RTC_Spider2020_Crawler_Preview>);
	}
};
