package csc7333;

import java.io.PrintStream;
import java.util.Map;
import java.util.Random;

import weka.classifiers.Classifier;
import weka.classifiers.Evaluation;
import weka.core.Attribute;
import weka.core.FastVector;
import weka.core.Instance;
import weka.core.Instances;

/**
 * This superclass provides tools for setting up a Weka classifier for the UCI Spam Data.
 */
public abstract class ClassifierTest {
	protected DataLoader loader;
	protected FastVector attributes;
	protected PrintStream output;
	
	/**
	 * Create a new classifier on the specified data.
	 * @param loader The data loader.
	 * @param output The output stream to print results to.
	 */
	protected ClassifierTest(DataLoader loader, PrintStream output) {
		this.loader = loader;
		this.output = output;
		initAttributes();
	}
	
	/**
	 * Create the attributes vector.
	 */
	private void initAttributes() {
		attributes = new FastVector(loader.getHeaders().size());
		
		//Add the 57 numeric attributes
		for (int i = 0; i < loader.getHeaders().size() - 1; i++) {
			Attribute attr = new Attribute(loader.getHeaders().get(i));
			attributes.addElement(attr);
		}
		
		//Last attribute is the class attribute
		FastVector classVals = new FastVector(2);
		classVals.addElement("Legit");
		classVals.addElement("Spam");
		Attribute classAttr = new Attribute(loader.getHeaders().get(loader.getHeaders().size() - 1), classVals);
		attributes.addElement(classAttr);
	}
	
	/**
	 * Convert a data record from the data loader into an instance for a Weka classifier.
	 * @param record The data record to convert.
	 * @return The instance derived from the given record.
	 */
	protected Instance makeInstance(Map<String, Double> record) {
		Instance instance = new Instance(loader.getHeaders().size());
		int numAttr = loader.getHeaders().size();
		for (int i = 0; i < numAttr - 1; i++) {
			instance.setValue((Attribute)attributes.elementAt(i), record.get(loader.getHeaders().get(i)));
		}
		//Set class attribute value
		instance.setValue((Attribute)attributes.elementAt(numAttr - 1), record.get(loader.getHeaders().get(numAttr - 1)) == 0 ? "Legit" : "Spam");
		return instance;
	}
	
	/**
	 * Perform 10-fold cross validation on the classifier.
	 * @param rand A random number generator.
	 */
	public abstract void crossValidate(Random rand);
	
	/**
	 * Perform 10-fold cross validation on the classifier.
	 * @param rand A random number generator.
	 * @param classifier The classifier to use.
	 */
	protected void crossValidate(Random rand, Classifier classifier) {
		Instances data = new Instances("UCI Spam", attributes, loader.getDataSet().size());
		data.setClassIndex(loader.getHeaders().size() - 1);
		loader.getDataSet().forEach(u -> data.add(makeInstance(u)));
		try{
			Evaluation eval = new Evaluation(data);
			long startTime = System.currentTimeMillis();
			eval.crossValidateModel(classifier, data, 10, rand);
			long endTime = System.currentTimeMillis();
			printResults(eval, endTime - startTime);
		} catch (Exception ex) {
			System.err.println("Failed to train and test Naive Bayes on 10-fold cross validation data.");
			ex.printStackTrace();
		}
	}
	
	/**
	 * Print the results of an evaluation to the output stream.
	 * @param eval The evaluation.
	 * @param runtime How long (in mSec) the evaluation took.
	 * @throws Exception The class details string throws an exception.
	 */
	protected void printResults(Evaluation eval, long runtime) throws Exception {
		output.println("Process runtime (milliSeconds): " + runtime);
		output.println(eval.toSummaryString());
		output.println(eval.toClassDetailsString());
		output.println(eval.toMatrixString());
	}
}
