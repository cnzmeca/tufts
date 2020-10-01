;; step 5

(check-type 3 int)
(check-type #t bool)
(check-type 'hello sym)

;; step 6
(check-type (if #t 1 2) int)
(check-type (if #f 'a 'b) sym)
(check-type-error (if 1 2 3))

;; step 7
(check-type + (int int -> int))

;; step 9
(val x 1)
(check-type x int)

(val y #f)
(check-type y bool)

;; step 10
(check-type (+ 3 3) int)
(check-type (< 3 3) bool)

;; step 12
(check-type (lambda ([x : int]) x) (int -> int))

;; step 13
(check-type (while #f 1) unit)
(check-type (set x 1) int)
(check-type (begin 1 2 3 4) int)

;; step 14
(check-type (let* ((x 1)) x) int)
