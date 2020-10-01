import java.util.*;

public class Suite {

    @BeforeClass
    public static void beforeClassA() {
        System.out.println("BeforeClass A");
    }

    @BeforeClass
    public static void beforeClassB() {
        System.out.println("BeforeClass B");
    }

    @Before
    public void beforeA() {
        System.out.println("Before A");
    }

    @Before
    public void beforeB() {
        System.out.println("Before B");
    }

    @Test
    public void testO() {
        System.out.println("Test O"); 
        ArrayList<String> o1 = new ArrayList<String>();
        ArrayList<String> o2 = new ArrayList<String>();
        o2.add("potato");
        ArrayList<String> o3 = null;
   
        Assertion.assertThat(o1).isNotNull().isEqualTo(new ArrayList<String>()).isNotEqualTo(o2);
        Assertion.assertThat(o3).isNull();
    }

    @Test
    public void testS() {
        System.out.println("Test S");
        String s1 = "";
        String s2 = null;
        String s3 = "computer";
        String s4 = "comp";
        String s5 = "ute";
        Assertion.assertThat(s2).isNull();
        Assertion.assertThat(s3).isNotNull().isNotEqualTo(s4).isEqualTo("computer").startsWith(s4).contains(s5);
    }

    @Test
    public void testB() {
        System.out.println("Test B");
        boolean b1 = true;
        boolean b2 = false;

        Assertion.assertThat(b1).isEqualTo(true).isTrue();
        Assertion.assertThat(b2).isEqualTo(false).isFalse();
    }

    @Test
    public void testI() {
        System.out.println("Test I");
        int i1 = 5;
        int i2 = 3;
        int i3 = 7;
        Assertion.assertThat(i1).isEqualTo(5).isLessThan(i3).isGreaterThan(i2);
    }

    @After
    public void afterA() {
        System.out.println("After A");
    }

    @After
    public void afterB() {
        System.out.println("After B");
    }

    @AfterClass
    public static void afterClassA() {
        System.out.println("Afterclass A");
    }

    @AfterClass
    public static void afterClassB() {
        System.out.println("Afterclass B");
    }

    @Property
    public boolean propI(@IntRange(min=-20, max=20) Integer i1, @IntRange(min=-10, max=10) Integer i2) {
        System.out.println("Property I");
        return !(i1 == -15 && i2 == -9);    
    }

    @Property
    public boolean propS(@StringSet(strings={"a", "b"}) String s1, @StringSet(strings={"c", "d"}) String s2) {
        System.out.println("Property S");
        return !(s1.equals("a") && s2.equals("d"));
    }

    @Property
    public boolean propL(@ListLength(min=0, max=2) List<@ListLength(min=0, max=2) List<@IntRange(min=5, max=5) Integer>> l){
        System.out.println("Property L");
        return !(l.equals((List<Object>) new ArrayList<Object>()));
    }

    @Property
    public boolean propO(@ForAll(name="genIntSet", times=10) Object o) {
        System.out.println("Property O");
        int[] o2 = {0, 1, 2, 3, 4};
        return !(Arrays.equals((int []) o, o2));
    }

    int count = 0;
    Object genIntSet() {
        int[] l = new int[count];
        for (int i=0; i<count; i++) { l[i] = i; }
        count++;
    return l;
    }
}
