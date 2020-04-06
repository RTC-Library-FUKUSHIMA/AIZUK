/*!
 * @file ModeWrapper.h
 * @brief 動作指令の状態入出力のラッパークラス
 * @author C.Saito
 * @date 2019/04/16
 */

#ifndef MODE_WRAPPER_H
#define MODE_WRAPPER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include <cstdint>

/*!
 * @brief 動作指令の状態入出力のラッパークラス
 * @details 次のlong型配列で提供するデータの操作APIを提供する
 *          [0]: 操作モード
 *          [1]: 走行操作 速度レベル
 *          [2]: 走行操作 最大速度フラグ
 *          [3]: 走行モード フリッパーの選択状態
 *          [4]: 走行モード フリッパーの動作状態
 *          [5]: 走行モード 台車の位置姿勢のクリア
 */
class ModeWrapper
{
public:
	/*!
	* @enum 列挙子
	* 速度レベルの種類
	*/
	enum SPEED_LEVEL_t
	{
		SPEED_LEVEL_LOW,		/*!< 低速			*/
		SPEED_LEVEL_MID,		/*!< 中速			*/
		SPEED_LEVEL_HIGH,		/*!< 高速			*/
		SPEED_LEVEL_NUM,		/*!< データの数		*/
	};

	/*!
	* @enum 列挙子
	* 最大速度フラグの種類
	*/
	enum SPEED_MAX_t
	{
		SPEED_MAX_OFF,		/*!< OFF			*/
		SPEED_MAX_ON,		/*!< ON				*/
		SPEED_MAX_NUM,		/*!< データの数		*/
	};

	/*!
	* @enum 列挙子
	* 操作モードの種類
	*/
	enum CONTROL_t
	{
		CONTROL_DRIVE,		/*!< 走行			*/
		CONTROL_ARM,		/*!< アーム			*/
		CONTROL_NUM,		/*!< データの数		*/
	};

	/*!
	* @enum 列挙子
	* フリッパーの選択状態の種類
	*/
	enum FLIPPER_SELECT_t
	{
		FLIPPER_SELECT_OFF,		/*!< 非選択			*/
		FLIPPER_SELECT_ON,		/*!< 選択			*/
		FLIPPER_SELECT_NUM,		/*!< データの数		*/
	};

	/*!
	* @enum 列挙子
	* フリッパーの動作状態の種類
	*/
	enum FLIPPER_STATUS_t
	{
		FLIPPER_STATUS_STAY,	/*!< 現状維持		*/
		FLIPPER_STATUS_UP,		/*!< 上昇			*/
		FLIPPER_STATUS_DOWN,	/*!< 下降			*/
		FLIPPER_STATUS_NUM,		/*!< データの数		*/
	};

	/*!
	* @enum 列挙子
	* 台車の位置姿勢のクリアの種類
	*/
	enum CRAWLER_POSE_CLEAR_t
	{
		CRAWLER_POSE_CLEAR_OFF,		/*!< OFF			*/
		CRAWLER_POSE_CLEAR_ON,		/*!< ON				*/
		CRAWLER_POSE_CLEAR_NUM,		/*!< データの数		*/
	};

	/*!
	 * コンストラクタ
	 * @method ModeWrapper
	 * @param  Port   ラッピングする変数
	 */
	ModeWrapper(RTC::TimedLongSeq& Port);

	/*!
	 * デストラクタ
	 * @method ModeWrapper
	 */
	virtual ~ModeWrapper();

	/*!
	 * 代入演算子のオーバーロード
	 * @method operator=
	 */
	ModeWrapper& operator=(const ModeWrapper& rhs);

	/*!
	 * タイムスタンプを設定する
	 * @method SetTimestamp
	 * @return なし
	 */
	void SetTimestamp(void);

	/*!
	 * 動作指令の状態の入出力の配列数と値を初期化する
	 * @method InitData
	 * @return なし
	 */
	void InitData(void);

	/*!
	 * 動作指令の状態の数を取得する
	 * @method GetDataNumber
	 * @return データの数
	 */
	 uint8_t GetDataNumber(void);


	/*!
	 * 速度レベルを取得する
	 * @method GetSpeedLevel
	 * @return 操作モードの種類
	 */
	int32_t GetSpeedLevel(void);

