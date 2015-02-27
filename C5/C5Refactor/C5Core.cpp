// COPYRIGHT: Open source by GPL (GNU General Public License)
// Based on C5.0 GPL Edition provided by Rulequest Research Pty Ltd.
//===================================================================
//
// Main C5 object, contains all required data and functions.
//
//===================================================================
//  FEB 2013  Creation:                       Ramirez, GOD RECEPRION
//===================================================================

#include "C5Core.h"
#include "C5CrossPlatform.h"

#pragma warning(disable:4244)
#pragma warning(disable:4996)

C5Core::C5Core(C5Params iParams)
{
  _parameters = iParams;
  InitPropertys();
  if(strlen(_parameters.InfoOutputFile) == 0)
    Of = stdout;
  else
    Of = fopen(_parameters.InfoOutputFile, "w");
  _isInited = false;
  _isClassificatorLoadedFromFile = false;
  _isClassificatorConstructed = false;
  _totalCaseSpace = 0;
  _ConfusionMat = NULL;
  _Usage = NULL;
  _pMyAttributeRow = NULL;
  LBp = LineBuffer;
  ApplyParameters();
}

C5Core::~C5Core()
{
  FreeMem(_ConfusionMat);
  FreeMem(_Usage);
  delete _pMyAttributeRow;
  FreeMem(ClassSum);
  if(strlen(_parameters.InfoOutputFile) != 0)
    fclose(Of);
}

// apply specified attributes
bool C5Core::Init(C5AttributeRow* iAttrebuteRow)
{
  C5AssertV(!_isInited, " alredy inited ", false);
  C5AssertV(iAttrebuteRow, " Null pointer ", false);
  _pMyAttributeRow = iAttrebuteRow;
  _pMyAttributeRow->Init(this);
  char tmpFileName[255];
  sprintf(tmpFileName, "GDSGSD_%s.txt", _pMyAttributeRow->GetTagetAttrebute().GetName());
  FILE* f = fopen(tmpFileName, "w");
  C5Attribute& taget = _pMyAttributeRow->GetTagetAttrebute();
  std::vector<std::string> vals = taget.GetAllNamedValues();
  fprintf(f, "%s. | the target attribute\n\n", taget.GetName());
  for(int i = 0; i < _pMyAttributeRow->GetSize(); i++) {
    C5Attribute* attr = (*iAttrebuteRow)[i];
    fprintf(f, "%s\n", attr->GetDefinition().c_str());
  }
  fprintf(f, "\n%s\n", taget.GetDefinition().c_str());
  fclose(f);
  f = fopen(tmpFileName, "r");
  GetNames(f);
  C5DeleteFile(tmpFileName);
  SomeMiss = AllocZero(MaxAtt + 1, Boolean);
  SomeNA   = AllocZero(MaxAtt + 1, Boolean);
  _isInited = true;
  return true;
}

// here SET value of target attribute
bool C5Core::AddTeachData(C5AttributeRow& ipValues)
{
  C5AssertV(_isInited, "Not inited", false);
  AttributeValue* inData = ipValues.GetRawData();
  int memSize = sizeof(AttributeValue) * (ipValues.GetSize() + 1);
  AttributeValue* dataCopy = (AttributeValue*) malloc(memSize);
  memcpy(dataCopy, inData, memSize);
  return AddTeachData(dataCopy);
}

#define Inc 2048
bool C5Core::AddTeachData(AttributeValue* ipValues)
{
  C5AssertV(_isInited, "Not inited", false);
  C5AssertV(ipValues, "Null pointer", false);
  if(Case == NULL) {
    Case = AllocateMem(1, DataRec);
  }
  /*  Make sure there is room for another case  */
  if (MaxCase + 1 >= _totalCaseSpace) {
    _totalCaseSpace += Inc;
    ReallocateMem(Case, _totalCaseSpace + 1, DataRec);
  }
  MaxCase++;
  Case[MaxCase] = ipValues;
  return true;
}

bool C5Core::ReadAttributes(const char* ipFileName)
{
  C5AssertV(!_isInited, " alredy inited ", false);
  FILE* F = fopen(ipFileName, "r");
  if(F == NULL) {
    C5Error(NOFILE, "", "");
    return false;
  }
  GetNames(F);
  ConstructAttributeRow();
  _isInited = true;
  return true;
}


bool C5Core::ReadAttributes()
{
  C5AssertV(!_isInited, " alredy inited ", false);
  FILE* F = NULL;
  if (!(F = GetFile(".names", "r"))) {
    C5Error(NOFILE, "", "");
    return false;
  }
  GetNames(F);
  ConstructAttributeRow();
  _isInited = true;
  return true;
}

