步驟:
git clone https://github.com/MrBraveOuO/blackjack	clone資料夾下來
git checkout -b X					創建新分支X
git checkout X						切換到分支X
							寫完功能
git add .
git commit -m "ex:12/16"
git push origin X					要PUSH到自己的分支X

* X自己取名

差不多完成後再merge

git checkout main
git merge X1
git merge X2
git merge X3

https://gist.github.com/justneedtxt/fea5f1d9e58468a62bb6
