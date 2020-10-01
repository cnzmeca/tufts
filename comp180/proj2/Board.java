import java.util.*;
        
public class Board {

    private Piece[][] pieces = new Piece[8][8];
    private static Board obj = null;
    private List<BoardListener> lists = new ArrayList<BoardListener>();
    
    private Board() { }
    
    public static Board theBoard() {
        if (obj == null) {
            obj = new Board();
        }
        return obj;
    }

    // Returns piece at given loc or null if no such piece
    // exists
    public Piece getPiece(String loc) {
        int file = loc.charAt(0) - 97;
        int rank = loc.charAt(1) - 49;

        return pieces[file][rank];
    }

    public void addPiece(Piece p, String loc) {
        int file = loc.charAt(0) - 97;
        int rank = loc.charAt(1) - 49;
        if (pieces[file][rank] == null) { 
            pieces[file][rank] = p;
        } else {
            throw new RuntimeException();
        }
    }

    private void removePiece(String loc) {
        int file = loc.charAt(0) - 97;
        int rank = loc.charAt(1) - 49;

        pieces[file][rank] = null;
    }

    public void movePiece(String from, String to) {
        Piece p1 = getPiece(from);
        Piece p2 = getPiece(to);
        
        if (p1 == null) {
            throw new RuntimeException();
        }

        List<String> moves = p1.moves(this, from);
        if (!moves.contains(to)) {
            throw new RuntimeException();
        }

        for (BoardListener l : lists) {
            l.onMove(from, to, p1);
        }
        
        if (p2 != null) {
            for (BoardListener l : lists) {
                l.onCapture(p1, p2);
            }
        }
        removePiece(to);
        addPiece(p1, to);
        removePiece(from); 
        
    }

    public void clear() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                pieces[i][j] = null;
            }
        }
    }

    public void registerListener(BoardListener bl) {
        lists.add(bl);
    }

    public void removeListener(BoardListener bl) {
        lists.remove(bl);
    }

    public void removeAllListeners() {
        lists.clear();
    }

    public void iterate(BoardExternalIterator bi) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                String loc = "" + (char)(j + 97) + (char)(i + 49);
                Piece p = getPiece(loc);
                bi.visit(loc, p);
            }
        }
    }
}
