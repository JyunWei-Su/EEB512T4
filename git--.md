顯示分支清單
$ git branch
	加上 -r 參數，將顯示遠端分支。
	加上 -a 參數，可以顯示遠端與本地端的分支。

建立分支
$ git branch <branchname>

修改分支的名稱
$ git branch -m <oldbranch> <newbranch>

刪除分支
$ git branch -d <branchname>
	如果有未合併到 HEAD 
	強制刪除請加上 -D 參數執行。

切換分支
$ git checkout <branch>
	-b執行新建分支和已建分支之間的切換。

存到暫存(切換branch時使用, 尤其是從自己的分支要切回去時)
$ git stash

查看暫存(切回branch時使用)
$ git stash list

讀取暫存(切回branch時使用)
$ git stash pop <stash>

合併分支
$ git merge <branch>
	加上 --no-ff 參數，將建立合併提交，而不是使用 fast-forward 合併。這可以保留分支合併的紀錄，是個非常有用的參數。
	
##  開發步驟參考：
	在自己的分支中開發 -> 確認可執行 -> push到自己的branch
	-> checkout到develop -> merge 自己的專案到 develop
	-> 再次確認可以執行 -> 回到自己的分支 merge develop -> push
##  每周(或重大進度)：
	將 develop merge 到 main (merge develop)-> 確認可執行
	develop merge main (同步)
	(選擇性) 個人分支重新 merge main
	
刪除分支
$ git branch -d <branchname>
	如果有未合併到 HEAD 
	強制刪除請加上 -D 參數執行。
刪除遠端分支
$ git push origin --delete <branchname>