void C5Core::ConstructAttributeRow()
{
  std::vector<std::string> classes;
  for(int i = 1; i <= MaxClass; i++)
    classes.push_back(ClassName[i]);
  _pMyAttributeRow = new C5AttributeRow(C5Attribute::CreateAttribute("TagetClass", classes));
  int Att;
  ForEach(Att, 1, MaxAtt) {
    if (Discrete(Att)) {
      int valId;
      std::vector<std::string> vals;
      ForEach( valId, 2, MaxAttVal[Att]) {
        vals.push_back(std::string(AttValName[Att][valId]));
      }
      _pMyAttributeRow->PushBackAttrebute(C5Attribute::CreateAttribute(AttName[Att], vals));
    } else {
      C5AttributeType type;
      if(TStampVal(Att)) {
        type = eTimestamp;
      } else
        if(DateVal(Att)) {
          type = eDate;
        } else
          if( TimeVal(Att)) {
            type = eTime;
          } else {
            type = eContinuous;
          }
      _pMyAttributeRow->PushBackAttrebute(C5Attribute::CreateAttribute(AttName[Att], type));
    }
  }
  _pMyAttributeRow->Init(this);
  NotifyStage(READDATA);
  Progress(-1.0);
  /*  Allocate space for SomeMiss[] and SomeNA[] */
  SomeMiss = AllocZero(MaxAtt + 1, Boolean);
  SomeNA   = AllocZero(MaxAtt + 1, Boolean);
}


bool C5Core::ReadTrainData()
{
  C5AssertV(_isInited, "Not inited", false);
  FILE* F = NULL;
  if (!(F = GetFile(".data", "r"))) {
    C5Error(NOFILE, "", "");
    return false;
  }
  GetData(F, true, false);
  return true;
}

bool C5Core::ReadTrainData(const char* ipFileName)
{
  C5AssertV(_isInited, "Not inited", false);
  FILE* F = fopen(ipFileName, "r");
  if (F == NULL) {
    C5Error(NOFILE, "", "");
    return false;
  }
  GetData(F, true, false);
  return true;
}

bool C5Core::Train()
{
  C5AssertV(_isInited, "Not inited", false);
  C5AssertV(!_isClassificatorConstructed, " alredy constructed", false);
  InitialiseTreeData();
  if ( RULES ) {
    RuleSet = AllocZero(TRIALS + 1, CRuleSet);
  }
  if ( WINNOW ) {
    NotifyStage(WINNOWATTS);
    Progress(-MaxAtt);
    WinnowAtts();
  }
  if ( XVAL ) {
    CrossVal();
  } else {
    NotifyStage(1);
    ConstructClassifiers();
    /*  Evaluation  */
    fprintf(Of, T_EvalTrain, MaxCase + 1);
    NotifyStage(EVALTRAIN);
    Progress(-TRIALS * (MaxCase + 1.0));
    Evaluate(CMINFO | USAGEINFO);
  }
  _isClassificatorConstructed = true;
  _isClassificatorLoadedFromFile = false;
  //  fprintf(Of, T_Time, ExecTime() - StartTime);
  return true;
}

bool C5Core::LoadClassifier()
{
  C5AssertV(_isInited, "Not inited", false);
  C5AssertV(!_isClassificatorConstructed, " alredy constructed", false);
  if ( RULES ) {
    CheckFile(".rules", false);
    RuleSet = AllocZero(TRIALS + 1, CRuleSet);
    RuleNo TotalRules = 0;
    ForEach(Trial, 0, TRIALS - 1) {
      RuleSet[Trial] = GetRules(".rules");
      TotalRules += RuleSet[Trial]->SNRules;
    }
    MostSpec = AllocateMem(MaxClass + 1, CRule);
    ClassSum = AllocateMem(MaxClass + 1, float);
  } else {
    CheckFile(".tree", false);
    Pruned = AllocZero(TRIALS + 1, Tree);
    ForEach(Trial, 0, TRIALS - 1) {
      Pruned[Trial] = GetTree(".tree");
    }
    ClassSum = AllocateMem(MaxClass + 1, float);
  }
  _isClassificatorConstructed = true;
  _isClassificatorLoadedFromFile = true;
  return true;
}

