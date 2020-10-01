;;;;;;;;;;;;;;;;;;; COMP 105 SCHEME ASSIGNMENT ;;;;;;;;;;;;;;;




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise 30

;; a. vector-length implements the euclidean distance equation between a point
;; (x y) and the origin
;; b. since vanilla let applies all bindings at once, the meaning of the
;; functions + and * can be swapped to complete the distance equation without
;; interfering with each other




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise 2


;; (count x xs) returns the number of times atom x appears as a top level
;; element in list xs. 

;; laws:
;;   (count x '()) == 0
;;   (count x (cons x xs)) == (+ 1 (count x xs))
;;   (count x (cons y xs)) == (count x xs)

(define count (x xs)
    (if (null? xs)
        0
        (if (= x (car xs))
            (+ 1 (count x (cdr xs)))
            (count x (cdr xs)))))

        (check-expect (count 'a '()) 0)
        (check-expect (count 'a '(1 b a (c a))) 1)
        (check-expect (count 'a '(a b 1 (c a))) 1)



;; (countall x xs) returns the number of times atom x appears anywhere in
;; the list xs, not only at the top level. 

;; laws:
;;   (countall x '()) == 0
;;   (countall x (cons ys xs)) == (+ (countall x ys) (countall x xs))
;;   (countall x (cons x xs)) == (+ 1 (countall x xs))
;;   (countall x (cons y xs)) == (countall x xs)

(define countall (x xs)
    (if (null? xs)
        0
        (if (pair? (car xs))
            (+ (countall x (car xs)) (countall x (cdr xs)))
            (if (= x (car xs))
                (+ 1 (countall x (cdr xs)))
                (countall x (cdr xs))))))

        (check-expect (countall 'a '()) 0)
        (check-expect (countall 'a '(1 b a)) 1)
        (check-expect (countall 'a '(a b 1)) 1)
        (check-expect (countall 'a '(1 b a (c a))) 2)


;; (contig-sublist? xs ys) returns true if list xs is a contiguous sublist of
;; list ys

;; laws:
;;   (contig-sublist? '() ys) == #t
;;   (contig-sublist? xs '()) == #f
;;   (contig-sublist? (cons x xs) (cons x ys)) == (contig-sublist? xs ys)
;;   (contig-sublist? (cons x xs) (cons y ys)) == 
;;                              (contig-sublist? (cons y (cons x xs)) ys)

(define contig-sublist? (xs ys)
    (if (null? xs)
        #t
        (if (null? ys)
            #f
            (if (= (car xs) (car ys))
                (contig-sublist? (cdr xs) (cdr ys))
                (contig-sublist? (cons (car ys) xs) (cdr ys))))))
                
        (check-assert (contig-sublist? '() '()))
        (check-assert (not (contig-sublist? '(a) '())))
        (check-assert (contig-sublist? '(a b) '(a b c d)))
        (check-assert (not (contig-sublist? '(b d) '(a b c d))))

;; (sublist? xs ys) returns true if list xs is a sublist of list ys

;; laws:
;;   (sublist? '() ys) == #t
;;   (sublist? xs '()) == #f
;;   (sublist? (cons x xs) (cons x ys)) == (sublist? xs ys)
;;   (sublist? (cons x xs) (cons y ys)) == (sublist? (cons x xs) ys)

(define sublist? (xs ys)
    (if (null? xs)
        #t
        (if (null? ys)
            #f
            (if (= (car xs) (car ys))
                (sublist? (cdr xs) (cdr ys))
                (sublist? xs (cdr ys))))))

        (check-assert (sublist? '() '()))
        (check-assert (not (sublist? '(a) '())))
        (check-assert (sublist? '(a d) '(a b c d)))
        (check-assert (not (sublist? '(b e) '(a b c d))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise 10


;; (takewhile p? xs) returns the longest prefix list of xs such that each
;; element satisfies p?

;; laws:
;;   (takewhile p? '()) == '()
;;   (takewhile p? (cons x xs)) == (cons x (takewhile p? xs)) for (p? x) == #t
;;   (takewhile p? (cons x xs)) == '() for (p? x) == #f

(define takewhile (p? xs)
    (if (null? xs)
        '()
        (if (p? (car xs))
            (cons (car xs) (takewhile p? (cdr xs)))
            '())))

        (check-expect(takewhile symbol? '()) '())
        (check-expect(takewhile symbol? '(a b c 7 8 10 12)) '(a b c))
        (check-expect(takewhile symbol? '(1)) '())

;; (dropwhile p? xs) returns a suffix list of xs that is missing the longest
;; possible prefix list such that each element missing satisfies p?

;; laws:
;;   (dropwhile p? '()) == '()
;;   (dropwhile p? (cons x xs)) == (dropwhile p? xs)
;;   (dropwhile p? (cons x xs)) == xs for (p? x) == #f

(define dropwhile (p? xs)
    (if (null? xs)
        '()
        (if (p? (car xs))
            (dropwhile p? (cdr xs))
            xs)))

        (check-expect(dropwhile symbol? '()) '())
        (check-expect(dropwhile symbol? '(a b c 7 8 10 12)) '(7 8 10 12))
        (check-expect(dropwhile symbol? '(1)) '(1))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise B


;; (take n xs) returns a list of at most length natural number  n that is a
;; prefix list of xs

;; laws:
;;   (take 0 xs) == '()
;;   (take n '()) == '()
;;   (take n cons(x xs)) == (cons (x (take ((- n 1) xs))))

(define take (n xs)
    (if (= n 0)
        '()
        (if (null? xs)
            '()
            (cons (car xs) (take (- n 1) (cdr xs))))))
        
        (check-expect (take 0 '(a b c)) '())
        (check-expect (take 2 '()) '())
        (check-expect (take 2 '(a b c)) '(a b))



;; (drop n xs) returns a suffix list of xs that is missing at most the first
;; natural number n elements

;; laws:
;;   (drop 0 xs) == xs
;;   (drop n '()) == '()
;;   (drop n cons(x xs)) == (drop (- n 1) xs)

(define drop (n xs)
    (if (= 0 n)
        xs
        (if (null? xs)
            '()
            (drop (- n 1) (cdr xs)))))

        (check-expect (drop 0 '(a b c)) '(a b c))
        (check-expect (drop 2 '()) '())
        (check-expect (drop 2 '(a b c)) '(c))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise C


;; (zip xs ys) returns an association list given a pair of lists

;; laws:
;;   (zip '() '()) == '()
;;   (zip (cons x xs) (cons y ys)) == (cons (list2 x y) (zip xs ys))

(define zip (xs ys)
    (if (null? xs)
        '()
        (cons (list2 (car xs) (car ys)) (zip (cdr xs) (cdr ys)))))

        (check-expect (zip '() '()) '())
        (check-expect (zip '(1 2 3) '(a b c)) '((1 a) (2 b) (3 c)))

;; (first-elements ps) returns a list that has the first elements of the
;; sublists of association list ps.

;; laws:
;;   (first-elements '()) == '()
;;   (first-elements (cons z zs)) == (cons (car z) (first-elements zs))

(define first-elements (ps)
     (if (null? ps)
        '()
        (cons (caar ps) (first-elements (cdr ps)))))

        (check-expect (first-elements '()) '())
        (check-expect (first-elements '((1 a) (2 b) (3 c))) '(1 2 3))

;; (second-elements ps) returns a list that has the second elements of the
;; sublists of association list ps.

;; laws:
;;   (second-elements '()) == '()
;;   (second-elements (cons z zs)) == (cons (cadr z) (second-elements zs))

(define second-elements (ps)
     (if (null? ps)
        '()
        (cons (cadar ps) (second-elements (cdr ps)))))

        (check-expect (second-elements '()) '())
        (check-expect (second-elements '((1 a) (2 b) (3 c))) '(a b c))

;; (unzip ps) returns a pair of lists given an association list

(define unzip (ps)
    (list2 (first-elements ps) (second-elements ps)))

        (check-expect (unzip '()) '(() ()))
        (check-expect (unzip '((1 a) (2 b) (3 c))) '((1 2 3) (a b c)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise N

;;1.            
;;   LIST1(A) = LIST(A) where A = a
;;
;;2.            a = A as = '()
;;   LIST1(A) = ___________________
;;              (cons a as) ∈ LIST1(A)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise D

;; (arg-max f xs) returns the input value from a list xs that maximizes the
;; output of a function f

;; laws:
;;   (arg-max f x) == x
;;   (arg-max f (cons x xs)) == x if x > (arg-max f xs)
;;   (arg-max f (cons x xs)) == (arg-max f xs) if x <= (arg-max f xs)

(define arg-max (f xs)
    (if (null? (cdr xs))
        (car xs)
        (if (> (f (car xs)) (f (arg-max f (cdr xs))))
            (car xs)
            (arg-max f (cdr xs)))))

(define square (x) (* x x))
        (check-expect (arg-max square '(1)) 1)
        (check-expect (arg-max square '(1 2 3 4 5)) 5)
        (check-expect (arg-max square '(2 1 3 4 5)) 5)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise E


;; (rightmost-point ps) returns the x coordinate of the rightmost point in
;; list of point records ps 

(define rightmost-point (ps)
    (max* (car (unzip ps))))

        (check-expect (rightmost-point '((1 2) (3 4) (5 6))) 5)



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise F


;; (remove-one-copy sx sxs) removes a copy of an S-expression sx from a list
;; of S-expressions sxs. CRE when sx is not in sxs

;; laws:
;;   (remove-one-copy sx '()) == CRE
;;   (remove-one-copy sx (cons sx sxs) == sxs
;;   (remove-one-copy sx (cons sy sxs) == (cons sy (remove-one-copy sxs))

(define remove-one-copy (sx sxs)
    (if (null? sxs)
        (error removed-an-absent-item)
        (if (equal? sx (car sxs))
            (cdr sxs)
            (cons (car sxs) (remove-one-copy sx (cdr sxs))))))
    
        (check-error (remove-one-copy 'a '()))
        (check-expect (remove-one-copy 'a '(a b c a)) '(b c a))
        (check-expect (remove-one-copy 'a '(b a c a)) '(b c a))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise G

;; (remove-element x ys) removes an element x from list ys

;; laws:
;;   (remove-element x '()) == '()
;;   (remove-element x (cons x xs) == xs
;;   (remove-element x (cons y xs) == (cons y (remove-element xs))

(define remove-element (x ys)
    (if (null? ys)
        '()
        (if (equal? x (car ys))
            (cdr ys)
            (cons (car ys) (remove-element x (cdr ys))))))

        (check-expect (remove-element 'a '(a b c)) '(b c))

;; (permutation? xs ys) returns true if lists xs and ys are permutations of
;; each other

;; laws:
;;   (permutation? '() '()) == #t
;;   (permutation? '() ys  == #f
;;   (permutation? (cons x xs) (cons x ys)) == (permutation? xs ys))
;;   (permutation? (cons x xs) (cons y ys)) == (permutation? xs (cons y ys))

(define permutation? (xs ys)
    (if (and (null? xs) (null? ys))
        #t
        (if (equal? ys (remove-element (car xs) ys))
            #f
            (permutation? (cdr xs) (remove-element (car xs) ys)))))
        
        (check-assert (permutation? '() '()))
        (check-assert (permutation? '(a b c) '(c b a)))
        (check-assert (not (permutation? '(a b b) '(c b a))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise H

;; (alternating-elements xs) returns a list of alternating elements of list xs

;; laws:
;;   (alternating-elements '()) == '()
;;   (alternating-elements x) == x
;;   (alternating-elements (cons x xs)) ==
;;                                      (cons x (alternating-elements (cdr xs)
(define alternating-elements (xs)
    (if (null? xs)
        '()
        (if (null? (cdr xs))
            (list1 (car xs))
            (cons (car xs) (alternating-elements (cddr xs))))))
        

        (check-expect (alternating-elements '()) '())
        (check-expect (alternating-elements '(a)) '(a))
        (check-expect (alternating-elements '(a b c)) '(a c))

;; (split-list xs) returns a list that contains two sublists that are
;; a nearly equal split of the elements in xs

;; laws:
;;   (split-list xs) ==
;;             (list2 (alternating-elements xs) (alternating-elements (cdr xs)))

(define split-list (xs)
        (list2 (alternating-elements xs) (alternating-elements (cdr xs))))
        
        (check-expect (split-list '(a b c d e)) '((a c e) (b d)))
