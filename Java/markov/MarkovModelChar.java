package markov;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;

public class MarkovModelChar extends AbstractMarkovModel {

    private HashMap<String, List<String>> wordMap;
    private HashMap<String, HashMap<String, Double>> predWordMap;
    private int keySize;

    public MarkovModelChar(int keySize) {
        super();
        this.keySize = keySize;
        wordMap = new HashMap<>();
        predWordMap = new HashMap<>();
    }

    @Override
    public void setRandomTrainingText(String s) {
        super.setRandomTrainingText(s);
        buildMap();
    }

    @Override
    public void setPredictiveTrainingText(String text, String language) {

    }

    private void predMapAdd(String s, String language) {

    }

    private void buildPredMap(String text, String language) {

    }

    public void predictLanguage(String testText) {

    }

    private void buildMap() {
        wordMap.clear();

        // Go through each char of trainingText
        for (int pos = 0;
             pos < trainingRandomText.length() - keySize;
             pos++) {
            // Get the next key
            String key = trainingRandomText.substring(pos, pos + keySize);
            // Check if key is not already in hashmap
            if (!wordMap.containsKey(key)) {
                // get all the following letters
                int from = pos;
                List<String> follows = new ArrayList<>();
                while (from < trainingRandomText.length()) {
                    int start = trainingRandomText.indexOf(key, from);
                    if (start == -1) break;
                    if (start + key.length() >= trainingRandomText.length() - 1) break;
                    String next = trainingRandomText.substring(
                            start + key.length(), start + key.length() + 1);
                    follows.add(next);
                    from = start + key.length();
                }
                wordMap.put(key, follows);
            }
        } // end of for
        // Check for key at very end
        String key = trainingRandomText.substring(
                trainingRandomText.length() - keySize);
        if (!wordMap.containsKey(key)) {
            wordMap.put(key, new ArrayList<>());
        }
    } // end of buildMap

    @Override
    public List<String> getFollows(String key) {
        if (wordMap.containsKey(key)) {
            return wordMap.get(key);
        }
        else {
            return new ArrayList<String>();
        }
    }

    @Override
    public String getRandomText(int numChars) {
        if (trainingRandomText == null) return "";

        StringBuilder sb = new StringBuilder();

        int index = generator.nextInt(trainingRandomText.length() - keySize);
        String key = trainingRandomText.substring(index, index + keySize);
        sb.append(key);
        for (int i = 0; i < numChars - keySize; i++) {
            List<String> follows = getFollows(key);
            if (follows.size() == 0) break;
            index = generator.nextInt(follows.size());
            String next = follows.get(index);
            sb.append(next);
            key = key.substring(1) + next;
        }

        return sb.toString();
    }

    @Override
    public String toString() {
        return super.toString() + keySize;
    }
}
