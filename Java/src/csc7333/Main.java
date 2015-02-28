package csc7333;

import java.io.File;

public class Main {
	public static void main(String[] args) {
		System.out.println("CSC 7333 Machine Learning Project");
		
		uciSpam();
		
		System.out.println("Execution Complete.");
	}
	
	/**
	 * Analyze the UCI Spam Data.
	 */
	private static void uciSpam() {
		File headers = new File("data/spambase.names");
		File data = new File("data/spambase.data");
		DataLoader dataLoader = new DataLoader(headers, data);
		
		//Train using C4.5 on the whole data set
		System.out.println("C4.5 on all data:");
		System.out.println("=======================================");
		C45Classifier c45 = new C45Classifier(dataLoader);
		c45.trainAll();
	}
}