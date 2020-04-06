// -*- C++ -*-
/*!
 * @file  RTC_Single_Jaco2_Practice.h
 * @brief Spider2020 コレオノイドモデルのJaco2アーム制御RTC
 * @date  $Date$
 *
 * $Id$
 */

#ifndef RTC_SINGLE_JACO2_PRACTICE_H
#define RTC_SINGLE_JACO2_PRACTICE_H

#include <cnoid/BodyIoRTC>
#include <cnoid/EigenUtil>
#include <cnoid/JointPath>
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

#include "FingerDeltaWrapper.h"

using namespace cnoid;

/*!
 * @enum 列挙子
 * リンクデータのインデクサ
 */
enum LINK_t
{
	LINK_BASE,				/*!< BASEリンク			*/
	LINK_SHOULDER,			/*!< SHOULDERリンク		*/
	LINK_ARM,				/*!< ARMリンク			*/
	LINK_FOREARM,			/*!< FOREARMリンク		*/
	LINK_WRIST1,			/*!< WRIST1リンク		*/
	LINK_WRIST2,			/*!< WRIST2リンク		*/
	LINK_HAND,				/*!< HANDリンク			*/
	LINK_END_EFFECTOR,		/*!< END EFFECTORリンク	*/
	LINK_FINGER1,			/*!< FINGER1リンク		*/
	LINK_FINGER2,			/*!< FINGER2リンク		*/
	LINK_FINGER3,			/*!< FINGER3リンク		*/
	LINK_NUM,
};

/*!
 * @class RTC_Single_Jaco2_Practice
 * @brief Spider2020 コレオノイドモデルのJaco2アーム制御RTC
 *
 */
class RTC_Single_Jaco2_Practice
  : public BodyIoRTC
{
public:
	/*!
	* @brief constructor
	* @param manager Maneger Object
	*/
	RTC_Single_Jaco2_Practice(RTC::Manager* manager);

	/*!
	* @brief destructor
	*/
	~RTC_Single_Jaco2_Practice();

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

	void setArmAngle(Link* link, double angle);
	void setFingerAngle(Link* link, long delta);

	/*!
	 * 手先位置姿勢の変位速度をポートから読み込む
	 * @method ReadPoseDelta
	 * @return なし
	 */
	void ReadPoseDelta(void);

	/*!
	 * 指の開閉具合の変位速度をポートから読み込む
	 * @method ReadFingerDelta
	 * @return なし
	 */
	void ReadFingerDelta(void);

	/*!
	 * 初期姿勢遷移指令をポートから読み込む
	 * @method ReadHome
	 * @return なし
	 */
	void ReadHome(void);

protected:
	// <rtc-template block="protected_attribute">

	// </rtc-template>

	// <rtc-template block="protected_operation">

	// </rtc-template>

	// Configuration variable declaration
	// <rtc-template block="config_declare">
	/*!
	 * 入力ポートへ指定時間以上新しい入力がなければ、
	 * 暴走を回避するため入力データのクリアなどを実施する。
	 * - Name: フェイルセーフ時間 FAILSAFE_SEC
	 * - DefaultValue: 1.0
	 */
	double m_FAILSAFE_SEC;

	// </rtc-template>

	// DataInPort declaration
	// <rtc-template block="inport_declare">
	RTC::TimedPose3D m_PoseDelta_In;
	/*!
	 * 手先位置姿勢の変位速度
	 * - Type: TimedPose3D
	 * - Number: 1
	 * - Unit: [m,rad]
	 */
	RTC::InPort<RTC::TimedPose3D> m_PoseDelta_InIn;
	RTC::TimedLongSeq m_FingerDelta_In;
	/*!
	 * 指の開閉具合の変位速度
	 * - Type: TimedLongSeq
	 * - Number: 3
	 * - Semantics: [0]: 親指
	 *              [1]: 差指
	 *              [2]: 中指
	 * - Unit: [u]
	 */
	RTC::InPort<RTC::TimedLongSeq> m_FingerDelta_InIn;
	RTC::TimedLong m_Home_In;
	/*!
	 * 初期姿勢遷移指令
	 * - Type: TimedLong
	 * - Number: 1
	 * - Semantics: 0: 姿勢制御を処理する
	 *              1: 初期姿勢に戻す
	 */
	RTC::InPort<RTC::TimedLong> m_Home_InIn;

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

	FingerDeltaWrapper m_FingerDelta_InWrap;	/*!< m_FingerDelta_Inのラッパークラス	*/

	struct timeval m_stPoseDeltaReadTime;		/*!< m_PoseDelta_Inの入力時刻			*/
	struct timeval m_stFingerDeltaReadTime;		/*!< m_FingerDelta_Inの入力時刻			*/

	Link* m_cnoid_Link[LINK_NUM];			/*!< コレオノイドモデルのリンク		*/
	double		m_cnoid_TimeStep;

//#ifdef CNOID_BACKWARD_COMPATIBILITY
typedef std::shared_ptr<JointPath> JointPathPtr;
//#endif
	JointPathPtr m_BaseToEndEffector;

};


extern "C"
{
	DLL_EXPORT void RTC_Single_Jaco2_PracticeInit(RTC::Manager* manager);
};

#endif // RTC_SINGLE_JACO2_PRACTICE_H
