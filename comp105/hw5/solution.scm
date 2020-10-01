;;;;;;;;;;;;;;;;;;;;;;;; COMP 105 CONTINUATIONS ASSIGNMENT ;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise L

;; (list-of? A? v) returns true if every element in a list or value v satisfies
;; predicate A?

;; laws:
;; (list-of? A? '()) == #t
;; (list-of? A? (cons x xs)) == (and (A? x) (list-of? A? xs))
;; (list-of? A? y) == (A? y)
(define list-of? (A? v)
    (if (null? v)
        #t
        (if (pair? v)
            (and (A? (car v)) (list-of? A? (cdr v)))
            (A? v))))

        (check-assert (list-of? symbol? '()))
        (check-assert (list-of? symbol? 'a))
        (check-assert (list-of? symbol? '(a b c)))
        (check-assert (not (list-of? symbol? '(a b c 1))))
        (check-assert (list-of? number? '(1 2 3)))
        (check-assert (not (list-of? number? '(1 2 3 a))))
        (check-assert (list-of? boolean? '(#t #t #t)))
        (check-assert (not (list-of? boolean? '(#f #f #f 1))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise F

(record not [arg])
(record or  [args])
(record and [args])

;; (formula? v) returns true if value v is a formula

;; laws:
;; (formula? (make-not f)) == (formula? f)
;; (formula? (make-and fs) == (foldl (lambda (x y) (and (formula? x) y)) #t fs)
;; (formula? (make-or fs)) == (foldl (lambda (x y) (and (formula? x) y)) #t fs)
;; (formula? v) == #t if v is a symbol
;; (formula? v) == #f if v does not have any of the above forms
(define formula? (v)
    (if (not? v)
        (formula? (not-arg v))
        (if (and? v)
            (foldl (lambda (x y) (and (formula? x) y)) #t (and-args v))
            (if (or? v)
                (foldl (lambda (x y) (and (formula? x) y)) #t (or-args v))
                (if (symbol? v)
                    #t
                    #f)))))

(val not-test (make-not 'a))
(val or-test (make-or (list2 not-test not-test)))
(val and-test (make-and (list2 or-test or-test)))

        (check-assert (not (formula? '())))
        (check-assert (formula? 'a))
        (check-assert (not (formula? 1)))
        (check-assert (formula? not-test))
        (check-assert (formula? or-test))
        (check-assert (formula? and-test))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise E

;; (eval-formula f env) returns true if the formula f is satisfied by env

;; laws:
;; (eval-formula (make-not f) env) == (not (eval-formula) (not-arg f) env)
;; (eval-formula (make-and fs) env) == (foldl (lambda (x y) 
;;                                      (and (eval-formula x env) y)) #t fs)
;; (eval-formula (make-or fs) env) == (foldl (lambda (x y) 
;;                                      (or (eval-formula x env) y)) #f fs)
;; (eval-formula f env) == (find f env) if f is a symbol
(define eval-formula (f env)
    (if (not? f)
        (not (eval-formula (not-arg f) env))
        (if (and? f) 
            (foldl (lambda (x y) (and (eval-formula x env) y)) #t (and-args f))
            (if (or? f)
                (foldl (lambda (x y) (or (eval-formula x env) y)) #f
                                                                    (or-args f))
                (find f env)))))

(val envt '((a #t)))
(val envf '((a #f)))

        (check-assert (eval-formula 'a envt))
        (check-assert (not (eval-formula 'a envf)))
        (check-assert (eval-formula not-test envf))
        (check-assert (not (eval-formula not-test envt)))
        (check-assert (eval-formula and-test envf))
        (check-assert (not (eval-formula and-test envt)))
        (check-assert (eval-formula or-test envf))
        (check-assert (not (eval-formula or-test envt)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise S

;; (find-formula-true-asst x f s) returns a map from variables to booleans
;; that causes x to be evaluate to true, with failure and success continuations
;; f and s
(define find-formula-true-asst (x f s)
    (letrec
        ;;(find-formula-asst x b c f s) == (find-formula-symbol x b c f s)
        ;;(find-formula-asst (make-not x) b c f s) ==
        ;;                              (find-formula-asst x (not b) c f s)
        ;;(find-formula-asst (make-or xs) #t c f s) ==
        ;;                              (find-any-asst xs #t c f s)
        ;;(find-formula-asst (make-or xs) #f c f s) == 
        ;;                              (find-all-asst xs #f c f s)
        ;;(find-formula-asst (make-and xs) #t c f s) == 
        ;;                              (find-all-asst xs #t c f s)
        ;;(find-formula-asst (make-and xs) #f c f s) == 
        ;;                              (find-any-asst xs #f c f s)
        [(find-formula-asst
            (lambda (x b c f s)
                (if (not? x)
                    (find-formula-asst (not-arg x) (not b) c f s)
                    (if (or? x)
                        (if b
                            (find-any-asst (or-args x) #t c f s)
                            (find-all-asst (or-args x) #f c f s))
                        (if (and? x)
                            (if b
                                (find-all-asst (and-args x) #t c f s)
                                (find-any-asst (and-args x) #f c f s))
                            (find-formula-symbol x b c f s))))))
        ;;(find-all-asst '() b c f s) == (s c f)
        ;;(find-all-asst (cons x xs) b c f s) == (find-formula-asst x b c f ns) 
         (find-all-asst
            (lambda (xs b c f s) 
                (if (null? xs)
                    (s c f)
                    (find-formula-asst (car xs) b c f
                        (lambda (c r) (find-all-asst (cdr xs) b c r s))))))
        ;;(find-any-asst '() b c f s) == (f)
        ;;(find-any-asst (cons x xs) b c f s) == (find-formula-asst x b c nf s)
         (find-any-asst
            (lambda (xs b c f s) 
                (if (null? xs)
                    (f)
                    (find-formula-asst (car xs) b c  
                        (lambda () (find-any-asst (cdr xs) b c f s)) s))))
        ;;(find-formula-symbol x b c f s) == (f) if x is (not b) in c
        ;;(find-formula-symbol x b c f s) == (s c f) if x is b in c
        ;;(find-formula-symbol x b c f s) == (s (bind x b c) f) if x is not in c
         (find-formula-symbol
            (lambda (x b c f s) 
                (let [(y (find x c))]
                    (if (null? y)
                        (s (bind x b c) f)
                        (if (equal? y b)
                            (s c f)
                            (f))))))]
        (find-formula-asst x #t '() f s)))

        (use solver-interface-tests.scm)
