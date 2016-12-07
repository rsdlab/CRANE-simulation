//ReturnID.h
#ifndef __ReturnID_H__
#define __ReturnID_H__

static JARA_ARM::RETURN_ID* RETURN_CODE(int id, const char *comment)
{
  JARA_ARM::RETURN_ID_var RETURNCODE = new JARA_ARM::RETURN_ID;
  RETURNCODE->id = id;
  RETURNCODE->comment = comment;
  return RETURNCODE._retn(); 
}


#endif//__ReturnID_H__