	/*!
	 * 速度レベルを設定する
	 * @method SetSpeedLevel
	 * @param  iValue   速度レベルの種類
	 * @return なし
	 */
	void SetSpeedLevel(const int32_t iValue);

	/*!
	 * 最大速度フラグを取得する
	 * @method GetSpeedMax
	 * @return 最大速度フラグの種類
	 */
	int32_t GetSpeedMax(void);

	/*!
	 * 最大速度フラグを設定する
	 * @method SetSpeedMax
	 * @param  iValue   最大速度フラグの種類
	 * @return なし
	 */
	void SetSpeedMax(const int32_t iValue);

	/*!
	 * 操作モードを取得する
	 * @method GetControl
	 * @return 操作モードの種類
	 */
	int32_t GetControl(void);

	/*!
	 * 操作モードを設定する
	 * @method SetControl
	 * @param  iValue   操作モードの種類
	 * @return なし
	 */
	void SetControl(const int32_t iValue);

	/*!
	 * 右前方フリッパーの選択状態を取得する
	 * @method GetFrontRightFlipperSelect
	 * @return フリッパーの選択状態の種類
	 */
	int32_t GetFrontRightFlipperSelect(void);

	/*!
	 * 右前方フリッパーの選択状態を設定する
	 * @method SetFrontRightFlipperSelect
	 * @param  iValue   フリッパーの選択状態の種類
	 * @return なし
	 */
	void SetFrontRightFlipperSelect(const int32_t iValue);

	/*!
	 * 左前方フリッパーの選択状態を取得する
	 * @method GetFrontLeftFlipperSelect
	 * @return フリッパーの選択状態の種類
	 */
	int32_t GetFrontLeftFlipperSelect(void);

	/*!
	 * 左前方フリッパーの選択状態を設定する
	 * @method SetFrontLeftFlipperSelect
	 * @param  iValue   フリッパーの選択状態の種類
	 * @return なし
	 */
	void SetFrontLeftFlipperSelect(const int32_t iValue);

	/*!
	 * 右後方フリッパーの選択状態を取得する
	 * @method GetFrontRightFlipperSelect
	 * @return フリッパーの選択状態の種類
	 */
	int32_t GetBackRightFlipperSelect(void);

	/*!
	 * 右後方フリッパーの選択状態を設定する
	 * @method SetFrontRightFlipperSelect
	 * @param  iValue   フリッパーの選択状態の種類
	 * @return なし
	 */
	void SetBackRightFlipperSelect(const int32_t iValue);

	/*!
	 * 左後方フリッパーの選択状態を取得する
	 * @method GetBackLeftFlipperSelect
	 * @return フリッパーの選択状態の種類
	 */
	int32_t GetBackLeftFlipperSelect(void);

	/*!
	 * 左後方フリッパーの選択状態を設定する
	 * @method SetBackLeftFlipperSelect
	 * @param  iValue   フリッパーの選択状態の種類
	 * @return なし
	 */
	void SetBackLeftFlipperSelect(const int32_t iValue);

	/*!
	 * フリッパーの動作状態を取得する
	 * @method GetBackLeftFlipperSelect
	 * @return フリッパーの動作状態の種類
	 */
	int32_t GetFlipperStatus(void);

	/*!
	 * フリッパーの動作状態を設定する
	 * @method SetFlipperStatus
	 * @param  iValue   フリッパーの動作状態の種類
	 * @return なし
	 */
	void SetFlipperStatus(const int32_t iValue);

	/*!
	 * 台車の位置姿勢のクリアを取得する
	 * @method GetCrawlerPoseClear
	 * @return 台車の位置姿勢のクリアの種類
	 */
	int32_t GetCrawlerPoseClear(void);

	/*!
	 * 台車の位置姿勢のクリアを設定する
	 * @method SetCrawlerPoseClear
	 * @param  iValue   台車の位置姿勢のクリアの種類
	 * @return なし
	 */
	void SetCrawlerPoseClear(const int32_t iValue);

private:
	RTC::TimedLongSeq& m_Port;	/*!< ラッピングする変数の参照変数	*/
};

#endif//MODE_WRAPPER_H
