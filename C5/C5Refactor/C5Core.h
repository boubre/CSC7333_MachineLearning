// COPYRIGHT: Open source by GPL (GNU General Public License)
// Based on C5.0 GPL Edition provided by Rulequest Research Pty Ltd.
//===================================================================
//
// Main C5 object, contains all required data and functions.
//
//===================================================================
//  FEB 2013  Creation:                       Ramirez, GOD RECEPRION
//===================================================================


#ifndef DTC5_H
#define DTC5_H

#include "stdio.h"
#include "C5defns.h"
#include "C5Params.h"
#include "C5Attribute.h"
#include "C5AttributeRow.h"

#define  MAXLINEBUFFER  10000

// common tutorial http://www.rulequest.com/see5-unix.html
class C5Core 
{
  friend class C5Attribute;
  friend class C5AttributeRow;
public:
  C5Core(C5Params iParams);
  ~C5Core();

// Initialize classifier
  // apply specified attributes
  bool Init(C5AttributeRow* iAttrebuteRow);
  // read names from C5Params::ModelName.names file 
  bool ReadAttributes();
  bool ReadAttributes(const char* ipFileName);

  C5AttributeRow* GetMyAttributes() { return _pMyAttributeRow;}

// Build classifier
  // here SET value of target attribute
  bool AddTeachData(C5AttributeRow& ipValues);
  // C5 core delete this value, memory should be allocated by malloc
  bool AddTeachData(AttributeValue* ipValues);

  // read train data block from file
  bool ReadTrainData();
  bool ReadTrainData(const char* ipFileName);

  // generate classifier on specified train data
  bool Train();

  // you can load previous step building classifier from file C5Params::ModelName.tree or C5Params::ModelName.rules.
  // be attention with params like C5Params::BoostTrialsNumber
  bool LoadClassifier();
  bool LoadClassifier(const char* ipFileName);

// use classifier
  // here GET value of target attribute
  bool ClassifyValue(C5AttributeRow& ipValues);
  int  ClassifyValue(AttributeValue* ipValues); // return target class ID

// statistic of classification building
  // usage specified attribute in classification
  float GetAttributeUsage(C5Attribute* ipAttribute);
  float GetAttributeUsage(const char* ipAttibuteName);
  float GetAttributeUsage(int iAttrId);

  // how many cases analyzed class classified as other class
  int GetResultClassificationValue(const char* ipAnalyzeClassName, const char* ipClassificateAsClassName);
  int GetResultClassificationValue(int ipAnalyzeClassId, int ipClassificateAsClassId);

private:
  void ConstructAttributeRow();

  bool _isInited;
  bool _isClassificatorConstructed;
  bool _isClassificatorLoadedFromFile;

  C5AttributeRow* _pMyAttributeRow;

  CaseNo _totalCaseSpace;
  CaseNo*  _ConfusionMat, *_Usage;

  int _attrNumber;

  C5Params _parameters;
  void ApplyParameters();

  void InitPropertys();

  int  Delimiter;
  char  LineBuffer[MAXLINEBUFFER];
  char* LBp;

  int    VERBOSITY,
         TRIALS,
         FOLDS,
         UTILITY,
         NCPU;

  Boolean    SUBSET,
             BOOST,
             PROBTHRESH,
             RULES,
             XVAL,
             NOCOSTS,
             WINNOW,
             GLOBAL;

  CaseCount  MINITEMS,
             LEAFRATIO;

  float    CF,
           SAMPLE;

  Boolean    LOCK;

  Attribute  ClassAtt,
             LabelAtt,
             CWtAtt;

  double    AvCWt;

  String*    ClassName,
             *AttName,
             ** AttValName;

  char*     IgnoredVals;
  int    IValsSize,
         IValsOffset;

  int    MaxAtt,
         MaxClass,
         MaxDiscrVal,
         MaxLabel,
         LineNo,
         ErrMsgs,
         AttExIn,
         TSBase;

