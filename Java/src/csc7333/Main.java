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
	}
}