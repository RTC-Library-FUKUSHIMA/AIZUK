/*!
 * @file ButtonWrapper.h
 * @brief ボタン入出力のラッパークラス
 * @author C.Saito
 * @date 2019/04/15
 */

#ifndef BUTTON_WRAPPER_H
#define BUTTON_WRAPPER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include <cstdint>

/*!
 * @brief ボタン入出力のラッパークラス
 * @details ULong型で提供するデータの操作APIを提供する
 *          bit1: SQUAREボタンの押下状態
 *          bit2: CROSSボタンの押下状態
 *          bit3: CIRCLEボタンの押下状態
 *          bit4: TRIANGLEボタンの押下状態
 *          bit5: L1ボタンの押下状態
 *          bit6: R1ボタンの押下状態
 *          bit7: L2ボタンの押下状態
 *          bit8: R2ボタンの押下状態
 *          bit9: SHAREボタンの押下状態
 *          bit10: OPTIONSボタンの押下状態
 *          bit11: L3ボタンの押下状態
 *          bit12: R3ボタンの押下状態
 *          bit13: PSボタンの押下状態
 *          bit14: TOUCHボタンの押下状態
 *          bit15-32: 未使用
 */
class ButtonWrapper
{
public:
	/*!
	 * コンストラクタ
	 * @method Button
	 * @param  Port   ラッピングする変数
	 */
	ButtonWrapper(RTC::TimedULong& Port);

	/*!
	 * デストラクタ
	 * @method ButtonWrapper
	 */
	virtual ~ButtonWrapper();

	/*!
	 * 代入演算子のオーバーロード
	 * @method operator=
	 */
	ButtonWrapper& operator=(const ButtonWrapper& rhs);

	/*!
	 * タイムスタンプを設定する
	 * @method SetTimestamp
	 * @return なし
	 */
	void SetTimestamp(void);

	/*!
	 * ボタンの値を初期化する
	 * @method InitData
	 * @return なし
	 */
	void InitData(void);

	/*!
	 * ボタンの数を取得する
	 * @method GetDataNumber
	 * @return ボタンの数
	 */
	 uint8_t GetDataNumber(void);

	/*!
	 * SQUAREボタンの押下状態を取得する
	 * @method GetSquare
	 * @return 押下状態
	 */
	int16_t GetSquare(void);

	/*!
	 * SQUAREボタンの押下状態を設定する
	 * @method SetSquare
	 * @param  iValue   押下状態
	 * @return なし
	 */
	void SetSquare(const int16_t iValue);

	/*!
	 * CROSSボタンの押下状態を取得する
	 * @method GetCross
	 * @return 押下状態
	 */
	int16_t GetCross(void);

	/*!
	 * CROSSボタンの押下状態を設定する
	 * @method SetCross
	 * @param  iValue   押下状態
	 * @return なし
	 */
	void SetCross(const int16_t iValue);

	/*!
	 * CIRCLEボタンの押下状態を取得する
	 * @method GetCircle
	 * @return 押下状態
	 */
	int16_t GetCircle(void);

	/*!
	 * CIRCLEボタンの押下状態を設定する
	 * @method SetCircle
	 * @param  iValue   押下状態
	 * @return なし
	 */
	void SetCircle(const int16_t iValue);

	/*!
	 * TRIANGLEボタンの押下状態を取得する
	 * @method GetTriangle
	 * @return 押下状態
	 */
	int16_t GetTriangle(void);

	/*!
	 * TRIANGLEボタンの押下状態を設定する
	 * @method SetTriangle
	 * @param  iValue   押下状態
	 * @return なし
	 */
	void SetTriangle(const int16_t iValue);

	/*!
	 * L1ボタンの押下状態を取得する
	 * @method GetL1
	 * @return 押下状態
	 */
	int16_t GetL1(void);

	/*!
	 * L1ボタンの押下状態を設定する
	 * @method SetL1
	 * @param  iValue   押下状態
	 * @return なし
	 */
	void SetL1(const int16_t iValue);

	/*!
	 * R1ボタンの押下状態を取得する
	 * @method GetR1
	 * @return 押下状態
	 */
	int16_t GetR1(void);

	/*!
	 * R1ボタンの押下状態を設定する
	 * @method SetR1
	 * @param  iValue   押下状態
	 * @return なし
	 */
	void SetR1(const int16_t iValue);

	/*!
	 * L2ボタンの押下状態を取得する
	 * @method GetL2
	 * @return 押下状態
	 */
	int16_t GetL2(void);

	/*!
	 * L2ボタンの押下状態を設定する
	 * @method SetL2
	 * @param  iValue   押下状態
	 * @return なし
	 */
	void SetL2(const int16_t iValue);

	/*!
	 * R2ボタンの押下状態を取得する
	 * @method GetR2
	 * @return 押下状態
	 */
	int16_t GetR2(void);

	/*!
	 * R2ボタンの押下状態を設定する
	 * @method SetR2
	 * @param  iValue   押下状態
	 * @return なし
	 */
	void SetR2(const int16_t iValue);

	/*!
	 * SHAREボタンの押下状態を取得する
	 * @method GetShare
	 * @return 押下状態
	 */
	int16_t GetShare(void);

	/*!
	 * SHAREボタンの押下状態を設定する
	 * @method SetShare
	 * @param  iValue   押下状態
	 * @return なし
	 */
	void SetShare(const int16_t iValue);

	/*!
	 * OPTIONSボタンの押下状態を取得する
	 * @method GetOptions
	 * @return 押下状態
	 */
	int16_t GetOptions(void);

	/*!
	 * OPTIONSボタンの押下状態を設定する
	 * @method SetOptions
	 * @param  iValue   押下状態
	 * @return なし
	 */
	void SetOptions(const int16_t iValue);

	/*!
	 * L3ボタンの押下状態を取得する
	 * @method GetL3
	 * @return 押下状態
	 */
	int16_t GetL3(void);

	/*!
	 * L3ボタンの押下状態を設定する
	 * @method SetL3
	 * @param  iValue   押下状態
	 * @return なし
	 */
	void SetL3(const int16_t iValue);

	/*!
	 * R3ボタンの押下状態を取得する
	 * @method GetR3
	 * @return 押下状態
	 */
	int16_t GetR3(void);

	/*!
	 * R3ボタンの押下状態を設定する
	 * @method SetR3
	 * @param  iValue   押下状態
	 * @return なし
	 */
	void SetR3(const int16_t iValue);

	/*!
	 * PSボタンの押下状態を取得する
	 * @method GetPS
	 * @return 押下状態
	 */
	int16_t GetPS(void);

	/*!
	 * PSボタンの押下状態を設定する
	 * @method SetPS
	 * @param  iValue   押下状態
	 * @return なし
	 */
	void SetPS(const int16_t iValue);

	/*!
	 * TOUCHボタンの押下状態を取得する
	 * @method GetTouch
	 * @return 押下状態
	 */
	int16_t GetTouch(void);

	/*!
	 * TOUCHボタンの押下状態を設定する
	 * @method SetTouch
	 * @param  iValue   押下状態
	 * @return なし
	 */
	void SetTouch(const int16_t iValue);

private:
	RTC::TimedULong& m_Port;	/*!< ラッピングする変数の参照変数	*/
};

#endif//BUTTON_WRAPPER_H
