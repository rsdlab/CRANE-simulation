#include "Craneplus.h"

//コンストラクタ
Craneplus::Craneplus()
{
  for(int i=0;i<ARM_FREEDOM;i++){
    Writedata[i].CW_ComplianceMargin = 0;
    Writedata[i].CCW_ComplianceMargin = 0;
    Writedata[i].CW_ComplianceSlope = 0;
    Writedata[i].CCW_ComplianceSlope = 0;
    Writedata[i].Angle = 0;
    Writedata[i].Speed = 0;
    Writedata[i].Torque = 0;
    ReadAngle[i] = 0;
    }

  CRANEJointLimit[0].Upper = Angle1_LimitMax;
  CRANEJointLimit[0].Lower = Angle1_LimitMin;
  CRANEJointLimit[1].Upper = Angle2_LimitMax;
  CRANEJointLimit[1].Lower = Angle2_LimitMin;
  CRANEJointLimit[2].Upper = Angle3_LimitMax;
  CRANEJointLimit[2].Lower = Angle3_LimitMin;
  CRANEJointLimit[3].Upper = Angle4_LimitMax;
  CRANEJointLimit[3].Lower = Angle4_LimitMin;

  CRANECartesianLimit.x.Upper = X_LimitMax;
  CRANECartesianLimit.x.Lower = X_LimitMin;
  CRANECartesianLimit.y.Upper = Y_LimitMax;
  CRANECartesianLimit.y.Lower = Y_LimitMin;
  CRANECartesianLimit.z.Upper = Z_LimitMax;
  CRANECartesianLimit.z.Lower = Z_LimitMin;

#ifdef WIN32
#else
  bzero(&newtio, sizeof(newtio)); //initialize
  fd = 0;
#endif
}

//グローバル変数宣言
Craneplus crane;

/*==============================================================================*/
/*                                  private関数                                 */
/*==============================================================================*/


/************************************************

	void serialWrite(char *buf, int length)

	概要：シリアル通信でデータを送信する

	引数：
              *buf・・・送るデータの配列
              length・・・データの長さ
	
	戻り値：なし

*************************************************/
void Craneplus::serialWrite(uchar *buf, int length)
{
#ifdef WIN32
	sc.SendMessage(buf, length);
#else
	write(fd, buf, length);
	tcflush(fd, TCOFLUSH);

#endif
}

/************************************************

void serialRead(char *buf, int length)

概要：シリアル通信でデータを受信する

引数：
*buf・・・送るデータの配列
length・・・データの長さ

戻り値：なし

*************************************************/
void Craneplus::serialRead(uchar *buf, int length)
{
#ifdef WIN32
	sc.ReceiveMessage(buf, length);
#else
	read(fd, buf, length);
	tcflush(fd, TCIFLUSH);
#endif
}

/************************************************

	char calcCheckSum(char *buf, int Datasize)

	概要：シリアル通信用のチェックサムを計算する

	引数：
              *buf・・・送るデータの配列
              Datasize・・・データの数
	
	戻り値：計算結果

*************************************************/
uchar Craneplus::calcCheckSum(uchar *buf, int Datasize)
{
  int checksum = 0;

  buf += 2;	//skip 0xff 0xff

  for(int i=2;i<Datasize-1;i++)
    {
      checksum += *buf;
      buf += 1;
    }
  return 0xff & (~checksum);
}


/************************************************

        void checkserial()

	概要：シリアル通信できているか確認する

	引数：なし
	
	戻り値：なし

*************************************************/
void Craneplus::checkserial()
{
  uchar recv[4];

  serialRead(recv, 4);

  //if((recv[0] & recv[1] & 0xff) != 0xff)
  //  {
      //printf("ステータスパケットが異常です。正しく動作していない可能性があります。\n");
      //printf("return value:\n%02X %02X %02X %02X \n", recv[0], recv[1], recv[2], recv[3]);
      //exit(-1);
  //  }

}