bool C5Core::LoadClassifier(const char* ipFileName)
{
  std::string fileName(ipFileName);
  C5AssertV( fileName.length() >= 5, " file name should be ended by .tree or .rules ", false);
  if(fileName.substr(fileName.length() - 5) == ".tree") {
    fileName = fileName.substr(0, fileName.length() - 5);
    FileStem = const_cast<char*>(fileName.c_str());
    LoadClassifier();
  } else {
    C5AssertV( fileName.length() >= 6, " file name should be ended by .tree or .rules ", false);
    if(fileName.substr(fileName.length() - 6) == ".rules") {
      fileName = fileName.substr(0, fileName.length() - 6);
      FileStem = const_cast<char*>(fileName.c_str());
      LoadClassifier();
    }
    C5AssertV(false, " file name should be ended by .tree or .rules ", false);
  }
  return true;
}


bool C5Core::ClassifyValue(C5AttributeRow& ipValues)
{
  C5AssertV(_isClassificatorConstructed, " Classificatory not constructed ", false);
  int id = ClassifyValue(ipValues.GetRawData());
  ipValues.GetTagetAttrebute().SetValue(id);
  return true;
}

int C5Core::ClassifyValue(AttributeValue* ipValues)
{
  C5AssertV(_isClassificatorConstructed, " Classificatory not constructed ", 0);
  return Classify(ipValues) - 1;
}

float C5Core::GetAttributeUsage(C5Attribute* ipAttribute)
{
  return GetAttributeUsage(ipAttribute->GetName());
}

float C5Core::GetAttributeUsage(const char* ipAttibuteName)
{
  return GetAttributeUsage(_pMyAttributeRow->GetIdByName(std::string(ipAttibuteName)));
}

float C5Core::GetAttributeUsage(int iAttrId)
{
  C5AssertV(!_isClassificatorLoadedFromFile, " Classificatory loaded from file. This info unavailable", 0);
  return (100 * _Usage[iAttrId + 1]) /  Max(1, MaxCase + 1);
}

int C5Core::GetResultClassificationValue(const char* ipAnalyzeClassName, const char* ipClassificateAsClassName)
{
  int analyzeClassNum = _pMyAttributeRow->GetTagetAttrebute().GetClassId(ipAnalyzeClassName);
  int asClassName = _pMyAttributeRow->GetTagetAttrebute().GetClassId(ipClassificateAsClassName);
  return GetResultClassificationValue(analyzeClassNum, asClassName);
}

int C5Core::GetResultClassificationValue(int ipAnalyzeClassId, int ipClassificateAsClassId)
{
  C5AssertV(!_isClassificatorLoadedFromFile, " Classificatory loaded from file. This info unavailable", 0);
  return _ConfusionMat[(ipAnalyzeClassId + 1) * (MaxClass + 1) + ipClassificateAsClassId + 1];
}

void C5Core::ApplyParameters()
{
  FileStem = _parameters.ModelName;
  SUBSET = _parameters.IsPartitionDiscreteValuesIntoSubsets;
  RULES = _parameters.IsUseRuleClassifier;
  UTILITY = _parameters.UtilitySortRulesIntoBandsValue;
  if(UTILITY > 0)
    RULES = true;
  TRIALS = _parameters.BoostTrialsNumber;
  WINNOW = _parameters.IsDisplayAttributesBeforeConstructingClassifier;
  PROBTHRESH = _parameters.IsUseSoftThresholds;
  GLOBAL = _parameters.IsNotSafeClassifierToFile;
  MINITEMS = _parameters.MinimumCasesForSplitTwoBranches;
  XVAL = _parameters.IsCarryOutCrossValidation;
  FOLDS = _parameters.CrossValidationFolds;
}

