;FILENAME:  EXA210.ASM
;求数组最小值及负数个数
.486
DATA        SEGMENT     USE16
NUM         DB          1,-2,3,-4,5,-6,7,-8,9            ;九个有符号数
NUMCNT      EQU         $-NUM                            ;数字个数
MIN         DB          ?                                ;最小值
AB          DB          '0'                              ;负数个数
DATA        ENDS
CODE        SEGMENT     USE16
            ASSUME      CS:CODE,    DS:DATA
BEG:        MOV         AX,         DATA
            MOV         DS,         AX
            MOV         BX,         OFFSET NUM
            MOV         DL,         NUM                  ;初始化最小值
            MOV         CX,         NUMCNT               ;设置循环次数
AGAIN:      CMP         BYTE PTR [BX],    0
            JGE         COMP
            INC         AB                               ;负数个数加一
COMP:       CMP         [BX],       DL
            JGE         NEXT
            MOV         DL,         [BX]                 ;更新最小值
NEXT:       INC         BX                               ;偏移地址加一
            LOOP        AGAIN
            MOV         MIN,        DL                   ;将最小值存放到MIN单元
            MOV         AH,         2                    ;显示负数个数
            MOV         DL,         AB
            INT         21H
            MOV         AH,         4CH
            INT         21H
CODE        ENDS
            END         BEG
