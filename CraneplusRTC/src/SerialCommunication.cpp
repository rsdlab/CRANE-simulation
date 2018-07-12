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
#ifdef _WIN32
#include"SerialCommunication.h"

//コンストラクタ
//Constructor
SerialCommunication::SerialCommunication(){
}

//シリアルポートへの接続
//Connect to Specified Serial Port
//portname	: Target COM port name(example: "COM1")
//baudrate	: Baud Rate of this communication
//
//*Reterun Value*
//true			: Connection OK
//false			: Connection NG
bool SerialCommunication::Connect(const char *portname,long baudrate){
	LPCSTR			szPort=portname;
	//Get Device Handle
	hDevice=CreateFileA(szPort,							//Device Name
						GENERIC_READ | GENERIC_WRITE,	//Accessibility setting
						0,								//Shared method
						NULL,							//Security attribution(nomally, "0")
						OPEN_EXISTING,					//Opening Action
						FILE_ATTRIBUTE_NORMAL,			//Flag and attribution(Always "FILE_ATTRIBUTE_NORMAL")
						NULL);							//Template File(Always "NULL")
	//Create File Error Handling
	if( hDevice == INVALID_HANDLE_VALUE){
		std::cout<<"Cannot open com port!"<<std::endl;
		return false ;
	}

	//通信イベントのセット
	//Monitoring selected event
	//hDevice		:Device Handler
	//EV_RXCHAR		:RS232C Received event
	if(!SetCommMask( hDevice, EV_RXCHAR )){
		std::cout<<"SetCommMask Error:"<<GetLastError()<<std::endl;
		return false;
	}

	//シリアル通信用バッファのセット
	//Send and Receive Buffer Size Setting
	DWORD	ReceiveBufferSize= DATA_MAX;
	DWORD	SendBufferSize	 = DATA_MAX;
	if(! SetupComm( hDevice, ReceiveBufferSize, SendBufferSize)){
		std::cout<<"SetupComm Error:"<<GetLastError()<<std::endl;
		return false;
	}

	//COMポートデバイスのバッファクリア
	//Buffer Clear of COM port Device
	if(!PurgeComm( hDevice, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR )){
		std::cout<<"PurgeComm Error:"<<GetLastError()<<std::endl;
		return false;
	}

	//タイムアウトの設定
	//Time out setting
	COMMTIMEOUTS	CommTimeOuts;
//	CommTimeOuts.ReadIntervalTimeout		= 0xFFFFFFFF ;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0 ;			//Wait time for 1Byte receive
	CommTimeOuts.ReadTotalTimeoutConstant	= 10 ;		//Wait time for ReadFile()
	CommTimeOuts.WriteTotalTimeoutMultiplier= 0 ;			//Wait time for 1Byte send
	CommTimeOuts.WriteTotalTimeoutConstant	= 1000 ;		//Wait time for WriteFile()
	if(!SetCommTimeouts( hDevice, &CommTimeOuts )){
		std::cout<<"SetCommTimeouts Error:"<<GetLastError()<<std::endl;
		return false;
	}

	// Communication State Get
	DCB	dcb;		//Data structure for Serial Communication 
	dcb.DCBlength = sizeof( DCB ) ;
	if(!GetCommState( hDevice, &dcb )){
		std::cout<<"GetCommState Error:"<<GetLastError()<<std::endl;
		return false;
	}

	//シリアル通信設定
	//RS232C communication Setting
	dcb.BaudRate		=baudrate;					//Communication Baudrate
	dcb.ByteSize		=8;							//Bit number for 1 byte
	dcb.Parity			=NOPARITY;					//Patiry Setting
	dcb.StopBits		=ONESTOPBIT ;				//Stop bit setting
//	dcb.StopBits		= TWOSTOPBITS ;

	//CTS/DSR Flow ON
//	dcb.fOutxDsrFlow	=TRUE ;
//	dcb.fOutxCtsFlow	=TRUE ;
	dcb.fOutxDsrFlow	=FALSE ;
	dcb.fOutxCtsFlow	=FALSE ;

	//RTS Flow Control Setting
	dcb.fRtsControl		=RTS_CONTROL_DISABLE;		//Disable to use RTS Flow Control
//	dcb.fRtsControl		=RTS_CONTROL_ENABLE;		//Enable to use RTS Flow Control
//	dcb.fRtsControl		=RTS_CONTROL_HANDSHAKE;		//
//	dcb.fRtsControl		=RTS_CONTROL_TOGGLE;		//

	//DTR Flow Control Setting
	dcb.fDtrControl		=DTR_CONTROL_DISABLE;		//Disable to use DTR Flow Control
//	dcb.fDtrControl		=DTR_CONTROL_ENABLE;		//Enable to use DTR Flow Control
//	dcb.fDtrControl		=DTR_CONTROL_HANDSHAKE;		//


	dcb.fInX			= FALSE;					//XON/XOFF Flow Control(Receive)
	dcb.fOutX			= FALSE;					//XON/XOFF Flow Control(Send)
	dcb.fBinary			= TRUE ;					//Mode setting flag(In the case of Windows, this parameter is always "TRUE")
	dcb.fParity			= TRUE ;					//Parity check flag

	//Set COM port setting
	if (!SetCommState(hDevice,&dcb )){
		std::cout<<"SetCommState Error:"<<GetLastError()<<std::endl;
		Disconnect();
		return false;
	}
	return true;
}

