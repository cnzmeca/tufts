import java.util.*;

public class NFA {

    private List<Object> states;
    private Object start;
    private List<Object> finals;
    private Map<Object, List<Map.Entry<Character, Object>>> transitions;
    
    NFA() {
        states = new ArrayList<Object>();
        finals = new ArrayList<Object>();
        transitions = new HashMap<Object, List<Map.Entry<Character, Object>>>();
        start = this.newState();
    }

    Object newState() {
        UUID new_state = UUID.randomUUID();
        states.add(new_state);
        transitions.put(new_state, new ArrayList<Map.Entry<Character, Object>>());
        return new_state;
    }

    void newTransition(Object start, char c, Object end) {
        List<Map.Entry<Character, Object>> tlist = transitions.get(start);
        if (tlist == null) {
            throw new RuntimeException();
        }

        if (transitions.get(end) == null) {
            throw new RuntimeException();
        }        

        Character ch = new Character(c);
        Map.Entry<Character, Object> entry = new AbstractMap.SimpleEntry<Character, Object>(ch, end);
        tlist.add(entry);
        transitions.put(start, tlist);
    }
    
    void makeFinal(Object s) {
        if (!states.contains(s)) {
            throw new RuntimeException();
        }
        finals.add(s);
    }

    NFA(Regex re) {
        NFA temp = helper(re);
        states = temp.states;
        start = temp.start;
        finals = temp.finals;
        transitions = temp.transitions;
    }

    private NFA helper(Regex re) {
        Class outer = re.getClass();
        if (outer == ROr.class) {
            ROr temp = (ROr) re;
            NFA l = helper(temp.left);
            NFA r = helper(temp.right);
            
            NFA ret = new NFA();
            Object s1 = ret.start;
            ret.states.addAll(l.states);
            ret.states.addAll(r.states);
            ret.transitions.putAll(l.transitions);
            ret.transitions.putAll(r.transitions);
            ret.newTransition(s1, '#', l.start);
            ret.newTransition(s1, '#', r.start);
            ret.start = s1;
            ret.finals.addAll(l.finals);
            ret.finals.addAll(r.finals);
            return ret;
        } else if (outer == RSeq.class) {
            RSeq temp = (RSeq) re;
            NFA l = helper(temp.left);
            NFA r = helper(temp.right);
            
            l.states.addAll(r.states);
            l.transitions.putAll(r.transitions);
            for (Object o : l.finals) {
                l.newTransition(o, '#', r.start);
            }
            l.finals = r.finals;
            return l;
        } else if (outer == RStar.class) {
            RStar temp = (RStar) re;
            NFA ret = helper(temp.re);
            
            Object s1 = ret.newState();
            ret.newTransition(s1, '#', ret.start);
            for (Object o : ret.finals) {
                ret.newTransition(o, '#', s1);
            }
            ret.start = s1;
            ret.finals.clear();
            ret.finals.add(s1);
            return ret;
        } else if (outer == RChar.class) {
            RChar temp = (RChar) re;
            char c = temp.c;

            NFA ret = new NFA();
            Object s1 = ret.newState();
            ret.newTransition(ret.start, c, s1);
            ret.makeFinal(s1);
            return ret;
        } else {
            throw new RuntimeException();
        }
    }

    public List<Object> states() {
        return states;
    }

    public Object start_state() {
        return start;
    }

    public List<Object> final_states() {
        return finals;
    }

    public List<Map.Entry<Character, Object>> transition(Object state) {
        return transitions.get(state);
    }

    boolean match(String s, int nthreads) {
        int curr_threads = 1;
        List<Object> curr_states = epsilon(start);
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            List<Object> new_states = new ArrayList<Object>();
            for (Object o : curr_states) {
                if (curr_threads < nthreads) {
                    Thread obj = new Thread();
                    curr_threads++;
                    obj.start();
                }
                List<Map.Entry<Character, Object>> tlist = transitions.get(o);
                for (Map.Entry<Character, Object> e : tlist) {
                    if (e.getKey().charValue() == c) {
                        new_states.addAll(epsilon(e.getValue()));
                    }
                }
                
            }
            curr_threads = 1;
            curr_states = new_states;
        }

        for (Object o : curr_states) {
            if (finals.contains(o)) {
                return true;
            }   
        }

        return false;
    }

    private List<Object> epsilon(Object state) {
        List<Object> ret = new ArrayList<Object>();
        ret.add(state);
        List<Map.Entry<Character, Object>> tlist = transitions.get(state);
        for (Map.Entry<Character, Object> e : tlist) {
            if (e.getKey().charValue() == '#') {
                Object o = e.getValue();
                ret.addAll(epsilon(o));
            }
        }
        return ret;
    }
}
