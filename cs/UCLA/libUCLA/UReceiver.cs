﻿using System;

using CrossroadsIO;

namespace libUCLA {
    public delegate void UReceiveHandler(object sender, UDataReceivedArgs e);

    public class UDataReceivedArgs : EventArgs {
        public byte[] Buffer { get; set; }

        public UDataReceivedArgs(byte[] buffer)
            : base() {
            this.Buffer = buffer;
        }
    }

    public class UReceiver : IDisposable {
        public const int MaxDataLength = 1024;

        /// <summary>
        /// True if receiver has been started
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

        private bool _disposed;

        /// <summary>
        /// UCLA Receiver constructor.
        /// Creates receiver instance from specified config.
        /// </summary>
        /// <param name="config">Reference to configuration object.</param>
        /// <param name="autostart">Tells if receiver will be started automatically.</param>
        public UReceiver(UConfig config, bool autostart = false) {
            this.endpoint = config.Endpoint;

            if (autostart) {
                this.Start();
            }
        }

        /// <summary>
        /// Starts a receiver.
        /// </summary>
        public void Start() {
            EnsureNotDisposed();

            if (this.isStarted) return;

            try {
                this.ctx = Context.Create();
                this.sock = this.ctx.CreateSocket(SocketType.PULL);

                this.sock.Bind(this.endpoint);
            }
            catch (XsException ex) {
                throw new UException(ex.Message, ex);
            }

            this.isStarted = true;
        }

        /// <summary>
        /// Receives single message.
        /// </summary>
        public void Receive() {
            EnsureNotDisposed();
            if (!this.isStarted) {
                this.Start();
            }

            byte[] buf = new byte[UReceiver.MaxDataLength];
            int receivedLength = -1;

            try {
                receivedLength = this.sock.Receive(buf);
            }
            catch (XsException ex) {
                throw new UException(ex.Message, ex);
            }

            if (this.DataReceived != null) {
                byte[] callBuf = new byte[receivedLength];
                Array.Copy(buf, callBuf, receivedLength);

                this.DataReceived(this, new UDataReceivedArgs(callBuf));
            }
        }

        /// <summary>
        /// Run in loop and receive messages.
        /// NOTE: This is infinite loop - just don't expect it to stop.
        /// </summary>
        public void Run() {
            EnsureNotDisposed();

            while (true) {
                this.Receive();
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
