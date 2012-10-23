namespace libUCLA {
    public class UConfig {
        public const string Proto = "tcp";

        /// <summary>
        /// Gets endpoint String
        /// </summary>
        public string Endpoint {
            get {
                return UConfig.Proto + "://" + source + ":" + port;
            }
        }

        private string source;
        private string port;

        /// <summary>
        /// UConfig constructor.
        /// </summary>
        /// <param name="source">IP address of host if client or interface if server(http://www.crossroads.io/1-0:xs-tcp).</param>
        /// <param name="port">Port number (as string).</param>
        public UConfig(string source, string port) {
            this.source = source;
            this.port = port;
        }
    }
}