/************************************************

        void RegWrite(int id, ServoWrite data[])

	概要：DynamixelのRegWriteでデータを送信する

	引数：
              id・・・モータのID
              data・・・データに代入する値 
	
	戻り値：なし

*************************************************/
void Craneplus::RegWrite(int id, ServoWrite data[])
{
  uchar buf[17] = {0};
  int angle = (int)( 1024.0 * (data[id-1].Angle / 300.0) );
  int speed = (int)( data[id-1].Speed / 0.111 );
  int torque = (int) ( data[id-1].Torque * 1024.0 );
  
  
  buf[0] = 0xff;
  buf[1] = 0xff;       //init
  buf[2] = id & 0xff;  //id
  buf[3] = 13;         //length
  buf[4] = 4;          //instruction
  buf[5] = 26;         //start address
  buf[6] = data[id-1].CW_ComplianceMargin;
  buf[7] = data[id-1].CCW_ComplianceMargin;
  buf[8] = data[id-1].CW_ComplianceSlope;
  buf[9] = data[id-1].CCW_ComplianceSlope;
  buf[10] = angle & 0xff;
  buf[11] = (angle >> 8) & 0xff;
  buf[12] = speed & 0xff;
  buf[13] = (speed >> 8) & 0xff;
  buf[14] = torque & 0xff;
  buf[15] = (torque >> 8) & 0xff;

  buf[16] = calcCheckSum(buf, sizeof(buf));

  serialWrite(buf, sizeof(buf));

  checkserial();
}


/************************************************

        void Action(void)

	概要：DynamixelのActionでデータを送信する

	引数：なし
	
	戻り値：なし

*************************************************/
void Craneplus::Action(void)
{
  uchar buf[6] = {0};

  buf[0] = 0xff;
  buf[1] = 0xff;
  buf[2] = 254;
  buf[3] = 2;
  buf[4] = 5;
  buf[5] = calcCheckSum(buf, sizeof(buf));;
  
  serialWrite(buf, sizeof(buf));
}


/************************************************

       void ReadServoAngle(int id, double ReadAngle)

       概要：サーボのAngle値を受け取る

       引数：
             id・・・サーボのID

       戻り値：なし

*************************************************/
void Craneplus::ReadServoAngle(int id, double ReadAngle[])
{
  uchar buf[8] = {0};
  uchar recv[8];

  buf[0] = 0xff;
  buf[1] = 0xff;
  buf[2] = id & 0xff;
  buf[3] = 4;
  buf[4] = 2;
  buf[5] = 0x24;
  buf[6] = 2;
  buf[7] = calcCheckSum(buf, sizeof(buf));

  serialWrite(buf,sizeof(buf));

  serialRead(recv, 8);

  ReadAngle[id-1] = 300.0 * (recv[5] | (recv[6] << 8)) / 1024.0;

}


/************************************************

	void ReadArmAngle()

	概要：アームの各関節のAngle値を受け取る

	引数：なし
	
	戻り値：なし

*************************************************/
void Craneplus::ReadArmAngle()
{
  int i = 0;
  for(i=0;i<ARM_FREEDOM;i++)
    {
      ReadServoAngle(i+1,ReadAngle);
    }

}


/*==============================================================================*/
/*                                  public関数                                  */
/*==============================================================================*/

/************************************************

	int OpenCOMDevice(const char *SERIAL_PORT)

	概要：シリアル通信を開始する

	引数：const char *SERIAL_PORT・・・ポート名
	
	戻り値：なし

*************************************************/
int Craneplus::OpenCOMDevice(const char *SERIAL_PORT)
{
  dev = (char*)SERIAL_PORT;

#ifdef WIN32
  std::cout << "Open COM Port:" << dev << std::endl;
  sc.Connect(SERIAL_PORT, 1000000);
#else
  fd = open(dev, O_RDWR | O_NOCTTY );
  if(fd < 0){
    std::cout<<"Cannot Open expected COM Port!"<<std::endl;
    return false;
  }
  else{
    std::cout<<"Open COM Port:"<<dev<<std::endl;
  }
  
  newtio.c_cflag = B1000000 | CS8 | CREAD | CLOCAL;
  
  newtio.c_cc[VTIME] = 10;
  newtio.c_cc[VMIN] = 10;
  newtio.c_lflag = 0;
  newtio.c_iflag = IGNPAR;
  newtio.c_oflag = 0;
  
  tcflush(fd, TCIOFLUSH);
  tcsetattr(fd, TCSANOW, &newtio);
#endif
  return true;
}


