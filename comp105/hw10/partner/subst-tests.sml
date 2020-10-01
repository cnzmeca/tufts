structure S = SealedSolution
val N : S.term = S.app (S.app (S.var "fst") (S.var "x")) (S.var "y")
val checkExpectTerm = Unit.checkExpectWith toString
val () = checkExpectTerm "subst, case (a)" (fn () =>
        S.subst ("x", N) (S.var "x")) N
val () = checkExpectTerm "subst, case (b)" (fn () =>
        S.subst ("x", N) (S.var "y")) (S.var "y")
val () = checkExpectTerm "subst, case (c)" (fn () =>
        S.subst ("x", N) N)
        (S.app (S.app (S.var "fst") N) (S.var "y"))
val () = checkExpectTerm "subst, case (d)" (fn () =>
        S.subst ("x", N) (S.lam "x" N)) (S.lam "x" N)
val () = checkExpectTerm "subst, case (e)" (fn () =>
        S.subst ("x", (S.lam "y" (S.var "y"))) ((S.lam "y" (S.var "x"))))
        (S.lam "y" (S.lam "y" (S.var "y")))
val () = checkExpectTerm "subst, renaming" (fn () =>
        S.subst ("x", N) (S.lam "y" (S.app (S.var "x") (S.var "y")))) 
        (S.lam "ya" (S.app N (S.var "ya")))

val () = Unit.reportWhenFailures ()
