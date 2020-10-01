import java.util.*;

public class Run {
    public static void main(String[] args) {
        HashMap<String, Throwable> result1 = Unit.testClass("Suite");
        System.out.println(result1);
        HashMap<String, Object[]> result2 = Unit.quickCheckClass("Suite"); 
        System.out.println(result2);
    }
}
