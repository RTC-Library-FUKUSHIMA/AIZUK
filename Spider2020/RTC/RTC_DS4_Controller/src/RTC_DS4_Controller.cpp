// -*- C++ -*-
/*!
 * @file  RTC_DS4_Controller.cpp
 * @brief DualShock4コントローラの情報を取得する
 * @date 2019/04/05
 *
 * $Id$
 */

#include "RTC_DS4_Controller.h"

// Module specification
// <rtc-template block="module_spec">
static const char* rtc_ds4_controller_spec[] =
{
	"implementation_id", "RTC_DS4_Controller",
	"type_name",         "RTC_DS4_Controller",
	"description",       "DualShock4コントローラの情報を取得する",
	"version",           "1.0.0",
	"vendor",            "AIZUK",
	"category",          "Controller",
	"activity_type",     "PERIODIC",
	"kind",              "DataFlowComponent",
	"max_instance",      "1",
	"language",          "C++",
	"lang_type",         "compile",

	// Configuration variables
	"conf.default.DEVICE_NAME", "/dev/input/js0",
	"conf.default.USE_ERROR_STATE", "1",

	// Widget
	"conf.__widget__.DEVICE_NAME", "text",
	"conf.__widget__.USE_ERROR_STATE", "text",

	// Constraints
	"conf.__type__.DEVICE_NAME", "string",
	"conf.__type__.USE_ERROR_STATE", "long",

	""
};
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RTC_DS4_Controller::RTC_DS4_Controller(RTC::Manager* manager)
	// <rtc-template block="initializer">
	: RTC::DataFlowComponentBase(manager)
	,m_Axis_OutOut("Axis_Out", m_Axis_Out)
	,m_Button_OutOut("Button_Out", m_Button_Out)
	,m_CapacityRatio_OutOut("CapacityRatio_Out", m_CapacityRatio_Out)

	// </rtc-template>
	, m_Axis_OutWrap(m_Axis_Out)
	, m_Button_OutWrap(m_Button_Out)
{
}

/*!
 * @brief destructor
 */
RTC_DS4_Controller::~RTC_DS4_Controller()
{
}

