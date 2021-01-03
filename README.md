# EEB512T4
Computer programming
* SUMA

* 進度資料請至suma/suma/TeamWork.md查看


## Git Bash 內的 Vi 亂碼解決
* [解決方案參考](https://www.itread01.com/p/879487.html)
* cd到 /etc 編輯vimrc 在set ai 前加上下方程式碼

```
set nu
set ff=unix "fileformat
set ffs=unix,dos,mac "fileformats (MUST)
set enc=utf8 "encoding
set fenc=utf8 "fileencoding
set fencs=utf8,taiwan,chinese,ucs-bom,default,latin1 "fileencodings
set termencoding=big5
```
