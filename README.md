# 111暑假專案

## Requirements

* 要做出三種不同的DoS攻擊
* 能夠有介面控制不同Host進行攻擊和停止
* DoS程式使用 C C++ 撰寫

## 工具使用方法

### syn-flood attack
```
$ gcc -o syn syn_flood_custom.c -lpthread
$ sudo ./syn <IPaddress> <port>
```
