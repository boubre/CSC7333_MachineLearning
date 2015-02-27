using System;
using System.Collections.Generic;
using System.Text;

using System.Runtime.InteropServices;

namespace CSharpC5User
{
    enum C5AttributeType
    {
        eContinuous = 0,
        eDate = 1,
        eTime = 2,
        eTimestamp = 3,
        eDiscrete = 4,
        eLabel = 6
    };

    class C5Attribute
    {
        //** create attributes
        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern IntPtr C5AttributeCreate(string ipAttrName, int iAttrType);

        // attr string named value to specified attribute, return assigned class ID 
        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern int C5AttributeAddValue(IntPtr iAttr, string iValue);

        // for any type
        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern string C5AttributeGetValue(IntPtr iAttr);
        // for date, time, timestamp (using convert required), continues
        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern float C5AttributeGetContinuesValue(IntPtr iAttr);
        // for discrete and enumeration types
        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern int C5AttributeGetDiscreteValue(IntPtr iAttr);

        // set values allow only after add to AttributeRow
        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern bool C5AttributeSetValueString(IntPtr iAttr, string ipValue);
        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern bool C5AttributeSetValueFloat(IntPtr iAttr, float iValue);
        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern bool C5AttributeSetValueInt(IntPtr iAttr, int iValue);

        public static C5Attribute CreateAttribute(string iAttrName, C5AttributeType iType)
        {
            IntPtr ptr = C5AttributeCreate(iAttrName, (int)iType);
            if (ptr.ToInt32() == 0) return null;

            C5Attribute attr = new C5Attribute();
            attr._pItem = ptr;
            attr.DataType = iType;
            attr.Name = iAttrName;
            return attr;
        }

        public static C5Attribute CreateAttribute(string iAttrName, params string[] iValues)
        {
            IntPtr ptr = C5AttributeCreate(iAttrName, (int)C5AttributeType.eDiscrete);
            if (ptr.ToInt32() == 0) return null;

            C5Attribute attr = new C5Attribute();
            attr.DataType = C5AttributeType.eDiscrete;
            attr._pItem = ptr;
            attr.Name = iAttrName;
            int idx = 0;
            foreach (var v in iValues)
            {
                C5AttributeAddValue(attr._pItem, v);
                attr._values.Add(v);
                attr._name2Key.Add(v, idx);
                idx++;
            }
            return attr;
        }

        public IntPtr _pItem;

        List<string> _values = new List<string>();
        Dictionary<string, int> _name2Key = new Dictionary<string, int>();

        public C5AttributeType DataType
        {
            get;
            private set;
        }

        public string Name
        {
            get;
            private set;
        }

        public string GetValue()
        {
            return C5AttributeGetValue(_pItem);
        }

        // for date, time, timestamp (using convert required), continues
        public float GetContinuesValue()
        {
            return C5AttributeGetContinuesValue(_pItem);
        }

        // for discrete and enumeration types
        public int GetDiscreteValue()
        {
            return C5AttributeGetDiscreteValue(_pItem);
        }

        // set values allow only after add to AttributeRow
        public bool SetValue(string ipValue)
        {
            return C5AttributeSetValueString(_pItem, ipValue);
        }

        public bool SetValue(float iValue)
        {
            return C5AttributeSetValueFloat(_pItem, iValue);
        }

        public bool SetValue(int iValue)
        {
            return C5AttributeSetValueInt(_pItem, iValue);
        }

        public int GetClassId(string ipClassName)
        {
            return _name2Key[ipClassName];
        }
    }
}
