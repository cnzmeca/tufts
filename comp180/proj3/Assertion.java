public class Assertion {
    /* You'll need to change the return type of the assertThat methods */
    static OAssert assertThat(Object o) {
        return new OAssert(o);
    }
    static SAssert assertThat(String s) {
        return new SAssert(s);
    }
    static BAssert assertThat(boolean b) {
        return new BAssert(b);
    }
    static IAssert assertThat(int i) {
       return new IAssert(i);
    }
}