/************************************************

	int CloseCOMDevice()

	概要：シリアル通信を終了する

	引数：なし
	
	戻り値：なし

*************************************************/
void Craneplus::CloseCOMDevice()
{
  std::cout<<"Close COM Port："<<dev<<std::endl;
#ifdef WIN32
  sc.Disconnect();
#else
  close(fd);
#endif
}


/************************************************

        void initServo(int id ,t_servo *servo)

       概要：サーボモーターに送るデータの変数を初期化する関数

       引数：
            id・・・サーボモーターのID
            data・・・各IDのDynamixelに送るデータの変数

       戻り値：なし

*************************************************/
void Craneplus::initServo(int id, ServoWrite data[])
{
	data[id-1].CW_ComplianceMargin = 1;
	data[id-1].CCW_ComplianceMargin = 1;
	data[id-1].CW_ComplianceSlope = 32;
	data[id-1].CCW_ComplianceSlope = 32;
	data[id-1].Angle = 150;
	data[id-1].Speed = 20;
	data[id-1].Torque = 0.95;
}



/************************************************

       void initArm()

       概要：すべてのサーボモーターに送るデータの変数を初期化する関数

       引数：なし

       戻り値：なし

*************************************************/
void Craneplus::initArm()
{
	int i;
	for(i = 0; i < ARM_FREEDOM; i++)
	{
	  initServo(i+1, Writedata);
	}
}


/************************************************

       void setCRANEJointdata(double JointPos[])

       概要：JointPos[]の値をWritedata[].Angleに書き込む

       引数：
            double JointPos[]・・・セットする角度データ

       戻り値：なし

*************************************************/
void Craneplus::setCRANEJointdata(double JointPos[])
{
  Writedata[0].Angle = 150 + JointPos[0];
  Writedata[1].Angle = 150 + JointPos[1];
  Writedata[2].Angle = 150 - JointPos[2];
  Writedata[3].Angle = 150 - JointPos[3];
}


/************************************************

       void setCRANESpeeddata(double spdRatio)

       概要：spdRatioの値をWritedata[].Speedに書き込む

       引数：
            double spdRatio・・・セットする速度データ

       戻り値：なし

*************************************************/
void Craneplus::setCRANESpeeddata(int id, double spdRatio)
{
  
  Writedata[id-1].Speed = spdRatio;
  
}


/************************************************

       void setCRANECartesianLimit(Cartesian CartesianLimit)

       概要：CartesianLimitの値をCRANECartesianLimitに書き込む

       引数：
            Cartesian CartesianLimit・・・セットするリミットデータの構造体(詳しくはCraneplus.h)

       戻り値：なし

*************************************************/
void Craneplus::setCRANECartesianLimit(Cartesian CartesianLimit)
{
  CRANECartesianLimit.x.Upper = CartesianLimit.x.Upper;
  CRANECartesianLimit.x.Lower = CartesianLimit.x.Lower;
  CRANECartesianLimit.y.Upper = CartesianLimit.y.Upper;
  CRANECartesianLimit.y.Lower = CartesianLimit.y.Lower;
  CRANECartesianLimit.z.Upper = CartesianLimit.z.Upper;
  CRANECartesianLimit.z.Lower = CartesianLimit.z.Lower;
}


/************************************************

       void setCRANEJointLimit(JLimit JointLimit[])

       概要：JointLimit[]の値をCRANEJointLimit[]に書き込む

       引数：
            JLimit JointLimit[]・・・セットするリミットデータの構造体(詳しくはCraneplus.h)

       戻り値：なし

*************************************************/
void Craneplus::setCRANEJointLimit(JLimit JointLimit[])
{
  CRANEJointLimit[0].Upper = JointLimit[0].Upper;
  CRANEJointLimit[0].Lower = JointLimit[0].Lower;
  CRANEJointLimit[1].Upper = JointLimit[1].Upper;
  CRANEJointLimit[1].Lower = JointLimit[1].Lower;
  CRANEJointLimit[2].Upper = JointLimit[2].Upper;
  CRANEJointLimit[2].Lower = JointLimit[2].Lower;
  CRANEJointLimit[3].Upper = JointLimit[3].Upper;
  CRANEJointLimit[3].Lower = JointLimit[3].Lower;
}


