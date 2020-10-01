functor BignumFn(structure N : NATURAL) :> BIGNUM = struct
type bigint = N.nat * bool

(*
 * abstraction n = (n, true) where n is a positive integer
 * abstraction n = (n, false) where n is a negative integer
 *)

fun invariant (i, s) = if (N.compare (i, N.ofInt 0)) = LESS then false else true

exception BadDivision

fun ofInt n = (N.ofInt(n), true) handle N.Negative => (N.ofInt(0 - n), false)
fun negated (i, s) = (i, (not s))
fun <+> ((i1, s1), (i2, s2)) =
        if (s1 = s2) then (N./+/ (i1, i2), s1)
        else (N./-/ (i1, i2), s1) handle N.Negative => (N./-/ (i2, i1), s2)
fun <-> (b1, b2) = (<+> (b1, (negated b2)))
fun <*> ((i1, s1), (i2, s2)) =
        if (s1 = s2) then (N./*/ (i1, i2), true)
        else (N./*/ (i1, i2), false)
fun sdiv ((i1, s1), v) =
        let val {quotient = q, remainder = r} = N.sdiv (i1, v)
        in {quotient = (q, s1), remainder = r}
        end

fun compare ((i1, s1), (i2, s2)) =
        if (s1 = true) then
            if (s2 = true) then (N.compare (i1, i2))
            else GREATER
        else
            if (s2 = true) then LESS
            else (N.compare (i2, i1))

fun toString (i, s) =
        let val str = (List.foldr (fn (x, y) =>
                (concat ((Int.toString x)::[y]))) "" (N.decimal i))
        in  if s then str
            else (concat ("-"::[str]))
        end
end
