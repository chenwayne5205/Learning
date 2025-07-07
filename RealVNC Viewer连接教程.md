# RealVNC Viewer使用教程
## 以连接比科奇服务器hzvncs1.pct.bj为例,还是建议先安装git
1. 首先执行  
```bash
ssh -OhostKeyAlgorithms=+ssh zhengc@hzvncs1.pct.bj
``` 
随后按照提示输入服务器账号密码，进入到服务器
2.随后输入：
```bash
vncserver -geometry 1920x1080 -depth 24
```
3. 记录下生成的端口号，再RealVNC Viewer这个软件中新建连接，VNC Server这一栏中填写：hzvncs1.pct.bj:端口号，随机输入账号密码即可登录
