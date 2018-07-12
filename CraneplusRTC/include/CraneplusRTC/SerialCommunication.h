///////////////////////////////////////////////////////////////////////
//Serial Communication Class
//このクラスはシリアル通信ためのクラスです．
//Written  by Daiki   Kawakami, Osaka Univ.
//Modified by Kenichi Ohara   , Osaka Univ.
//=====================================================================
//バージョン管理
//Version Information
//=====================================================================
//Ver. 0.2:	少し修正				2009/03/08
//			SimpleModification
//Ver. 0.1:	基本実装(Windows版) 	2008/08/04
//			Basic Implementation
//=====================================================================
//依存性
//Dependency
//=====================================================================
//このクラスはWindowsでのみ利用可能です．
//This class can be used on Windows.
///////////////////////////////////////////////////////////////////////
#ifndef _SERIALCOMMUNICATION_H_
#define _SERIALCOMMUNICATION_H_

//Include File
#include<iostream>
//For Windows
//#ifdef WIN32
#include<windows.h>
#include<conio.h>
//#endif

#define DATA_MAX 1024

typedef unsigned char uchar;

class SerialCommunication{
private:
#ifdef WIN32
	//シリアル通信用のデバイスハンドラ
	//Device Handle for Serial Port
	HANDLE	hDevice;
#endif

public:
	//コンストラクタ
	//Constructor
	SerialCommunication();
	
	//シリアルポートへの接続
	//Connect to Specified Serial Port
	//portname	: Target COM port name(example: "COM1")
	//baudrate	: Baud Rate of this communication
	//
	//*Reterun Value*
	//true			: Connection OK
	//false			: Connection NG
	bool	Connect(const char *portname,long baudrate);

	//COMポートからの切断
	//Close from connected COM port
	bool	Disconnect();

	//データの送信
	//Send message to connected COM port
	//senddata		: Send data for connected COM port
	//length		: Data length of send data
	//
	//*Reterun Value*
	//true			: Data send OK
	//false			: Data send NG.
	bool	SendMessage(uchar *senddata, int length);

	//データの受信
	//Receive message from connected COM port
	//receivedata	: Receive data from connected COM port
	//length		: Data length of receivedata
	//
	//*Return Value*
	//Receive data size
	//(If this function returns "-1", data receive is failed.)
	long	ReceiveMessage(uchar *receivedata, int length);
};


#endif