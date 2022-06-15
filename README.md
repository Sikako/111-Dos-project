# 111暑假專案

## Requirements

* 要做出三種不同的DoS攻擊
* 能夠有介面控制不同Host進行攻擊和停止
* DoS程式使用 C C++ 撰寫
* 能夠random source IP

## 構想
使用client-server的架構，在遠端電腦建立flask server，透過request並傳送所需參數完成攻擊和停止指令

## UML
[UML diagram](https://drive.google.com/file/d/1Wl6fYA4naVCfMY4u6Kba2XZunE7Qp2Mz/view?usp=sharing)

![](https://i.imgur.com/7OS6bR3.png)

`Use Case Diagram`

![](https://i.imgur.com/syvTlwX.png)

`Activity Diagram`

![](https://i.imgur.com/FmO4ETZ.png)
`Sequence Diagram`


## 環境
* python 3.5 up

## 攻擊種類
* SYN Flood
* ACK Flood
* UDP Flood
* Smurf

---
# 架設方法
## Server 端
:::danger
 使用root架flask server
:::
```shell=
# cd 111-Dos-project/python/
# python3 server.py

* Running on http://<IP>:9999 (Press CTRL+C to quit)
```

## Client 端




---
## 工具使用方法
### compile
```
$ ./compile.sh
```

### tcp_flood_attack
```
$ sudo ./tcp_attack <IPaddress> <port> <mode>
```

### udp_flood_attack
```
$ sudo ./udp_attack <IPaddress> <port>
```
### smurf_attack

```
$ gcc smurf.c -o tools/smurf_attack
$ sudo ./smurf_attack 192.168.200.55 192.168.200.255

The first ip is attacked address, second is the local area network.
```
