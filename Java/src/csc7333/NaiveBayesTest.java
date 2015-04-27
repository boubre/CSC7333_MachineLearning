package csc7333;

import java.io.PrintStream;
import java.util.Random;

import weka.classifiers.bayes.NaiveBayes;

/**
 * This class sets up a Naive Bayes classifier for the UCI spam data.
 */
public class NaiveBayesTest extends ClassifierTest {
	/**
	 * Create a new test of the Naive Bayes classifier.
	 * @param loader The data loader.
	 * @param output The output stream to print results to.
	 */
	public NaiveBayesTest(DataLoader loader, PrintStream output) {
		super(loader, output);
	}
	
	@Override
	public void crossValidate(Random rand) {
		crossValidate(rand, new NaiveBayes());
	}
}
