# RealVNC Viewer使用教程（实验室服务器不需要连接VNC，rdp远程连接即可）
## 以连接比科奇服务器hzvncs1.pct.bj为例，还是建议先安装git
- **首先打开本地terminal**
```bash
ssh -OhostKeyAlgorithms=+ssh zhengc@hzvncs1.pct.bj
``` 
随后按照提示输入服务器账号密码，进入到服务器  
- **进入到服务器后，执行下面的指令**
```bash
vncserver -geometry 1920x1080 -depth 24
```  
- **记录下生成的端口号，再RealVNC Viewer这个软件中新建连接，VNC Server这一栏中填写：hzvncs1.pct.bj:端口号，随机输入账号密码即可登录**
