// -*- C++ -*-
/*!
 * @file SHCommunicator.h
 * @brief SHマイコンとの通信クラス
 * @author C.Saito
 * @date 2019/05/30
 */

#ifndef SH_COMMUNICATOR_H
#define SH_COMMUNICATOR_H

#include <stdint.h>
#include <string>

typedef uint8_t BYTE;

/*!
 * SHマイコンとの通信クラス
 */
class SHCommunicator
{
public:
	/*!
	 * コンストラクタ
	 * @method SHCommunicator
	 */
	SHCommunicator();

	/*!
	 * デストラクタ
	 * @method ~SHCommunicator
	 */
	virtual ~SHCommunicator();

	/*!
	 * シリアルポートをオープンする
	 * @method Open
	 * @param  sDeviceName デバイス名
	 * @param  sBaudrate 通信速度
	 * @retval true 成功
	 * @retval false 失敗
	 */
	bool Open(const std::string &sDeviceName, const std::string &sBaudrate);

	/*!
	 * シリアルポートのオープン状態をチェックする
	 * @method IsOpen
	 * @return true オープン
	 * @retval false クローズ
	 */
	bool IsOpen(void);

	/*!
	 * シリアルポートをクローズする
	 * @method Close
	 * @return なし
	 */
	void Close(void);

	/*!
	 * 文字列を送信する
	 * @method Send
	 * @param  sData 送信文字列
	 * @retval true 成功
	 * @retval false 失敗
	 * @attensition 送信文字列の最大長は256
	 */
	bool Send(const std::string &sData);

	/*!
	 * 文字列を受信する
	 * @method Recv
	 * @return 受信文字列
	 * @attensition 受信文字列の最大長は256
	 */
	std::string Recv(void);

private:
	int m_fd;		/*!< ファイルディスクリプタ			*/
};

#endif//SH_COMMUNICATOR_H
