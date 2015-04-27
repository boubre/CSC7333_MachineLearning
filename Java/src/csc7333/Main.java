package csc7333;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.util.Random;

public class Main {
	private static final int RANDOM_SEED = 235346;
	
	public static void main(String[] args) {
		System.out.println("CSC 7333 Machine Learning Project");
		
		File outputFile = new File("./results.txt");
		if (!outputFile.exists()) {
			try {
				outputFile.createNewFile();
			} catch (IOException e) {
				e.printStackTrace();
				System.exit(1);
			}
		}
		
		try (PrintStream output = new PrintStream(new FileOutputStream(outputFile))) {
			uciSpam(output);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			System.exit(2);
		}
		
		System.out.println("Execution Complete.");
	}
	
	/**
	 * Analyze the UCI Spam Data.
	 */
	private static void uciSpam(PrintStream output) {
		File headers = new File("data/spambase.names");
		File data = new File("data/spambase.data");
		DataLoader dataLoader = new DataLoader(headers, data);
		
		//10-fold cross validation C4.5
		System.out.println("Running C4.5 10-fold cross validation...");
		output.println("=======================================");
		output.println("C4.5 on 10-fold cross validation data:");
		output.println("=======================================");
		ClassifierTest c45 = new C45Test(dataLoader, output);
		c45.crossValidate(new Random(RANDOM_SEED));;
		
		System.out.println("Running Naive Bayes 10-fold cross validation...");
		//10-fold cross validation Naive Bayes
		output.println("=======================================");
		output.println("Naive Bayes on 10-fold cross validation data:");
		output.println("=======================================");
		ClassifierTest nbt = new NaiveBayesTest(dataLoader, output);
		nbt.crossValidate(new Random(RANDOM_SEED));;
	}
}