RTC::ReturnCode_t RTC_DS4_Controller::onInitialize()
{
	// Registration: InPort/OutPort/Service
	// <rtc-template block="registration">
	// Set InPort buffers

	// Set OutPort buffer
	addOutPort("Axis_Out", m_Axis_OutOut);
	addOutPort("Button_Out", m_Button_OutOut);
	addOutPort("CapacityRatio_Out", m_CapacityRatio_OutOut);

	// Set service provider to Ports

	// Set service consumers to Ports

	// Set CORBA Service Ports

	// </rtc-template>

	// <rtc-template block="bind_config">
	// Bind variables and configuration variable
	bindParameter("DEVICE_NAME", m_DEVICE_NAME, "/dev/input/js0");
	bindParameter("USE_ERROR_STATE", m_USE_ERROR_STATE, "1");
	// </rtc-template>

	// 軸キーの入力具合を初期化する
	m_Axis_OutWrap.InitData();

	// ボタンの押下状態を初期化する
	m_Button_OutWrap.InitData();

	// バッテリ残存容量比を初期化する
	m_CapacityRatio_Out.data = -1.0;

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_DS4_Controller::onFinalize()
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_DS4_Controller::onStartup(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_DS4_Controller::onShutdown(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

RTC::ReturnCode_t RTC_DS4_Controller::onActivated(RTC::UniqueId ec_id)
{
	// キー入力の取得処理を開始する
	m_DS4Capture.Start(m_DEVICE_NAME);

	return RTC::RTC_OK;
}

RTC::ReturnCode_t RTC_DS4_Controller::onDeactivated(RTC::UniqueId ec_id)
{
	// キー入力の取得処理を終了する
	m_DS4Capture.Stop();

	return RTC::RTC_OK;
}

RTC::ReturnCode_t RTC_DS4_Controller::onExecute(RTC::UniqueId ec_id)
{
	// キー入力の取得の可否をチェックする
	if(!m_DS4Capture.IsValid())
	{
		// エラー状態を使用する場合、キー入力の取得不可でエラーを返す
		if(m_USE_ERROR_STATE)
		{
			return RTC::RTC_ERROR;
		}
		// エラー状態を使用しない場合、キー入力の取得不可でデバイスへの再接続を試みる
		else
		{
			// キー入力の取得処理を終了する
			m_DS4Capture.Stop();

			// キー入力の取得処理を開始する
			m_DS4Capture.Start(m_DEVICE_NAME);
		}
	}

	// 軸キーの入力具合を更新する
	m_Axis_OutWrap.SetDirVertical(m_DS4Capture.GetDirVerticalAxisValue() / 32767.0);
	m_Axis_OutWrap.SetDirHorizontal(m_DS4Capture.GetDirHorizontalAxisValue() / 32767.0);
	m_Axis_OutWrap.SetLStickVertical(m_DS4Capture.GetLStickVerticalAxisValue() / 32767.0);
	m_Axis_OutWrap.SetLStickHorizontal(m_DS4Capture.GetLStickHorizontalAxisValue() / 32767.0);
	m_Axis_OutWrap.SetRStickVertical(m_DS4Capture.GetRStickVerticalAxisValue() / 32767.0);
	m_Axis_OutWrap.SetRStickHorizontal(m_DS4Capture.GetRStickHorizontalAxisValue() / 32767.0);
	m_Axis_OutWrap.SetL2(m_DS4Capture.GetL2AxisValue() / 32767.0);
	m_Axis_OutWrap.SetR2(m_DS4Capture.GetR2AxisValue() / 32767.0);

	// 軸キーの入力具合をポートに出力する
	m_Axis_OutWrap.SetTimestamp();
	m_Axis_OutOut.write();

	// ボタンの押下状態を更新する
	m_Button_OutWrap.SetSquare(m_DS4Capture.GetSquareButtonValue());
	m_Button_OutWrap.SetCross(m_DS4Capture.GetCrossButtonValue());
	m_Button_OutWrap.SetCircle(m_DS4Capture.GetCircleButtonValue());
	m_Button_OutWrap.SetTriangle(m_DS4Capture.GetTriangleButtonValue());
	m_Button_OutWrap.SetL1(m_DS4Capture.GetL1ButtonValue());
	m_Button_OutWrap.SetR1(m_DS4Capture.GetR1ButtonValue());
	m_Button_OutWrap.SetL2(m_DS4Capture.GetL2ButtonValue());
	m_Button_OutWrap.SetR2(m_DS4Capture.GetR2ButtonValue());
	m_Button_OutWrap.SetShare(m_DS4Capture.GetShareButtonValue());
	m_Button_OutWrap.SetOptions(m_DS4Capture.GetOptionsButtonValue());
	m_Button_OutWrap.SetL3(m_DS4Capture.GetL3ButtonValue());
	m_Button_OutWrap.SetR3(m_DS4Capture.GetR3ButtonValue());
	m_Button_OutWrap.SetPS(m_DS4Capture.GetPSButtonValue());
	m_Button_OutWrap.SetTouch(m_DS4Capture.GetTouchButtonValue());

	// ボタンの押下状態をポートに出力する
	m_Button_OutWrap.SetTimestamp();
	m_Button_OutOut.write();

	// バッテリ残容量比を更新する
	m_CapacityRatio_Out.data = (double)((int8_t)m_DS4Capture.GetCapacityRatio());

	// バッテリ残存容量比をポートに出力する
	setTimestamp(m_CapacityRatio_Out);
	m_CapacityRatio_OutOut.write();

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_DS4_Controller::onAborting(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

RTC::ReturnCode_t RTC_DS4_Controller::onError(RTC::UniqueId ec_id)
{
	// 軸キーの入力具合を初期化する
	m_Axis_OutWrap.InitData();

	// 軸キーの入力具合をポートに出力する
	m_Axis_OutWrap.SetTimestamp();
	m_Axis_OutOut.write();

	// ボタンの押下状態を初期化する
	m_Button_OutWrap.InitData();

	// ボタンの押下状態をポートに出力する
	m_Button_OutWrap.SetTimestamp();
	m_Button_OutOut.write();

	// バッテリ残存容量比を初期化する
	m_CapacityRatio_Out.data = -1.0;

	// バッテリ残存容量比をポートに出力する
	setTimestamp(m_CapacityRatio_Out);
	m_CapacityRatio_OutOut.write();

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_DS4_Controller::onReset(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_DS4_Controller::onStateUpdate(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_DS4_Controller::onRateChanged(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/


extern "C"
{
	void RTC_DS4_ControllerInit(RTC::Manager* manager)
	{
		coil::Properties profile(rtc_ds4_controller_spec);
		manager->registerFactory(profile, RTC::Create<RTC_DS4_Controller>, RTC::Delete<RTC_DS4_Controller>);
	}
};
