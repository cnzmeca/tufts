structure Coins :> GAME = struct

type state = Player.player * (int * int * int)

(*
 * My state abstraction function maps a game state onto a 2-tuple containing
 * a player and a 3-tuple containing 3 integers, one for each coin denomination
 *)

fun invariant (p, (qs, ds, ns)) =
        if ((p = Player.X orelse p = Player.O) andalso (qs >= 0) andalso
                (ds >= 0) andalso (ns >= 0)) then true
        else false

structure Move = struct
datatype move = Q of int | D of int | N of int

(*
 * My move abstraction function maps a move to a datatype which has subtypes
 * Q, D, and N, for each denomination, all of which require an interger for
 * how many of that coin will be taken
 *)

fun invariant (Q n) = if (n >= 1) then true else false
|   invariant (D n) = if (n >= 1) then true else false
|   invariant (N n) = if (n >= 1) then true else false

exception Move

fun findName s =
  List.find (fn name => String.isSubstring name s) 
            ["quarter", "dime", "nickel"]

val findNumber =
  Int.fromString o implode o List.filter Char.isDigit o explode

fun parse str =
case (findName str, findNumber str) of
         (NONE, _) => raise Move
        |(_, NONE) => raise Move
        |(SOME coin, SOME n) =>
        case coin of
                 "quarter" => (Q n)
                |"dime" => (D n)
                |"nickel" => (N n)
                | _ => raise Move
fun prompt p = "What coins does player " ^ (Player.unparse p) ^ " take?\t"

fun visualize p (Q n) =
"Player " ^ (Player.unparse p) ^ " takes " ^ (Int.toString n) ^ " quarters"
|   visualize p (D n) =
"Player " ^ (Player.unparse p) ^ " takes " ^ (Int.toString n) ^ " dimes"
|   visualize p (N n) =
"Player " ^ (Player.unparse p) ^ " takes " ^ (Int.toString n) ^ " nickels"

end
fun initial p = (p, (4, 10, 7))
fun makemove (p, (qs, ds, ns)) (Move.Q n) =
        if (n <= qs) then ((Player.otherplayer p), (qs - n, ds, ns))
        else raise Move.Move
|   makemove (p, (qs, ds, ns)) (Move.D n) =
        if (n <= ds) then ((Player.otherplayer p), (qs, ds - n, ns))
        else raise Move.Move
|   makemove (p, (qs, ds, ns)) (Move.N n) =
        if (n <= ns) then ((Player.otherplayer p), (qs, ds, ns - n))
        else raise Move.Move
fun visualize (p, (qs, ds, ns)) =
"Player " ^ (Player.unparse p) ^ " sees " ^ (Int.toString qs) ^ " quarters, " ^
(Int.toString ds) ^ " dimes and " ^ (Int.toString ns) ^ " nickels\n"
fun whoseturn (p, (qs, ds, ns)) = p
fun isOver (p, (qs, ds, ns)) =
        if ((qs = 0) andalso (ds = 0) andalso (ns = 0)) then true
        else false
fun outcome (p, (qs, ds, ns)) = 
        if (isOver (p, (qs, ds, ns))) then
                (SOME (Player.WINS (Player.otherplayer p)))
        else NONE

infix 9 downto
fun n downto i = if n < i then []
                 else n :: (n - 1) downto i

fun legalmoves (p, (qs, ds, ns)) =
(List.concat ([(List.map Move.Q (qs downto 1)),
               (List.map Move.D (ds downto 1)),
               (List.map Move.N (ns downto 1))]))

end
