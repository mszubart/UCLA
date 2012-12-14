package UCLA_Receiver;

import java.io.IOException;
import java.util.Random;
import libUCLA.USender;
import libUCLA.UException;
import libUCLA.ULoader_JSON;

public class Sender {

    public static void main(String[] args) {
        System.out.printf("Me is client. Me is input. Me sending random number things.\n");
        System.out.printf("Me waiting connection...\n");

        try {
            USender sender = new ULoader_JSON("config.json").getSender("output1");

            for (int i = 0; i < 3; i++) {
                sender.SendData(_8randomBytes());
            }

            sender.Close();

            System.out.
                    printf("Data sent successfully. Me exiting after you pressing return.\n");
        } catch (UException ex) {
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
