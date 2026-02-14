# Simple remote code execution in c

## 💡 introduction

This is a simple c project that allows for remote shell connection and run commands remotely.

> **Note:** As of now it is not compatible with windows only unix like

## 💻 Installation and usage

- *Install build tools if you don't already have them.*

| tool | required |
| --- | --- |
| gcc | ✅ |
| make | ✅ |

- *Clone the repository and move into the directory.*

```sh
git clone https://github.com/Alpinine99/remote-cshell.git
cd remote-cshell
```

- *On the folder run make, to compile the binaries.*

```sh
make
```

- *running the binaries.*

```sh
./slave # from one terminal window

./master 127.0.0.1 2223 # from another terminal window
```

![master output](/resources/image.png)

> You can go one step further and access another machine from your network by compiling and running the slave from it and connect to from your local machine via its local ip.

- *Use `exit` to terminate the connection.*

## Hope you find it useful 😅