  DiscrValue*  MaxAttVal;

  char*    SpecialStatus;

  Definition*  AttDef;
  Attribute**  AttDefUses;

  Boolean*    SomeMiss,
              *SomeNA,
              Winnowed;

  ContValue*  ClassThresh;

  CaseNo    MaxCase;

  DataRec*    Case;

  DataRec*    SaveCase;

  String    FileStem;

  Tree*    Raw,
           *Pruned,
           WTree;

  float    Confidence,
           SampleFrac,
           *Vote,
           *BVoteBlock,
           ** MCost,
           ** NCost,
           *WeightMul;

  CRule*    MostSpec;

  Boolean    UnitWeights,
             CostWeights;

  int    Trial,
         MaxTree;

  ClassNo*    TrialPred;

  double*    ClassFreq,
             ** DFreq;

  float*    Gain,
            *Info,
            *EstMaxGR,
            *ClassSum;

  ContValue*  Bar;

  double    GlobalBaseInfo,
            ** Bell;

  Byte*    Tested;

  Set**    Subset;
  int*    Subsets;

  EnvRec    GEnv;

  CRule*    Rule;

  RuleNo    NRules,
            RuleSpace;

  CRuleSet*   RuleSet;

  ClassNo    Default;

  Byte**    Fires,
       *CBuffer;

  int*    CovBy,
          *List;

  float    AttTestBits,
           *BranchBits;
  int*    AttValues,
          *PossibleCuts;

  double*    LogCaseNo,
             *LogFact;

  int*    UtilErr,
          *UtilBand;
  double*    UtilCost;

  int    KRInit,
         Now;

  FILE*    TRf;
  char    Fn[500];

  FILE*      Of;


  // methods
  void GetNames(FILE* f);


  /* xval.c */
  void      CrossVal(void);
  void      Prepare(void);
  void      Shuffle(int* Vec);
  void      Summary(void);
  float      SE(float sum, float sumsq, int no);


  // attwinnow.cpp
  void WinnowAtts();
  float TrialTreeCost(Boolean FirstTime);
  float ErrCost(Tree T, CaseNo Fp, CaseNo Lp);
  void ScanTree(Tree T, Boolean* Used);


  /* classify.c */
  ClassNo      TreeClassify(DataRec Case, Tree DecisionTree);
  void      FollowAllBranches(DataRec Case, Tree T, float Fraction);
  ClassNo      RuleClassify(DataRec Case, CRuleSet RS);
  int      FindOutcome(DataRec Case, Condition OneCond);
  Boolean      Matches(CRule R, DataRec Case);
  void      CheckActiveSpace(int N);
  void      MarkActive(RuleTree RT, DataRec Case);
  void      SortActive(void);
  void      CheckUtilityBand(int* u, RuleNo r, ClassNo Actual, ClassNo Default);
  ClassNo      BoostClassify(DataRec Case, int MaxTrial);
  ClassNo      SelectClass(ClassNo Default, Boolean UseCosts);
  ClassNo      Classify(DataRec Case);
  double      Interpolate(Tree T, ContValue Val);
  void FreeClassifier(int Trial);
  void FindLeaf(DataRec Case, Tree T, Tree PT, float Fraction);
  Boolean Satisfies(DataRec Case, Condition OneCond);


  // conformat.cpp
  void PrintConfusionMatrix(CaseNo* ConfusionMat);
  void PrintErrorBreakdown(CaseNo* ConfusionMat);
  void PrintUsageInfo(CaseNo* Usage);

  //construct.cpp
  void ConstructClassifiers();
  void InitialiseWeights();
  void SetAvCWt();
  void Evaluate(int Flags);
  void EvaluateSingle(int Flags);
  void EvaluateBoost(int Flags);
  void RecordAttUsage(DataRec Case, int* Usage);

