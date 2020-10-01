import java.util.*;
public class Main {

    // Run "java -ea Main" to run with assertions enabled (If you run
    // with assertions disabled, the default, then assert statements
    // will not execute!)
    
    public static void test1() {
	Graph g = new ListGraph();
	assert g.addNode("a");
	assert g.hasNode("a");
    assert g.addNode("b");
    assert g.hasNode("b");
    assert g.addNode("c");
    assert g.hasNode("c");
    assert g.addNode("d");
    assert g.hasNode("d");
    assert g.addNode("e");
    assert g.hasNode("e");
    assert g.addNode("f");
    assert g.hasNode("f");
    assert !g.hasNode("g");

    assert g.addEdge("a", "a");
    assert g.hasEdge("a", "a");
    assert g.addEdge("a", "b");
    assert g.hasEdge("a", "b");
    assert g.addEdge("a", "c");
    assert g.hasEdge("a", "c");
    assert g.addEdge("d", "f");
    assert g.hasEdge("d", "f");
    assert g.addEdge("e", "f");
    assert g.hasEdge("e", "f");
    assert g.addEdge("f", "f");
    assert g.hasEdge("f", "f"); 
    assert g.addEdge("f", "d");
    assert g.hasEdge("f", "d");
    assert g.addEdge("d", "e");
    assert g.hasEdge("d", "e");    
    assert !g.hasEdge("a", "f");



    List<String> succ = new LinkedList<String>();
    succ.add("a");
    succ.add("b");
    succ.add("c");

    assert g.succ("a").equals(succ); 

    List<String> pred = new LinkedList<String>();
    pred.add("d");
    pred.add("e");
    pred.add("f");  

    assert g.pred("f").equals(pred);
    
    assert g.connected("a", "a");
    assert g.connected("a", "b");
    assert !g.connected("b", "a");
    assert !g.connected("a", "d");
    
    assert g.connected("f", "e");
    assert g.connected("e", "f");
    }


    public static void test2() {
	Graph g = new ListGraph();
	EdgeGraph eg = new EdgeGraphAdapter(g);
	
    Edge e1 = new Edge("a", "b");
    Edge e2 = new Edge("b", "c");
    Edge e3 = new Edge("c", "d");
    Edge e4 = new Edge("d", "e");
    Edge e5 = new Edge("d", "f");

    assert eg.addEdge(e1);
	assert eg.hasEdge(e1);
    assert eg.addEdge(e2);
    assert eg.hasEdge(e2);
    assert eg.addEdge(e3);
    assert eg.hasEdge(e3);
    assert eg.addEdge(e4);
    assert eg.hasEdge(e4);
    assert !eg.hasEdge(e5);

    assert eg.hasNode("a");
    assert eg.hasNode("b");
    assert eg.hasNode("c");
    assert eg.hasNode("d");
    assert eg.hasNode("e");
    assert !eg.hasNode("f");

    List<Edge> path1 = new LinkedList<Edge>();
    path1.add(e1);
    path1.add(e2);
    path1.add(e3);
    path1.add(e4);
    
    List<Edge> path2 = new LinkedList<Edge>();
    path2.add(e1);
    path2.add(e2);
    path2.add(e3);
    path2.add(e5);   
 
    assert eg.hasPath(path1); 
    assert !eg.hasPath(path2); 
    }
    
    public static void main(String[] args) {
	test1();
	test2();
    }

}
