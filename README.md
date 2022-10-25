先编译两个模块并安装
```
cd lkm
make test # 获取到设备的Major号
sudo mknod /dev/lkm_example c MAJOR 0 # 将MAJOR替换为刚刚获取到的MAJOR号，将lkm模块挂载到/dev/lkm_example

cd hook_byname
make
sudo insmod hook_byname.ko
```bash

接着开启另一个终端观察回调函数打印的结果
```
sudo cat /sys/kernel/tracing/trace_pipe
```bash

在第一个终端中触发device_read，回车完可立马ctrl + c，避免输出信息过多
```
cat /dev/lkm_example
```bash

接着查看device_read打印的参数详情
```
sudo dmesg
```bash