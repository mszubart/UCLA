using libUCLA;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.IO;

namespace libUCLA {

    /// <summary>
    /// This exception is being thrown when something go wrong during config processing.
    /// For best debugging, you should check inner exception.
    /// </summary>
    [Serializable]    
    public class ULoaderException : Exception {
        public ULoaderException() : base() { }
        public ULoaderException(string message) : base(message) { }
        public ULoaderException(string message, Exception innerException) : base(message, innerException) { }
    }

    public class ULoader_JSON {
        private JObject clientConfig;
        private JObject serverConfig;

        /// <summary>
        /// Preloads configuration file.
        /// </summary>
        /// <param name="configFile">File name</param>
        public ULoader_JSON(string configFile) {
            try {
                using (StreamReader reader = File.OpenText(configFile)) {
                    JObject config = (JObject) JToken.ReadFrom(new JsonTextReader(reader));

                    //Inputs
                    if (config.GetValue("inputs") != null) {
                        var inputs = config.GetValue("inputs").ToString(Newtonsoft.Json.Formatting.None);
                        this.serverConfig = JObject.Parse(inputs);
                    }

                    //Outputs
                    if (config.GetValue("outputs") != null) {
                        var outputs = config.GetValue("outputs").ToString(Newtonsoft.Json.Formatting.None);
                        this.clientConfig = JObject.Parse(outputs);
                    }
                }
            } catch (Exception ex) {
                throw new ULoaderException("Cannot load configuration from file: '" + configFile + "'", ex);
            }
        }

        /// <summary>
        /// Creates configuration object for server.
        /// </summary>
        /// <param name="serverName">Server name.</param>
        /// <returns>Configuration object.</returns>
        public UConfig GetServerConfig(string serverName) {
            if (this.serverConfig.GetValue(serverName) == null)
                throw new ULoaderException("There is no such server defined in config file. Server name: '" + serverName + "'");

            var configInterface = this.serverConfig.GetValue(serverName)["interface"];
            if (configInterface == null)
                throw new ULoaderException("Cannot read 'interface' vale from specified configuration.");

            var configPort = this.serverConfig.GetValue(serverName)["port"];
            if (configPort == null)
                throw new ULoaderException("Cannot read 'port' vale from specified configuration.");

            UConfig config = new UConfig((String) configInterface, (String) configPort);

            return config;
        }

        /// <summary>
        /// Creates server based on configuration.
        /// </summary>
        /// <param name="serverName">Name of server.</param>
        /// <returns>Server object. (no autostart)</returns>
        public UServer GetServer(string serverName) {
            UServer server = new UServer(GetServerConfig(serverName));
            return server;
        }

        /// <summary>
        /// Creates configuration object for client.
        /// </summary>
        /// <param name="serverName">Server name.</param>
        /// <returns>Configuration object.</returns>
        public UConfig GetClientConfig(string clientName) {
            if (this.clientConfig.GetValue(clientName) == null)
                throw new ULoaderException("There is no such client defined in config file. Client name: '" + clientName + "'");

            var configHost = this.clientConfig.GetValue(clientName)["host"];
            if (configHost == null)
                throw new ULoaderException("Cannot read 'host' vale from specified configuration.");

            var configPort = this.clientConfig.GetValue(clientName)["port"];
            if (configPort == null)
                throw new ULoaderException("Cannot read 'port' vale from specified configuration.");

            UConfig config = new UConfig((String) configHost, (String) configPort);
            return config;
        }

        /// <summary>
        /// Creates client based on configuration.
        /// </summary>
        /// <param name="serverName">Name of server.</param>
        /// <returns>Client object. (no autostart)</returns>
        public UClient GetClient(string clientName) {
            UClient client = new UClient(GetClientConfig(clientName));
            return client;
        }
    }
}