/************************************************

      void getCRANEJointdata(double JointPos[])

      概要：クラス内の変数の角度データを入手する

      引数：
            double JointPos][]・・・入手した角度データを格納する変数

      戻り値：なし

*************************************************/
void Craneplus::getCRANEJointdata(double JointPos[])
{

  ReadArmAngle(); 

  //アームが立った状態からの角度
  JointPos[0] = -150 + ReadAngle[0];
  JointPos[1] = -150 + ReadAngle[1];
  JointPos[2] = 150 - ReadAngle[2];
  JointPos[3] = 150 - ReadAngle[3];
}


/************************************************

      void getCRANESpeeddata(double spdRatio)

      概要：クラス内の変数の速度データを入手する

      引数：
            double spdRatio・・・入手した角度データを格納する変数

      戻り値：なし

*************************************************/
void Craneplus::getCRANESpeeddata(double spdRatio)
{
  spdRatio = Writedata[0].Speed;
}


/************************************************

      void getCRANECartesianLimit(Cartesian CartesianLimit)

      概要：クラス内の変数の範囲リミットデータを入手する

      引数：
            Cartesian CartesianLimit・・・入手した範囲リミットデータを格納する変数

      戻り値：なし

*************************************************/
void Craneplus::getCRANECartesianLimit(Cartesian CartesianLimit)
{
  CartesianLimit.x.Upper = CRANECartesianLimit.x.Upper;
  CartesianLimit.x.Lower = CRANECartesianLimit.x.Lower;
  CartesianLimit.y.Upper = CRANECartesianLimit.y.Upper;
  CartesianLimit.y.Lower = CRANECartesianLimit.y.Lower;
  CartesianLimit.z.Upper = CRANECartesianLimit.z.Upper;
  CartesianLimit.z.Lower = CRANECartesianLimit.z.Lower;

}


/************************************************

      void getCRANECartesianLimit(Cartesian CartesianLimit)

      概要：クラス内の変数の範囲リミットデータを入手する

      引数：
            Cartesian CartesianLimit・・・入手した範囲リミットデータを格納する変数

      戻り値：なし

*************************************************/
void Craneplus::getCRANEJointLimit(JLimit JointLimit[])
{
  JointLimit[0].Upper = CRANEJointLimit[0].Upper;
  JointLimit[0].Lower = CRANEJointLimit[0].Lower;
  JointLimit[1].Upper = CRANEJointLimit[1].Upper;
  JointLimit[1].Lower = CRANEJointLimit[1].Lower;
  JointLimit[2].Upper = CRANEJointLimit[2].Upper;
  JointLimit[2].Lower = CRANEJointLimit[2].Lower;
  JointLimit[3].Upper = CRANEJointLimit[3].Upper;
  JointLimit[3].Lower = CRANEJointLimit[3].Lower;
}


/************************************************

      void ServoOnOff(int torque)

      概要：DynamixelのWrite_DataでサーボモーターのトルクのOnOffをする

      引数：
            int truque・・・トルク(1…ON,0…OFF)

      戻り値：なし

*************************************************/
void Craneplus::ServoOnOff(int torque)
{
  int i = 0;
  uchar buf[8] = {0};
  for(i=0;i<ARM_FREEDOM;i++)
    {
      buf[0] = 0xff;
      buf[1] = 0xff;
      buf[2] = (i+1) & 0xff;
      buf[3] = 0x04;
      buf[4] = 0x03;
      buf[5] = 0x18;
      buf[6] = torque & 0xff;
      buf[7] = calcCheckSum(buf, sizeof(buf));
      
      serialWrite(buf, sizeof(buf));
      checkserial();
    } 
}


/************************************************

      void ArmAction()

      概要：DynamixelのRegWrite-ActionでWritedata[]に書き込まれたデータをDynamixelに送信する

      引数：なし

      戻り値：なし

*************************************************/
void Craneplus::ArmAction()
{
	int i;
	for (i = 0; i < ARM_FREEDOM; i++)
	{
		RegWrite(i+1,Writedata);
	}
	Action();
}


