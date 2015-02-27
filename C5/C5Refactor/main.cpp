// COPYRIGHT: Open source by GPL (GNU General Public License)
// Based on C5.0 GPL Edition provided by Rulequest Research Pty Ltd.
//===================================================================
//
// some using example
//
//===================================================================
//  FEB 2013  Creation:                       Ramirez, GOD RECEPRION
//===================================================================

#include "C5.h"

void TestC5ShellAPIModel();
void TestC5ShellFileModel();
void SetAttRowVals(C5AttributeRow& attrRow, int i);

void main (void)
{
  TestC5ShellAPIModel();
  //TestC5ShellFileModel();
  return;
}

void TestC5ShellFileModel()
{
  C5Params p;
  sprintf_s(p.ModelName, 512, "allbp");

  C5 obj(p);
  obj.ReadAttributes();
  obj.ReadTrainData();
  obj.Train();

  C5AttributeRow& attrRow = *obj.GetMyAttributes(); 

  for(int i = 0; i < 200; i++) {
    attrRow[0]->SetValue( (float)(i % 10));
    attrRow[1]->SetValue( i % 3 ? "M" : "F");

    attrRow[2]->SetValue( i % 2);
    attrRow[3]->SetValue( i % 2 == 0 ? "t" : "f");
    attrRow[4]->SetValue( (i + 2) % 5 == 0 ? "t" : "f");
    attrRow[5]->SetValue( i % 6 == 0 ? "t" : "f");
    attrRow[6]->SetValue( (i + 1) % 3 == 0 ? "t" : "f");
    attrRow[7]->SetValue( i % 4 == 0 ? "t" : "f");
    attrRow[8]->SetValue( (i + 5) % 7 == 0 ? "t" : "f");
    attrRow[9]->SetValue( (i + 2) % 8 == 0 ? "t" : "f");
    attrRow[10]->SetValue( i % 5 == 0 ? "t" : "f");
    attrRow[11]->SetValue( i % 11 == 0 ? "t" : "f");
    attrRow[12]->SetValue( (i + 54) % 34 == 0 ? "t" : "f");
    attrRow[13]->SetValue( i % 6 == 0 ? "t" : "f");
    attrRow[14]->SetValue( (i + 3) % 5 == 0 ? "t" : "f");
    attrRow[15]->SetValue( (i + 1) % 3 == 0 ? "t" : "f");

    attrRow[16]->SetValue( (i + 3) % 4 == 0 ? "t" : "f");
    attrRow[17]->SetValue( (float)(i % 11) / 11);

    attrRow[18]->SetValue( (i + 1) % 3 == 0 ? "t" : "f");
    attrRow[19]->SetValue( (float)((i + 23) % 20) / 11);

    attrRow[20]->SetValue( (i + 2) % 4 == 0 ? "t" : "f");
    attrRow[21]->SetValue( (float)(i % 11) / 11);

    attrRow[22]->SetValue( (i + 1) % 5 == 0 ? "t" : "f");
    attrRow[23]->SetValue( (float)(i + 3 % 11) / 11);

    attrRow[24]->SetValue( (i + 2) % 7 == 0 ? "t" : "f");
    attrRow[25]->SetValue( (float)(i + 7% 11) / 11);

    attrRow[26]->SetValue( (i + 3) % 3 == 0 ? "t" : "f");
    attrRow[27]->SetValue( (float)(i + 2% 11) / 11);

    attrRow[28]->SetValue( (i * i + 2) % 7 - 1);


    attrRow.GetTagetAttrebute().SetValue(i % 3);

    obj.ClassifyValue(attrRow);
  }

  printf(" %d \n", obj.GetResultClassificationValue("increased binding protein", "negative" )); 
}

