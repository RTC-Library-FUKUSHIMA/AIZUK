/*!
 * @file AxisWrapper.h
 * @brief 軸キー入出力のラッパークラス
 * @author C.Saito
 * @date 2019/04/15
 */

#ifndef AXIS_WRAPPER_H
#define AXIS_WRAPPER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include <cstdint>

/*!
 * @brief 軸キー入出力のラッパークラス
 * @details 次のdouble型配列で提供するデータの操作APIを提供する
 *          [0]: 十字ボタン(上下)の入力具合
 *          [1]: 十字ボタン(左右)の入力具合
 *          [2]: 左スティック(上下)の入力具合
 *          [3]: 左スティック(左右)の入力具合
 *          [4]: 右スティック(上下)の入力具合
 *          [5]: 右スティック(左右)の入力具合
 *          [6]: L2ボタンの入力具合
 *          [7]: R2ボタンの入力具合
 */
class AxisWrapper
{
public:
	/*!
	 * コンストラクタ
	 * @method AxisWrapper
	 * @param  Port   ラッピングする変数
	 */
	AxisWrapper(RTC::TimedDoubleSeq& Port);

	/*!
	 * デストラクタ
	 * @method AxisWrapper
	 */
	virtual ~AxisWrapper();

	/*!
	 * 代入演算子のオーバーロード
	 * @method operator=
	 */
	AxisWrapper& operator=(const AxisWrapper& rhs);

	/*!
	 * タイムスタンプを設定する
	 * @method SetTimestamp
	 * @return なし
	 */
	void SetTimestamp(void);

	/*!
	 * 軸キーの入出力の配列数と値を初期化する
	 * @method InitData
	 * @return なし
	 */
	void InitData(void);

	/*!
	 * 軸キーの数を取得する
	 * @method GetDataNumber
	 * @return 軸キーの数
	 */
	 uint8_t GetDataNumber(void);

	/*!
	 * 十字ボタン(左右)の入力具合を取得する
	 * @method GetDirHorizontal
	 * @return 押下具合
	 */
	double GetDirHorizontal(void);

	/*!
	 * 十字ボタン(左右)の入力具合を設定する
	 * @method SetDirHorizontal
	 * @param  dValue   入力具合
	 * @return なし
	 */
	void SetDirHorizontal(const double dValue);

	/*!
	 * 十字ボタン(上下)の入力具合を取得する
	 * @method GetDirHorizontal
	 * @return 押下具合
	 */
	double GetDirVertical(void);

	/*!
	 * 十字ボタン(上下)の入力具合を設定する
	 * @method SetDirHorizontal
	 * @param  dValue   入力具合
	 * @return なし
	 */
	void SetDirVertical(const double dValue);

	/*!
	 * 左スティック(左右)の入力具合を取得する
	 * @method GetLStickHorizontal
	 * @return 押下具合
	 */
	double GetLStickHorizontal(void);

	/*!
	 * 左スティック(左右)の入力具合を設定する
	 * @method SetLStickHorizontal
	 * @param  dValue   入力具合
	 */
	void SetLStickHorizontal(const double dValue);

	/*!
	 * 左スティック(上下)の入力具合を取得する
	 * @method GetLStickVertical
	 * @return 押下具合
	 */
	double GetLStickVertical(void);

	/*!
	 * 左スティック(上下)の入力具合を設定する
	 * @method SetLStickVertical
	 * @param  dValue   入力具合
	 */
	void SetLStickVertical(const double dValue);

	/*!
	 * 右スティック(左右)の入力具合を取得する
	 * @method GetRStickHorizontal
	 * @return 押下具合
	 */
	double GetRStickHorizontal(void);

	/*!
	 * 右スティック(左右)の入力具合を設定する
	 * @method SetRStickHorizontal
	 * @param  dValue   入力具合
	 */
	void SetRStickHorizontal(const double dValue);

	/*!
	 * 右スティック(上下)の入力具合を取得する
	 * @method GetRStickVertical
	 * @return 押下具合
	 */
	double GetRStickVertical(void);

	/*!
	 * 右スティック(上下)の入力具合を設定する
	 * @method SetRStickVertical
	 * @param  dValue   入力具合
	 */
	void SetRStickVertical(const double dValue);

	/*!
	 * L2ボタンの入力具合を取得する
	 * @method GetL2
	 * @return 押下具合
	 */
	double GetL2(void);

	/*!
	 * L2ボタンの入力具合を設定する
	 * @method SetL2
	 * @param  dValue   入力具合
	 */
	void SetL2(const double dValue);

	/*!
	 * R2ボタンの入力具合を取得する
	 * @method GetR2
	 * @return 押下具合
	 */
	double GetR2(void);

	/*!
	 * R2ボタンの入力具合を設定する
	 * @method SetR2
	 * @param  dValue   入力具合
	 */
	void SetR2(const double dValue);

private:
	RTC::TimedDoubleSeq& m_Port;	/*!< ラッピングする変数の参照変数	*/
};

#endif//AXIS_WRAPPER_H
