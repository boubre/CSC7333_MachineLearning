using System;
using System.IO;

namespace MLSpam
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("CSC 7333 Machine Learning Project");

            uciSpamAnalysis();

            Console.WriteLine("Execution Complete.");
            Console.ReadLine(); //Wait for enter to be pressed before exiting
        }

        /// <summary>
        /// Analyze and produce results for the UCI spam data set.
        /// </summary>
        private static void uciSpamAnalysis()
        {
            //Load Data
            string dataLoc = Directory.GetCurrentDirectory() + "/UCIData/spambase.data";
            string headerLoc = Directory.GetCurrentDirectory() + "/UCIData/spambase.names";
            var dataLoader = new DataLoader(dataLoc, headerLoc);
        }
    }
}
