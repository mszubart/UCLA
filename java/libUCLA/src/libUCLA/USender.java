package libUCLA;

import io.crossroads.jni.*;
import java.nio.ByteBuffer;

public final class USender {

    /**
     * Tells if connection has been started.
     *
     * @return True if connection has been started
     */
    public boolean isStarted() {
        return this.isStarted;
    }
    private boolean isStarted = false;
    private long ctx = 0;
    private long sock = 0;
    private XsLibrary xs;
    private String endpoint;

    /**
     * UCLA Client constructor.
     *
     * Creates client instance from specified config.
     *
     * @param config Reference to configuration object
     * @throws XSErrorException Will never ever throw this exception, because
     * autostart is off by default so there's no attempt to even use libxs.
     */
    public USender(UConfig config) throws UException {
        this(config, false);
    }

    /**
     * UCLA Client constructor.
     *
     * Creates client instance from specified config.
     *
     * @param config Reference to configuration object
     * @param autostart Tells if connection will be started automatically.
     * Otherwise you will have to call Start method. Default value = false.
     * @throws XSErrorException exception when something fails (only if
     * autostart is enabled).
     */
    public USender(UConfig config, boolean autostart) throws UException {
        this.endpoint = config.getEndpoint();

        if (autostart) {
            this.Start();
        }
    }

    /**
     * Starts connection to a server.
     *
     * @throws XSErrorException exception when something fails.
     */
    public void Start() throws UException {
        if (this.isStarted) {
            return;
        }

        this.xs = new XsLibrary();
        this.ctx = this.xs.xs_init();
        this.sock = this.xs.xs_socket(this.ctx, XsConstants.XS_PUSH);

        int rc = this.xs.xs_connect(this.sock, this.endpoint);

        if (rc == -1) {
            throw new UException(xs);
        }

        this.isStarted = true;
    }

    /**
     * Sends data to a server.
     *
     * @param buf Buffer with data.
     * @param len Length of the data.
     * @throws XSErrorException exception when something fails.
     */
    public void SendData(byte[] data) throws UException {
        if (!this.isStarted) {
            this.Start();
        }

        ByteBuffer buf = ByteBuffer.allocateDirect(data.length);
        buf.put(data);

        int rc = this.xs.xs_send(this.sock, buf, 0, data.length, 0);

        if (rc == -1) {
            throw new UException(this.xs);
        }
    }

    /**
     * Closes connection and terminates the client.
     * Use of this method is not optional.
     * @throws XSErrorException exception when something fails.
     */
    public void Close() throws UException {
        if (!this.isStarted) {
            return;
        }

        int rc = this.xs.xs_close(this.sock);
        
        if (rc != 0) {
            throw new UException(this.xs);
        }
        
        rc = this.xs.xs_term(this.ctx);
        
        if (rc != 0) {
            throw new UException(this.xs);
        }
        
        this.isStarted = false;
    }
}
