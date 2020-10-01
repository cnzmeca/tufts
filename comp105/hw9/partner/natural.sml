structure Natural :> NATURAL = struct
type nat = int list
val b = 32768

exception Negative
exception BadDivisor

(*
 * abstraction 0 = []
 * abstraction d = [d] where d < b
 * abstraction d = (d mod b) :: abstraction (d div b)
 *)

fun invariant [] = true
|   invariant (d::[]) =
        if (d = 0) then false
        else true
|   invariant (d::n) = (invariant n)

fun addInt (x, 0) = x
|   addInt ([], p) = (p mod b)::(addInt ([], (p div b)))
|   addInt (x::xs, p) = ((p + x) mod b)::(addInt (xs, ((p + x) div b)))

fun shiftAdd (p, 0, x) = addInt(x, p)
|   shiftAdd (p, n, []) = 0::(shiftAdd (p, (n - 1), []))
|   shiftAdd (p, n, x::xs) = x::(shiftAdd (p, (n - 1), xs)) 

fun ofInt n =
    if n < 0 then raise Negative
    else
        addInt([], n)

fun /+/ (n1, []) = n1
|   /+/ ([], n2) = n2
|   /+/ (d1::n1, d2::n2) = ((d1 + d2) mod b)::
                             (addInt ((/+/ (n1, n2)), ((d1 + d2) div b)))

fun borrow [] = raise Negative
|   borrow (0::n) = 9::(borrow n)
|   borrow (d::n) = (d - 1)::n

fun /-/ (n1, []) = n1
|   /-/ ([], n2) = raise Negative
|   /-/ (d1::[], d2::[]) = 
        if (d1 >= d2) then
            (d1 - d2)::[]
            else raise Negative
|   /-/ (d1::n1, d2::n2) =
        if (d1 >= d2) then
            (d1 - d2)::(/-/ (n1, n2))
            else
                (b + d1 - d2)::(/-/ ((borrow n1), n2))

fun multInt (x, 0) = []
|   multInt ([], p) = []
|   multInt (x::xs, p) = ((p * x) mod b)::
                         (addInt ((multInt (xs, p)), (p * x div b)))

fun /*/ (n1, []) = []   
|   /*/ ([], n2) = []
|   /*/ (n1, d2::n2) =
        (/+/ ((multInt (n1, d2)), (0::(/*/ (n1, n2)))))

fun sdiv ([], v) = 
        if (v = 0) then raise BadDivisor
        else
            {quotient = [], remainder = 0}
|   sdiv (n::ns, v) =
        if (0 >= v orelse v > b) then raise BadDivisor
        else
            let val {quotient = q, remainder = r} = (sdiv (ns, v))
            in  if (q = []) then
                    {quotient = addInt(q, (((r * b) + n) div v)),
                    remainder = (((r * b) + n) mod v)}
                else
                    {quotient = addInt(0::q, (((r * b) + n) div v)),
                    remainder = (((r * b) + n) mod v)}
            end

fun compare ([], []) = EQUAL
|   compare (n1, []) = GREATER
|   compare ([], n2) = LESS
|   compare (d1::[], d2::[]) =
        if (d1 = d2) then
            EQUAL
            else if (d1 < d2) then
                LESS
                else GREATER
|   compare (d1::n1, d2::n2) = compare(n1, n2)

fun reverse_decimal [] = []
|   reverse_decimal n = 
        let val {quotient = q, remainder = r} = (sdiv (n, 10))
        in  (r :: (reverse_decimal q))
        end

fun decimal n = 
    let val dec = (List.rev (reverse_decimal n))
    in  if (null dec) then [0]
        else dec
    end
end
