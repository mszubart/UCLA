using System;

using libUCLA;

namespace UCLA_Server {
    class Server {
        static void Main(string[] args) {
            Console.Write("Hi there! You will be receiving a random numbers from remote input.\n");
            Console.Write("Use them to win the lottery!\n");
            Console.Write("Waiting for connection...\n");

            try {
                UReceiver server = new ULoader_JSON("config.json").GetReceiver("input1");
                server.DataReceived += new UReceiveHandler(OnDataReceived);

                server.Run();
            } catch (UException ex) {
                Console.Write(String.Format("Something went horribly wrong:\n\t{0}\n", ex.Message));
            }

            Console.ReadKey();
        }

        private static void OnDataReceived(object sender, UDataReceivedArgs e) {
            Console.Write("\n");

            foreach (byte b in e.Buffer) {
                Console.Write(String.Format("{0:d}\t", b));
            }
        }
    }
}
