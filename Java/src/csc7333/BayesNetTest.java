package csc7333;

import java.io.PrintStream;
import java.util.Random;

import weka.classifiers.bayes.BayesNet;


/**
 * This class sets up a Bayes Net classifier for the UCI spam data.
 */
public class BayesNetTest extends ClassifierTest {
	/**
	 * Create a new test of the Bayes Net classifier.
	 * @param loader The data loader.
	 * @param output The output stream to print results to.
	 */
	public BayesNetTest(DataLoader loader, PrintStream output) {
		super(loader, output);
	}
	
	@Override
	public void crossValidate(Random rand) {
		crossValidate(rand, new BayesNet());
	}
}
