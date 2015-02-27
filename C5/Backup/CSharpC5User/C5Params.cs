using System;
using System.Collections.Generic;
using System.Text;

using System.Runtime.InteropServices;

namespace CSharpC5User
{

    [StructLayout(LayoutKind.Sequential)]
    class C5Params
    {
        public C5Params()
        {
            InitDefaults();
        }

        public void InitDefaults()
        {
            ModelName = "NONE";
            InfoOutputFile = "";

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

        // if empty, put output to stdout
        [MarshalAs(UnmanagedType.LPStr, SizeConst = 512)]
        public string InfoOutputFile;

        // file system name space
        [MarshalAs(UnmanagedType.LPStr, SizeConst = 512)]
        public string ModelName;

        public bool IsPartitionDiscreteValuesIntoSubsets;
        public bool IsUseRuleClassifier;

        public int UtilitySortRulesIntoBandsValue;

        public int BoostTrialsNumber;
        public bool IsDisplayAttributesBeforeConstructingClassifier;
        public bool IsUseSoftThresholds;
        public bool IsNotSafeClassifierToFile;
        public int MinimumCasesForSplitTwoBranches;
        public bool IsCarryOutCrossValidation;
        public int CrossValidationFolds;
    }
}
