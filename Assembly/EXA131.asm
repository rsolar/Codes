;FILENAME:  EXA131.ASM
;两位数加法(程序改错)
.486
DATA        SEGMENT     USE16                      ;DATA    SEGME  NT   USE16
SUM         DB    ?,?                              ;SUM     DB    ?,?,
MESG        DB    '25+9='
            DB    0,0,'$'                          ;        DB    0,0
N1          DB    9,0F0H                           ;N1      DB    9,F0H
N2          DB    25                               ;N2      DW    25
DATA        ENDS
CODE        SEGMENT     USE16
            ASSUME      CS:CODE,    DS:DATA
BEG:        MOV         AX,         DATA
            MOV         DS,         AX
            MOV         BX,         OFFSET SUM
            MOV         AH,         N1
            MOV         AL,         N2
            ADD         AH,         AL
            MOV         [BX],       AH
            CALL        CHANG
            MOV         AH,         9
            MOV         DX,         OFFSET MESG    ;        MOV         DX,         OFFSET MEST
            INT         21H
            MOV         AH,         4CH
            INT         21H
CHANG       PROC                                   ;CHANG:  PROC
LAST:       CMP         BYTE PTR [BX],    10       ;LAST:   CMP         [BX],       10
            JC          NEXT
            SUB         BYTE PTR [BX],    10       ;        SUB         [BX],       10
            INC         BYTE PTR [BX+7]            ;        INC         [BX+7]
            JMP         LAST
NEXT:       MOV         DL,         SUM            ;NEXT:
            ADD         BYTE PTR [BX+8],  DL       ;        ADD         [BX+8],     SUM
            ADD         BYTE PTR [BX+7],  30H      ;        ADD         [BX+7],     30H
            ADD         BYTE PTR [BX+8],  30H      ;        ADD         [BX+8],     30H
            RET
CHANG       ENDP                                   ;CHANG:  ENDP
CODE        ENDS
            END         BEG
