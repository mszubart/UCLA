package UCLA_Server;

import libUCLA.UConfig;
import libUCLA.UReceiveHandler;
import libUCLA.UServer;
import libUCLA.XSErrorException;

class MessageDisplay implements UReceiveHandler {

    @Override
    public void OnDataReceived(byte[] buf) {
        System.out.printf("\n");

        for (byte b : buf) {
            System.out.printf("%d\t", b);
        }
    }
}

public class Server {

    public static void main(String[] args) {
        MessageDisplay md = new MessageDisplay();
        try {
            UConfig config = new UConfig("*", "5555");
            UServer server = new UServer(config, true);

            server.SetupReceiveHandler(md);

            server.Run();
        } catch (XSErrorException ex) {
            System.out.printf("%s", ex.what());
        }
    }
}
