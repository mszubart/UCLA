package libUCLA;

import io.crossroads.jni.XsLibrary;

public class UException extends Exception {

    private String message;
    private int code;
    private Exception innerEcxeption = null;
    
    public UException() {
        super();
        this.message = "unknown";
        this.code = 0; // Error: "No error"
    }

    public UException(String message, int code) {
        super(message); // You won the lottery!
        this.message = message;
        this.code = code;
    }

    public UException(XsLibrary xs) {
        this(xs.xs_strerror(xs.xs_errno()), xs.xs_errno());
    }
    
    public UException(String message, Exception innerException){
        super(message);
        this.message = message;
        this.innerEcxeption = innerException;
    }

    public Exception getInnerException(){
        return this.innerEcxeption;
    }
    
    public String what() {
        return this.message;
    }
    
    public int errno(){
        return this.code;
    }
}
