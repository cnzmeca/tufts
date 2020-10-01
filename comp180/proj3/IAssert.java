public class IAssert {
    private int i;

    public IAssert(int i) {
        this.i = i;
    }

    public IAssert isEqualTo(int i2) {
        if (i != i2) {
            throw new RuntimeException();
        }
        return this;
    }

    public IAssert isLessThan(int i2) {
        if (i >= i2) {
            throw new RuntimeException();
        }
        return this;
    }

    public IAssert isGreaterThan(int i2) {
        if (i <= i2) {
            throw new RuntimeException();
        }
        return this;
    }
}
