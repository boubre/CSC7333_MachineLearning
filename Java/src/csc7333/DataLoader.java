package csc7333;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * This class loads data from the UCI Spam data base into memory.
 * The data set is represented as a list of data records. Each record is a map from the column header to that record's value.
 */
public class DataLoader {
	private List<String> headers;
	private List<Map<String, Double>> dataSet;
	
	/**
	 * Create a new DataLoader and load the data.
	 * @param headers The file containing the data headers (.name).
	 * @param data The file containing the data records (.data).
	 */
	public DataLoader(File headers, File data) {
		loadHeaders(headers);
		loadData(data);
	}
	
	/**
	 * Load the data headers from the .names file.
	 * @param headerFile The file.
	 */
	private void loadHeaders(File headerFile) {
		try (Stream<String> lines = Files.lines(headerFile.toPath())) {
			headers = lines.filter(u -> !(u.startsWith("|") || u.trim().isEmpty()))
					.map(u -> u.split(":")[0])
					.collect(Collectors.toList());
		} catch (IOException ex) {
			System.err.println("Could not read from data headers file (.names)");
			ex.printStackTrace();
			System.exit(1);
		}
	}

	/**
	 * Load the data records from the .data file.
	 * NOTE: Load the headers before the records.
	 * @param dataFile The file.
	 */
	private void loadData(File dataFile) {
		assert headers != null : "Should call loadHeaders first!";
		
		try (Stream<String> lines = Files.lines(dataFile.toPath())) {
			dataSet = lines.filter(u -> !(u.startsWith("|") || u.trim().isEmpty()))
					.map(u -> recordToMap(u))
					.collect(Collectors.toList());
		} catch (IOException ex) {
			System.err.println("Could not read from data records file (.data)");
			ex.printStackTrace();
			System.exit(1);
		}
	}
	
	/**
	 * Convert a data record represented as a comma separated string into a map from column headers to record values.
	 * @param record The data record to convert. (A comma separated string.)
	 * @return The converted record. (A map from a column header to the records value for that column.)
	 */
	private Map<String, Double> recordToMap(String record) {
		assert headers != null : "Should call loadHeaders first!";
		
		Map<String, Double> newRecord = new HashMap<>();
		String[] splitRecord = record.split(",");
		for(int i = 0; i < splitRecord.length; i++) {
			newRecord.put(headers.get(i), Double.parseDouble(splitRecord[i]));
		}
		return newRecord;
	}
	
	/**
	 * @return A list of data headers. (In the same order as they were loaded.)
	 */
	public List<String> getHeaders() {
		return headers;
	}
	
	/**
	 * @return The data set.
	 */
	public List<Map<String, Double>> getDataSet() {
		return dataSet;
	}
}
