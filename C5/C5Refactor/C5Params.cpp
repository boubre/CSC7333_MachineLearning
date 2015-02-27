// COPYRIGHT: Open source by GPL (GNU General Public License)
// Based on C5.0 GPL Edition provided by Rulequest Research Pty Ltd.
//===================================================================
//
// algorithm parameters object 
//
//===================================================================
//  FEB 2013  Creation:                       Ramirez, GOD RECEPRION
//===================================================================

#include "C5Params.h"

C5Params::C5Params()
{
  sprintf_s(ModelName, C5ParamsStringSize, "NONE");
  InfoOutputFile[0] = 0;

  IsPartitionDiscreteValuesIntoSubsets = false; 
  IsUseRuleClassifier = false;
  UtilitySortRulesIntoBandsValue = 0;
  BoostTrialsNumber = 1;
  IsDisplayAttributesBeforeConstructingClassifier = false;
  IsUseSoftThresholds = false;
  IsNotSafeClassifierToFile = true;
  MinimumCasesForSplitTwoBranches = 2;
  IsCarryOutCrossValidation = false;
  CrossValidationFolds = 10;
}
