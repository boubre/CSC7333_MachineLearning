// COPYRIGHT: Open source by GPL (GNU General Public License)
// Based on C5.0 GPL Edition provided by Rulequest Research Pty Ltd.
//===================================================================
//
// C interface 
//
//===================================================================
//  FEB 2013  Creation:                       Ramirez, GOD RECEPRION
//===================================================================

#ifndef C5Export_H
#define C5Export_H

#include "C5Params.h"

typedef void* C5Handle;
typedef void* C5AttributeHandle;
typedef void* C5AttributeRowHandle;
typedef void* C5AttributeDataHandle;

#define C5CallType __stdcall
#ifdef _C5_
#define C5Export(RetType) extern "C" __declspec(dllexport) RetType C5CallType
#else
#define C5Export(RetType) extern "C" __declspec(dllimport) RetType C5CallType
#endif

//** create attributes
  C5Export(C5AttributeHandle) C5AttributeCreate(const char* ipAttrName, int iAttrType);
  // att string named value to specified attribute, return assigned class ID 
  C5Export(int) C5AttributeAddValue(C5AttributeHandle iAttr, const char* iValue);

  // for any type
  C5Export(const char*) C5AttributeGetValue(C5AttributeHandle iAttr);
  // for date, time, timestamp (using convert required), continues
  C5Export(float) C5AttributeGetContinuesValue(C5AttributeHandle iAttr);
  // for discrete and enumeration types
  C5Export(int) C5AttributeGetDiscreteValue(C5AttributeHandle iAttr);

  // set values allow only after add to AttributeRow
  C5Export(bool) C5AttributeSetValueString(C5AttributeHandle iAttr, const char* ipValue);
  C5Export(bool) C5AttributeSetValueFloat(C5AttributeHandle iAttr, float iValue);
  C5Export(bool) C5AttributeSetValueInt(C5AttributeHandle iAttr, int iValue);

//** create attribute rows
  C5Export(C5AttributeRowHandle) C5AttributeRowCreate(C5AttributeHandle TagetAttr);

  // return assigned row ID
  C5Export(int) C5AttributeRowAdd(C5AttributeRowHandle iTaget, C5AttributeHandle TagetAttr);
  C5Export(void) C5AttributeRowInit(C5AttributeRowHandle iTaget, C5Handle iC5instance);
  C5Export(C5AttributeDataHandle) C5AttributeRowGetRawData(C5AttributeRowHandle iTaget);


// initialize C5 instance
  C5Export(C5Handle)C5InstanceCreate( const char* InfoOutputFile, const char* ModelName, bool IsPartitionDiscreteValuesIntoSubsets,
                                      bool IsUseRuleClassifier, int UtilitySortRulesIntoBandsValue, int BoostTrialsNumber,
                                      bool IsDisplayAttributesBeforeConstructingClassifier, bool IsUseSoftThresholds,
                                      bool IsNotSafeClassifierToFile, int MinimumCasesForSplitTwoBranches, bool IsCarryOutCrossValidation, 
                                      int CrossValidationFolds);

  C5Export(bool) C5InstanceInit(C5Handle iC5instance, C5AttributeRowHandle iAttrRow);


//** construct classifier
  // in data value of target attribute on first place other values are followed in order same as adding order
  C5Export(bool) C5InstanceAddTrainData(C5Handle iC5instance, C5AttributeDataHandle iC5Data);

  C5Export(bool) C5InstanceReadTrainDataSTDFile(C5Handle iC5instance);
  C5Export(bool) C5InstanceReadTrainDataSPFile(C5Handle iC5instance, const char* ipFile);

  C5Export(bool) C5InstanceTrain(C5Handle iC5instance);

  C5Export(bool) C5InstanceReadFromFileSTDFile(C5Handle iC5instance);
  C5Export(bool) C5InstanceReadFromFileSPFile(C5Handle iC5instance, const char* ipFileName);

//** use classifier
  // size and structure of classified data same as train data. Classify change value of first (target) value in array
  C5Export(int) C5InstanceClassify(C5Handle iC5instance, C5AttributeDataHandle iC5Data);


//** get statistical data from classifier
  C5Export(float) C5InstanceGetAttributeUsage1(C5Handle iC5instance, const char* ipAttibuteName);
  C5Export(float) C5InstanceGetAttributeUsage2(C5Handle iC5instance, int iAttrId);

  // how many cases analyzed class classified as other class
  C5Export(int) C5InstanceGetResultClassificationValue1(C5Handle iC5instance, const char* ipAnalyzeClassName, const char* ipClassificateAsClassName);
  C5Export(int) C5InstanceGetResultClassificationValue2(C5Handle iC5instance, int ipAnalyzeClassId, int ipClassificateAsClassId);

#endif

