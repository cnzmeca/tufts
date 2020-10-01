;;SAT Solver Test Cases 

(record not [arg])   ;; OK if these are duplicates
(record or  [args])
(record and [args])

;; Checks that contradiction doesn't short-circuit or
(val f1 (make-or (list2 (make-and (list2 'x (make-not 'x))) 'y)))
(val s1 '((y #t)))

;; Checks that tautology doesn't short-circuit and
(val f2 (make-and (list2 (make-or (list2 'x (make-not 'x))) 'y)))
(val s2 '((y #t)))

;; Checks that double negation cancels properly
(val f3 (make-not (make-not 'x)))
(val s3 '((x #t)))
