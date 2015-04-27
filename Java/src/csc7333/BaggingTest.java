package csc7333;

import java.io.PrintStream;
import java.util.Random;

import weka.classifiers.meta.Bagging;

/**
 * This class sets up a Bagging classifier for the UCI spam data.
 */
public class BaggingTest extends ClassifierTest {
	/**
	 * Create a new test of the Bagging classifier.
	 * @param loader The data loader.
	 * @param output The output stream to print results to.
	 */
	public BaggingTest(DataLoader loader, PrintStream output) {
		super(loader, output);
	}
	
	@Override
	public void crossValidate(Random rand) {
		Bagging b = new Bagging();
		/*String[] options = {"-W", "weka.classifiers.trees.J48"};
		try {
			b.setOptions(options);
		} catch (Exception e) {
			e.printStackTrace();
		}*/
		crossValidate(rand, b);
	}
}
