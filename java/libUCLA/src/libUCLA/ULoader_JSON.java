package libUCLA;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import net.sf.json.JSONObject;
import net.sf.json.JSONSerializer;

public class ULoader_JSON {

    private JSONObject jsonData;
    private JSONObject serverData;
    private JSONObject clientData;

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

    public UConfig getServerConfig(String serverName) throws UException {
        String iface = "";
        String port = "";

        try {
            serverData = jsonData.getJSONObject("inputs");
            iface = serverData.getJSONObject(serverName).getString("interface");
            port = serverData.getJSONObject(serverName).getString("port");
        } catch (Exception e) {
            throw new UException("Cannot read server values from specified configuration.", e);
        }

        UConfig config = new UConfig(iface, port);
        return config;
    }

    public UServer getServer(String serverName) throws UException {
        UServer server = new UServer(this.getServerConfig(serverName));

        return server;
    }

    public UConfig getClientConfig(String clientName) throws UException {
        String host = "";
        String port = "";

        try {
            clientData = jsonData.getJSONObject("outputs");
            host = clientData.getJSONObject(clientName).getString("host");
            port = clientData.getJSONObject(clientName).getString("port");
        } catch (Exception e) {
            throw new UException("Cannot read client values from specified configuration.", e);
        }

        UConfig config = new UConfig(host, port);
        return config;
    }

    public UClient getClient(String clientName) throws UException {
        UClient client = new UClient(this.getClientConfig(clientName));

        return client;
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
