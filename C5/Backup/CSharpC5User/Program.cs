using System;
using System.Collections.Generic;
using System.Text;

namespace CSharpC5User
{
    class Program
    {
        static void Main(string[] args)
        {
            TestC5API();
        }

        static void TestC5API()
        {

            C5AttributeRow attrRow = new C5AttributeRow(C5Attribute.CreateAttribute("classes", "increased binding protein", "decreased binding protein", "negative"));

            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("age", C5AttributeType.eContinuous));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("sex", "M", "F"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("on thyroxine", "t", "f"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("query on thyroxine", "t", "f"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("on antithyroid medication", "t", "f"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("sick", "t", "f"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("pregnant", "t", "f"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("thyroid surgery", "t", "f"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("I131 treatment", "t", "f"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("query hypothyroid", "t", "f"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("query hyperthyroid", "t", "f"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("lithium", "t", "f"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("goitre", "t", "f"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("tumor", "t", "f"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("hypopituitary", "t", "f"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("psych", "t", "f"));

            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("TSH measured", "t", "f"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("TSH", C5AttributeType.eContinuous));

            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("T3 measured", "t", "f"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("T3", C5AttributeType.eContinuous));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("TT4 measured", "t", "f"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("TT4", C5AttributeType.eContinuous));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("T4U measured", "t", "f"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("T4U", C5AttributeType.eContinuous));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("FTI measured", "t", "f"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("FTI", C5AttributeType.eContinuous));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("TBG measured", "t", "f"));
            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("TBG", C5AttributeType.eContinuous));


            attrRow.PushBackAttrebute(C5Attribute.CreateAttribute("referral source", "WEST", "STMW", "SVHC", "SVI", "SVHD", "other"));

            C5Params p = new C5Params();
            p.IsUseRuleClassifier = false;
            p.IsNotSafeClassifierToFile = false;
            p.InfoOutputFile = "out.txt";

            C5 obj = new C5(p);
            obj.Init(attrRow);

            for (int i = 0; i < 200; i++)
            {
                SetAttRowVals(attrRow, i);
                obj.AddTeachData(attrRow);
            }

            obj.Train();

            for (int i = 0; i < 200; i++)
            {
                SetAttRowVals(attrRow, i);
                int v = attrRow.GetTagetAttrebute().GetDiscreteValue();
                if (v != obj.ClassifyValue(attrRow))
                    Console.WriteLine("ERR");
            }
        }

        static void SetAttRowVals(C5AttributeRow attrRow, int i)
        {
            attrRow[0].SetValue((float)(i % 10));
            attrRow[1].SetValue((i % 3 == 0) ? "M" : "F");
            attrRow[2].SetValue(i % 2);
            attrRow["query on thyroxine"].SetValue(i % 2 == 0 ? "t" : "f");
            attrRow[4].SetValue((i + 2) % 5 == 0 ? "t" : "f");
            attrRow[5].SetValue(i % 6 == 0 ? "t" : "f");
            attrRow[6].SetValue((i + 1) % 3 == 0 ? "t" : "f");
            attrRow[7].SetValue(i % 4 == 0 ? "t" : "f");
            attrRow[8].SetValue((i + 5) % 7 == 0 ? "t" : "f");
            attrRow[9].SetValue((i + 2) % 8 == 0 ? "t" : "f");
            attrRow[10].SetValue(i % 5 == 0 ? "t" : "f");
            attrRow[11].SetValue(i % 11 == 0 ? "t" : "f");
            attrRow[12].SetValue((i + 54) % 34 == 0 ? "t" : "f");
            attrRow[13].SetValue(i % 6 == 0 ? "t" : "f");
            attrRow[14].SetValue((i + 3) % 5 == 0 ? "t" : "f");
            attrRow[15].SetValue((i + 1) % 3 == 0 ? "t" : "f");

            attrRow[16].SetValue((i + 3) % 4 == 0 ? "t" : "f");
            attrRow[17].SetValue((float)(i % 11) / 11);

            attrRow[18].SetValue((i + 1) % 3 == 0 ? "t" : "f");
            attrRow[19].SetValue((float)((i + 23) % 20) / 11);

            attrRow[20].SetValue((i + 2) % 4 == 0 ? "t" : "f");
            attrRow[21].SetValue((float)(i % 11) / 11);

            attrRow[22].SetValue((i + 1) % 5 == 0 ? "t" : "f");
            attrRow[23].SetValue((float)(i + 3 % 11) / 11);

            attrRow[24].SetValue((i + 2) % 7 == 0 ? "t" : "f");
            attrRow[25].SetValue((float)(i + 7 % 11) / 11);

            attrRow[26].SetValue((i + 3) % 3 == 0 ? "t" : "f");
            attrRow[27].SetValue((float)(i + 2 % 11) / 11);

            attrRow[28].SetValue((i * i + 2) % 7 - 1);
            attrRow.GetTagetAttrebute().SetValue(i % 3);
        }
    }
}
