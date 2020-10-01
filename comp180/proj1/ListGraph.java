import java.util.*;

public class ListGraph implements Graph {
    private HashMap<String, LinkedList<String>> nodes = new HashMap<>();;
    
    public boolean addNode(String n) {
	    boolean in = hasNode(n);
        if (!in) {
            LinkedList<String> ll = new LinkedList<String>();
            nodes.put(n, ll);
        }
        return !in;
    }

    public boolean addEdge(String n1, String n2) {
        if (!(hasNode(n1) && hasNode(n2))) {
            throw new NoSuchElementException();
        }

        boolean in = hasEdge(n1, n2);
        if (!in) {
            nodes.get(n1).add(n2);
        }      
        return !in; 
    }

    public boolean hasNode(String n) {
        return nodes.containsKey(n);
    }

    public boolean hasEdge(String n1, String n2) {
        return nodes.get(n1).contains(n2); 
    }
    
    public List<String> succ(String n) {
        if(!hasNode(n)){
            throw new NoSuchElementException();
        }
        
        return nodes.get(n);
    }

    public List<String> pred(String n) {
        if(!hasNode(n)){
            throw new NoSuchElementException();
        }
        
        List<String> preds = new LinkedList<String>();
        for (String n2 : nodes.keySet()) { 
            LinkedList<String> ll = nodes.get(n2);
            if (ll.contains(n)) {
                preds.add(n2);
            }
        }
        return preds;
    }

    public boolean connected(String n1, String n2) {
        if (!(hasNode(n1) && hasNode(n2))) {
            throw new NoSuchElementException();
        }
        
        if(n1.equals(n2)) {
            return true;
        }

        List<String> queue = succ(n1);
        List<String> visited = new LinkedList<String>();
        visited.add(n1);

        while (!queue.isEmpty()) {
            String curr = queue.get(0);
            queue.remove(0);
            if (!visited.contains(curr)) {
                visited.add(curr);
                if (curr.equals(n2)){
                    return true;
                }

                for (String s : succ(curr)) {
                    queue.add(s);
                }
            }
        }
        return false;
    }
}