/************************************************

      void CRANEcloseGripper()

      概要：CRANEのハンドを閉じる

      引数：なし

      戻り値：なし

*************************************************/
void Craneplus::CRANEcloseGripper()
{
  Writedata[ARM_FREEDOM-1].Angle = Hand_LimitMin;
  RegWrite(ARM_FREEDOM, Writedata);
  
  Action();
}


/************************************************

      void CRANEopenGripper()

      概要：CRANEのハンドを開く

      引数：なし

      戻り値：なし

*************************************************/
void Craneplus::CRANEopenGripper()
{
  Writedata[ARM_FREEDOM-1].Angle = Hand_LimitMax;
  RegWrite(ARM_FREEDOM, Writedata);
  
  Action();
}


/************************************************

      void CRANEopenGripper()

      概要：CRANEのハンド指定した開度でを開く

      引数：double angleRatio・・・開度

      戻り値：なし

*************************************************/
void Craneplus::CRANEmoveGripper(double angleRatio)
{
  Writedata[ARM_FREEDOM-1].Angle = (Hand_LimitMax-Hand_LimitMin)*(angleRatio*0.01)+Hand_LimitMin;
  RegWrite(ARM_FREEDOM, Writedata);

  Action(); 
}


/************************************************

	int CartesianLimitJudgement( double x , double y , double z )
	
	概要：Catesianソフトリミットの判定を行う

	引数：
		double x・・・x[mm]
		double y・・・y[mm]
		double z・・・z[mm]

	戻り値：Cartesianソフトリミットを満たしていればtrue、そうでなければfalse

*************************************************/
int Craneplus::CartesianLimitJudgement( double x , double y , double z )
{
  if(( x > CRANECartesianLimit.x.Upper )||
     ( x < CRANECartesianLimit.x.Lower )||
     ( y > CRANECartesianLimit.y.Upper )||
     ( y < CRANECartesianLimit.y.Lower )||
     ( z > CRANECartesianLimit.z.Upper )||
     ( z < CRANECartesianLimit.z.Lower )
     ){
    return false;
  }
  
    return true;
}


/************************************************

	int JointLimitJudgement()
	
	概要：Jointソフトリミットの判定を行う

	引数：なし

	戻り値：Jointソフトリミットを満たしていればtrue、そうでなければfalse

*************************************************/
int Craneplus::JointLimitJudgement()
{
  
  for(int i=0;i<ARM_FREEDOM-1;i++){
    if(( Writedata[i].Angle > CRANEJointLimit[i].Upper )||
       ( Writedata[i].Angle < CRANEJointLimit[i].Lower ))
      {
	std::cout<<"ERROR : Wrong Value"<<std::endl<<std::endl;
	return false;
      }
  }
 
    return true;
}


/************************************************

	int CRANELimitJudgement(double x, double y, double z)
	
	概要：CRANE+リミットの判定を行う

	引数：先端座標値
		double x・・・x[mm]
                double y・・・y[mm]
		double z・・・z[mm]

	戻り値：CRANE+リミットを満たしていればtrue、そうでなければfalse

*************************************************/
int Craneplus::CRANELimitJudgement(double x, double y, double z)
{

  x = x - 14.5;
  z = z - 45.4;

  if(sqrt(x*x+z*z+y*y)>314.5)
    {
      return false;
    }
  else if(sqrt(x*x+z*z+y*y) < 200)
    {
      return false;
    }
  else
    return true;

}


