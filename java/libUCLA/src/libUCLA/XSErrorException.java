package libUCLA;

import io.crossroads.jni.XsLibrary;

public class XSErrorException extends Exception {

    private String message;

    public XSErrorException() {
        super();
        message = "unknown";
    }

    public XSErrorException(String message) {
        super(message);
        this.message = message;
    }

    public XSErrorException(XsLibrary xs) {
        this(xs.xs_strerror(xs.xs_errno()));
    }

    public String what() {
        return this.message;
    }
}
