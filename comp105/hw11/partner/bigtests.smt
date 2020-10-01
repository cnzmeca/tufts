; Summary: Natural addition
(check-print (+ (new: Natural 100) (new: Natural 100)) 200)
; Summary: Natural subtraction
(check-print (- (new: Natural 100) (new: Natural 100)) 0)
; Summary: Natural multiplication
(check-print (* (new: Natural 100) (new: Natural 100)) 100000)

; Summary: Positive multiplication
(check-print (* (new: LargePositiveInteger 100000)
     (new: LargePositiveInteger 100000)) 10000000000)

; Summary: Negative multiplication
(check-print (* (new: LargePositiveInteger 100000)
     (new: LargeNegativeInteger 100000)) -10000000000)

; Summary: Mixed multiplication
(check-print (* (new: LargeNegativeInteger 100000)
     (new: LargeNegativeInteger 100000)) 10000000000)

; Summary: Mixed addition
(check-print (+ (new: LargePositiveInteger 100000) 1) 100001)
; Summary: Mixed subtraction
(check-print (- (new: LargePositiveInteger 100000) 1) 99999)
; Summary: Mixed multiplication
(check-print (* (new: LargePositiveInteger 100000) 2) 200000)