  //contin.cpp
  void EvalContinuousAtt(Attribute Att, CaseNo Fp, CaseNo Lp);
  void EstimateMaxGR(Attribute Att, CaseNo Fp, CaseNo Lp);
  void PrepareForContin(Attribute Att, CaseNo Fp, CaseNo Lp);
  CaseNo PrepareForScan(CaseNo Lp);
  void ContinTest(Tree Node, Attribute Att);
  void AdjustThresholds(Tree T, Attribute Att, CaseNo* Ep);
  ContValue GreatestValueBelow(ContValue Th, CaseNo* Ep);
  void AdjustAllThresholds(Tree T);

  // discr.cpp 
  void      EvalDiscreteAtt(Attribute Att, CaseCount Cases);
  void      EvalOrderedAtt(Attribute Att, CaseCount Cases);
  void      SetDiscrFreq(Attribute Att);
  double      DiscrKnownBaseInfo(CaseCount KnownCases, DiscrValue MaxVal);
  void      DiscreteTest(Tree Node, Attribute Att);


  /* formrules.c */
  CRuleSet    FormRules(Tree T);
  void      Scan(Tree T);
  void      SetupNCost(void);
  void      PushCondition(void);
  void      PopCondition(void);
  void      PruneRule(Condition Cond[], ClassNo TargetClass);
  void      ProcessLists(void);
  void      AddToList(CaseNo* List, CaseNo N);
  void      DeleteFromList(CaseNo* Before, CaseNo N);
  int      SingleFail(CaseNo i);
  void      Increment(int d, CaseNo i, double* Total, double* Errors);
  void      FreeFormRuleData(void);


  /* formtree.c */
  void      InitialiseTreeData(void);
  void      FreeTreeData(void);
  void      SetMinGainThresh(void);
  void      FormTree(CaseNo, CaseNo, int, Tree*);
  void      SampleEstimate(CaseNo Fp, CaseNo Lp, CaseCount Cases);
  void      Sample(CaseNo Fp, CaseNo Lp, CaseNo N);
  Attribute   ChooseSplit(CaseNo Fp, CaseNo Lp, CaseCount Cases, Boolean Sampled);
  void      ProcessQueue(CaseNo WFp, CaseNo WLp, CaseCount WCases);
  Attribute   FindBestAtt(CaseCount Cases);
  void      EvalDiscrSplit(Attribute Att, CaseCount Cases);
  CaseNo      Group(DiscrValue, CaseNo, CaseNo, Tree);
  CaseCount   SumWeights(CaseNo, CaseNo);
  CaseCount   SumNocostWeights(CaseNo, CaseNo);
  void      FindClassFreq(double [], CaseNo, CaseNo);
  void      FindAllFreq(CaseNo, CaseNo);
  void      Divide(Tree Node, CaseNo Fp, CaseNo Lp, int Level);

  /* getdata.c */
  void      GetData(FILE* Df, Boolean Train, Boolean AllowUnknownClass);
  DataRec      GetDataRec(FILE* Df, Boolean Train);
  CaseNo      CountData(FILE* Df);
  int      StoreIVal(String s);
  void      FreeData(void);
  void      CheckValue(DataRec Case, Attribute Att);

  /* getnames.c */
  Boolean      ReadName(FILE* f, String s, int n, char ColonOpt);
  void      ExplicitAtt(FILE* Nf);
  int      Which(String Val, String* List, int First, int Last);
  void      ListAttsUsed(void);
  void      FreeNames(void);
  int      InChar(FILE* f);

  /* implicitatt.c */
  void      ImplicitAtt(FILE* Nf);
  void      ReadDefinition(FILE* f);
  void      Append(char c);
  Boolean      Expression(void);
  Boolean      Conjunct(void);
  Boolean      SExpression(void);
  Boolean      AExpression(void);
  Boolean      Term(void);
  Boolean      Factor(void);
  Boolean      Primary(void);
  Boolean      Atom(void);
  Boolean      Find(String S);
  int      FindOne(String* Alt);
  Attribute   FindAttName(void);
  void      DefSyntaxError(String Msg);
  void      DefSemanticsError(int Fi, String Msg, int OpCode);
  void      Dump(char OpCode, ContValue F, String S, int Fi);
  void      DumpOp(char OpCode, int Fi);
  Boolean      UpdateTStack(char OpCode, ContValue F, String S, int Fi);
  AttValue    EvaluateDef(Definition D, DataRec Case);

