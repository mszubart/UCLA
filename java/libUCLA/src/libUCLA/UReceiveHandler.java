package libUCLA;

public interface UReceiveHandler {

    /**
     * This handler is called every time when message is received. 
     * NOTE: Handler shouldn't be blocking.
     */
    public void OnDataReceived(byte[] buf);
}
