
#include "C5Export.h"
#include "C5Core.h"
#include "C5Attribute.h"
#include "C5AttributeRow.h"


C5AttributeHandle C5CallType C5AttributeCreate(const char* ipAttrName, int iAttrType)
{
  return C5Attribute::CreateAttribute(ipAttrName, (C5AttributeType) iAttrType);
}

int C5CallType C5AttributeAddValue(C5AttributeHandle iAttr, const char* iValue)
{
  C5Attribute* pAttr = (C5Attribute*) iAttr;
  pAttr->AddStringValue(iValue);
  return pAttr->GetAllNamedValues().size() - 1;
}

// for any type
const char* C5CallType C5AttributeGetValue(C5AttributeHandle iAttr)
{
  C5Attribute* pAttr = (C5Attribute*) iAttr;
  return pAttr->GetValue().c_str();
}
// for date, time, timestamp (using convert required), continues
float C5CallType C5AttributeGetContinuesValue(C5AttributeHandle iAttr)
{
  C5Attribute* pAttr = (C5Attribute*) iAttr;
  return pAttr->GetContinuesValue();
}

// for discrete and enumeration types
int C5CallType C5AttributeGetDiscreteValue(C5AttributeHandle iAttr)
{
  C5Attribute* pAttr = (C5Attribute*) iAttr;
  return pAttr->GetDiscreteValue();
}

// set values allow only after add to AttributeRow
bool C5CallType C5AttributeSetValueString(C5AttributeHandle iAttr, const char* ipValue)
{
  C5Attribute* pAttr = (C5Attribute*) iAttr;
  return pAttr->SetValue(ipValue);
}

bool C5CallType C5AttributeSetValueFloat(C5AttributeHandle iAttr, float iValue)
{
  C5Attribute* pAttr = (C5Attribute*) iAttr;
  return pAttr->SetValue(iValue);
}

bool C5CallType C5AttributeSetValueInt(C5AttributeHandle iAttr, int iValue)
{
  C5Attribute* pAttr = (C5Attribute*) iAttr;
  return pAttr->SetValue(iValue);
}

C5AttributeRowHandle C5CallType C5AttributeRowCreate(C5AttributeHandle TagetAttr)
{
  return new C5AttributeRow((C5Attribute*) TagetAttr);
}

int C5CallType C5AttributeRowAdd(C5AttributeRowHandle iTaget, C5AttributeHandle TagetAttr)
{
  C5AttributeRow* pRow = (C5AttributeRow*)iTaget;
  pRow->PushBackAttrebute((C5Attribute*) TagetAttr);
  return pRow->GetSize() - 1;
}

void C5CallType C5AttributeRowInit(C5AttributeRowHandle iTaget, C5Handle iC5instance)
{
  C5AttributeRow* pRow = (C5AttributeRow*)iTaget;
  pRow->Init((C5Core*) iC5instance);
}

C5AttributeDataHandle C5CallType C5AttributeRowGetRawData(C5AttributeRowHandle iTaget)
{
  C5AttributeRow* pRow = (C5AttributeRow*)iTaget;
  return pRow->GetRawData();
}

C5Handle C5CallType C5InstanceCreate( const char* InfoOutputFile, const char* ModelName, bool IsPartitionDiscreteValuesIntoSubsets,
                                     bool IsUseRuleClassifier, int UtilitySortRulesIntoBandsValue, int BoostTrialsNumber,
                                     bool IsDisplayAttributesBeforeConstructingClassifier, bool IsUseSoftThresholds,
                                     bool IsNotSafeClassifierToFile, int MinimumCasesForSplitTwoBranches, bool IsCarryOutCrossValidation, 
                                     int CrossValidationFolds)
{
  C5Params p;
  sprintf_s(p.InfoOutputFile, 512, "%s", InfoOutputFile);
  sprintf_s(p.ModelName, 512, "%s",  ModelName);
  p.IsPartitionDiscreteValuesIntoSubsets = IsPartitionDiscreteValuesIntoSubsets;
  p.IsUseRuleClassifier = IsUseRuleClassifier;
  p.UtilitySortRulesIntoBandsValue = UtilitySortRulesIntoBandsValue;
  p.BoostTrialsNumber = BoostTrialsNumber;
  p.IsDisplayAttributesBeforeConstructingClassifier = IsDisplayAttributesBeforeConstructingClassifier;
  p.IsUseSoftThresholds = IsUseSoftThresholds;
  p.IsNotSafeClassifierToFile = IsNotSafeClassifierToFile;
  p.MinimumCasesForSplitTwoBranches = MinimumCasesForSplitTwoBranches;
  p.IsCarryOutCrossValidation = IsCarryOutCrossValidation;
  p.CrossValidationFolds = CrossValidationFolds;
  return new C5Core(p);
}

