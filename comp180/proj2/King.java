import java.util.*;

public class King extends Piece {
    public King(Color c) {
        if (c == Color.BLACK || c == Color.WHITE) {
            clr = c;
        } else {
            throw new RuntimeException();
        }
    }

    public String toString() {
        if (clr == Color.BLACK) {
            return "bk";
        } else {
            return "wk";
        }
    }

    public List<String> moves(Board b, String loc) {
        List<String> ret = new ArrayList<String>();
        int file = loc.charAt(0);
        int rank = loc.charAt(1);
        
        int[] h = {1, 0, -1, 0, 1, 1, -1, -1};
        int[] v = {0, 1, 0, -1, 1, -1, 1, -1};

        for (int i = 0; i < 8; i++) {
            int f = file + h[i];
            int r = rank + v[i];
            String move = "" + (char)f + (char)r;
            try {
                Piece p = b.getPiece(move);
                if (p == null) {
                    ret.add(move);
                } else {
                    if (p.color() != clr) {
                        ret.add(move);
                    }
                }
            } catch (ArrayIndexOutOfBoundsException e) {}
        }

        return ret;
    }

}