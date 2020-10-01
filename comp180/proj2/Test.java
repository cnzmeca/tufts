import java.util.*;
public class Test {

    // Run "java -ea Test" to run with assertions enabled (If you run
    // with assertions disabled, the default, then assert statements
    // will not execute!)

    public static void pawnTest() {
	    Board b = Board.theBoard();
	    Piece.registerPiece(new PawnFactory());
	    Piece wp = Piece.createPiece("wp");
	    Piece bp = Piece.createPiece("bp");
   	    b.addPiece(bp, "a7");
   	    b.addPiece(wp, "b6");
        List<String> list = bp.moves(b, "a7");
        System.out.println(Arrays.toString(list.toArray()));
    }

    public static void knightTest() {
        Board b = Board.theBoard();
        Piece.registerPiece(new KnightFactory());
        Piece.registerPiece(new PawnFactory());
        Piece bn = Piece.createPiece("bn");
        Piece wp = Piece.createPiece("wp");
        Piece bp = Piece.createPiece("bp");
        b.addPiece(bn, "g4");
        b.addPiece(bp, "f2");
        b.addPiece(wp, "f6");
        List<String> list = bn.moves(b, "g4");
        System.out.println(Arrays.toString(list.toArray()));
    }

    public static void bishopTest() {
        Board b = Board.theBoard();
        Piece.registerPiece(new BishopFactory());
        Piece.registerPiece(new PawnFactory());
        Piece bb = Piece.createPiece("bb");
        Piece wp = Piece.createPiece("wp");
        Piece bp = Piece.createPiece("bp");
        b.addPiece(bb, "f3");
        b.addPiece(bp, "d1");
        b.addPiece(wp, "h5");
        List<String> list = bb.moves(b, "f3");
        System.out.println(Arrays.toString(list.toArray()));
    }
    public static void rookTest() {
        Board b = Board.theBoard();
        Piece.registerPiece(new RookFactory());
        Piece.registerPiece(new PawnFactory());
        Piece br = Piece.createPiece("br");
        Piece wp = Piece.createPiece("wp");
        Piece bp = Piece.createPiece("bp");
        b.addPiece(br, "e5");
        b.addPiece(bp, "e7");
        b.addPiece(wp, "c5");
        List<String> list = br.moves(b, "e5");
        System.out.println(Arrays.toString(list.toArray())); 
    }
    public static void queenTest() {
        Board b = Board.theBoard();
        Piece.registerPiece(new QueenFactory());
        Piece.registerPiece(new PawnFactory());
        Piece bq = Piece.createPiece("bq");
        Piece wp = Piece.createPiece("wp");
        Piece bp = Piece.createPiece("bp");
        b.addPiece(bq, "e5");
        b.addPiece(bp, "e7");
        b.addPiece(wp, "c5");
        List<String> list = bq.moves(b, "e5");
        System.out.println(Arrays.toString(list.toArray()));
    }
    public static void kingTest() {
        Board b = Board.theBoard();
        Piece.registerPiece(new KingFactory());
        Piece.registerPiece(new PawnFactory());
        Piece bk = Piece.createPiece("bk");
        Piece wp = Piece.createPiece("wp");
        Piece bp = Piece.createPiece("bp");
        b.addPiece(bk, "e5");
        b.addPiece(bp, "e6");
        b.addPiece(wp, "d5");
        List<String> list = bk.moves(b, "e5");
        System.out.println(Arrays.toString(list.toArray()));
    }

    public static void main(String[] args) {
	pawnTest();
    knightTest();
    bishopTest();
    rookTest();
    queenTest();
    kingTest();
    }

}
