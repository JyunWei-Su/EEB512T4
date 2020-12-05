# EEB512T4
Computer programming
* 關檔案一要記得存專案

## 預定進度

### 12/03
- [x] 遊戲專案建立

### 12/06
- [X] 遊戲畫面1600*900
- [X] 標題，icon(遊戲部分，不含選單)
- [ ] 人物移動(鍵盤控制)
- [ ] 聲音
- [ ] timer/event/loop

### 12/07~12/09
- [ ] 12/6部分整合
- [ ] 更新進度

### 12/14
- [ ] 物件設定(金幣、跟班、障礙)

### 12/21
- [ ] 碰撞設定、分數計分、其他調教

### 12/28
- [ ] 整體的修正補足

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
