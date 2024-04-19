>
```
# 存在するサーバーのオープン中ポート（例えばRDP）の場合は接続成功
> ConsoleApplication1.exe 127.0.0.1 3389
connect: OK

# 存在するサーバーのクローズ中ポート（例えばSSH）の場合は WSAECONNREFUSED(10061) になる
> ConsoleApplication1.exe 127.0.0.1 22
connect failed with error: 10061

# IPアドレスが接続先として不適切の場合は WSAEADDRNOTAVAIL(10049) になる
> ConsoleApplication1.exe 0.0.0.0 22
connect failed with error: 10049

# 同一ネットワークだが、存在しないサーバーの場合は WSAETIMEDOUT(10060) になる
>ConsoleApplication1.exe 192.168.1.2 22
connect failed with error: 10060
```