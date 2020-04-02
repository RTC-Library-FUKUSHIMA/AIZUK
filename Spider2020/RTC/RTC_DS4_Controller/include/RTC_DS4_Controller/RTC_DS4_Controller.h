// -*- C++ -*-
/*!
 * @file  RTC_DS4_Controller.h
 * @brief DualShock4コントローラの情報を取得する
 * @date  2019/04/05
 *
 * $Id$
 */

#ifndef RTC_DS4_CONTROLLER_H
#define RTC_DS4_CONTROLLER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "BasicDataTypeStub.h"

// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include "AxisWrapper.h"
#include "ButtonWrapper.h"
#include "DualShock4Capture.h"

using namespace RTC;

/*!
 * @class RTC_DS4_Controller
 * @brief DualShock4コントローラの情報を取得する
 *
 */
class RTC_DS4_Controller
  : public RTC::DataFlowComponentBase
{
public:
	/*!
	 * @brief constructor
	 * @param manager Maneger Object
	 */
	RTC_DS4_Controller(RTC::Manager* manager);

	/*!
	 * @brief destructor
	 */
	~RTC_DS4_Controller();

	// <rtc-template block="public_attribute">

	// </rtc-template>

	// <rtc-template block="public_operation">

	// </rtc-template>

	/***
	 *
	 * The initialize action (on CREATED->ALIVE transition)
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	virtual RTC::ReturnCode_t onInitialize();

	/***
	 *
	 * The finalize action (on ALIVE->END transition)
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	// virtual RTC::ReturnCode_t onFinalize();

	/***
	 *
	 * The startup action when ExecutionContext startup
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	// virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

	/***
	 *
	 * The shutdown action when ExecutionContext stop
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	// virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

	/***
	 *
	 * The activated action (Active state entry action)
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

	/***
	 *
	 * The deactivated action (Active state exit action)
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

	/***
	 *
	 * The execution action that is invoked periodically
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

	/***
	 *
	 * The aborting action when main logic error occurred.
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	// virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

	/***
	 *
	 * The error action in ERROR state
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

	/***
	 *
	 * The reset action that is invoked resetting
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	// virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);

	/***
	 *
	 * The state update action that is invoked after onExecute() action
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	// virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

	/***
	 *
	 * The action that is invoked when execution context's rate is changed
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	// virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


protected:
	// <rtc-template block="protected_attribute">

	// </rtc-template>

	// <rtc-template block="protected_operation">

	// </rtc-template>

	// Configuration variable declaration
	// <rtc-template block="config_declare">
	/*!
	 * DualShock4コントローラのデバイス名
	 * - Name: デバイス名 DEVICE_NAME
	 * - DefaultValue: /dev/input/js0
	 */
	std::string m_DEVICE_NAME;
	/*!
	 * 0:
	 * DualShock4コントローラの未接続検知でエラー状態に遷移しない。コ
	 * ントローラの再接続で復帰する。
	 * 1:
	 * DualShock4コントローラの未接続検知でエラー状態に遷移する。復帰
	 * にはリセットが必要。
	 * - Name: エラー状態の使用有無 USE_ERROR_STATE
	 * - DefaultValue: 1
	 */
	long int m_USE_ERROR_STATE;

	// </rtc-template>

	// DataInPort declaration
	// <rtc-template block="inport_declare">

	// </rtc-template>


	// DataOutPort declaration
	// <rtc-template block="outport_declare">
	RTC::TimedDoubleSeq m_Axis_Out;
	/*!
	 * DualShock4コントローラの軸キーの入力具合
	 * - Type: TimedDoubleSeq
	 */
	RTC::OutPort<RTC::TimedDoubleSeq> m_Axis_OutOut;
	RTC::TimedULong m_Button_Out;
	/*!
	 * DualShock4コントローラのボタンの押下状態
	 * - Type: TimedULong
	 */
	RTC::OutPort<RTC::TimedULong> m_Button_OutOut;
	RTC::TimedDouble m_CapacityRatio_Out;
	/*!
	 * DualShock4コントローラのバッテリ残容量比
	 * - Type: TimedDouble
	 * - Unit: [%]
	 */
	RTC::OutPort<RTC::TimedDouble> m_CapacityRatio_OutOut;

	// </rtc-template>

	// CORBA Port declaration
	// <rtc-template block="corbaport_declare">

	// </rtc-template>

	// Service declaration
	// <rtc-template block="service_declare">

	// </rtc-template>

	// Consumer declaration
	// <rtc-template block="consumer_declare">

	// </rtc-template>

private:
	// <rtc-template block="private_attribute">

	// </rtc-template>

	// <rtc-template block="private_operation">

	// </rtc-template>

	AxisWrapper m_Axis_OutWrap;			/*!< m_Axis_Outのラッパークラス			*/
	ButtonWrapper m_Button_OutWrap;		/*!< m_Button_Outのラッパークラス		*/

	DualShock4Capture m_DS4Capture;		/*!< DualShock4のキー入力の取得クラス	*/

};


extern "C"
{
	DLL_EXPORT void RTC_DS4_ControllerInit(RTC::Manager* manager);
};

#endif // RTC_DS4_CONTROLLER_H
