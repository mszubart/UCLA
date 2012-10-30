package libUCLA;

import io.crossroads.jni.*;
import java.nio.ByteBuffer;

public final class UServer {

    public static final int MaxDataLength = 256;

    /**
     * Tells if server has been started.
     *
     * @return True if server has been started
     */
    public boolean isStarted() {
        return this.isStarted;
    }
    private UReceiveHandler DataReceivedHandler = null;
    private boolean isStarted = false;
    private long ctx = 0;
    private long sock = 0;
    private XsLibrary xs;
    private String endpoint;

    /**
     * UCLA Server constructor.
     *
     * Creates server instance from specified config.
     *
     * @param config Reference to configuration object
     * @throws XSErrorException Will never ever throw this exception, because
     * autostart is off by default so there's no attempt to even use libxs.
     */
    public UServer(UConfig config) throws XSErrorException {
        this(config, false);
    }

    /**
     * UCLA Server constructor.
     *
     * Creates server instance from specified config.
     *
     * @param config Reference to configuration object
     * @param autostart Tells if server will be started automatically. Otherwise
     * you will have to call Start method.
     * @throws XSErrorException exception when something fails (only if
     * autostart is enabled).
     */
    public UServer(UConfig config, boolean autostart) throws XSErrorException {
        this.endpoint = config.getEndpoint();

        if (autostart) {
            this.Start();
        }
    }

    /**
     * Starts a server.
     *
     * @throws XSErrorException exception when something fails.
     */
    public void Start() throws XSErrorException {
        if (this.isStarted) {
            return;
        }

        this.xs = new XsLibrary();
        this.ctx = this.xs.xs_init();
        this.sock = this.xs.xs_socket(this.ctx, XsConstants.XS_PULL);

        int rc = this.xs.xs_bind(this.sock, this.endpoint);

        if (rc == -1) {
            throw new XSErrorException(xs);
        }

        this.isStarted = true;
    }

    /**
     * Receives single message.
     *
     * NOTE: This is blocking.
     *
     * @throws XSErrorException exception when something fails.
     */
    public void Receive() throws XSErrorException {
        ByteBuffer buf = ByteBuffer.allocateDirect(UServer.MaxDataLength);

        int receivedLength =
                this.xs.xs_recv(this.sock, buf, 0, MaxDataLength, 0);

        if (receivedLength < 0) {
            throw new XSErrorException(this.xs);
        }

        if (this.DataReceivedHandler != null) {
            byte[] callBuf = new byte[receivedLength];
            buf.get(callBuf, 0, receivedLength);

            this.DataReceivedHandler.OnDataReceived(callBuf);
        }
    }

    /**
     * Run in loop and receive messages.
     *
     * NOTE: This is infinite loop - just don't expect it to stop.
     */
    public void Run() {
        while (true) {
            try {
                this.Receive();
            } catch (XSErrorException ex) {
                System.err.
                        printf("libxs caught exception: %s\n Who cares! This loop will continue.",
                               ex.what());
                continue;
            }

        }
    }

    /**
     * Sets ReceiveHandler.
     *
     * This handler is called every time when message is received. NOTE: Handler
     * shouldn't be blocking.
     *
     * @param handler Pointer to void (char*, int) function.
     */
    public void SetupReceiveHandler(UReceiveHandler handler) {
        this.DataReceivedHandler = handler;
    }

    /**
     * Closes connection and terminates the server. 
     * Use of this method is not optional.
     *
     * @throws XSErrorException exception when something fails.
     */
    public void Close() throws XSErrorException {
        if (!this.isStarted) {
            return;
        }

        int rc = this.xs.xs_close(this.sock);

        if (rc != 0) {
            throw new XSErrorException(this.xs);
        }

        rc = this.xs.xs_term(this.ctx);

        if (rc != 0) {
            throw new XSErrorException(this.xs);
        }

        this.isStarted = false;
    }
}
