functor AgsFun (structure Game : GAME) :> AGS 
        where type Game.Move.move = Game.Move.move
        and   type Game.state     = Game.state = struct

structure Game = Game
exception AGSError

fun advice state =
    if (Game.isOver(state)) then
        case (Game.outcome state) of
            SOME oc => {move = NONE, expectedOutcome = oc}
            |NONE => raise AGSError 
    else
        let fun solve_moves x = case x of
            [] => raise AGSError
            |move::[] =>
            let val {move = m, expectedOutcome = oc} =
                (advice (Game.makemove state move))
            in {move = SOME move, expectedOutcome = oc}
            end
            |move::moves =>
            let val {move = m, expectedOutcome = oc} =
                (advice (Game.makemove state move))
            in  if (oc = (Player.WINS (Game.whoseturn state))) then
                    {move = SOME move, expectedOutcome = oc} else
                if (oc = Player.TIE) then
                    let val {move = mr, expectedOutcome = ocr} =
                        (solve_moves moves)
                    in  if (ocr = (Player.WINS (Game.whoseturn state))) then
                        (solve_moves moves) else
                        {move = SOME move, expectedOutcome = oc}
                    end else
                    (solve_moves moves) 
            end
        in solve_moves (Game.legalmoves state)
        end
(*
        let val moves = (Game.legalmoves state)
            val win = (List.find (fn (x) =>
                (Game.outcome (Game.makemove state x)) =
                (SOME (Player.WINS (Game.whoseturn state)))) moves)
        in  case win of
            (SOME move) => {move = win,
                expectedOutcome = Player.WINS (Game.whoseturn state)}
            |NONE => {move = SOME (List.last moves),
                expectedOutcome = Player.TIE}
        end
*)
end
