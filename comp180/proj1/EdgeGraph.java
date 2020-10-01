import java.util.*;

public interface EdgeGraph {
    boolean addEdge(Edge e);
    boolean hasNode(String n);
    boolean hasEdge(Edge e);
    boolean hasPath(List<Edge> l);
}