// COPYRIGHT: Open source by GPL (GNU General Public License)
// Based on C5.0 GPL Edition provided by Rulequest Research Pty Ltd.
//===================================================================
//
// C5Core wrap (for hide a lot of private mambers)
//
//===================================================================
//  FEB 2013  Creation:                        Ramirez, GOD RECEPRION
//===================================================================

#include "C5Core.h"

class C5
{
public:
  C5(C5Params iParams) { _core = new C5Core(iParams); }
  ~C5() { delete _core; }

//** Initialize classifier
  // apply specified attributes
  bool Init(C5AttributeRow* iAttrebuteRow) { return _core->Init(iAttrebuteRow); }
  // read names from C5Params::ModelName.names file 
  bool ReadAttributes() { return _core->ReadAttributes(); }

  C5AttributeRow* GetMyAttributes() { return _core->GetMyAttributes(); }

//** Build classifier
  // here SET value of target attribute
  bool AddTeachData(C5AttributeRow& ipValues) { return _core->AddTeachData(ipValues); }
  // C5 core delete this value, memory should be allocated by malloc
  bool AddTeachData(AttributeValue* ipValues) { return _core->AddTeachData(ipValues); }

  // read train data block from file
  bool ReadTrainData() { return _core->ReadTrainData(); }
  // here you can specify name with path or other than C5Params::ModelName name. Wrong file will case crash 
  bool ReadTrainData(const char* ipFileName) { return _core->ReadTrainData(ipFileName); }

  // generate classifier on specified train data
  bool Train() { return _core->Train(); }


  // you can load previous step building classifier from file C5Params::ModelName.tree or C5Params::ModelName.rules.
  // be attention with params like C5Params::BoostTrialsNumber
  bool LoadClassifier() { return _core->LoadClassifier(); }

  // here you can specify name with path or other than C5Params::ModelName name. Wrong file will case crash 
  bool LoadClassifier(const char* ipFileName) { return _core->LoadClassifier(ipFileName); }


//** use classifier
  // here GET value of target attribute
  bool ClassifyValue(C5AttributeRow& ipValues) { return _core->ClassifyValue(ipValues); }
  // return target class ID
  int  ClassifyValue(AttributeValue* ipValues) { return _core->ClassifyValue(ipValues); }

//** get statistic of classification building
  // usage specified attribute in classification
  float GetAttributeUsage(C5Attribute* ipAttribute) { return _core->GetAttributeUsage(ipAttribute); }
  float GetAttributeUsage(const char* ipAttibuteName) { return _core->GetAttributeUsage(ipAttibuteName); }
  float GetAttributeUsage(int iAttrId) { return _core->GetAttributeUsage(iAttrId); }

  // how many cases analyzed class classified as other class
  int GetResultClassificationValue(const char* ipAnalyzeClassName, const char* ipClassificateAsClassName) { return _core->GetResultClassificationValue( ipAnalyzeClassName, ipClassificateAsClassName); }
  int GetResultClassificationValue(int ipAnalyzeClassId, int ipClassificateAsClassId) { return _core->GetResultClassificationValue( ipAnalyzeClassId, ipClassificateAsClassId); }

private:
  C5Core* _core;
};