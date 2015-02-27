using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace MLSpam
{
    class DataLoader
    {
        private List<string> headers;

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

        private void loadHeaders(string headerPath)
        {
            headers = new List<string>();
            var rawHeaders = File.ReadAllLines(headerPath).Where(u => !u.StartsWith("|")).Where(u => !String.IsNullOrEmpty(u));
            char[] splitChars = { ':' };
            foreach (string header in rawHeaders)
            {
                var parsedHeader = header.Split(splitChars).First();
                headers.Add(parsedHeader);
            }
        }

        private void loadData(string dataPath)
        {
            var rawData = File.ReadAllLines(dataPath).Where(u => !String.IsNullOrEmpty(u));
            char[] splitChars = { ',', '\n', '\r' };
            foreach (string record in rawData)
            {
                var parsedRecord = record.Split(splitChars).Where(u => !String.IsNullOrEmpty(u)).Select(u => Double.Parse(u));             
            }
        }
    }
}
