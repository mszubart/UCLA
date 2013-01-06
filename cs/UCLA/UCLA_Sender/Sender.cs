using System;

using libUCLA;

namespace UCLA_Sender {
    class Sender {
        static Random rnd = new Random();

        static void Main(string[] args) {
            Console.Write("Me is client. Me is input. Me sending random number things.\n");
            Console.Write("Me waiting connection...\n");

            try {
                USender sender = new ULoader_JSON("config.json").GetSender("output1");

                for (int i = 0; i < 3; i++) {
                    sender.SendData(_8randomBytes());
                }

                Console.Write("Data sent successfully. Me exiting after you pressing return.\n");
            } catch (UException ex) {
                Console.Write(String.Format("Something went horribly wrong:\n\t{0}\n", ex.Message));
            }

            Console.ReadKey();
        }

        static byte[] _8randomBytes() {
            byte[] r = new byte[8];


            for (int i = 0; i < 8; i++) {
                r[i] = (byte) rnd.Next(1, 48);
            }

            return r;
        }
    }
}
