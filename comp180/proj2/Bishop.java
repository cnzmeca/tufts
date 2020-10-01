import java.util.*;

public class Bishop extends Piece {
    public Bishop(Color c) {
        if (c == Color.BLACK || c == Color.WHITE) {
            clr = c;
        } else {
            throw new RuntimeException();
        }
    }

    public String toString() {
        if (clr == Color.BLACK) {
            return "bb";
        } else {
            return "wb";
        }
    }

    public List<String> moves(Board b, String loc) {
        List<String> ret = new ArrayList<String>();
        int file = loc.charAt(0);
        int rank = loc.charAt(1);
       
        int[] h = {1, 1, -1, -1};
        int[] v = {1, -1, 1, -1};

        for (int i = 0; i < 4; i++) {
            int j = 1;
            boolean open = true;
            while (open) {
                int f = file + h[i] * j;
                int r = rank + v[i] * j;
                String move = "" + (char)f + (char)r;
                try {
                    Piece p = b.getPiece(move);
                    if (p == null) {
                        ret.add(move);
                    } else {
                        open = false;
                        if (p.color() != clr) {
                            ret.add(move);
                        }
                    }
                } catch (ArrayIndexOutOfBoundsException e) {
                    open = false;
                }
                j++;
            }
        }

         
        return ret;
    }

}
