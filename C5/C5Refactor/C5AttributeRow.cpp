// COPYRIGHT: Open source by GPL (GNU General Public License)
// Based on C5.0 GPL Edition provided by Rulequest Research Pty Ltd.
//===================================================================
//
// Implementaion of attribute row container 
//
//===================================================================
//  FEB 2013  Creation:                       Ramirez, GOD RECEPRION
//===================================================================

#include "C5AttributeRow.h"
#include "C5Attribute.h"

C5AttributeRow::C5AttributeRow(C5Attribute* iTagetAttebute)
{
  _tagetAttr = iTagetAttebute;
  _c5Instance = NULL;
  _values = NULL;
  iTagetAttebute->_isTagetAttr = true;
}

bool C5AttributeRow::PushBackAttrebute(C5Attribute* iValue)
{
  _attrebutes.push_back(iValue);
  _name2Id.insert(std::pair<std::string, int>( iValue->_name, _attrebutes.size() - 1));
   return true;
}

void C5AttributeRow::Init(C5Core* ipC5Coreinstance)
{
  _c5Instance = ipC5Coreinstance;
  _values = (_attribute_value*)malloc(sizeof( _attribute_value) * _attrebutes.size() + 1);
  for(unsigned int i = 0; i < _attrebutes.size(); i++) {
    _attrebutes[i]->_value = &_values[i + 1];
  }
  _tagetAttr->_value = &_values[0];
}

C5Attribute* C5AttributeRow::operator[](int i)
{
  if( i < (int)_attrebutes.size())
    return _attrebutes[i];
  return NULL;
}

int C5AttributeRow::GetIdByName(std::string& iName)
{
  std::map<std::string, int>::iterator it = _name2Id.find(iName);
  if(it != _name2Id.end())
    return it->second;
  return -1;
}

C5Attribute* C5AttributeRow::operator[](std::string& iName)
{
  int idx = GetIdByName(iName);
  return idx != -1 ? _attrebutes[idx] : NULL;
}

C5Attribute*  C5AttributeRow::operator[](const char* iName)
{
  int idx = GetIdByName(std::string(iName));
  return idx != -1 ? _attrebutes[idx] : NULL;
}

std::string C5AttributeRow::ConvertToC5LineFormat()
{
  std::string oValue;
  for(int i = 0; i < GetSize(); i++)
    oValue += _attrebutes[i]->GetValue() + ",";
  oValue += GetTagetAttrebute().GetValue() + ".";
  return oValue;
}

#pragma warning (disable:4996)
void C5AttributeRow::ConvertToC5LineFormat(char* iTagetBuffer)
{
  int pos = 0;
  for(int i = 0; i < GetSize(); i++)
    pos += sprintf(&iTagetBuffer[pos], "%s,", _attrebutes[i]->GetValue().c_str());
  sprintf(&iTagetBuffer[pos], "%s.\n", GetTagetAttrebute().GetValue().c_str());
}
#pragma warning (default:4996)

