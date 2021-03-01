package markov;

public interface IMarkovModel {

    public void setRandomTrainingText(String text);
    public void setPredictiveTrainingText(String text, String language);
    public String getRandomText(int numChars);
    public void predictLanguage(String testText);
    public void setRandom(int seed);

}
