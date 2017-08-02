;FILENAME:  EXA317.ASM
;字符串比对及彩色文本显示
            .486
DATA        SEGMENT     USE16
            MESG        DB          'Please input password:'
            MESGLEN     EQU         $-MESG
            RIGHT       DB          'RIGHT! Press any key to exit.'
            RIGHTLEN    EQU         $-RIGHT
            WRONG       DB          'WRONG! Please retry.'
            WRONGLEN    EQU         $-WRONG
            PWD         DB          'hello'
            PWDLEN      EQU         $-PWD
            INPUT       DB          64 DUP(?)
            INPUTLEN    DB          0
DATA        ENDS

CODE        SEGMENT     USE16
            ASSUME      CS:CODE,    DS:DATA,      ES:DATA
BEG:        MOV         AX,         DATA
            MOV         DS,         AX
            MOV         ES,         AX
            ;设置屏幕显示方式为“80x25 彩色文本方式”
            MOV         AX,         0003H
            INT         10H         
AGAIN:      ;清屏
            MOV         AX,         0700H
            MOV         BH,         0FH
            MOV         CX,         0
            MOV         DH,         24
            MOV         DL,         79
            INT         10H
            ;黑白方式显示
            ;MOV         AH,         09H
            ;MOV         DX,         OFFSET MESG
            ;INT         21H
            ;彩色方式显示
            MOV         AX,         1301H
            MOV         BH,         0
            MOV         BL,         00001100B
            MOV         CX,         MESGLEN
            MOV         DH,         0
            MOV         DL,         0
            MOV         BP,         OFFSET MESG
            INT         10H
            ;已输入长度置0
            MOV         INPUTLEN,   0
GETC:       ;无回显方式读入一个字符，不响应Ctrl_C
            MOV         AH,         07H
            INT         21H
            ;读到回车则结束输入
            CMP         AL,         0DH         
            JE          CHECK
            ;将读到的字符存入INPUT，并将已输入长度加一
            MOV         BX,         OFFSET INPUT
            ADD         BX,         WORD PTR INPUTLEN
            MOV         [BX],       AL
            INC         INPUTLEN
            ;显示一个星号
            MOV         AH,         02H
            MOV         DL,         '*'
            INT         21H         
            ;继续读入下一字符
            JMP         GETC
CHECK:      ;比较输入长度和通信字长度
            MOV         DL,         PWDLEN
            CMP         DL,         INPUTLEN
            JNE         NO
            ;比较输入字符串和通信字字符串
            MOV         SI,         OFFSET INPUT
            MOV         DI,         OFFSET PWD
            MOV         CX,         PWDLEN
            CLD
            REPE        CMPSB
            ;输入和通信字完全相同
            JE          YES         
NO:         ;黑白方式显示
            ;MOV         AH,         09H
            ;MOV         DX,         OFFSET WRONG
            ;INT         21H
            ;彩色方式显示
            MOV         AX,         1301H
            MOV         BH,         0
            MOV         BL,         00001100B
            MOV         CX,         WRONGLEN          
            MOV         DH,         1
            MOV         DL,         0
            MOV         BP,         OFFSET WRONG
            INT         10H
            ;等待用户按任意键
            MOV         AH,         00H
            INT         16H
            ;重新开始输入
            JMP         AGAIN
YES:        ;黑白方式显示
            ;MOV         AH,         09H
            ;MOV         DX,         OFFSET RIGHT
            ;INT         21H
            ;彩色方式显示
            MOV         AX,         1301H
            MOV         BH,         0
            MOV         BL,         00001010B
            MOV         CX,         RIGHTLEN          
            MOV         DH,         1
            MOV         DL,         0
            MOV         BP,         OFFSET RIGHT
            INT         10H
            ;等待用户按任意键
            MOV         AH,         00H
            INT         16H
            ;退出程序，返回DOS
            MOV         AH,         4CH
            INT         21H
CODE        ENDS
            END         BEG
