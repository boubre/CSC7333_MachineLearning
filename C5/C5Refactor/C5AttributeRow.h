// COPYRIGHT: Open source by GPL (GNU General Public License)
// Based on C5.0 GPL Edition provided by Rulequest Research Pty Ltd.
//===================================================================
//
// Implementaion of attribute row container 
//
//===================================================================
//  FEB 2013  Creation:                       Ramirez, GOD RECEPRION
//===================================================================

#ifndef C5AttributeRow_H
#define C5AttributeRow_H

#include "C5defns.h"
#include <string>
#include <vector>
#include <map>

class C5Core;
class C5Attribute;

typedef _attribute_value AttributeValue;

class C5AttributeRow
{
  friend class C5Attribute;
public:
  // Create ONLY one instance of Attribute row for each 
  C5AttributeRow(C5Attribute* iTagetAttebute);

  C5Attribute& GetTagetAttrebute() { return *_tagetAttr; } 

  bool PushBackAttrebute(C5Attribute* iValie);
  int GetSize() const { return _attrebutes.size(); }
  C5Attribute* operator[](int i);
  C5Attribute* operator[](std::string& iName);
  C5Attribute* operator[](const char* iName);

  int GetIdByName(std::string& iName);

  std::string ConvertToC5LineFormat();
  void ConvertToC5LineFormat(char* iTagetBuffer);


  AttributeValue* GetRawData() const { return _values; }

  void Init(C5Core* ipC5instance);

private:
  C5Core* _c5Instance;

  C5Attribute* _tagetAttr;

  std::vector<C5Attribute*> _attrebutes;
  std::map<std::string, int> _name2Id;
  _attribute_value* _values;
};




#endif