/************************************************

       kinematics(double x, double y, double z, double JointPos[])

       概要：アームの逆運動学を計算する

       引数：
            double x・・・x座標
            double y・・・y座標
            double z・・・z座標     
            double JointPos[]・・・計算した角度を格納する変数  
    
       戻り値：関節角度

*************************************************/
void Craneplus::kinematics(double x, double y, double z, double JointPos[])
{
	double x3;
	double y3;
	double z3;
	double theta1;
	double theta2;
	double theta3;
	double theta4;
	int i;
	double sentan = 0;
	double sentan_rad;
	double theta3_value;
	double deg;
	double rad;


	deg = M_PI / 180;  //degをradへ
	rad = 180 / M_PI;  //radをdegへ

	//座標原点合わせ
	x = x - 14.5;
	z = z - 45.4;

	if (x == 0)
		theta1 = 0;
	else
		theta1 = atan2(y, x);


	for (i = 0; i < 92; i++)
	{
		sentan_rad = sentan*deg;
		x3 = x - r3*cos(sentan_rad)*cos(theta1);
		y3 = y - r3*cos(sentan_rad)*sin(theta1);
		z3 = z - r3*sin(sentan_rad);

		theta3_value = ((x3*cos(theta1) + y3*sin(theta1))*(x3*cos(theta1) + y3*sin(theta1)) + z3*z3 - r2*r2 - r1*r1) / (2 * r1*r2);
		theta3 = acos(theta3_value);

		if (theta3 > 0)
		{
			//printf("theta3が+は綺麗じゃない\n");
			theta3 = -theta3;
		}


		if (i > 90)
		{
			//printf("この位置に移動できません\nquit program\n");
			//exit();
		}
		else if (theta3 != theta3)
		{
			//printf("sentan = %f\n", sentan);
			//printf("この位置に移動できません\n");
			sentan++;
		}

		else
		{
			//printf("先端角度は%f\n", sentan);
			//printf("x3=%f\n", x3);
			//printf("y3=%f\n", y3);
			//printf("angle2=%f\n", angle2);
			break;
		}
	}

	if (z >= 0)
	{
		//θ2の計算
		double alfa;
		alfa = atan((-r2*sin(theta3)) / (r1 + r2*cos(theta3)));

		theta2 = acos(sqrt(x3*x3 + y3*y3) / sqrt((r1 + r2*cos(theta3))*(r1 + r2*cos(theta3)) + (r2*sin(theta3))*(r2*sin(theta3)))) + alfa;

		if (theta2 < 0)
		{
			//printf("theta2がマイナス\n");
			theta3 = -theta3;
			alfa = atan((-r2*sin(theta3)) / (r1 + r2*cos(theta3)));
			theta2 = acos(sqrt(x3*x3 + y3*y3) / sqrt((r1 + r2*cos(theta3))*(r1 + r2*cos(theta3)) + (r2*sin(theta3))*(r2*sin(theta3)))) + alfa;
		
		}
		double kenzanx3;
		kenzanx3 = cos(theta1)*(r1*cos(theta2) + r2*cos((theta3 + theta2)));
		double kenzany3;
		kenzany3 = sin(theta1)*(r1*cos(theta2) + r2*cos((theta3 + theta2)));

		if (x3 - kenzanx3 > 1 || x3 - kenzanx3 < -1|| y3 - kenzany3 > 1 || y3 - kenzany3 < -1)
		{
	theta2 = acos(-sqrt(x3*x3 + y3*y3) / sqrt((r1 + r2*cos(theta3))*(r1 + r2*cos(theta3)) + (r2*sin(theta3))*(r2*sin(theta3)))) + alfa;
		}
	}

	else
	{
		//θ2の計算
		double alfa;
		alfa = atan((-r2*sin(theta3)) / (r1 + r2*cos(theta3)));
		theta2 = -acos(sqrt(x3*x3 + y3*y3) / sqrt((r1 + r2*cos(theta3))*(r1 + r2*cos(theta3)) + (r2*sin(theta3))*(r2*sin(theta3)))) + alfa;
	}



	theta4 = sentan_rad - theta2 - theta3;

	//第一関節AX-12Aの可動範囲外
	if ((theta1 > 150*deg && theta1 <= 180*deg) || (theta1 < -150*deg && theta1 >= -180*deg))
	{
		theta1 = theta1 - M_PI;
		theta2 = M_PI - theta2;
		theta3 = -theta3;
		theta4 = -theta4;
	}

	//アームが立った状態からの角度
	JointPos[0] = theta1*rad;
	JointPos[1] = 90 - theta2*rad;
	JointPos[2] = -theta3*rad;
	JointPos[3] = -theta4*rad;

}
