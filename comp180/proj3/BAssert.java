public class BAssert{
    private boolean b;

    public BAssert(boolean b) {
        this.b = b;
    }

    public BAssert isEqualTo(boolean b2) { 
        if (b != b2) {
            throw new RuntimeException();
        }
        return this;
    }

    public BAssert isTrue() {
        if (b == false) {
            throw new RuntimeException();
        }
        return this;
    }

    public BAssert isFalse() {
        if (b == true) {
            throw new RuntimeException();
        }
        return this;
    }
}