bool SerialCommunication::Disconnect(){
	// Communication Event Clear
	SetCommMask( hDevice, 0 ) ;

	//DTR OFF
	EscapeCommFunction( hDevice, CLRDTR ) ;

	//RTS OFF
	EscapeCommFunction( hDevice, CLRRTS ) ;

	//Buffer Clear
	PurgeComm(hDevice, PURGE_TXABORT | PURGE_RXABORT |
						PURGE_TXCLEAR | PURGE_RXCLEAR ) ;

	// Handle Close
	if(!CloseHandle(hDevice)){
		std::cout<<"Close Handle Error:"<<GetLastError()<<std::endl;
		return false;
	}

	std::cout<<"Success to close COM port"<<std::endl;
	return true;
}

//シリアルポートへの接続
//Connect to Specified Serial Port
//portname	: Target COM port name(example: "COM1")
//BaudRate	: Baud Rate of this communication
//
//*Reterun Value*
//true			: Connection OK
//false			: Connection NG
long SerialCommunication::ReceiveMessage(uchar *message, int length){
	BOOL		readstatus;
	DWORD		errorflags;
	COMSTAT		ComStat;
	DWORD		receivebytes;

	//Clear the receive buffer
	memset(message, NULL, length);

	//Obtain the com port debice error.
	ClearCommError( hDevice,				//Handle of the Com port device
					&errorflags,			//Pointer of memory for error flag 
					&ComStat ) ;			//Pointer for COMSTAT structure
	if(errorflags>0){
		std::cout<<"Communication Error:"<<errorflags<<std::endl;
		return -1;
	}

	readstatus = ReadFile(	hDevice,		//Device hadle for com port
							message,		//Buffer of receive message
							length,			//Set Buffer length
							&receivebytes,	//Return value of receive buffer length
							NULL);
	if(!readstatus){
		std::cout<<"Receive Error:"<<GetLastError()<<std::endl;;
		return -1;
	}
	return receivebytes;
}

//データの送信
//Send message to connected COM port
//senddata		: Send data for connected COM port
//length		: Data length of send data
//
//*Reterun Value*
//true			: Data send OK
//false			: Data send NG.
bool SerialCommunication::SendMessage(uchar *message,int	length){
	BOOL		sendstatus;		//Status flag of WriteFile
	DWORD		writtenbytes;	//Actual Send Message Length
	
	//Send Message through the Target File Handle 
	sendstatus =WriteFile(	hDevice,				//File Handle
							(LPCVOID) message,		//Message Buffer Pointer
							length,					//Buffer Size
							&writtenbytes,			//Actual Send Message Length
							NULL ) ;				
	//Send Error Detection
	if (!sendstatus){
		std::cout<<"Send Error:"<<GetLastError()<<std::endl;
		return false;
	}
	//Send data length check
	if ( writtenbytes == 0){
		std::cout<<"Send TimeOut Error"<<std::endl;
		return false;
	}
	
	//Display send data
	std::cout<<"Send Message:";
	for(int i(0); i < length ;i++){
		std::cout<<message[i];
	}
	std::cout<<std::endl;
	return true;
}
#endif