  //info.cpp
  double ComputeGain(double BaseInfo, float UnknFrac, DiscrValue MaxVal, CaseCount TotalCases);
  void PrintDistribution(Attribute Att, DiscrValue MinVal, DiscrValue MaxVal, double** Freq, double* ValFreq, Boolean ShowNames);
  double TotalInfo(double V[], DiscrValue MinVal, DiscrValue MaxVal);


  // mcost.cpp
  void GetMCosts(FILE* Cf);

  /* modelfiles.c */
  void      CheckFile(String Extension, Boolean Write);
  void      WriteFilePrefix(String Extension);
  void      ReadFilePrefix(String Extension);
  void      SaveDiscreteNames(void);
  void      SaveTree(Tree T, String Extension);
  void      OutTree(Tree T);
  void      SaveRules(CRuleSet RS, String Extension);
  void      AsciiOut(String Pre, String S);
  void      ReadHeader(void);
  Tree      GetTree(String Extension);
  Tree      InTree(void);
  CRuleSet    GetRules(String Extension);
  CRuleSet    InRules(void);
  CRule      InRule(void);
  Condition   InCondition(void);
  int      ReadProp(char* Delim);
  String      RemoveQuotes(String S);
  Set      MakeSubset(Attribute Att);
  void      StreamIn(String S, int n);

  /* p-thresh.c */
  void      SoftenThresh(Tree T);
  void      ResubErrs(Tree T, CaseNo Fp, CaseNo Lp);
  void      FindBounds(Tree T, CaseNo Fp, CaseNo Lp);

  /* prune.c */
  void      Prune(Tree T);
  void      EstimateErrs(Tree T, CaseNo Fp, CaseNo Lp, int Sh, int Flags);
  void      GlobalPrune(Tree T);
  void      FindMinCC(Tree T);
  void      InsertParents(Tree T, Tree P);
  void      CheckSubsets(Tree T, Boolean);
  void      InitialiseExtraErrs(void);
  float      ExtraErrs(CaseCount N, CaseCount E, ClassNo C);
  float      RawExtraErrs(CaseCount N, CaseCount E);
  void      RestoreDistribs(Tree T);
  void      CompressBranches(Tree T);
  void      SetGlobalUnitWeights(int LocalFlag);

  /* rules.c */
  Boolean      NewRule(Condition Cond[], int NConds, ClassNo TargetClass,
    Boolean* Deleted, CRule Existing,
    CaseCount Cover, CaseCount Correct, float Prior);
  void      ListSort(int* L, int Fp, int Lp);
  Byte*      Compress(int* L);
  void      Uncompress(Byte* CL, int* UCL);
  Boolean      SameRule(RuleNo r, Condition Cond[], int NConds, ClassNo TargetClass);
  void      FreeRule(CRule R);
  void      FreeRules(CRuleSet RS);
  void      PrintRules(CRuleSet, String);
  void      PrintRule(CRule R);
  void      PrintCondition(Condition C);


  /* ruletree.c */
  void      ConstructRuleTree(CRuleSet RS);
  void      SetTestIndex(Condition C);
  RuleTree    GrowRT(RuleNo* RR, int RRN, CRule* Rule);
  int      DesiredOutcome(CRule R, int TI);
  int      SelectTest(RuleNo* RR, int RRN, CRule* Rule);
  void      FreeRuleTree(RuleTree RT);