void C5Core::InitPropertys()
{
  VERBOSITY = 0; /* verbosity level (0 = none) */
  TRIALS = 1; /* number of trees to be grown */
  FOLDS = 10; /* crossvalidation folds */
  UTILITY = 0; /* rule utility bands */
  SUBSET = 0; /* subset tests allowed */
  BOOST = 0; /* boosting invoked */
  PROBTHRESH = 0; /* to use soft thresholds */
  RULES = 0; /* rule-based classifiers */
  XVAL = 0;  /* perform crossvalidation */
  NOCOSTS = 0; /* ignoring costs */
  WINNOW = 0; /* attribute winnowing */
  GLOBAL = 1; /* use global pruning for trees */
  MINITEMS = 2; /* minimum cases each side of a cut */
  LEAFRATIO = 0; /* leaves per case for boosting */
  CF = 0.25; /* confidence limit for tree pruning */
  SAMPLE = 0.0; /* sample training proportion */
  LOCK = false; /* sample locked */
  /*************************************************************************/
  /*                   */
  /*    Attributes and data           */
  /*                   */
  /*************************************************************************/
  ClassAtt = 0; /* attribute to use as class */
  LabelAtt = 0; /* attribute to use as case ID */
  CWtAtt = 0; /* attribute to use for case weight */
  ClassName = 0; /* class names */
  AttName = 0; /* att names */
  AttValName = 0; /* att value names */
  IgnoredVals = 0; /* values of labels and atts marked ignore */
  IValsSize = 0; /* size of above */
  IValsOffset = 0; /* index of first free char */
  MaxDiscrVal = 3; /* max discrete values for any att */
  MaxLabel = 0; /* max characters in case label */
  LineNo = 0; /* input line number */
  ErrMsgs = 0; /* errors found */
  AttExIn = 0; /* attribute exclusions/inclusions */
  TSBase = 0; /* base day for time stamps */
  MaxAttVal = 0; /* number of values for each att */
  SpecialStatus = 0; /* special att treatment */
  AttDef = 0; /* definitions of implicit atts */
  AttDefUses = 0; /* list of attributes used by definition */
  SomeMiss = Nil; /* att has missing values */
  SomeNA = Nil; /* att has N/A values */
  Winnowed = 0; /* atts have been winnowed */
  ClassThresh = 0; /* thresholded class attribute */
  MaxCase = -1; /* max data case number */
  Case = 0; /* data cases */
  SaveCase = 0;
  FileStem = "undefined";
  /*************************************************************************/
  /*                   */
  /*    Trees               */
  /*                   */
  /*************************************************************************/
  Raw = 0;  /* unpruned trees */
  Pruned = 0; /* pruned trees */
  WTree = 0; /* winnow tree */
  SampleFrac = 1; /* fraction used when sampling */
  Vote = 0; /* total votes for classes */
  BVoteBlock = 0; /* boost voting block */
  MCost = 0; /* misclass cost [pred][real] */
  NCost = 0; /* normalised MCost used for rules */
  WeightMul = 0; /* prior adjustment factor */
  MostSpec = 0; /* most specific rule for each class */
  UnitWeights = 1; /* all weights are 1.0 */
  CostWeights = 0; /* reweight cases for costs */
  Trial;    /* trial number for boosting */
  MaxTree = 0; /* max tree grown */
  TrialPred = 0; /* predictions for each boost trial */
  ClassFreq = 0; /* ClassFreq[c] = # cases of class c */
  DFreq = 0; /* DFreq[a][c*x] = Freq[][] for attribute a */
  Gain = 0; /* Gain[a] = info gain by split on att a */
  Info = 0; /* Info[a] = max info from split on att a */
  EstMaxGR = 0; /* EstMaxGR[a] = est max GR from folit on a */
  ClassSum = 0; /* class weights during classification */
  Bar = 0;  /* Bar[a]  = best threshold for contin att a */
  GlobalBaseInfo;  /* base information before split */
  Bell = 0; /* table of Bell numbers for subsets */
  Tested = 0; /* Tested[a] = att a already tested */
  Subset = 0; /* Subset[a][s] = subset s for att a */
  Subsets = 0; /* Subsets[a] = no. subsets for att a */
  /*************************************************************************/
  /*                   */
  /*    Rules               */
  /*                   */
  /*************************************************************************/
  Rule = 0; /* current rules */
  NRules;    /* number of rules */
  RuleSpace;  /* space currently allocated for rules */
  RuleSet = 0; /* rulesets */
  Default;  /* default class associated with ruleset or
           boosted classifier */
  Fires = Nil; /* Fires[r][*] = cases covered by rule r */
  CBuffer = Nil; /* buffer for compressing lists */
  CovBy = Nil; /* entry numbers for Fires inverse */
  List = Nil; /* temporary list of cases or rules */
  AttTestBits;  /* average bits to encode tested attribute */
  BranchBits = 0; /* ditto attribute value */
  AttValues = 0; /* number of attribute values in the data */
  PossibleCuts = 0; /* number of thresholds for an attribute */
  LogCaseNo = 0; /* LogCaseNo[i] = log2(i) */
  LogFact = 0; /* LogFact[i] = log2(i!) */
  UtilErr = 0; /* error by utility band */
  UtilBand = 0; /* last rule in each band */
  UtilCost = 0; /* cost ditto */
  /*************************************************************************/
  /*                   */
  /*    Misc               */
  /*                   */
  /*************************************************************************/
  KRInit = 0; /* KRandom initializer for SAMPLE */
  Now = 0;  /* current stage */
  TRf = 0;  /* file pointer for tree and rule i/o */
  Of = 0;  /* output file */
}


