package csc7333;

import java.util.Map;

import weka.classifiers.Classifier;
import weka.classifiers.Evaluation;
import weka.classifiers.trees.J48;
import weka.core.Attribute;
import weka.core.FastVector;
import weka.core.Instance;
import weka.core.Instances;

/**
 * This class sets up a C4.5 decision tree classifier for the UCI spam data.
 */
public class C45Classifier {
	private DataLoader loader;
	private FastVector attributes;
	
	/**
	 * Create a new classifier on the specified data.
	 * @param loader The data loader.
	 */
	public C45Classifier(DataLoader loader) {
		this.loader = loader;
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
	private Instance makeInstance(Map<String, Double> record) {
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
			System.out.println(test.toSummaryString());
		} catch (Exception ex) {
			System.err.println("Failed to train and test C4.5 on all data.");
			ex.printStackTrace();
		}
	}
}
