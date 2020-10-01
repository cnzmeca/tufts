val constraints =
    [CONAPP (TYCON "list", [TYVAR "a"]) ~ TYVAR "a"
    ,TYVAR "a" ~ TYVAR "b" /\ TYVAR "b" ~ TYVAR "c" /\ TYVAR "a" ~ TYVAR "c"
    ,CONAPP (TYCON "list", [TYCON "int"]) ~ CONAPP (TYCON "list", [TYCON "sym"])
    ]
