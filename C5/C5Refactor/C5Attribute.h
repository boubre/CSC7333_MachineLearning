// COPYRIGHT: Open source by GPL (GNU General Public License)
// Based on C5.0 GPL Edition provided by Rulequest Research Pty Ltd.
//===================================================================
//
// Implementation of one attribute object 
//
//===================================================================
//  FEB 2013  Creation:                       Ramirez, GOD RECEPRION
//===================================================================

#ifndef C5Attribute_H
#define C5Attribute_H

#include "C5defns.h"
#include <string>
#include <vector>

class C5Core;
class C5AttributeRow;

enum C5AttributeType
{
  eContinuous,
  eDate,
  eTime,
  eTimestamp,
  eDiscrete,
  eOrderedDiscrete,
  eLabel
};

class C5Attribute
{
  friend class C5AttributeRow;
public:
  static C5Attribute* CreateAttribute(const char* iAttrName, C5AttributeType iType);
  static C5Attribute* CreateAttribute(const char* iAttrName, std::vector<std::string> iValues, C5AttributeType iType = eDiscrete);
  static C5Attribute* CreateAttribute(const char* iAttrName, std::string iValue1, std::string iValue2);

  C5AttributeType GetType() const { return _type; }

  const char* GetName() const { return _name.c_str(); }

  // for any type
  std::string GetValue() const;

  // for date, time, timestamp (using convert required), continues
  ContValue GetContinuesValue() const;

  // for discrete and enumeration types
  DiscrValue GetDiscreteValue() const;

  // set values allow only after add to AttributeRow
  bool SetValue(const char* ipValue);
  bool SetValue(float iValue);
  bool SetValue(int iValue);

  const std::vector<std::string>& GetAllNamedValues() const { return _values; }
  int GetClassId(const char* ipClassName);

  void AddStringValue(const char* ipClassName);

  std::string& GetDefinition() { return _defintion; };

private:
  C5Attribute();

  bool _isTagetAttr;

  std::string _defintion;
  std::vector<std::string> _values;
  std::string _name;
  C5AttributeType _type;

  C5AttributeRow* _pMaster;
  _attribute_value* _value;
};


#endif
