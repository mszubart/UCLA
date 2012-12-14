package UCLA_Server;

import java.io.IOException;
import libUCLA.UReceiveHandler;
import libUCLA.UReceiver;
import libUCLA.UException;
import libUCLA.ULoader_JSON;

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
        System.out.printf("Hi there! You will be receiving a random numbers from remote input.\n");
        System.out.printf("Use them to win the lottery!\n");
        System.out.printf("Waiting for connection...\n");

        MessageDisplay md = new MessageDisplay();
        try {
            UReceiver server = new ULoader_JSON("config.json").getReceiver("input1");

            server.SetupReceiveHandler(md);

            server.Run();

            server.Close(); // Will never be reached.
        } catch (UException ex) {
            System.out.printf("Something went horribly wrong:\n\t%s", ex.what());
        }
        
        try {
            System.in.read();
        } catch (IOException ex) {
            System.out.printf("Java is so super safe, that even reading input can throw an exception.");
        }
    }
}
