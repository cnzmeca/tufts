import java.io.*;
import java.util.*;

public class Chess {
    public static void main(String[] args) {
	if (args.length != 2) {
	    System.out.println("Usage: java Chess layout moves");
	}
    
    Piece.registerPiece(new KingFactory());
	Piece.registerPiece(new QueenFactory());
	Piece.registerPiece(new KnightFactory());
	Piece.registerPiece(new BishopFactory());
	Piece.registerPiece(new RookFactory());
	Piece.registerPiece(new PawnFactory());
	Board.theBoard().registerListener(new Logger());
    
    File layout = new File(args[0]); 
    File moves = new File(args[1]);
    try {
        Scanner sc1 = new Scanner(layout);
        Scanner sc2 = new Scanner(moves);
        while (sc1.hasNextLine()){
            String square = sc1.nextLine();
            if (square.charAt(0) != '#'){
                if (square.charAt(2) != '=') {
                    throw new RuntimeException();
                }
                String loc = square.substring(0,2);
                String name = square.substring(3,5);
                Piece p = Piece.createPiece(name);
                Board.theBoard().addPiece(p, loc); 
            }
        }
        while (sc2.hasNextLine()) {
            String move = sc2.nextLine();
            if (move.charAt(0) != '#'){
                if (move.charAt(2) != '-') {
                    throw new RuntimeException();
                }
                String from = move.substring(0,2);
                String to = move.substring(3,5);
                Board.theBoard().movePiece(from, to);
            }
        }
    } catch (FileNotFoundException e) {
    }



	// args[0] is the layout file name
	// args[1] is the moves file name
	// Put your code to read the layout file and moves files
	// here.

	// Leave the following code at the end of the simulation:
	System.out.println("Final board:");
	Board.theBoard().iterate(new BoardPrinter());
    }
}
