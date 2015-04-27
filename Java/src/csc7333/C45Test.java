package csc7333;

import java.io.PrintStream;
import java.util.Random;

import weka.classifiers.Classifier;
import weka.classifiers.Evaluation;
import weka.classifiers.trees.J48;
import weka.core.Instances;

/**
 * This class sets up a C4.5 decision tree classifier for the UCI spam data.
 */
public class C45Test extends ClassifierTest {
	
	/**
	 * Create a new test of the C4.5 decision tree classifier.
	 * @param loader The data loader.
	 * @param output The output stream to print results to.
	 */
	public C45Test(DataLoader loader, PrintStream output) {
		super(loader, output);
	}
	
	/**
	 * Train a C4.5 tree on all of the data and print the evaluation results.
	 */
	public void trainAll() {
		Instances trainingData = new Instances("UCI Spam", attributes, loader.getDataSet().size());
		trainingData.setClassIndex(loader.getHeaders().size() - 1);
		loader.getDataSet().forEach(u -> trainingData.add(makeInstance(u)));
		Classifier classifier = new J48();
		try {
			classifier.buildClassifier(trainingData);
			Evaluation test = new Evaluation(trainingData);
			test.evaluateModel(classifier, trainingData);
			printResults(test);
		} catch (Exception ex) {
			System.err.println("Failed to train and test C4.5 on all data.");
			ex.printStackTrace();
		}
	}
	
	@Override
	public void crossValidate(Random rand) {
		crossValidate(rand, new J48());
	}
}
