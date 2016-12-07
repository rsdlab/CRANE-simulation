// -*- C++ -*-
/*!
 * @file  CraneplusRTC.cpp
 * @brief CraneplusRTC
 * @date $Date$
 *
 * $Id$
 */

#include "CraneplusRTC.h"
#include "Craneplus.h"

// Module specification
// <rtc-template block="module_spec">
static const char* craneplusrtc_spec[] =
  {
    "implementation_id", "CraneplusRTC",
    "type_name",         "CraneplusRTC",
    "description",       "CraneplusRTC",
    "version",           "1.0.0",
    "vendor",            "rsdlab",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.port_name", "/dev/ttyUSB0",

    // Widget
    "conf.__widget__.port_name", "text",
    // Constraints

    "conf.__type__.port_name", "string",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
CraneplusRTC::CraneplusRTC(RTC::Manager* manager)
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
CraneplusRTC::~CraneplusRTC()
{
}



RTC::ReturnCode_t CraneplusRTC::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  m_ManipulatorCommonInterface_CommonPort.registerProvider("ManipulatorCommonInterface_Common", "JARA_ARM::ManipulatorCommonInterface_Common", m_ManipulatorCommonInterface_Common);
  m_ManipulatorCommonInterface_MiddlePort.registerProvider("ManipulatorCommonInterface_Middle", "JARA_ARM::ManipulatorCommonInterface_Middle", m_ManipulatorCommonInterface_Middle);
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  addPort(m_ManipulatorCommonInterface_CommonPort);
  addPort(m_ManipulatorCommonInterface_MiddlePort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("port_name", m_port_name, "/dev/ttyUSB0");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CraneplusRTC::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CraneplusRTC::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CraneplusRTC::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t CraneplusRTC::onActivated(RTC::UniqueId ec_id)
{
  if(!crane.OpenCOMDevice(m_port_name.c_str()))
    {
      std::cout << "OpenCOMDevice Error!" << std::endl;
    }

  crane.initArm();
  std::cout << "initArm" << std::endl << std::endl;
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CraneplusRTC::onDeactivated(RTC::UniqueId ec_id)
{
  crane.ServoOnOff(0);
  crane.CloseCOMDevice();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CraneplusRTC::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CraneplusRTC::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CraneplusRTC::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CraneplusRTC::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CraneplusRTC::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CraneplusRTC::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void CraneplusRTCInit(RTC::Manager* manager)
  {
    coil::Properties profile(craneplusrtc_spec);
    manager->registerFactory(profile,
                             RTC::Create<CraneplusRTC>,
                             RTC::Delete<CraneplusRTC>);
  }
  
};


