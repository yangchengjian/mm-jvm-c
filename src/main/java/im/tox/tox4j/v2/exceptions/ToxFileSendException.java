package im.tox.tox4j.v2.exceptions;

public class ToxFileSendException extends SpecificToxException {

    public static enum Code {
        NULL,
        FRIEND_NOT_FOUND,
        NAME_EMPTY,
        NAME_TOO_LONG,
        TOO_MANY,
    }

    public final Code code;

    public ToxFileSendException(Code code) {
        this.code = code;
    }

    @Override
    public Code getCode() {
        return code;
    }

}