void TestC5ShellAPIModel()
{
  std::vector<std::string> classes;
  classes.push_back("increased binding protein");
  classes.push_back("decreased binding protein");
  classes.push_back("negative");

  // create row with target attribute
  C5AttributeRow& attrRow = *(new C5AttributeRow(C5Attribute::CreateAttribute("classes", classes)));

  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("age", eContinuous));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("sex", "M", "F"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("on thyroxine", "t", "f"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("query on thyroxine", "t", "f"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("on antithyroid medication", "t", "f"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("sick", "t", "f"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("pregnant", "t", "f"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("thyroid surgery", "t", "f"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("I131 treatment", "t", "f"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("query hypothyroid", "t", "f"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("query hyperthyroid", "t", "f"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("lithium", "t", "f"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("goitre", "t", "f"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("tumor", "t", "f"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("hypopituitary", "t", "f"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("psych", "t", "f"));

  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("TSH measured", "t", "f"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("TSH", eContinuous));

  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("T3 measured", "t", "f"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("T3", eContinuous));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("TT4 measured", "t", "f"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("TT4", eContinuous));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("T4U measured", "t", "f"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("T4U", eContinuous));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("FTI measured", "t", "f"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("FTI", eContinuous));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("TBG measured", "t", "f"));
  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("TBG", eContinuous));

  classes.clear();
  classes.push_back("WEST");
  classes.push_back("STMW");
  classes.push_back("SVHC");
  classes.push_back("SVI");
  classes.push_back("SVHD");
  classes.push_back("other");

  attrRow.PushBackAttrebute(C5Attribute::CreateAttribute("referral source", classes));


  C5Params p;
  sprintf_s(p.ModelName, 512, "allbp");
  p.IsUseRuleClassifier = false;
  p.IsNotSafeClassifierToFile = false;


  C5 obj(p);
  obj.Init(&attrRow);


  for(int i = 0; i < 200; i++) {

    SetAttRowVals(attrRow, i);
    //obj.AddTeachData(attrRow);
  }

  //obj.Train();
  obj.LoadClassifier("allbp.tree");


  for(int i = 0 ; i < attrRow.GetSize(); i++)
  {
    printf( " %s %f \n " , attrRow[i]->GetName(), obj.GetAttributeUsage(attrRow[i]));
  }

  printf(" %d \n", obj.GetResultClassificationValue("increased binding protein", "negative" )); 


  for(int i = 0; i < 200; i++) {

    SetAttRowVals(attrRow, i);
    int v = attrRow.GetTagetAttrebute().GetDiscreteValue();
    obj.ClassifyValue(attrRow);
    if( v != attrRow.GetTagetAttrebute().GetDiscreteValue())
      printf("ERR");
  }
}

void SetAttRowVals(C5AttributeRow& attrRow, int i)
{
  attrRow[0]->SetValue( (float)(i % 10));
  attrRow[1]->SetValue( i % 3 ? "M" : "F");

  attrRow[2]->SetValue( i % 2);
  attrRow["query on thyroxine"]->SetValue( i % 2 == 0 ? "t" : "f");
  attrRow[4]->SetValue( (i + 2) % 5 == 0 ? "t" : "f");
  attrRow[5]->SetValue( i % 6 == 0 ? "t" : "f");
  attrRow[6]->SetValue( (i + 1) % 3 == 0 ? "t" : "f");
  attrRow[7]->SetValue( i % 4 == 0 ? "t" : "f");
  attrRow[8]->SetValue( (i + 5) % 7 == 0 ? "t" : "f");
  attrRow[9]->SetValue( (i + 2) % 8 == 0 ? "t" : "f");
  attrRow[10]->SetValue( i % 5 == 0 ? "t" : "f");
  attrRow[11]->SetValue( i % 11 == 0 ? "t" : "f");
  attrRow[12]->SetValue( (i + 54) % 34 == 0 ? "t" : "f");
  attrRow[13]->SetValue( i % 6 == 0 ? "t" : "f");
  attrRow[14]->SetValue( (i + 3) % 5 == 0 ? "t" : "f");
  attrRow[15]->SetValue( (i + 1) % 3 == 0 ? "t" : "f");

  attrRow[16]->SetValue( (i + 3) % 4 == 0 ? "t" : "f");
  attrRow[17]->SetValue( (float)(i % 11) / 11);

  attrRow[18]->SetValue( (i + 1) % 3 == 0 ? "t" : "f");
  attrRow[19]->SetValue( (float)((i + 23) % 20) / 11);

  attrRow[20]->SetValue( (i + 2) % 4 == 0 ? "t" : "f");
  attrRow[21]->SetValue( (float)(i % 11) / 11);

  attrRow[22]->SetValue( (i + 1) % 5 == 0 ? "t" : "f");
  attrRow[23]->SetValue( (float)(i + 3 % 11) / 11);

  attrRow[24]->SetValue( (i + 2) % 7 == 0 ? "t" : "f");
  attrRow[25]->SetValue( (float)(i + 7% 11) / 11);

  attrRow[26]->SetValue( (i + 3) % 3 == 0 ? "t" : "f");
  attrRow[27]->SetValue( (float)(i + 2% 11) / 11);

  attrRow[28]->SetValue( (i * i + 2) % 7 - 1);


  attrRow.GetTagetAttrebute().SetValue(i % 3);
}
