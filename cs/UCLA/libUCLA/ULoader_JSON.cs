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
    public class ULoaderException : UException {
        public ULoaderException() : base() { }
        public ULoaderException(string message) : base(message) { }
        public ULoaderException(string message, Exception innerException) : base(message, innerException) { }
    }

    public class ULoader_JSON {
        private JObject outputConfig;
        private JObject inputConfig;

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
                        this.inputConfig = JObject.Parse(inputs);
                    }

                    //Outputs
                    if (config.GetValue("outputs") != null) {
                        var outputs = config.GetValue("outputs").ToString(Newtonsoft.Json.Formatting.None);
                        this.outputConfig = JObject.Parse(outputs);
                    }
                }
            } catch (Exception ex) {
                throw new ULoaderException("Cannot load configuration from file: '" + configFile + "'", ex);
            }
        }

        /// <summary>
        /// Creates configuration object for receiver.
        /// </summary>
        /// <param name="inputName">Input name.</param>
        /// <returns>Configuration object.</returns>
        public UConfig GetReceiverConfig(string inputName) {
            if (this.inputConfig.GetValue(inputName) == null)
                throw new ULoaderException("There is no such input defined in config file. Input name: '" + inputName + "'");

            var configInterface = this.inputConfig.GetValue(inputName)["interface"];
            if (configInterface == null)
                throw new ULoaderException("Cannot read 'interface' vale from specified configuration.");

            var configPort = this.inputConfig.GetValue(inputName)["port"];
            if (configPort == null)
                throw new ULoaderException("Cannot read 'port' vale from specified configuration.");

            UConfig config = new UConfig((String) configInterface, (String) configPort);

            return config;
        }

        /// <summary>
        /// Creates receiver based on configuration.
        /// </summary>
        /// <param name="inputName">Name of input.</param>
        /// <returns>Receiver object. (no autostart)</returns>
        public UReceiver GetReceiver(string inputName) {
            UReceiver server = new UReceiver(GetReceiverConfig(inputName));
            return server;
        }

        /// <summary>
        /// Creates configuration object for sender.
        /// </summary>
        /// <param name="outputName">Output name.</param>
        /// <returns>Configuration object.</returns>
        public UConfig GetSenderConfig(string outputName) {
            if (this.outputConfig.GetValue(outputName) == null)
                throw new ULoaderException("There is no such output defined in config file. Output name: '" + outputName + "'");

            var configHost = this.outputConfig.GetValue(outputName)["host"];
            if (configHost == null)
                throw new ULoaderException("Cannot read 'host' vale from specified configuration.");

            var configPort = this.outputConfig.GetValue(outputName)["port"];
            if (configPort == null)
                throw new ULoaderException("Cannot read 'port' vale from specified configuration.");

            UConfig config = new UConfig((String) configHost, (String) configPort);
            return config;
        }

        /// <summary>
        /// Creates sender based on configuration.
        /// </summary>
        /// <param name="outputName">Name of output.</param>
        /// <returns>Sender object. (no autostart)</returns>
        public USender GetSender(string outputName) {
            USender client = new USender(GetSenderConfig(outputName));
            return client;
        }
    }
}
