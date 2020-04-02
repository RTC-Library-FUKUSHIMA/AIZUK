// -*- C++ -*-
/*!
 * @file  RTC_Enatec_Battery.cpp
 * @brief エナテック製バッテリの情報取得RTC
 * @date $Date$
 *
 * $Id$
 */

#include "RTC_Enatec_Battery.h"

// Module specification
// <rtc-template block="module_spec">
static const char* rtc_enatec_battery_spec[] =
{
	"implementation_id", "RTC_Enatec_Battery",
	"type_name",         "RTC_Enatec_Battery",
	"description",       "エナテック製バッテリの情報取得RTC",
	"version",           "1.0.0",
	"vendor",            "AIZUK",
	"category",          "Controller",
	"activity_type",     "PERIODIC",
	"kind",              "DataFlowComponent",
	"max_instance",      "1",
	"language",          "C++",
	"lang_type",         "compile",

	// Configuration variables
	"conf.default.DEVICE_NAME", "/dev/ttyUSB3",

	// Widget
	"conf.__widget__.DEVICE_NAME", "text",

	// Constraints
	"conf.__type__.DEVICE_NAME", "string",

	""
};
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RTC_Enatec_Battery::RTC_Enatec_Battery(RTC::Manager* manager)
	// <rtc-template block="initializer">
	: RTC::DataFlowComponentBase(manager)
	, m_CapacityRatio_OutOut("CapacityRatio_Out", m_CapacityRatio_Out)

	// </rtc-template>
{
}

/*!
 * @brief destructor
 */
RTC_Enatec_Battery::~RTC_Enatec_Battery()
{
}

RTC::ReturnCode_t RTC_Enatec_Battery::onInitialize()
{
	// Registration: InPort/OutPort/Service
	// <rtc-template block="registration">
	// Set InPort buffers

	// Set OutPort buffer
	addOutPort("CapacityRatio_Out", m_CapacityRatio_OutOut);

	// Set service provider to Ports

	// Set service consumers to Ports

	// Set CORBA Service Ports

	// </rtc-template>

	// <rtc-template block="bind_config">
	// Bind variables and configuration variable
	bindParameter("DEVICE_NAME", m_DEVICE_NAME, "/dev/ttyUSB3");
	// </rtc-template>

	// バッテリ残存容量比を初期化する
	m_CapacityRatio_Out.data = -1.0;

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_Enatec_Battery::onFinalize()
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Enatec_Battery::onStartup(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Enatec_Battery::onShutdown(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Enatec_Battery::onActivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Enatec_Battery::onDeactivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

RTC::ReturnCode_t RTC_Enatec_Battery::onExecute(RTC::UniqueId ec_id)
{
	EnatecBatteryCapture oEnatecBattery;
	bool bIsOpen = false;

	// デバイスをオープンする
	bIsOpen = oEnatecBattery.Open(m_DEVICE_NAME);
	if(bIsOpen)
	{
		// バッテリ残存容量比を更新する
		m_CapacityRatio_Out.data = (double)((int8_t)oEnatecBattery.GetCapacityRatio());

		// デバイスをクローズする
		oEnatecBattery.Close();
	}
	else
	{
		// バッテリ残存容量比を初期化する
		m_CapacityRatio_Out.data = -1.0;
	}

	// バッテリ残存容量比をポートに出力する
	setTimestamp(m_CapacityRatio_Out);
	m_CapacityRatio_OutOut.write();

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_Enatec_Battery::onAborting(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Enatec_Battery::onError(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Enatec_Battery::onReset(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Enatec_Battery::onStateUpdate(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Enatec_Battery::onRateChanged(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/


extern "C"
{
	void RTC_Enatec_BatteryInit(RTC::Manager* manager)
	{
		coil::Properties profile(rtc_enatec_battery_spec);
		manager->registerFactory(profile, RTC::Create<RTC_Enatec_Battery>, RTC::Delete<RTC_Enatec_Battery>);
	}
};
