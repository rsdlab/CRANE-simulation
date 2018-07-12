///////////////////////////////////////////////////////////////////////
//Serial Communication Class
//���̃N���X�̓V���A���ʐM���߂̃N���X�ł��D
//Written  by Daiki   Kawakami, Osaka Univ.
//Modified by Kenichi Ohara   , Osaka Univ.
//=====================================================================
//�o�[�W�����Ǘ�
//Version Information
//=====================================================================
//Ver. 0.2:	�����C��				2009/03/08
//			SimpleModification
//Ver. 0.1:	��{����(Windows��) 	2008/08/04
//			Basic Implementation
//=====================================================================
//�ˑ���
//Dependency
//=====================================================================
//���̃N���X��Windows�ł̂ݗ��p�\�ł��D
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
	//�V���A���ʐM�p�̃f�o�C�X�n���h��
	//Device Handle for Serial Port
	HANDLE	hDevice;
#endif

public:
	//�R���X�g���N�^
	//Constructor
	SerialCommunication();
	
	//�V���A���|�[�g�ւ̐ڑ�
	//Connect to Specified Serial Port
	//portname	: Target COM port name(example: "COM1")
	//baudrate	: Baud Rate of this communication
	//
	//*Reterun Value*
	//true			: Connection OK
	//false			: Connection NG
	bool	Connect(const char *portname,long baudrate);

	//COM�|�[�g����̐ؒf
	//Close from connected COM port
	bool	Disconnect();

	//�f�[�^�̑��M
	//Send message to connected COM port
	//senddata		: Send data for connected COM port
	//length		: Data length of send data
	//
	//*Reterun Value*
	//true			: Data send OK
	//false			: Data send NG.
	bool	SendMessage(uchar *senddata, int length);

	//�f�[�^�̎�M
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