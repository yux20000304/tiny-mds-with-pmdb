# tiny-mds-with-pmdb

## Abstract
- 这是我的本科毕业设计代码仓库
- 我的毕设选题是基于非忆失性存储的元数据缓存设计

## Build the project

```
    mkdir build && cd build
    cmake ..
    make -j($proc)
```
## Usage

1. open a master proc with 1 slave: ``` ./server -s8080 -n1 ```
2. open a slave proc and connext to master: ``` ./server -s8081 -i127.0.0.1 -p8080 ```
3. open a client proc: ``` ./client -i127.0.0.1 -p8080 ```

Then you can type commands in client, and the master node will send the metadata to the slaves.
