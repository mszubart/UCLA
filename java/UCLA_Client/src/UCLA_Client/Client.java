package UCLA_Client;

import java.io.IOException;
import java.util.Random;
import libUCLA.UClient;
import libUCLA.UConfig;
import libUCLA.XSErrorException;

public class Client {

    public static void main(String[] args) {
        System.out.printf("Me is client. Me is input. Me sending random number things.\n");
        System.out.printf("Me waiting connection...\n");

        try {
            UConfig config = new UConfig("127.0.0.1", "5555");
            UClient client = new UClient(config, true);

            for (int i = 0; i < 3; i++) {
                client.SendData(_8randomBytes());
            }

            client.Close();

            System.out.
                    printf("Data sent successfully. Me exiting after you pressing return.\n");
        } catch (XSErrorException ex) {
            System.out.printf("Something went horribly wrong:\n\t%s", ex.what());
        }
        
        try {
            System.in.read();
        } catch (IOException ex) {
            System.out.printf("Java is so super safe, that even reading input can throw an exception.");
        }
    }

    public static byte[] _8randomBytes() {
        byte[] r = new byte[8];

        Random rnd = new Random();

        for (int i = 0; i < 8; i++) {
            r[i] = (byte) (rnd.nextInt(48) + 1);
        }

        return r;
    }
}