  /* siftrules.c */
  void      SiftRules(float EstErrRate);
  void      InvertFires(void);
  void      FindTestCodes(void);
  float      CondBits(Condition C);
  void      SetInitialTheory(void);
  void      CoverClass(ClassNo Target);
  int      MessageLength(RuleNo NR, double RuleBits, float Errs);
  void      HillClimb(void);
  void      InitialiseVotes(void);
  void      CountVotes(CaseNo i);
  void      UpdateDeltaErrs(CaseNo i, double Delta, RuleNo Toggle);
  CaseCount   CalculateDeltaErrs(void);
  void      PruneSubsets(void);
  void      SetDefaultClass(void);
  void      SwapRule(RuleNo A, RuleNo B);
  int      OrderByUtility(void);
  int      OrderByClass(void);
  void      OrderRules(void);
  void      GenerateLogs(int MaxN);
  void      FreeSiftRuleData(void);

  /* sort.c */
  void      Quicksort(CaseNo Fp, CaseNo Lp, Attribute Att);
  void      Cachesort(CaseNo Fp, CaseNo Lp, SortRec* SRec);

  /* subset.c */
  void      InitialiseBellNumbers(void);
  void      EvalSubset(Attribute Att, CaseCount Cases);
  void      Merge(DiscrValue x, DiscrValue y, CaseCount Cases);
  void      EvaluatePair(DiscrValue x, DiscrValue y, CaseCount Cases);
  void      PrintSubset(Attribute Att, Set Ss);
  void      SubsetTest(Tree Node, Attribute Att);
  Boolean      SameDistribution(DiscrValue V1, DiscrValue V2);
  void      AddBlock(DiscrValue V1, DiscrValue V2);
  void      MoveBlock(DiscrValue V1, DiscrValue V2);


  /* trees.c */
  void      FindDepth(Tree T);
  void      PrintTree(Tree T, String Title);
  void      Show(Tree T, int Sh);
  void      ShowBranch(int Sh, Tree T, DiscrValue v, DiscrValue BrNo);
  DiscrValue  Elements(Attribute Att, Set S, DiscrValue* Last);
  int      MaxLine(Tree SubTree);
  void      Indent(int Sh, int BrNo);
  void      FreeTree(Tree T);
  Tree      Leaf(double* Freq, ClassNo NodeClass, CaseCount Cases, CaseCount Errors);
  void      Sprout(Tree T, DiscrValue Branches);
  void      UnSprout(Tree T);
  int      TreeSize(Tree T);
  int      ExpandedLeafCount(Tree T);
  int      TreeDepth(Tree T);
  Tree      CopyTree(Tree T);

  /* update.c (Unix) or winmain.c (WIN32) */
  void      NotifyStage(int);
  void      Progress(float);

  /* utility.c */

  void      PrintHeader(String Title);
  char      ProcessOption(int Argc, char** Argv, char* Str);
  void*      ProtMalloc(size_t Bytes);
  void*      ProtRealloc(void* Present, size_t Bytes);
  void*      ProtCalloc(size_t Number, unsigned int Size);
  void      FreeVector(void** V, int First, int Last);
  DataRec      NewCase(void);
  void      FreeCases(void);
  void      FreeLastCase(DataRec Case);
  double      KRandom(void);
  void      ResetKR(int KRInit);
  void      C5Error(int ErrNo, String S1, String S2);
  String      CaseLabel(CaseNo N);
  FILE*       GetFile(String Extension, String RW);
  double      ExecTime(void);
  int      Denominator(ContValue Val);
  int      GetInt(String S, int N);
  int      DateToDay(String DS);
  void      DayToDate(int DI, String Date);
  int      TimeToSecs(String TS);
  void      SecsToTime(int Secs, String Time);
  void      SetTSBase(int y);
  int      TStampToMins(String TS);
  void      Check(float Val, float Low, float High);
  void      CValToStr(ContValue CV, Attribute Att, String DS);
  //double      rint(double v);
  void      Cleanup(void);
#ifdef UTF8
  int      UTF8CharWidth(unsigned char* U);
  int      wcwidth(wchar_t ucs);
  int      wcswidth(const wchar_t* pwcs, size_t n);
#endif

};

#endif
