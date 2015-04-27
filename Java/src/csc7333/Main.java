package csc7333;

import java.io.File;
import java.util.Random;

public class Main {
	private static final int RANDOM_SEED = 235346;
	
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
		
		//10-fold cross validation C4.5
		System.out.println("=======================================");
		System.out.println("C4.5 on 10-fold cross validation data:");
		System.out.println("=======================================");
		ClassifierTest c45 = new C45Test(dataLoader, System.out);
		c45.crossValidate(new Random(RANDOM_SEED));;
		
		//10-fold cross validation Naive Bayes
		System.out.println("=======================================");
		System.out.println("Naive Bayes on 10-fold cross validation data:");
		System.out.println("=======================================");
		ClassifierTest nbt = new NaiveBayesTest(dataLoader, System.out);
		nbt.crossValidate(new Random(RANDOM_SEED));;
	}
}