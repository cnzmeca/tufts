(****************************COMP 105 ML ASSIGNMENT****************************)
(*
 * Christian Zinck
 * No collaborators
 * No extra credit
 *)
(***** Problem A *****)
(* fun mynull : 'a list -> bool *)
fun mynull [] = true
  | mynull x = false

        val () = Unit.checkAssert "empty" (fn () => mynull [])
        val () = Unit.checkAssert "non-empty" (fn () => not(mynull [1]))

(***** Problem B *****)
(* fun firstVowel : char list -> bool *)
fun firstVowel (x::_) = List.exists (fn y => x=y) [#"a", #"e", #"i", #"o", #"u"]
  | firstVowel [] = false
        
        val () = Unit.checkAssert "vowel" (fn () => firstVowel [#"a"])
        val () = Unit.checkAssert "cons" (fn () => not(firstVowel [#"b", #"a"]))

(***** Problem C *****)
(* fun reverse : 'a list -> 'a list *)
fun reverse x = List.foldl (op ::) [] x

        val () = Unit.checkExpectWith (Unit.listString Int.toString) "non-empty"
            (fn () => reverse [1, 2, 3]) [3, 2, 1]

(* fun minlist : int list -> int *)
fun minlist (x::xs) = List.foldl (fn (y, z) => if (z > y) then y else z) x xs
  | minlist [] = raise Match

        val () = Unit.checkExnWith Int.toString "empty"
            (fn () => minlist [])
        val () = Unit.checkExpectWith Int.toString "positive"
            (fn () => minlist [5, 4, 3, 2, 1]) 1
        val () = Unit.checkExpectWith Int.toString "mixed"
            (fn () => minlist [~5, 4, ~3, 2, ~1]) ~5

(***** Problem D *****)
exception Mismatch

(* fun zip  : 'a list * 'b list -> ('a * 'b) list *)
fun zip ((x::xs), (y::ys)) = (x, y)::(zip (xs, ys))
  | zip ([], []) = []
  | zip _ = raise Mismatch

        val () = Unit.checkExnWith (Unit.listString (Unit.pairString
            Int.toString Int.toString)) "mismatch"
            (fn () => zip ([1, 2, 3], []))
        val () = Unit.checkExpectWith (Unit.listString (Unit.pairString
            Int.toString Int.toString)) "equal"
            (fn () => zip ([1, 2, 3], [1, 2, 3])) [(1, 1), (2, 2), (3, 3)]

(***** Problem E *****)
(* fun pairfoldrEq : ('a * 'b * 'c -> 'c) -> 'c -> 'a list * 'b list -> 'c *)
fun pairfoldrEq f c (x::xs, y::ys) = f (x, y, (pairfoldrEq f c (xs, ys)))
  | pairfoldrEq f c ([], []) = c
  | pairfoldrEq f c _ = raise Mismatch

        val () = Unit.checkExnWith Int.toString "mismatch"
            (fn () => pairfoldrEq (fn (x, y, z) => x + y + z) 0
            ([1, 2, 3], [1, 2]))
        val () = Unit.checkExpectWith Int.toString "equal"
            (fn () => pairfoldrEq (fn (x, y, z) => x + y + z) 0
            ([1, 2, 3], [1, 2, 3])) 12

(* fun ziptoo : 'a list * 'b list -> ('a * 'b) list *)
fun ziptoo (x, y) = pairfoldrEq (fn (a, b, c) => (a, b)::c) [] (x, y)

        val () = Unit.checkExnWith (Unit.listString (Unit.pairString
            Int.toString Int.toString)) "mismatch"
            (fn () => ziptoo ([1, 2, 3], []))
        val () = Unit.checkExpectWith (Unit.listString (Unit.pairString
            Int.toString Int.toString)) "equal"
            (fn () => ziptoo ([1, 2, 3], [1, 2, 3])) [(1, 1), (2, 2), (3, 3)]

(***** Problem F *****)
(* fun concat : 'a list list -> 'a list *)
fun concat x = foldr (op @) [] x

        val () = Unit.checkExpectWith (Unit.listString Int.toString) "empty"
            (fn () => concat ([])) []
        val () = Unit.checkExpectWith (Unit.listString Int.toString) "non-empty"
            (fn () => concat ([[1], [2, 3, 4], [], [5, 6]])) [1, 2, 3, 4, 5, 6]

(***** Problem G *****)
type 'a env = string -> 'a
exception NotFound of string

(* val emptyEnv : 'a env *)
val emptyEnv = fn (x) => raise NotFound(x)

        val () = Unit.checkExnWith (Int.toString) "empty"
            (fn () => emptyEnv "dog")

(* fun bindVar : string * 'a * 'a env -> 'a env *)
fun bindVar (k, v, env) = fn (x) => if (x = k) then v else env (x)

        val () = Unit.checkExnWith (Int.toString) "wrong key"
            (fn () => (bindVar ("cat", 1, emptyEnv) "dog"))
        val () = Unit.checkExpectWith (Int.toString) "right key"
            (fn () => (bindVar ("dog", 1, emptyEnv) "dog")) 1

(* fun lookup : string * 'a env -> 'a *)
fun lookup (k, env) = env (k)

        val () = Unit.checkExpectWith (Int.toString) "right key"
            (fn () => lookup ("dog", (bindVar ("dog", 1, emptyEnv)))) 1

(* fun isbound : string * 'a env -> bool *)
fun isBound (k, env) = (if (env (k)  = env (k)) then true else true) 
                        handle NotFound(k) => false

        val () = Unit.checkAssert "bound"
            (fn () => isBound ("dog", (bindVar ("dog", 1, emptyEnv))))
        val () = Unit.checkAssert "not bound"
            (fn () => not (isBound ("dog", (bindVar ("cat", 1, emptyEnv)))))

(***** Problem H *****)
datatype nat = ZERO
             | TIMES10PLUS of nat * int

(* fun times10plus : nat * int -> nat *)
fun times10plus (ZERO, 0) = ZERO
  | times10plus (m, d)    = TIMES10PLUS (m, d)

fun times10 n = times10plus (n, 0)
fun natOfDigit d = times10plus (ZERO, d)
fun flip f (x, y) = f (y, x)
fun natOfDigits ds = foldl (flip times10plus) ZERO ds

(* fun intOfNat : nat -> int *)
fun intOfNat (ZERO) = 0
  | intOfNat (TIMES10PLUS (m, d)) = 10 * intOfNat (m) + d

        val () = Unit.checkExpectWith Int.toString "zero"
            (fn () => intOfNat(ZERO)) 0
        val () = Unit.checkExpectWith Int.toString "non-zero"
            (fn () => intOfNat(natOfDigits ([1, 2, 3]))) 123

(* fun natOfInt : int -> nat *)
fun natOfInt (0) = ZERO
  | natOfInt (x) = TIMES10PLUS (natOfInt(x div 10), x mod 10)

        val () = Unit.checkExpectWith Int.toString "zero"
            (fn () => intOfNat(natOfInt(0))) 0
        val () = Unit.checkExpectWith Int.toString "non-zero"
            (fn () => intOfNat(natOfInt(2018))) 2018

(* fun natString : nat -> string *)
fun natString (x) = Int.toString (intOfNat x)

        val () = Unit.checkExpectWith String.toString "zero"
            (fn () => natString (ZERO)) "0"     
        val () = Unit.checkExpectWith String.toString "non-zero"
            (fn () => natString (natOfDigits [2, 0, 1, 8])) "2018"      

(***** Problem I *****)
(* fun carryIntoNat : nat * int -> nat *)
fun carryIntoNat (n, 0) = n
  | carryIntoNat (ZERO, c) = natOfInt(c)
  | carryIntoNat (TIMES10PLUS (m,d), c) = times10plus(m, d + c)

        val () = Unit.checkExpectWith Int.toString "add zero"
            (fn () => intOfNat(carryIntoNat(natOfInt(5), 0))) 5
        val () = Unit.checkExpectWith Int.toString "add to zero"
            (fn () => intOfNat(carryIntoNat(ZERO, 1))) 1
        val () = Unit.checkExpectWith Int.toString "add to non-zero"
            (fn () => intOfNat(carryIntoNat(natOfInt(129), 1))) 130

(* fun addWithCarry : nat * nat * int -> nat *)
fun addWithCarry (n1, ZERO, c) = carryIntoNat (n1, c)
  | addWithCarry (ZERO, n2, c) = carryIntoNat (n2, c)
  | addWithCarry (TIMES10PLUS(m1, d1), TIMES10PLUS(m2, d2), c) = 
        let val d = (d1 + d2 + c) mod 10 
            val c' = (d1 + d2 + c) div 10
        in times10plus(addWithCarry (m1, m2, c'), d)
        end
        
        val () = Unit.checkExpectWith Int.toString "first zero"
            (fn () => intOfNat(addWithCarry(ZERO, natOfInt(5), 1))) 6
        val () = Unit.checkExpectWith Int.toString "second zero"
            (fn () => intOfNat(addWithCarry(natOfInt(5), ZERO, 1))) 6
        val () = Unit.checkExpectWith Int.toString "neither zero"
            (fn () => intOfNat(addWithCarry(natOfInt(5), natOfInt(3), 1))) 9

(* fun addNats : nat * nat -> nat *)
fun addNats (n1, n2) = addWithCarry (n1, n2, 0)

exception Negative

(* fun borrowFromNat : nat * int -> nat *)
fun borrowFromNat (n, 0) = n
  | borrowFromNat (ZERO, c) = raise Negative
  | borrowFromNat (TIMES10PLUS(m, 0), c) = times10plus(borrowFromNat(m,1), 10-c)
  | borrowFromNat (TIMES10PLUS(m, d), c) = times10plus(m, (d - c))

        val () = Unit.checkExnWith Int.toString "negative"
            (fn () => (intOfNat(borrowFromNat(ZERO, 1))))
        val () = Unit.checkExpectWith Int.toString "borrow zero"
            (fn () => (intOfNat(borrowFromNat(natOfInt(1), 0)))) 1
        val () = Unit.checkExpectWith Int.toString "borrow carry"
            (fn () => (intOfNat(borrowFromNat(natOfInt(100), 1)))) 99
        val () = Unit.checkExpectWith Int.toString "borrow no carry"
            (fn () => (intOfNat(borrowFromNat(natOfInt(12), 1)))) 11

(* fun subWithBorrow : nat * nat * int -> nat *)
fun subWithBorrow (n1, ZERO, b) = borrowFromNat (n1, b)
  | subWithBorrow (ZERO, n2, b) = raise Negative
  | subWithBorrow (TIMES10PLUS(m1, d1), TIMES10PLUS(m2, d2), b) =
   let val d  = (d1 - d2 - b) mod 10
       val b' = if d1 - d2 - b < 0 then 1 else 0
   in  times10plus (subWithBorrow (m1, m2, b'), d)
   end

        val () = Unit.checkExnWith Int.toString "negative"
            (fn () => (intOfNat(subWithBorrow(ZERO, ZERO, 1))))
        val () = Unit.checkExpectWith Int.toString "second zero"
            (fn () => (intOfNat(subWithBorrow(natOfInt(1), ZERO, 1)))) 0
        val () = Unit.checkExpectWith Int.toString "neither zero"
            (fn () => (intOfNat(subWithBorrow(natOfInt(5), natOfInt(2), 1)))) 2

(* fun subNats : nat * nat -> nat *)
fun subNats (n1, n2) = subWithBorrow (n1, n2, 0)

        val () = Unit.checkExnSatisfiesWith natString "1 - 5"
            (fn () => subNats (natOfDigits [1], natOfDigits [5]))
            ("Negative", fn Negative => true | _ => false)

fun opsAgree name intop natop n1 n2 =
  Unit.checkExpectWith Int.toString name
  (fn () => intOfNat (natop (natOfInt n1, natOfInt n2)))
  (intop (n1, n2))

val () = opsAgree "123 + 2018" (op +)  addNats 123 2018
val () = opsAgree "2018 - 123" (op -)  subNats 2018 123
val () = opsAgree "100 - 1   " (op -)  subNats 100 1

(***** Problem J *****)
(*
 * an flist of 'a consists of a 3 tuple of an inverted prefix list, a finger
 * element, and a suffix list
 *)
type 'a flist = 'a list * 'a * 'a list

(* fun singletonOf : 'a -> 'a flist *)
fun singletonOf (x) = (nil, x, nil)

(* fun atFinger : 'a flist -> 'a *)
fun atFinger ((l, f, r)) = f

        val () = Unit.checkExpectWith Int.toString "singleton"
            (fn () => atFinger(singletonOf(1))) 1

(* fun fingerLeft  : 'a flist -> 'a flist *)
fun fingerLeft ((x::xs), f, r) = (xs, x, f::r)
  | fingerLeft (nil, f, r) = raise Subscript

        val () = Unit.checkExnWith Int.toString "subscript"
            (fn () => atFinger(fingerLeft(singletonOf(1))))
        val () = Unit.checkExpectWith Int.toString "left"
            (fn () => atFinger(fingerLeft([1], 2, [3]))) 1

(* fun fingerRight : 'a flist -> 'a flist *)
fun fingerRight (l, f, (x::xs)) = (f::l, x, xs)
  | fingerRight (l, f, nil) = raise Subscript

        val () = Unit.checkExnWith Int.toString "subscript"
            (fn () => atFinger(fingerRight(singletonOf(1))))
        val () = Unit.checkExpectWith Int.toString "right"
            (fn () => atFinger(fingerRight([1], 2, [3]))) 3

(* fun deleteLeft  : 'a flist -> 'a flist *)
fun deleteLeft ((x::xs), f, r) = (xs, f, r)
  | deleteLeft (nil, f, r) = raise Subscript

        val () = Unit.checkExnWith Int.toString "subscript"
            (fn () => atFinger(deleteLeft(singletonOf(1))))
        val () = Unit.checkExnWith Int.toString "left"
            (fn () => atFinger(fingerLeft(deleteLeft([1], 2, [3]))))

(* fun deleteRight : 'a flist -> 'a flist *)
fun deleteRight (l, f, (x::xs)) = (l, f, xs)
  | deleteRight (l, f, nil) = raise Subscript

        val () = Unit.checkExnWith Int.toString "subscript"
            (fn () => atFinger(deleteRight(singletonOf(1))))
        val () = Unit.checkExnWith Int.toString "right"
            (fn () => atFinger(fingerRight(deleteRight([1], 2, [3]))))

(* fun insertLeft  : 'a * 'a flist -> 'a flist *)
fun insertLeft (x, (l, f, r)) = (x::l, f, r)
        
        val () = Unit.checkExpectWith Int.toString "left"
            (fn () => atFinger(fingerLeft(insertLeft(2, ([1], 3, [4]))))) 2

(* fun insertRight : 'a * 'a flist -> 'a flist *)
fun insertRight (x, (l, f, r)) = (l, f, x::r)

        val () = Unit.checkExpectWith Int.toString "right"
            (fn () => atFinger(fingerRight(insertRight(3, ([1], 2, [4]))))) 3

(* fun ffoldl : ('a * 'b -> 'b) -> 'b -> 'a flist -> 'b *)
fun ffoldl f c (l, fg, r) = foldl f (foldr f c l) r
        
        val () = Unit.checkExpectWith Int.toString "left"
            (fn () => ffoldl (op +) 0 ([1, 2, 3], 4, [5, 6, 7])) 24

(* fun ffoldr : ('a * 'b -> 'b) -> 'b -> 'a flist -> 'b *)
fun ffoldr f c (l, fg, r) = foldl f (foldr f c r) l

        val () = Unit.checkExpectWith Int.toString "right"
            (fn () => ffoldr (op +) 0 ([1, 2, 3], 4, [5, 6, 7])) 24

val () = Unit.reportWhenFailures ()
