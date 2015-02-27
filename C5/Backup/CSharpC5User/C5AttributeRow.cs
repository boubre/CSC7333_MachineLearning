using System;
using System.Collections.Generic;
using System.Text;

using System.Runtime.InteropServices;


namespace CSharpC5User
{
    class C5AttributeRow
    {
        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern IntPtr C5AttributeRowCreate(IntPtr TagetAttr);

        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern int C5AttributeRowAdd(IntPtr iTaget, IntPtr TagetAttr);

        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern void C5AttributeRowInit(IntPtr iTaget, IntPtr iC5instance);

        [DllImport(C5.DllName, CallingConvention = CallingConvention.StdCall)]
        private static extern IntPtr C5AttributeRowGetRawData(IntPtr iTaget);

        public C5AttributeRow(C5Attribute iTagetAttebute)
        {
            _tagetAttr = iTagetAttebute;
            _pItem = C5AttributeRowCreate(_tagetAttr._pItem);
        }
        C5Attribute _tagetAttr;
        public IntPtr _pItem;

        public C5Attribute GetTagetAttrebute()
        {
            return _tagetAttr;
        }

        public bool PushBackAttrebute(C5Attribute iValie)
        {
            _values.Add(iValie);
            _name2Value.Add(iValie.Name, _values.Count - 1);
            return C5AttributeRowAdd(_pItem, iValie._pItem) > 0;
        }

        List<C5Attribute> _values = new List<C5Attribute>();
        Dictionary<string, int> _name2Value = new Dictionary<string, int>();

        public int GetSize()
        {
            return _values.Count;
        }

        public C5Attribute this[int i]
        {
            get
            {
                return _values[i];
            }
        }

        public C5Attribute this[string iName]
        {
            get
            {
                return _values[GetIdByName(iName)];
            }
        }


        public int GetIdByName(string iName)
        {
            return _name2Value[iName];
        }

        public IntPtr GetRawData()
        {
            return C5AttributeRowGetRawData(_pItem);
        }

        public void Init(C5 ipC5instance)
        {
            C5AttributeRowInit(_pItem, ipC5instance._pItem);
        }
    }
}
