// -*- C++ -*-
/*!
 * @file  RTC_Single_Jaco2_Preview.h
 * @brief Spider2020 コレオノイドモデルのJaco2アームプレビューRTC
 * @date  $Date$
 *
 * $Id$
 */

#ifndef RTC_SINGLE_JACO2_PREVIEW_H
#define RTC_SINGLE_JACO2_PREVIEW_H

#include <cnoid/BodyIoRTC>
#include <cnoid/EigenUtil>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "ExtendedDataTypesStub.h"
#include "BasicDataTypeStub.h"

// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include "ArmAngularWrapper.h"
#include "FingerStatusWrapper.h"

using namespace cnoid;

/*!
 * @enum 列挙子
 * リンクデータのインデクサ
 */
enum LINK_t
{
	LINK_SHOULDER,			/*!< SHOULDERリンク		*/
	LINK_ARM,				/*!< ARMリンク			*/
	LINK_FOREARM,			/*!< FOREARMリンク		*/
	LINK_WRIST1,			/*!< WRIST1リンク		*/
	LINK_WRIST2,			/*!< WRIST2リンク		*/
	LINK_HAND,				/*!< HANDリンク			*/
	LINK_FINGER1,			/*!< FINGER1リンク		*/
	LINK_FINGER2,			/*!< FINGER2リンク		*/
	LINK_FINGER3,			/*!< FINGER3リンク		*/
	LINK_NUM,
};

/*!
 * @class RTC_Single_Jaco2_Preview
 * @brief Spider2020 コレオノイドモデルのJaco2アームプレビューRTC
 *
 */
class RTC_Single_Jaco2_Preview
  : public BodyIoRTC
{
public:
	/*!
	 * @brief constructor
	 * @param manager Maneger Object
	 */
	RTC_Single_Jaco2_Preview(RTC::Manager* manager);

	/*!
	 * @brief destructor
	 */
	~RTC_Single_Jaco2_Preview();

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
	virtual RTC::ReturnCode_t onInitialize(Body* body) override;

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
	// virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

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
	// virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

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
	// virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

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
	// virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

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

	virtual bool initializeSimulation(ControllerIO* io) override;
	virtual void inputFromSimulator() override;
	virtual void outputToSimulator() override;
	virtual void stopSimulation() override;

protected:
	// <rtc-template block="protected_attribute">

	// </rtc-template>

	// <rtc-template block="protected_operation">

	// </rtc-template>

	// Configuration variable declaration
	// <rtc-template block="config_declare">

	// </rtc-template>

	// DataInPort declaration
	// <rtc-template block="inport_declare">
	RTC::TimedDoubleSeq m_Angular_In;
	/*!
	 * 腕の角度
	 * - Type: TimedDoubleSeq
	 * - Number: 6
	 * - Semantics: [0]: 腕の1軸目
	 *              [1]: 腕の2軸目
	 *              [2]: 腕の3軸目
	 *              [3]: 腕の4軸目
	 *              [4]: 腕の5軸目
	 *              [5]: 腕の6軸目
	 * - Unit: [rad]
	 */
	RTC::InPort<RTC::TimedDoubleSeq> m_Angular_InIn;
	RTC::TimedLongSeq m_Finger_In;
	/*!
	 * 指の開閉具合
	 * - Type: TimedLongSeq
	 * - Number: 3
	 * - Semantics: [0]: 親指
	 *              [1]: 差指
	 *              [2]: 中指
	 * - Unit: [u]
	 */
	RTC::InPort<RTC::TimedLongSeq> m_Finger_InIn;

	// </rtc-template>

	// DataOutPort declaration
	// <rtc-template block="outport_declare">

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

	ArmAngularWrapper m_Angular_InWrap;		/*!< m_Angular_Inのラッパークラス	*/
	FingerStatusWrapper m_Finger_InWrap;	/*!< m_Finger_Inのラッパークラス	*/

	Link* m_cnoid_Link[LINK_NUM];			/*!< コレオノイドモデルのリンク		*/

};


extern "C"
{
	DLL_EXPORT void RTC_Single_Jaco2_PreviewInit(RTC::Manager* manager);
};

#endif // RTC_SINGLE_JACO2_PREVIEW_H
