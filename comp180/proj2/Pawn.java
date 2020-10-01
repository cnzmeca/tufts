import java.util.*;

public class Pawn extends Piece {
    public Pawn(Color c) {
        if (c == Color.BLACK || c == Color.WHITE) {
            clr = c;
        } else {
            throw new RuntimeException();
        }
    }

    public String toString() {
        if (clr == Color.BLACK) {
            return "bp";
        } else {
            return "wp";
        }
    }

    public List<String> moves(Board b, String loc) {
        List<String> ret = new ArrayList<String>();
        int f = loc.charAt(0);
        int r = loc.charAt(1);

        if (clr == Color.BLACK) {
            String move1 = "" + (char)(f + 1) + (char)(r - 1);
            String move2 = "" + (char)(f - 1) + (char)(r - 1);
            String move3 = "" + (char)f + (char)(r - 1);
            String move4 = "" + (char)f + (char)(r - 2);
            try {
                Piece p1 = b.getPiece(move1);
                if (p1 != null && p1.color() != clr) {
                    ret.add(move1);
                }
            } catch (ArrayIndexOutOfBoundsException e) {}            
            try {
                Piece p2 = b.getPiece(move2);
                if (p2 != null && p2.color() != clr) {
                    ret.add(move2);
                }
            } catch (ArrayIndexOutOfBoundsException e) {}
            try {
                Piece p3 = b.getPiece(move3);
                if (p3 == null) {
                    ret.add(move3);
                    try {
                        Piece p4 = b.getPiece(move4);
                            if (p4 == null && (char)r == '7') {
                                ret.add(move4);
                            }
                    } catch (ArrayIndexOutOfBoundsException e) {}
                }
            } catch (ArrayIndexOutOfBoundsException e) {}
        } else {
            String move1 = "" + (char)(f + 1) + (char)(r + 1);
            String move2 = "" + (char)(f - 1) + (char)(r + 1);
            String move3 = "" + (char)f + (char)(r + 1);
            String move4 = "" + (char)f + (char)(r + 2);
            try {
                Piece p1 = b.getPiece(move1);
                if (p1 != null && p1.color() != clr) {
                    ret.add(move1);
                }
            } catch (ArrayIndexOutOfBoundsException e) {}
            try {
                Piece p2 = b.getPiece(move2);
                if (p2 != null && p2.color() != clr) {
                    ret.add(move2);
                }
            } catch (ArrayIndexOutOfBoundsException e) {}
            try {
                Piece p3 = b.getPiece(move3);
                if (p3 == null) {
                    ret.add(move3);
                    try {
                        Piece p4 = b.getPiece(move4);
                            if (p4 == null && (char)r == '2') {
                                ret.add(move4);
                            }
                    } catch (ArrayIndexOutOfBoundsException e) {}
                }
            } catch (ArrayIndexOutOfBoundsException e) {}
        
        }
        return ret;
    }

}
