import java.util.*;

public class EdgeGraphAdapter implements EdgeGraph {

    private Graph g;
    
    EdgeGraphAdapter(Graph g) { this.g = g; }

    public boolean addEdge(Edge e) {
        String src = e.getSrc();
        String dst = e.getDst();
        g.addNode(src);
        g.addNode(dst);
        return g.addEdge(src, dst);
    }

    public boolean hasNode(String n) {
        return g.hasNode(n);
    }

    public boolean hasEdge(Edge e) {
        return g.hasEdge(e.getSrc(), e.getDst());
    }

    public boolean hasPath(List<Edge> l) {
        if (l.isEmpty()) {
            return true;
        }
        for (int i = 0; i < l.size()-1; i++) {
            String dst = l.get(i).getDst();
            String src = l.get(i+1).getSrc();
            if (!dst.equals(src)){
                throw new BadPath();
            }
        }

        for (Edge e: l){
            if (!hasEdge(e)){
                return false;
            }
        }
        return true;
    }

}
