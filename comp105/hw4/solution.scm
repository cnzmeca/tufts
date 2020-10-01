;;;;;;;;;;;;;;;;;;;;;;;;;;;;; COMP 105 HOFS ASSIGNMENT ;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise 14

;; Part b
;; (max* xs) returns the maximum element in a list xs
(define max* (xs)
    (foldl max (car xs) (cdr xs)))

        (check-expect (max* '(1 5 2 4 3)) 5)

;; Part c
;; (gdc* xs) returns the greatest common divisor of a list xs
(define gcd* (xs)
    (foldl gcd (car xs) (cdr xs)))

        (check-expect (gcd* '(2 4 6 8 10)) 2)

;; Part d
;; (lcm* xs) returns the least common multiple of a list xs
(define lcm* (xs)
    (foldl lcm (car xs) (cdr xs)))

        (check-expect (lcm* '(1 2 3 4 5)) 60)

;; Part e
;; (sum xs) returns the sum of a list xs
(define sum (xs)
    (foldl + 0 xs))

        (check-expect (sum '(1 2 3 4 5)) 15)

;; Part f
;; (product xs) returns the product of a list xs
(define product (xs)
    (foldl * 1 xs))

        (check-expect (product '(1 2 3 4 5)) 120)

;; Part h
;; (append xs ys) returns a list the is ys appended to xs
(define append (xs ys)
    (foldr cons ys xs))

        (check-expect(append '(1 2 3) '(4 5 6)) '(1 2 3 4 5 6))

;; Part j
;; (reverse xs) returns a list that is the reverse of xs
(define reverse (xs)
    (foldl cons '() xs))

        (check-expect(reverse '(1 2 3 4 5 6)) '(6 5 4 3 2 1))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise 15

;; (length xs) returns the length of a list xs
(define length (xs)
    (foldl (lambda (x y) (+ y 1)) 0 xs))

        (check-expect (length '(1 2 3 4 5)) 5)

;; (map f xs) takes single parameter function f and a list xs and returns a list
;; that is the result of applying f to each element in xs
(define map (f xs)
    (foldr (lambda (x y) (cons (f x) y)) '() xs))

        (check-expect (map symbol? '(a 1 b 2 c 3)) '(#t #f #t #f #t #f))

;; (filter f? xs) takes a predicate f? and a list xs and returns a list that
;; contains all elements of xs for which f? is true
(define filter (f? xs)
    (foldr (lambda (x y) (if (f? x) (cons x y) y)) '() xs))

        (check-expect (filter symbol? '(a 1 b 2 c 3)) '(a b c))

;; (exists? f? xs) returns true if an element of list x satisfies predicate f?
(define exists? (f? xs)
    (foldr (lambda (x y) (or (f? x) y)) #f xs))

        (check-assert (exists? symbol? '(1 2 3 4 5 a)))
        (check-assert (not (exists? symbol? '(1 2 3 4 5 6))))

;; (all? f? xs) returns true if all elements of list x satisfy predicate f?
(define all? (f? xs)
    (foldr (lambda (x y) (and (f? x) y)) #t xs))

        (check-assert (all? symbol? '(a b c d e f)))
        (check-assert (not (all? symbol? '(a b c d e 1))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;  Exercise 19

;; Part a
;; (evens x) returns true if x is even

;; laws:
;; (evens 2n) == #t
;; (evens 2n + 1) == #f
(define evens (x)
    (= 0 (mod x 2)))

        (check-assert (evens 2))
        (check-assert (not (evens 3)))

;; Part b
;; (two-digits x) returns true if x is a two digit decimal number

;; laws:
;; (two-digits x) = #t if 10 <= x < 100
;; (two-digits x) = #f if 10 > x or x >= 100
(define two-digits (x)
    (and (>= x 10) (< x 100)))

        (check-assert (two-digits 10))
        (check-assert (not (two-digits 100)))

;; Part c
;; (add-element x s) returns a characteristic function of a set s with the
;; addition of an element x

;; laws:
;; (member? x (add-element x s)) == #t
;; (member? x (add-element y s)) == (s x), where (not (equal? y x))
(define add-element (x s)
    (lambda (y) (or (equal? x y) (s y))))

        (check-assert ((add-element 1 (lambda (y) #f)) 1))
        (check-assert (not ((add-element '2 (lambda (y) #f)) 1)))
        (check-assert ((add-element 2 (lambda (y) (= y 1))) 1))

;; (union s1 s2) returns a characteristic function of a set that is the
;; union of sets s1 and s2

;; laws:
;; (member? x (union s1 s2)) == (or (s1 x) (s2 x))
(define union (s1 s2)
    (lambda (y) (or (s1 y) (s2 y))))

        (check-assert ((union (lambda (y) (= y 2)) (lambda (y) (= y 1))) 1))
        (check-assert (not ((union (lambda (y) #f) (lambda (y) (= y 1))) 2)))

;; (inter s1 s2) returns a characteristic function of a set that is the
;; intersection of sets s1 and s2

;; laws:
;; (member? x (inter s1 s2)) == (and (s1 x) (s2 x))
(define inter (s1 s2)
    (lambda (y) (and (s1 y) (s2 y))))

        (check-assert ((inter (lambda (y) (= y 1)) (lambda (y) (= y 1))) 1))
        (check-assert (not ((inter (lambda (y) #f) (lambda (y) (= y 1))) 2)))

;; (diff s1 s2) returns a characteristic function of a set that is the
;; difference between s1 and s2

;; laws:
;; (member? x (diff s1 s2)) == (and (s1 x) (not (s2 x)))
(define diff (s1 s2)
    (lambda (y) (and (s1 y) (not (s2 y)))))

        (check-assert ((diff (lambda (y) (= y 1)) (lambda (y) #f)) 1))
        (check-assert (not ((diff (lambda (y) (= y 1)) 
                                (lambda (y) (= y 1))) 1)))

;; Part d
(record set-ops (empty member? add-element union inter diff))

;; (set-ops-from eq?) returns a set of operations defined using the equivalence
;; predicate eq?
(define set-ops-from (eq?)
  (let ([empty   (lambda (x) (eq? x '()))]
        [member? (lambda (x s) (s x))]
        [add     (lambda (x s) (lambda (y) (or (eq? x y) (s y))))])
    (make-set-ops empty member? add union inter diff)))

(val atom-set-ops (set-ops-from =))
(val atom-member?      (set-ops-member? atom-set-ops))
        
        (check-assert (atom-member? 1 (lambda (y) (= y 1))))
        (check-assert (procedure? set-ops-from))
        (check-assert (set-ops? (set-ops-from =)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise A


;; (f-functional) returns identical output as f-imperative, but in functional
;; programming style

(define f-functional (x y)
    (letrec [(x e)] 
        (if (p? x y)
            (f-functional (g x y) y)
            (h x y))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise F


;; (flip f) takes a function f that accepts two arguments and returns a function
;; that also accepts two arguments and evaluates to the same as f with the first
;; and second arguments swapped

;; laws:
;; ((flip f) x y) == (f y x)

(define flip (f)
    (lambda (x y) (f y x)))

        (check-assert ((flip <) 5 4))
        (check-assert (not ((flip <) 4 5)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise G1

(record edge [from to])

;; (add-edges  es) takes a node a successors pair ns and an edge list es
;; and prepends each edge from ns to es

;; laws:
;; (add-edges '() es) == es
;; (add-edges (cons n '()) es) == es
;; (add-edges (cons n ss) es) == 
;;      (add-edges (cons n (cdr ss)) (cons (make-edge (n (car ss)) es)))
(define add-edges (ns es)
    (if (null? ns)
        es
        (if (null? (cadr ns))
            es
            (add-edges (cons (car ns) (list1 (cdadr ns)))
                (cons (make-edge (car ns) (caadr ns)) es)))))

        (check-expect (add-edges '() '()) '())
        (check-expect (add-edges '(A ()) '()) '())
        (check-expect (add-edges '(A (B C)) '())
            (list2 (make-edge 'A 'C) (make-edge 'A 'B)))

;; (edge-list g) takes a successor map g and returns a list of edges that
;; describe the same graph as the successor map
(define edge-list (g)
        (foldr add-edges '() g))

        (check-expect (edge-list '([A (B C)] [B (C)] [C ()]))
            (list3 (make-edge 'A 'C) (make-edge 'A 'B) (make-edge 'B 'C)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise G2


;; (add-edge e g) takes an edge e and a graph g and adds e to g, returning the
;; new modified g
(define add-edge (e g)
    (let* [(n (edge-from e)) (new-s (edge-to e)) (ss (find n g))]
        (if (null? g)
            (list2 n (list1 new-s))
            (if (null? ss)
                (bind n (list1 new-s) g)
                (bind n (cons new-s ss) g)))))

(define remove-one-copy (x xs)
  (if (null? xs)
      (error 'removed-an-absent-item)
      (if (equal? x (car xs))
          (cdr xs)
          (cons (car xs) (remove-one-copy x (cdr xs))))))

(define permutation? (xs ys)
  (if (null? xs)
      (null? ys)
      (let ([z  (car xs)]
            [zs (cdr xs)]
            [member? (lambda (a as) (exists? ((curry equal?) a) as))])
        (if (member? z ys)
            (permutation? zs (remove-one-copy z ys))
            #f))))

        (check-expect(add-edge (make-edge 'A 'B) '()) '(A (B)))
        (check-expect(add-edge (make-edge 'A 'B) '([B (C)])) '([B (C)] [A (B)]))
        (check-expect(add-edge (make-edge 'A 'B) '([A (C)])) '([A (B C)]))
        
        (check-assert
            (permutation? 
                (cons (make-edge 'C 'D) (edge-list '([A (B C)] [B (C)]))) 
                (edge-list (add-edge (make-edge 'C 'D) '([A (B C)] [B (C)])))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise G3

;; (remove-to n l) remove a node n from a list l and returns the new l
(define remove-to (n l)
    (foldr 
        (lambda (x y)
            (if (equal? x n)
                y
                (cons x y))) '() l))

        (check-expect (remove-to '2 '()) '())
        (check-expect (remove-to '2 '(2)) '())
        (check-expect (remove-to '2 '(1 2 3 4 5)) '(1 3 4 5))

;; (remove-node n g) removes a node n from a graph g and returns the new g
(define remove-node (n g)
    (foldr 
        (lambda (x y)
            (if (equal? (car x) n)
                y
                (cons (cons (car x) (list1(remove-to n (cadr x)))) y))) '() g))
        
        (check-expect (remove-node 'A '()) '())
        (check-expect (remove-node 'A '([A (B C)] [B (C)] [C ()]))
            '([B (C)] [C ()]))
        (check-expect (remove-node 'A '([A (B C)] [B (C)] [C (A)]))
            '([B (C)] [C ()]))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise O


;; (ordered-by? f) takes a comparison function f and returns a predicate that
;; determines if a list is ordered according to that comparison

;; laws:
;; ((ordered-by? f) '()) == #t
;; ((ordered-by? f) (cons x '())) == #t
;; ((ordered-by? f) (cons x (cons y zs))) == #f when (f x y) is false 
;; ((ordered-by? f) (cons x (cons y zs))) == ((ordered-by? f) (cons y zs) 
(define ordered-by? (f)
    (lambda (xs) 
        (if (null? xs)
            #t
            (if (null? (cdr xs))
                #t
                (if (f (car xs) (cadr xs))
                    ((ordered-by? f) (cdr xs))
                    #f)))))

        (check-assert (procedure? ordered-by?))
        (check-assert (procedure? (ordered-by? <)))
        (check-error (ordered-by? < '(1 2 3)))
        (check-assert ((ordered-by? <) '()))
        (check-assert ((ordered-by? <) '(1)))
        (check-assert ((ordered-by? <) '(1 2 3)))
        (check-assert (not ((ordered-by? <) '(3 2 1))))



