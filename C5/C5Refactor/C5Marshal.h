// COPYRIGHT: Open source by GPL (GNU General Public License)
// Based on C5.0 GPL Edition provided by Rulequest Research Pty Ltd.
//===================================================================
//
// Utilities for converting (marshaling) types betweens each others
//
//===================================================================
//  FEB 2013  Creation:                       Ramirez, GOD RECEPRION
//===================================================================


#ifndef C5Marshal_H
#define C5Marshal_H

#include <iostream>
#include <sstream>
#include <string>

namespace C5Marshal
{
  template<typename T>
  std::string ToString(const T& v)
  {
    std::ostringstream ss;
    ss.precision(12);
    ss << v;
    return ss.str();
  }

  template<>
  std::string ToString<std::string>(const std::string& v)
  {
    return v;
  }

  template<typename T>
  T Parse(const std::string& str)
  {
    T ret;
    return ret;
  }

  template<typename T>
  bool TryParse(const std::string& str, T& oValue)
  {
    std::istringstream ss(str);
    ss >> oValue;
    return ToString(oValue).find(str.substr(0, str.length() - 1)) == 0; // printed value start with source string
  }

  // specialized template implementation for string 
  template<>
  bool TryParse<std::string>(const std::string& str, std::string& oValue)
  {
    oValue = str;
    return true;
  }

  template<typename T>
  std::string ArrayToString(const T* ipArray, unsigned int iArrayLen)
  {
    std::string value;
    for(unsigned int i = 0; i < iArrayLen; i++) {
      value += ToString<T>(ipArray[i]);
      if(i != iArrayLen - 1)
        value += ",";
    }
    return value;
  }

  template<typename T>
  unsigned int ArrayParse(std::string& iString, T* opArray, unsigned int iArrayLen)
  {
    unsigned int valueCounter = 0;
    int idx = 0;
    int nextIdx = 0;
    while(nextIdx != -1) {
      nextIdx = iString.find_first_of(',', idx);
      std::string& val = iString.substr(idx, nextIdx != -1 ? nextIdx - idx : iString.length() - idx);
      idx = nextIdx + 1;

      // if unable parse read next
      valueCounter++;
    }
    return valueCounter;
  }
};

#endif //C5Marshal_H
