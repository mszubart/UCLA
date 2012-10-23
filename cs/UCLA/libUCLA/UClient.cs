using CrossroadsIO;

namespace libUCLA {
    public class UClient {

        /// <summary>
        /// True if connection has been started.
        /// </summary>
        public bool IsStarted {
            get { return this.isStarted; }
        }

        private bool isStarted = false;
        private Context ctx;
        private Socket sock;
        private string endpoint;

        /// <summary>
        /// UCLA Client constructor.
        /// Creates client instance from specified config.
        /// </summary>
        /// <param name="config">Reference to configuration object.</param>
        /// <param name="autostart">Tells if connection will be started automatically. 
	    /// Otherwise you will have to call Start method. Default value = false.</param>
        public UClient(UConfig config, bool autostart = false) {
            this.endpoint = config.Endpoint;

            if (autostart) {
                this.Start();
            }
        }

        /// <summary>
        /// Starts connection to a server.
        /// </summary>
        public void Start() {
            if (this.isStarted) return;

            this.ctx = Context.Create();
            this.sock = this.ctx.CreateSocket(SocketType.PUSH);

            this.sock.Connect(this.endpoint);

            this.isStarted = true;
        }

        /// <summary>
        /// Sends data to a server in blocking mode.    
        /// </summary>
        /// <param name="data">Buffer with data.</param>
        public void SendData(byte[] data) {
            if (!this.isStarted) {
                this.Start();
            }

            this.sock.Send(data);
        }

    }
}
