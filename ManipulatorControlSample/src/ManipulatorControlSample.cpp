// -*- C++ -*-
/*!
 * @file  ManipulatorControlSample.cpp
 * @brief ManipulatorControlSample
 * @date $Date$
 *
 * $Id$
 */

#include "ManipulatorControlSample.h"
#include <math.h>

// Module specification
// <rtc-template block="module_spec">
static const char* manipulatorcontrolsample_spec[] =
  {
    "implementation_id", "ManipulatorControlSample",
    "type_name",         "ManipulatorControlSample",
    "description",       "ManipulatorControlSample",
    "version",           "1.0.0",
    "vendor",            "rsdlab",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.Speed", "20",

    // Widget
    "conf.__widget__.Speed", "text",
    // Constraints

    "conf.__type__.Speed", "int",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ManipulatorControlSample::ManipulatorControlSample(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_ManipulatorCommonInterface_CommonPort("ManipulatorCommonInterface_Common"),
    m_ManipulatorCommonInterface_MiddlePort("ManipulatorCommonInterface_Middle")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
ManipulatorControlSample::~ManipulatorControlSample()
{
}



RTC::ReturnCode_t ManipulatorControlSample::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  m_ManipulatorCommonInterface_CommonPort.registerConsumer("ManipulatorCommonInterface_Common", "JARA_ARM::ManipulatorCommonInterface_Common", m_ManipulatorCommonInterface_Common);
  m_ManipulatorCommonInterface_MiddlePort.registerConsumer("ManipulatorCommonInterface_Middle", "JARA_ARM::ManipulatorCommonInterface_Middle", m_ManipulatorCommonInterface_Middle);
  
  // Set CORBA Service Ports
  addPort(m_ManipulatorCommonInterface_CommonPort);
  addPort(m_ManipulatorCommonInterface_MiddlePort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("Speed", m_Speed, "20");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ManipulatorControlSample::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ManipulatorControlSample::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ManipulatorControlSample::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t ManipulatorControlSample::onActivated(RTC::UniqueId ec_id)
{
  //プロバイダより遅くActivateするため
  sleep(1);

  //関節速度の設定
  JARA_ARM::ULONG spdRation;
  spdRation = m_Speed;//%
  m_ManipulatorCommonInterface_Middle->setSpeedJoint(spdRation);

  //ジョイントソフトリミットの初期化(AX-12A対応)
  JARA_ARM::LimitSeq softLimit;
  softLimit.length(5);
  softLimit[0].upper = 300;
  softLimit[0].lower = 0;
  softLimit[1].upper = 300;
  softLimit[1].lower = 0;
  softLimit[2].upper = 300;
  softLimit[2].lower = 0;
  softLimit[3].upper = 300;
  softLimit[3].lower = 0;
  m_ManipulatorCommonInterface_Common->setSoftLimitJoint(softLimit);

  //範囲ソフトリミットの初期化(CRANE+対応)
  JARA_ARM::LimitValue xLimit;
  JARA_ARM::LimitValue yLimit;
  JARA_ARM::LimitValue zLimit;
  xLimit.upper = 329;
  xLimit.lower = -300;
  yLimit.upper = 314.5;
  yLimit.lower = -314.5;
  zLimit.upper = 359.9;
  zLimit.lower = 0;
  m_ManipulatorCommonInterface_Middle->setSoftLimitCartesian(xLimit, yLimit, zLimit);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ManipulatorControlSample::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ManipulatorControlSample::onExecute(RTC::UniqueId ec_id)
{
  int c;

  std::cout << "コマンドを選択してください" << std::endl;
  std::cout << "1 : サーボON" << std::endl;
  std::cout << "2 : サーボOFF" << std::endl;
  std::cout << "3 : アーム先端の移動" << std::endl;
  std::cout << "4 : アーム関節の回転" << std::endl;
  std::cout << "5 : アーム先端座標の計算" << std::endl;
  std::cout << "6 : グリッパ開閉" << std::endl;
  std::cout << "7 : グリッパ閉" << std::endl;
  std::cout << "8 : グリッパ開" << std::endl;
  std::cout << "9 : 終了" << std::endl;


  std::cout << ">>";
  std::cin >> c; 
  std::cout << std::endl; 

  if(c == 1)
    {
      m_rid=m_ManipulatorCommonInterface_Common->servoON();
      if(m_rid->id != 0){//Error
	std::cout<<"Servo ON ERROR"<<std::endl;
	std::cout<<m_rid->comment<<std::endl<<std::endl;
      }
    }
  else if(c == 2)
    {
      m_rid=m_ManipulatorCommonInterface_Common->servoOFF();
      if(m_rid->id != 0){//Error
	std::cout<<"Servo OFF ERROR"<<std::endl;
	std::cout<<m_rid->comment<<std::endl<<std::endl;
      }
    }
  else if(c == 3)
    {
      double x;
      double y;
      double z;
      JARA_ARM::CarPosWithElbow pos;
      
      std::cout << "座標を入力してください" << std::endl;
      std::cout << "x座標 : "; 
      std::cin >> x;
      std::cout << "y座標 : ";
      std::cin >> y;
      std::cout << "z座標 : ";
      std::cin >> z;
      std::cout << std::endl; 
      
      //姿勢は自動で計算されるため初期化のみ
      //1列目
      pos.carPos[0][0]=cos(0);
      pos.carPos[1][0]=sin(0);
      pos.carPos[2][0]=0.0;
      
      //2列目
      pos.carPos[0][1]=-sin(0);
      pos.carPos[1][1]=cos(0);
      pos.carPos[2][1]=0.0;
      
      //3列目
      pos.carPos[0][2]=0.0;
      pos.carPos[1][2]=0.0;
      pos.carPos[2][2]=1.0;
      
      //4列目
      pos.carPos[0][3]=x;//[mm]
      pos.carPos[1][3]=y;
      pos.carPos[2][3]=z;
      
      m_rid=m_ManipulatorCommonInterface_Middle->movePTPCartesianAbs(pos);
      if(m_rid->id != 0){//Error
	std::cout<<"movePTPCartesianAbs ERROR"<<std::endl;
	std::cout<<m_rid->comment<<std::endl<<std::endl;
      }
    }
  
  else if(c == 4)
    {
      JARA_ARM::JointPos jointPoint;
      jointPoint.length(4);
      std::cout << "下からグリッパに向かって第1関節〜第4関節" << std::endl << "関節角度を入力してください　単位[°]" << std::endl;
      std::cout << "第1関節の角度 : ";
      std::cin >>jointPoint[0];
      std::cout << "第2関節の角度 : ";
      std::cin >>jointPoint[1];
      std::cout << "第3関節の角度 : ";
      std::cin >>jointPoint[2];
      std::cout << "第4関節の角度 : ";
      std::cin >>jointPoint[3];
      std::cout << std::endl; 
      
      m_rid=m_ManipulatorCommonInterface_Middle->movePTPJointAbs(jointPoint);
      if(m_rid->id != 0){//Error
	std::cout<<"movePTPJointAbs ERROR"<<std::endl;
	std::cout<<m_rid->comment<<std::endl<<std::endl;
      }
    }

  else if(c == 5)
    {
      JARA_ARM::CarPosWithElbow pos;
      pos.carPos[0][0]=cos(0);
      pos.carPos[1][0]=sin(0);
      pos.carPos[2][0]=0.0;
      
      //2列目
      pos.carPos[0][1]=-sin(0);
      pos.carPos[1][1]=cos(0);
      pos.carPos[2][1]=0.0;
      
      //3列目
      pos.carPos[0][2]=0.0;
      pos.carPos[1][2]=0.0;
      pos.carPos[2][2]=1.0;
      
      //4列目
      pos.carPos[0][3]=0;//[mm]
      pos.carPos[1][3]=0;
      pos.carPos[2][3]=0;
      m_rid=m_ManipulatorCommonInterface_Middle->getFeedbackPosCartesian(pos);
      if(m_rid->id != 0){//Error
	std::cout<<"getFeedbackPosCartesian ERROR"<<std::endl;
	std::cout<<m_rid->comment<<std::endl<<std::endl;
      }
    }  
  
  else if(c == 6)
    {
      JARA_ARM::ULONG angleRatio;
      std::cout << "開度を入力してください 1~100[%]" << std::endl;
      std::cin >> angleRatio;
      std::cout << std::endl; 
      
      if(angleRatio >= 1 && angleRatio <=100){
	m_rid=m_ManipulatorCommonInterface_Middle->moveGripper(angleRatio);
	if(m_rid->id != 0){//Error
	  std::cout<<"moveGripper ERROR"<<std::endl;
	  std::cout<<m_rid->comment<<std::endl<<std::endl;
	}
      }
      else 
	std::cout << "無効な値です" << std::endl;
    }

  else if(c == 7)
    {
      m_rid=m_ManipulatorCommonInterface_Middle->closeGripper();
      if(m_rid->id != 0){//Error
	std::cout<<"closeGripper ERROR"<<std::endl;
	std::cout<<m_rid->comment<<std::endl<<std::endl;
      }
    }
  
  else if (c == 8)
    {
      m_rid=m_ManipulatorCommonInterface_Middle->openGripper();
      if(m_rid->id != 0){//Error
	std::cout<<"openGripper ERROR"<<std::endl;
	std::cout<<m_rid->comment<<std::endl<<std::endl;
      }
    }
  
  else if(c == 9)
    {
      std::cout << "END" << std::endl;
      std::cout << "eclipseでシステムをDeactivateしてください" << std::endl<<std::endl;
      deactivate(ec_id);
    }
  
  else 
    std::cout << "無効な値です" << std::endl<<std::endl;
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ManipulatorControlSample::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ManipulatorControlSample::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ManipulatorControlSample::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ManipulatorControlSample::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ManipulatorControlSample::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void ManipulatorControlSampleInit(RTC::Manager* manager)
  {
    coil::Properties profile(manipulatorcontrolsample_spec);
    manager->registerFactory(profile,
                             RTC::Create<ManipulatorControlSample>,
                             RTC::Delete<ManipulatorControlSample>);
  }
  
};


