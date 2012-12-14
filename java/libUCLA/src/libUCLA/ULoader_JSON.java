package libUCLA;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import net.sf.json.JSONObject;
import net.sf.json.JSONSerializer;

public class ULoader_JSON {

    private JSONObject jsonData;
    private JSONObject receiverData;
    private JSONObject senderData;

    public ULoader_JSON(String fileName) throws UException {
        try {
            String json = this.readJsonFromFile(fileName);
            jsonData = (JSONObject) JSONSerializer.toJSON(json);
        } catch (FileNotFoundException ex) {
            throw new UException("Cannot load configuration from file: '" + fileName + "'", ex);
        } catch (IOException ex) {
            throw new UException("Cannot load configuration from file: '" + fileName + "'", ex);
        }

    }

    public UConfig getReceiverConfig(String inputName) throws UException {
        String iface = "";
        String port = "";

        try {
            receiverData = jsonData.getJSONObject("inputs");
            iface = receiverData.getJSONObject(inputName).getString("interface");
            port = receiverData.getJSONObject(inputName).getString("port");
        } catch (Exception e) {
            throw new UException("Cannot read server values from specified configuration.", e);
        }

        UConfig config = new UConfig(iface, port);
        return config;
    }

    public UReceiver getReceiver(String inputName) throws UException {
        UReceiver receiver = new UReceiver(this.getReceiverConfig(inputName));

        return receiver;
    }

    public UConfig getSenderConfig(String outputName) throws UException {
        String host = "";
        String port = "";

        try {
            senderData = jsonData.getJSONObject("outputs");
            host = senderData.getJSONObject(outputName).getString("host");
            port = senderData.getJSONObject(outputName).getString("port");
        } catch (Exception e) {
            throw new UException("Cannot read client values from specified configuration.", e);
        }

        UConfig config = new UConfig(host, port);
        return config;
    }

    public USender getSender(String outputName) throws UException {
        USender sender = new USender(this.getSenderConfig(outputName));

        return sender;
    }

    private String readJsonFromFile(String file) throws FileNotFoundException, IOException {
        BufferedReader reader = new BufferedReader(new FileReader(file));
        String line;
        StringBuilder stringBuilder = new StringBuilder();
        String ls = System.getProperty("line.separator");

        while ((line = reader.readLine()) != null) {
            stringBuilder.append(line);
            stringBuilder.append(ls);
        }

        return stringBuilder.toString();
    }
}
