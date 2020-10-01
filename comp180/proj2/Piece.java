import java.util.*;

abstract public class Piece {
    public Color clr;
    private static HashMap<Character, PieceFactory> facts = new HashMap<>();

    public static void registerPiece(PieceFactory pf) {
        facts.put(new Character(pf.symbol()), pf);
    }

    public static Piece createPiece(String name) {
        char color = name.charAt(0);
        char type = name.charAt(1);
        Color c;
        if (color == 'b') {
            c = Color.BLACK;
        } else if (color == 'w') {
            c = Color.WHITE;
        } else {
            throw new RuntimeException(); 
        }
        return facts.get(new Character(type)).create(c); 
    }

    public Color color() {
        return clr;
    }

    abstract public String toString();

    abstract public List<String> moves(Board b, String loc);
}
