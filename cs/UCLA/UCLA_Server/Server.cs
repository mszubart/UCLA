using System;

using libUCLA;

namespace UCLA_Server {
    class Server {
        static void Main(string[] args) {
            Console.Write("Hi there! You will be receiving a random numbers from remote input.\n");
            Console.Write("Use them to win the lottery!\n");
            Console.Write("Waiting for connection...\n");

            try {
                UConfig config = new UConfig("*", "5555");
                UServer server = new UServer(config, true);
                server.DataReceived += new UReceiveHandler(OnDataReceived);
                server.Run();
            } catch (Exception ex) {
                Console.Write(String.Format("Something went horribly wrong:\n\t{0}\n", ex.Message));
            }

            Console.ReadKey();
        }

        private static void OnDataReceived(byte[] buf) {
            Console.Write("\n");

            foreach (byte b in buf) {
                Console.Write(String.Format("{0:d}\t", b));
            }
        }
    }
}
