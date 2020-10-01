import java.util.*;

public class SAssert{
    private String s;

    public SAssert(String s) {
        this.s = s;
    }

    public SAssert isNotNull() {
        if (s == null) {
            throw new RuntimeException();
        }
        return this;
    }

    public SAssert isNull() {
        if (s != null) {
            throw new RuntimeException();
        }
        return this;
    }

    public SAssert isEqualTo(Object o) {
        if (!Objects.equals(s, o)) {
            throw new RuntimeException();
        }
        return this;
    }

    public SAssert isNotEqualTo(Object o) {
        if (Objects.equals(s, o)) {
            throw new RuntimeException();
        }
        return this;
    }

    public SAssert startsWith(String s2) {
        if (!s.startsWith(s2)) {
            throw new RuntimeException();
        }
        return this;
    }

    public SAssert isEmpty() {
        if (!s.isEmpty()) {
            throw new RuntimeException();
        }
        return this;
    }

    public SAssert contains(String s2) {
        if (s.indexOf(s2) == -1) {
            throw new RuntimeException();
        }
        return this;
    }
}
