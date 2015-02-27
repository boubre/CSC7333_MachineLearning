using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;

namespace MLSpam
{
    /// <summary>
    /// This class manages loading and converting the data files.
    /// The data set is represented as a list of records. Each record is a dictionary that maps a column header to that recoard's value.
    /// </summary>
    class DataLoader
    {
        public List<string> Headers { get; private set; }
        public List<Dictionary<string, double>> DataSet { get; private set; }

        /// <summary>
        /// Create a new data loader and load in the specified spam data set.
        /// </summary>
        /// <param name="data">The filepath to the data set.</param>
        /// <param name="headers">The filepath to column headers.</param>
        public DataLoader(string data, string headers)
        {
            loadHeaders(headers);
            loadData(data);
        }

        /// <summary>
        /// Load all of the attribute column headers from the .names file.
        /// </summary>
        /// <param name="headerPath">The path to the header file.</param>
        private void loadHeaders(string headerPath)
        {
            Headers = new List<string>();
            var rawHeaders = File.ReadAllLines(headerPath).Where(u => !u.StartsWith("|")).Where(u => !String.IsNullOrEmpty(u));
            char[] splitChars = { ':' };
            foreach (string header in rawHeaders)
            {
                var parsedHeader = header.Split(splitChars).First();
                Headers.Add(parsedHeader);
            }
        }

        /// <summary>
        /// Load all of the data records from the .data file.
        /// NOTE: Headers should be loaded before running this method.
        /// </summary>
        /// <param name="dataPath">The path to the data file.</param>
        private void loadData(string dataPath)
        {
            Debug.Assert(Headers != null);

            DataSet = new List<Dictionary<string, double>>();
            var rawData = File.ReadAllLines(dataPath).Where(u => !String.IsNullOrEmpty(u));
            char[] splitChars = { ',', '\n', '\r' };
            foreach (string record in rawData)
            {
                var parsedRecord = record.Split(splitChars).Where(u => !String.IsNullOrEmpty(u)).Select(u => Double.Parse(u));
                DataSet.Add(storeInDictionary(parsedRecord));
            }
        }

        /// <summary>
        /// Convert a parsed data record into a dictionary that asscoiates the column title with the record value.
        /// </summary>
        /// <param name="attr">The parsed data record.</param>
        /// <returns>A data record in the form of a dictionary. Each header is asscociated with the appropriate value for this recoard.</returns>
        private Dictionary<string, double> storeInDictionary(IEnumerable<double> attr)
        {
            var dict = new Dictionary<string, double>();
            IEnumerator<string> headerEnum = Headers.GetEnumerator();
            foreach (double val in attr)
            {
                headerEnum.MoveNext();
                dict.Add(headerEnum.Current, val);
            }
            return dict;
        }
    }
}
