package csc7333;

import java.io.PrintStream;
import java.util.Random;

import weka.classifiers.meta.AdaBoostM1;

/**
 * This class sets up a AdaBoost classifier for the UCI spam data.
 */
public class AdaBoostTest extends ClassifierTest {
	/**
	 * Create a new test of the AdaBoost classifier.
	 * @param loader The data loader.
	 * @param output The output stream to print results to.
	 */
	public AdaBoostTest(DataLoader loader, PrintStream output) {
		super(loader, output);
	}
	
	@Override
	public void crossValidate(Random rand) {
		crossValidate(rand, new AdaBoostM1());
	}
}
