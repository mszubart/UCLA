package libUCLA;

public class UConfig {

    public static final String Proto = "tcp";
    private String source;
    private String port;

    /**
     * @return Endpoint String
     */
    public String getEndpoint() {
        return UConfig.Proto + "://" + source + ":" + port;
    }

    /**
     * UConfig constructor.
     *
     * @param source IP address of host if client or interface if
     * server(http://www.crossroads.io/1-0:xs-tcp).
     * @param port Port number (as string).
     */
    public UConfig(String source, String port) {
        this.source = source;
        this.port = port;
    }
}
