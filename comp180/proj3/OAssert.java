import java.util.*;

public class OAssert{
    private Object o;

    public OAssert(Object o) {
        this.o = o;
    }

    public OAssert isNotNull() {
        if (o == null) {
            throw new RuntimeException();
        }
        return this;
    }

    public OAssert isNull() {
        if (o != null) {
            throw new RuntimeException();
        }
        return this;
    }

    public OAssert isEqualTo(Object o2) {
        if (!Objects.equals(o, o2)) {
            throw new RuntimeException();
        }
        return this;
    }

    public OAssert isNotEqualTo(Object o2) {
        if (Objects.equals(o, o2)) {
            throw new RuntimeException();
        }
        return this;
    }

    public OAssert isInstanceOf(Class c) {
        if (o.getClass() != c) {
            throw new RuntimeException();
        }
        return this;
    }
}
