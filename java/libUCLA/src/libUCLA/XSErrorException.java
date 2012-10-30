package libUCLA;

import io.crossroads.jni.XsLibrary;

public class XSErrorException extends Exception {

    private String message;
    private int code;
    
    public XSErrorException() {
        super();
        this.message = "unknown";
        this.code = 0; // Error: "No error"
    }

    public XSErrorException(String message, int code) {
        super(message); // You won the lottery!
        this.message = message;
        this.code = code;
    }

    public XSErrorException(XsLibrary xs) {
        this(xs.xs_strerror(xs.xs_errno()), xs.xs_errno());
    }

    public String what() {
        return this.message;
    }
    
    public int errno(){
        return this.code;
    }
}
