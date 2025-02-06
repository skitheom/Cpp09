# CPP Module 09
42 project

## Topics
- STL

## Exercises
- 各exerciseにおいて必ずコンテナを使う
- 各課題で用いるコンテナは重複してはならない

### Exercise 00: Bitcoin Exchange
- Bitcoin交換レートのCSVを{日付, ExchangeRate}の形式に整理する
- 特定の日付（あるいはそれに最も近いlowerの日付）の値で計算する
- mapを選択

### Exercise 01: Reverse Polish Notation
- Reverse Polish Notation は算式記法。被演算子のあとに演算子を置く
- 状態を持つ必要はない
- stackを選択


ex02
マージ挿入ソートアルゴリズム

## References

[CPP Module 09(For 42 École Students Only)](https://projects.intra.42.fr/projects/cpp-module-09)

__Exercise 00__
- [Program to check if a date is valid or not](https://www.geeksforgeeks.org/program-check-date-valid-not/)
- [How to Open and Close a File in C++?](https://www.geeksforgeeks.org/how-to-open-and-close-file-in-cpp/)
- [CSV File Management Using C++](https://www.geeksforgeeks.org/csv-file-management-using-c/)
- [std::map<Key,T,Compare,Allocator>::lower_bound](https://en.cppreference.com/w/cpp/container/map/lower_bound)

__Exercise 01__
- [逆ポーランド記法と木構造の絵](https://qiita.com/yumura_s/items/ddb0d143fb0e9a082891)
図があってわかりやすい解説
- [How to Split a String by a Delimiter in C++?](https://www.geeksforgeeks.org/how-to-split-string-by-delimiter-in-cpp/)
token分割の方法について

- []()
- []()
- []()
- []()
- []()
- []()
- []()
- []()
- []()
- []()
- []()
- []()
- []()
- []()
- []()
- []()
- []()
- []()
- []()
- []()

## ?

- [Learning c++98 in 2024](https://www.reddit.com/r/cpp_questions/comments/1986lga/learning_c98_in_2024/)

### 複数のリモートリポジトリを設定する (Githubと42リポジトリの使い分け)

#### `git remote add`
追加するラベルは、通常 origin とは別の名前を付ける
```
git remote add [任意のラベル] [新規で追加したいリモートリポジトリのアドレス]
```
Ex.
```
git remote add github git@github.com:skitheom/Cpp09.git
git remote add gitlab git@gitlab.com:skitheom/Cpp09.git
```

#### `git remote -v`
現在登録されているリモートリポジトリを確認
```
 ~/code/cppModules/Cpp09/ex01/ [main*] git remote -v
github  git@github.com:skitheom/Cpp09.git (fetch)
github  git@github.com:skitheom/Cpp09.git (push)
gitlab  git@gitlab.com:skitheom/Cpp09.git (fetch)
gitlab  git@gitlab.com:skitheom/Cpp09.git (push)
```

#### 特定のリモートへ `push`, `fetch`, `pull`

`git push [ラベル] main`

Ex.
```
git push github main   # GitHub に push
git push gitlab main   # GitLab に push

git fetch github       # GitHub の最新状態を取得
git fetch gitlab       # GitLab の最新状態を取得

git pull github main   # GitHub から `main` を pull
git pull gitlab main   # GitLab から `main` を pull
```

複数のリポジトリを設定することで、異なるリポジトリ間のコミット履歴を反映するg
