(* Lambda calculus solution template, COMP 105 *)
structure OpenSolution = struct

  (******************* EVALUATION BASICS ********************)

  datatype void = VOID of void  (* a type with no values *)

  datatype term = VAR of string | LAM of string * term | APP of term * term

  exception LeftAsExercise of string

  val var : string -> term         = fn x => VAR(x)
  val app : term   -> term -> term = fn x => fn y => APP(x, y)
  val lam : string -> term -> term = fn x => fn y => LAM(x, y)

  val cpsLambda :
      term -> 
      (string -> term -> 'a) -> 
      (term -> term -> 'a) -> 
      (string -> 'a) -> 
      'a
    =   fn t => fn f => fn g => fn h =>
            case t of
                (LAM (x, y)) => f x y
                |  (APP (x, y)) => g x y
                |  (VAR x) => h x

  (********************** SUBSTITUTION **********************)

  fun freeIn s t = case t of
            (LAM (x, y)) => (not (s = x) andalso (freeIn s y))
            |(APP (x, y)) => ((freeIn s x) orelse (freeIn s y))
            |(VAR x) => (s = x)

  fun freeVars t = [" "]
           
  fun subst (s, t1) t2 = case t2 of
            (LAM (x, y)) =>
                if (s = x) then t2
                else if ((not (freeIn s t2)) orelse (not (freeIn x t1))) then
                        (lam x (subst (s, t1) y))
                else (subst (s, t1) (lam (x^"a") (subst (x, (var (x^"a"))) y)))
            |(APP (x, y)) => (app (subst (s, t1) x) (subst (s, t1) y))
            |(VAR x) =>
                if (s = x) then t1      
                else (var x)
          
  (****************** REDUCTION STRATEGIES ******************)
 
  structure R = Reduction 
  val >=> = R.>=>
  infix 1 >=>

  fun beta t = case t of
        (APP ((LAM (x, M)), N)) => R.ONE_STEPS_TO((subst (x, N) M))
        |_ => R.DOESN'T_STEP
  fun eta t = case t of
        (LAM (x, (APP (M, (VAR y))))) =>
        if (x = y) andalso (not (freeIn x M)) then (R.ONE_STEPS_TO(M))
        else R.DOESN'T_STEP
        |_ => R.DOESN'T_STEP
  fun mu_maker r t = case t of
        (APP (M, N)) => (case (r N) of
            (R.ONE_STEPS_TO(Z)) => (R.ONE_STEPS_TO(APP (M, Z)))
            |R.DOESN'T_STEP => R.DOESN'T_STEP)
        |_ => R.DOESN'T_STEP
  fun nu_maker r t = case t of
        (APP (M, N)) => (case (r M) of
            (R.ONE_STEPS_TO(Z)) => (R.ONE_STEPS_TO(APP (Z, N)))
            |R.DOESN'T_STEP => R.DOESN'T_STEP)
        |_ => R.DOESN'T_STEP
  fun xi_maker r t = case t of
        (LAM (x, M)) => (case (r M) of
            (R.ONE_STEPS_TO(Z)) => (R.ONE_STEPS_TO(LAM (x, Z)))
            |R.DOESN'T_STEP => R.DOESN'T_STEP)
        |_ => R.DOESN'T_STEP

  fun reduceN t =
        let val this = reduceN
            val mu = mu_maker this
            val nu = nu_maker this
            val xi = xi_maker this
            val reduce = beta >=> xi >=> eta >=> nu >=> mu
        in reduce t
        end

  fun reduceA t =
        let val this = reduceA
            val mu = mu_maker this
            val nu = nu_maker this
            val xi = xi_maker this
            val reduce = mu >=> nu >=> xi >=> eta >=> beta
        in reduce t
        end

end

structure SealedSolution :> SOLUTION = OpenSolution
