// -*- C++ -*-
/*!
 * @file  RT_CRANE_RTC.cpp
 * @brief RT_CRANE_RTC
 * @date $Date$
 *
 * $Id$
 */

#include "RT_CRANE_RTC.h"
#include "Crane.h"

// Module specification
// <rtc-template block="module_spec">
static const char* rt_crane_rtc_spec[] =
  {
    "implementation_id", "RT_CRANE_RTC",
    "type_name",         "RT_CRANE_RTC",
    "description",       "RT_CRANE_RTC",
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
RT_CRANE_RTC::RT_CRANE_RTC(RTC::Manager* manager)
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
RT_CRANE_RTC::~RT_CRANE_RTC()
{
}



RTC::ReturnCode_t RT_CRANE_RTC::onInitialize()
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
RTC::ReturnCode_t RT_CRANE_RTC::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RT_CRANE_RTC::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RT_CRANE_RTC::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RT_CRANE_RTC::onActivated(RTC::UniqueId ec_id)
{
  crane.openSerialPort(m_port_name.c_str());
  std::cout << "openSerialPort" << std::endl;
  crane.initArm();
  std::cout << "initArm" << std::endl << std::endl;
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RT_CRANE_RTC::onDeactivated(RTC::UniqueId ec_id)
{
  crane.ServoOnOff(0);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RT_CRANE_RTC::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RT_CRANE_RTC::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RT_CRANE_RTC::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RT_CRANE_RTC::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RT_CRANE_RTC::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RT_CRANE_RTC::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void RT_CRANE_RTCInit(RTC::Manager* manager)
  {
    coil::Properties profile(rt_crane_rtc_spec);
    manager->registerFactory(profile,
                             RTC::Create<RT_CRANE_RTC>,
                             RTC::Delete<RT_CRANE_RTC>);
  }
  
};


