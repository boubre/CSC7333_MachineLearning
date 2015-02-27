// COPYRIGHT: Open source by GPL (GNU General Public License)
// Based on C5.0 GPL Edition provided by Rulequest Research Pty Ltd.
//===================================================================
//
// algorithm parameters object 
//
//===================================================================
//  FEB 2013  Creation:                       Ramirez, GOD RECEPRION
//===================================================================

#ifndef C5Params_H
#define C5Params_H

#include <string>

#define C5ParamsStringSize 512

struct C5Params
{
public:
  C5Params();

  // if empty, put output to stdout
  char InfoOutputFile[C5ParamsStringSize];

  // file system name space
  char ModelName[C5ParamsStringSize];

  bool IsPartitionDiscreteValuesIntoSubsets; 
  bool IsUseRuleClassifier;

  int UtilitySortRulesIntoBandsValue;

  int BoostTrialsNumber;
  bool IsDisplayAttributesBeforeConstructingClassifier;
  bool IsUseSoftThresholds;
  bool IsNotSafeClassifierToFile;
  int MinimumCasesForSplitTwoBranches;
  bool IsCarryOutCrossValidation;
  int CrossValidationFolds;
};

#endif
