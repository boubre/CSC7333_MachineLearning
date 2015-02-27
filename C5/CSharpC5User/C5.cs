using System;
using System.Collections.Generic;
using System.Text;

using System.Runtime.InteropServices;

namespace CSharpC5User
{
    class C5
    {
        public C5(C5Params iParams)
        {
            _pItem = C5InstanceCreate(iParams.InfoOutputFile, iParams.ModelName, iParams.IsPartitionDiscreteValuesIntoSubsets, iParams.IsUseRuleClassifier,
                                      iParams.UtilitySortRulesIntoBandsValue, iParams.BoostTrialsNumber, iParams.IsDisplayAttributesBeforeConstructingClassifier,
                                      iParams.IsUseSoftThresholds, iParams.IsNotSafeClassifierToFile, iParams.MinimumCasesForSplitTwoBranches, iParams.IsCarryOutCrossValidation, iParams.CrossValidationFolds);
        }
        public IntPtr _pItem;
        public const string DllName = "C5Refactor.dll";

        public bool Init(C5AttributeRow iAttrebuteRow)
        {
            MyAttributeRow = iAttrebuteRow;
            return C5InstanceInit(_pItem, iAttrebuteRow._pItem);
        }

        /*
        // read names from C5Params::ModelName.names file 
        bool ReadAttributes()
        {
            return C5In
        }
      

        bool ReadAttributes(string ipFileName)
        {
        }
         *    * */

        public C5AttributeRow MyAttributeRow
        {
            get;
            private set;
        }


        // Build classifier
        // here SET value of target attribute
        public bool AddTeachData(C5AttributeRow ipValues)
        {
            return C5InstanceAddTrainData(_pItem, ipValues.GetRawData());
        }

        // C5 core delete this value, memory should be allocated by malloc
        public bool AddTeachData(IntPtr ipValues)
        {
            return C5InstanceAddTrainData(_pItem, ipValues);
        }

        // read train data block from file
        public bool ReadTrainData()
        {
            return C5InstanceReadFromFileSTDFile(_pItem);
        }

        public bool ReadTrainData(string ipFileName)
        {
            return C5InstanceReadFromFileSPFile(_pItem, ipFileName);
        }

        // generate classifier on specified train data
        public bool Train()
        {
            return C5InstanceTrain(_pItem);
        }

        // you can load previous step building classifier from file C5Params::ModelName.tree or C5Params::ModelName.rules.
        // be attention with params like C5Params::BoostTrialsNumber
        public bool LoadClassifier()
        {
            return C5InstanceReadFromFileSTDFile(_pItem);
        }

        public bool LoadClassifier(string ipFileName)
        {
            return C5InstanceReadFromFileSPFile(_pItem, ipFileName);
        }

        // use classifier
        // here GET value of target attribute
        public int ClassifyValue(C5AttributeRow ipValues)
        {
            return C5InstanceClassify(_pItem, ipValues.GetRawData());
        }

        // return target class ID
        public int ClassifyValue(IntPtr ipValues)
        {
            return C5InstanceClassify(_pItem, ipValues);
        }

        // statistic of classification building
        // usage specified attribute in classification
        public float GetAttributeUsage(C5Attribute ipAttribute)
        {
            return C5InstanceGetAttributeUsage1(_pItem, ipAttribute.Name);
        }

        public float GetAttributeUsage(string ipAttibuteName)
        {
            return C5InstanceGetAttributeUsage1(_pItem, ipAttibuteName);
        }

        public float GetAttributeUsage(int iAttrId)
        {
            return C5InstanceGetAttributeUsage2(_pItem, iAttrId);
        }

        // how many cases analyzed class classified as other class
        public int GetResultClassificationValue(string ipAnalyzeClassName, string ipClassificateAsClassName)
        {
            return C5InstanceGetResultClassificationValue1(_pItem, ipAnalyzeClassName, ipClassificateAsClassName);
        }

        public int GetResultClassificationValue(int ipAnalyzeClassId, int ipClassificateAsClassId)
        {
            return C5InstanceGetResultClassificationValue2(_pItem, ipAnalyzeClassId, ipClassificateAsClassId);
        }


        // initialize C5 instance
        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern IntPtr  C5InstanceCreate( string InfoOutputFile, string ModelName, bool IsPartitionDiscreteValuesIntoSubsets,
                                      bool IsUseRuleClassifier, int UtilitySortRulesIntoBandsValue, int BoostTrialsNumber,
                                      bool IsDisplayAttributesBeforeConstructingClassifier, bool IsUseSoftThresholds,
                                      bool IsNotSafeClassifierToFile, int MinimumCasesForSplitTwoBranches, bool IsCarryOutCrossValidation, 
                                      int CrossValidationFolds);

        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern bool C5InstanceInit(IntPtr iC5instance, IntPtr iAttrRow);

        //** construct classifier
        // in data value of target attribute on first place other values are followed in order same as adding order
        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern bool C5InstanceAddTrainData(IntPtr iC5instance, IntPtr iC5Data);

        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern bool C5InstanceReadTrainDataSTDFile(IntPtr iC5instance);

        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern bool C5InstanceReadTrainDataSPFile(IntPtr iC5instance, string ipFile);

        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern bool C5InstanceTrain(IntPtr iC5instance);

        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern bool C5InstanceReadFromFileSTDFile(IntPtr iC5instance);

        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern bool C5InstanceReadFromFileSPFile(IntPtr iC5instance, string ipFileName);

        //** use classifier
        // size and structure of classified data same as train data. Classify change value of first (target) value in array
        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern int C5InstanceClassify(IntPtr iC5instance, IntPtr iC5Data);


        //** get statistical data from classifier
        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern float C5InstanceGetAttributeUsage1(IntPtr iC5instance, string ipAttibuteName);

        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern float C5InstanceGetAttributeUsage2(IntPtr iC5instance, int iAttrId);

        // how many cases analyzed class classified as other class
        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern int C5InstanceGetResultClassificationValue1(IntPtr iC5instance, string ipAnalyzeClassName, string ipClassificateAsClassName);

        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern int C5InstanceGetResultClassificationValue2(IntPtr iC5instance, int ipAnalyzeClassId, int ipClassificateAsClassId);
    }
}