bool C5CallType C5InstanceInit(C5Handle iC5instance, C5AttributeRowHandle iAttrRow)
{
  C5Core* pCore = (C5Core*) iC5instance;
  return pCore->Init((C5AttributeRow*)iAttrRow);
}


bool C5CallType C5InstanceAddTrainData(C5Handle iC5instance, C5AttributeDataHandle iC5Data)
{
  C5Core* pCore = (C5Core*) iC5instance;

  int memSize = sizeof(AttributeValue) * (pCore->GetMyAttributes()->GetSize() + 1);
  AttributeValue* dataCopy = (AttributeValue*) malloc(memSize);
  memcpy(dataCopy, iC5Data, memSize);
  return pCore->AddTeachData(dataCopy);
}

bool C5CallType C5InstanceReadTrainDataSTDFile(C5Handle iC5instance)
{
  C5Core* pCore = (C5Core*) iC5instance;
  return pCore->ReadTrainData();
}

bool C5CallType C5InstanceReadTrainDataSPFile(C5Handle iC5instance, const char* ipFile)
{
  C5Core* pCore = (C5Core*) iC5instance;
  return pCore->ReadTrainData(ipFile);
}

bool C5CallType C5InstanceTrain(C5Handle iC5instance)
{
  C5Core* pCore = (C5Core*) iC5instance;
  return pCore->Train();
}

bool C5CallType C5InstanceReadFromFileSTDFile(C5Handle iC5instance)
{
  C5Core* pCore = (C5Core*) iC5instance;
  return pCore->LoadClassifier();
}

bool C5CallType C5InstanceReadFromFileSPFile(C5Handle iC5instance, const char* ipFileName)
{
  C5Core* pCore = (C5Core*) iC5instance;
  return pCore->LoadClassifier(ipFileName);
}

int C5CallType C5InstanceClassify(C5Handle iC5instance, C5AttributeDataHandle iC5Data)
{
  C5Core* pCore = (C5Core*) iC5instance;
  return pCore->ClassifyValue((AttributeValue*) iC5Data);
}

//** get statistical data from classifier
float C5CallType C5InstanceGetAttributeUsage(C5Handle iC5instance, const char* ipAttibuteName)
{
  C5Core* pCore = (C5Core*) iC5instance;
  return pCore->GetAttributeUsage(ipAttibuteName);
}

float C5CallType C5InstanceGetAttributeUsage(C5Handle iC5instance, int iAttrId)
{
  C5Core* pCore = (C5Core*) iC5instance;
  return pCore->GetAttributeUsage(iAttrId);
}

  // how many cases analyzed class classified as other class
int C5CallType C5InstanceGetResultClassificationValue1(C5Handle iC5instance, const char* ipAnalyzeClassName, const char* ipClassificateAsClassName)
{
  C5Core* pCore = (C5Core*) iC5instance;
  return pCore->GetResultClassificationValue(ipAnalyzeClassName, ipClassificateAsClassName);
}

int C5CallType C5InstanceGetResultClassificationValue2(C5Handle iC5instance, int ipAnalyzeClassId, int ipClassificateAsClassId)
{
  C5Core* pCore = (C5Core*) iC5instance;
  return pCore->GetResultClassificationValue(ipAnalyzeClassId, ipClassificateAsClassId);
}
