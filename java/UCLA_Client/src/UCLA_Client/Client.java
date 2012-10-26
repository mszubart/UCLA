package UCLA_Client;

import java.util.Random;
import libUCLA.UClient;
import libUCLA.UConfig;
import libUCLA.XSErrorException;

public class Client {

    public static void main(String[] args){

        try {
            UConfig config = new UConfig("127.0.0.1", "5555");
            UClient client = new UClient(config, true);

            for (int i = 0; i < 3; i++) {
                client.SendData(_8randomBytes());
            }

        } catch (XSErrorException ex) {
            System.out.printf("%s", ex.what());
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
