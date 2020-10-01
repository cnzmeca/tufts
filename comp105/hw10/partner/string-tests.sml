structure S = SealedSolution
val (lam, var, app) = (S.lam, S.var, S.app)

val () = Unit.checkExpectWith (fn s => s) "nested apps"
        (fn () => toString (app (var "x") (app (var "y") (var "z"))))
        "(x (y z))"

val () = Unit.checkExpectWith (fn s => s) "nested lambdas"
        (fn () => toString (lam "w" (lam "x" (lam "y" (var "z")))))
        "(lambda (w) (lambda (x) (lambda (y) z)))"
val () = Unit.checkExpectWith (fn s => s) "chaos"
        (fn () => toString (app (lam "a" (app (lam "b" (var "c")) (app (var "d")
        (var "e")))) (lam "f" (app (var "g") (lam "h" (var "i"))))))
"((lambda (a) ((lambda (b) c) (d e))) (lambda (f) (g (lambda (h) i))))"

val () = Unit.reportWhenFailures ()
