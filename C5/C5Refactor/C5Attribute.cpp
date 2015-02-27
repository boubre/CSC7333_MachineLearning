// COPYRIGHT: Open source by GPL (GNU General Public License)
// Based on C5.0 GPL Edition provided by Rulequest Research Pty Ltd.
//===================================================================
//
// Implementation of one attribute object 
//
//===================================================================
//  FEB 2013  Creation:                       Ramirez, GOD RECEPRION
//===================================================================

#include "C5Attribute.h"
#include "C5Marshal.h"
#include "C5Core.h"
#include "math.h"

C5Attribute::C5Attribute()
{
  _isTagetAttr = false;
  _pMaster = NULL;
}

C5Attribute* C5Attribute::CreateAttribute(const char* iAttrName, C5AttributeType iType)
{
  //if(iType != eTimestamp && iType != eContinuous && iType != eDate && iType != eTime)
  //  return NULL;
  C5Attribute* attr = new C5Attribute();
  attr->_name = std::string(iAttrName);
  attr->_type = iType;

  switch(iType)
  {
  case eTimestamp:
    {
      attr->_defintion = attr->_name + ": timestamp.";
      break;
    }
  case eContinuous:
    {
      attr->_defintion = attr->_name + ": continuous.";
      break;
    }
  case eDate:
    {
      attr->_defintion = attr->_name + ": date.";
      break;
    }
  case eTime:
    {
      attr->_defintion = attr->_name + ": time.";
      break;
    }
  }
  return attr;
}

C5Attribute* C5Attribute::CreateAttribute(const char* iAttrName, std::string iValue1, std::string iValue2)
{
  C5Attribute* attr = new C5Attribute();
  attr->_type = eDiscrete;
  attr->_values.push_back(iValue1);
  attr->_values.push_back(iValue2);
  attr->_name = std::string(iAttrName);

  attr->_defintion =  attr->_name + ": " + iValue1 + ", " + iValue2 + ".";
  return attr;
}

C5Attribute* C5Attribute::CreateAttribute(const char* iAttrName, std::vector<std::string> iValues, C5AttributeType iType)
{
  if(iType != eOrderedDiscrete && iType != eDiscrete && iType != eLabel)
    return NULL;

  C5Attribute* attr = new C5Attribute();
  attr->_type = iType;
  attr->_values = iValues;
  attr->_name = std::string(iAttrName);

  attr->_defintion = attr->_name + ": " + (iType == eOrderedDiscrete ? " [ordered] " : " ");
  for(unsigned int i = 0; i < attr->_values.size(); i++) {
    attr->_defintion += attr->_values[i] + ( i == attr->_values.size() - 1 ? "." : ", ");
  }
  return attr;
}

// for any type
std::string C5Attribute::GetValue() const
{
  char buf[1024];

  switch(_type)
  {
  case eContinuous: return C5Marshal::ToString(_value->_cont_val);
  case eDate: 
    {
      _pMaster->_c5Instance->DayToDate( (int) _value->_cont_val, buf);
      return buf;
    }

  case eTime:
    {
      _pMaster->_c5Instance->SecsToTime( (int)_value->_cont_val, buf);
      return buf;
    }

  case eTimestamp: 
    {
      ContValue CV = _value->_cont_val;
      _pMaster->_c5Instance->DayToDate((int)(floor(CV / 1440) + _pMaster->_c5Instance->TSBase), buf);
      buf[10] = ' ';
      int Mins = (int) ((CV) - floor(CV / 1440) * 1440);
      _pMaster->_c5Instance->SecsToTime(Mins * 60, buf + 11);
      return buf;
    }
  }

  if(_type == eDiscrete || _type == eOrderedDiscrete) {
    if(_values.size() == 0)
      return C5Marshal::ToString(_value->_discr_val);
    if(_value->_discr_val - 1 < (int)_values.size())
      return _values[_value->_discr_val - 1];
  }
  return "ERROR";
}

// for date, time, timestamp (using convert required), continues
ContValue C5Attribute::GetContinuesValue() const
{
  if(_type != eContinuous && _type != eDate && _type != eTime && _type != eTimestamp || _value == NULL) {
    return (ContValue)1.00E032;
  }
  return _value->_cont_val;
}

// for discrete and enumeration types
DiscrValue C5Attribute::GetDiscreteValue() const
{
  if(_type != eDiscrete && _type != eOrderedDiscrete) {
    return INT_MIN;
  }
  return _value->_discr_val - 1;
}

// set values allow only after add to AttributeRow
bool C5Attribute::SetValue(const char* ipValue)
{
  if(_strcmpi("N/A", ipValue) == 0 || _strcmpi("?", ipValue) == 0) {
    _value->_discr_val = UNKNOWN;
    return true;
  }

  if(_type == eOrderedDiscrete || _type == eDiscrete) {
    for(unsigned int i = 0; i < _values.size(); i++) {
      if(_strcmpi( _values[i].c_str(), ipValue) == 0) {
        _value->_discr_val = i + 2 + (_isTagetAttr ? -1 : 0);
        return true;
      }
    }
    return false;
  }

  if(_type == eDate) {
    _value->_discr_val = _pMaster->_c5Instance->DateToDay(const_cast<char*> (ipValue));
    return _value->_discr_val != 0;
  }

  if(_type == eTime) {
    _value->_discr_val = _pMaster->_c5Instance->TimeToSecs(const_cast<char*> (ipValue));
    return _value->_discr_val != 0;
  }

  if(_type == eTimestamp) {
    _value->_discr_val = _pMaster->_c5Instance->TStampToMins(const_cast<char*> (ipValue));
    return _value->_discr_val != 0;
  }
  return false;
}

bool C5Attribute::SetValue(float iValue)
{
  if(_type != eDate && _type != eTime && _type != eTimestamp && _type != eContinuous)
    return  false;
  _value->_cont_val = iValue;
  return true;
}

bool C5Attribute::SetValue(int iValue)
{
  if(_type != eDiscrete && _type != eOrderedDiscrete)
    return false;

  if(iValue == -1) {
    _value->_discr_val = UNKNOWN;
    return true;
  }

  _value->_discr_val = iValue + 2 + ( _isTagetAttr ? -1 : 0) ;
  return true;
}

int C5Attribute::GetClassId(const char* ipClassName)
{
  for(unsigned int i = 0; i < _values.size(); i++) 
    if(strcmp(_values[i].c_str(), ipClassName) == 0)
      return i;
  return -1;
}


void C5Attribute::AddStringValue(const char* ipClassName)
{
  _values.push_back(ipClassName);
  _defintion = _name + ": " + (_type == eOrderedDiscrete ? " [ordered] " : " ");
  for(unsigned int i = 0; i < _values.size(); i++) {
    _defintion += _values[i] + ( i == _values.size() - 1 ? "." : ", ");
  }
}




