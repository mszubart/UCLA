﻿using System;

using libUCLA;

namespace UCLA_Client {
    class Client {
        static Random rnd = new Random();

        static void Main(string[] args) {
            Console.Write("Me is client. Me is input. Me sending random number things.\n");
            Console.Write("Me waiting connection...\n");

            try {
                UConfig config = new UConfig("127.0.0.1", "5555");
                UClient client = new UClient(config, true);

                for (int i = 0; i < 3; i++) {
                    client.SendData(_8randomBytes());
                }
            } catch (Exception ex) {
                Console.Write(String.Format("Something went horribly wrong:\n\t{0}\n", ex.Message));
            }

            Console.Write("Data sent successfully. Me exiting after you pressing return.\n");
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
