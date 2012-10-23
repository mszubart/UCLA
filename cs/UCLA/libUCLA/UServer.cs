using System;

using CrossroadsIO;

namespace libUCLA {
    public delegate void UReceiveHandler(byte[] buf);

    public class UServer {
        public const int MaxDataLength = 256;

        /// <summary>
        /// True if server has been started
        /// </summary>
        public bool IsStarted {
            get { return this.isStarted; }
        }

        /// <summary>
        /// This handler is called every time when message is received.
        /// </summary>
        public event UReceiveHandler DataReceived;

        private bool isStarted = false;
        private Context ctx;
        private Socket sock;
        private string endpoint;

        /// <summary>
        /// UCLA Server constructor.
        /// Creates server instance from specified config.
        /// </summary>
        /// <param name="config">Reference to configuration object.</param>
        /// <param name="autostart">Tells if server will be started automatically.</param>
        public UServer(UConfig config, bool autostart = false) {
            this.endpoint = config.Endpoint;

            if (autostart) {
                this.Start();
            }
        }
        
        /// <summary>
        /// Starts a server.
        /// </summary>
        public void Start() {
            if (this.isStarted) return;

            this.ctx = Context.Create();
            this.sock = this.ctx.CreateSocket(SocketType.PULL);

            this.sock.Bind(this.endpoint);

            this.isStarted = true;
        }

        /// <summary>
        /// Receives single message.
        /// </summary>
        public void Receive() {
            byte[] buf = new byte[UServer.MaxDataLength];
            int receivedLength = this.sock.Receive(buf);

            if (this.DataReceived != null) {
                byte[] callBuf = new byte[receivedLength];
                Array.Copy(buf, callBuf, receivedLength);

                this.DataReceived(callBuf);
            }
        }
        
        /// <summary>
        /// Run in loop and receive messages.
        /// NOTE: This is infinite loop - just don't expect it to stop.
        /// </summary>
        public void Run() {
            while (true) {
                this.Receive();
            }
        }
    }
}
