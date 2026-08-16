# 暗号化マシーン
## 使い方
実行するには`-r`オプション、
復号化するには`-d`オプションを使用します！
すべてのコマンドは次の通りです：
```
-help      | help                                      |
-h         | help                                      |
-r         | run                                       |
-with-zero | Include null characters during encryption |
-d         | decryption                                |
-ic        | input console                             | [input]
-oc        | output console                            |
-of        | output file                               | [file name]
-if        | input file                                | [file name]
-ff        | file name flip                            |
```

## 例
### 1.
```
.\angoka.exe -r -ic 暗号化～ -oc
```
結果
```
022440032175023265022110022605030855021285015840000165
```
### 2.
```
.\angoka.exe -r -d -ic 022440032175023265022110022605030855021285015840000165 -oc
```
結果
```
暗号化～
```
