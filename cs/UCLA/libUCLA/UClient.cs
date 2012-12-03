using CrossroadsIO;
using System;

namespace libUCLA {
    public class UClient : IDisposable {

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

        private bool _disposed;

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

            try {
                this.ctx = Context.Create();
                this.sock = this.ctx.CreateSocket(SocketType.PUSH);

                this.sock.Connect(this.endpoint);
            }
            catch (XsException ex) {
                throw new UException(ex.Message, ex);
            }

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

            try {
                this.sock.Send(data, data.Length, SocketFlags.None);
            }
            catch (XsException ex) {
                throw new UException(ex.Message, ex);
            }
        }

        public void Dispose() {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing) {
            if (!this._disposed) {
                if (disposing) {
                    try {
                        this.sock.Close();
                        this.ctx.Terminate();

                        this.sock.Dispose();
                        this.ctx.Dispose();
                    }
                    catch (XsException ex) {
                        throw new UException(ex.Message, ex);
                    }
                }

                this._disposed = true;
            }
        }

        private void EnsureNotDisposed() {
            if (this._disposed) {
                throw new ObjectDisposedException(GetType().FullName);
            }
        }
    }
}
