package markov;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public abstract class AbstractMarkovModel implements IMarkovModel {

    protected String trainingRandomText;
    protected Random generator;

    public AbstractMarkovModel() {
        generator = new Random();
    }

    public void setRandomTrainingText(String s)
    {
        trainingRandomText = s.trim();
    }

    public void setRandom(int seed) {
        generator = new Random(seed);
    }

    protected List<String> getFollows(String key) {
        List<String> follows = new ArrayList<>();
        int pos = 0;

        while (pos < trainingRandomText.length()) {
            int start = trainingRandomText.indexOf(key, pos);
            if (start == -1) break;
            if (start + key.length() >= trainingRandomText.length() - 1) break;
            String next = trainingRandomText.substring(start + key.length(), start + key.length() + 1);
            follows.add(next);
            pos = start + key.length();
        }

        return follows;
    }

    @Override
    public String toString() {
        return "Markov Model of order ";
    }

    abstract public String getRandomText(int numChars);
    abstract public void setPredictiveTrainingText(String s, String language);
}
