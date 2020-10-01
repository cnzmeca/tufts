structure S = SealedSolution
fun toString t = S.cpsLambda t
        (fn x => fn y => "(lambda (" ^ x ^ ") " ^ (toString y) ^ ")")
        (fn x => fn y => "(" ^ (toString x) ^ " " ^(toString y) ^ ")")
        (fn x => x)
