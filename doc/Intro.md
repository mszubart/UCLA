# Unified Communication Layer Alternative

## Introduction

This library provides quick and easy way to communicate between processes (even on remote machines).

### Supported programming languages:

* C++11 (MSVC2012 or GCC4.6+)
* C# (probably Mono)
* Java v1.6+

### Features:

* Automatic reconnection.
* Fault tolerance.
* Message queuing.
* Super easy [configuration](https://github.com/mszubart/UCLA/blob/master/doc/Config.md) and usage.

### Dependencies:

* [Crossroads I/O](http://www.crossroads.io/)
* C++ - [cppxs](https://github.com/250bpm/cppxs) + [Jansson](http://www.digip.org/jansson/) + [CMake](http://www.cmake.org/) on Linux
* C# - [crossroads-net](https://github.com/jgoz/crossroads-net) + [Json.NET](http://james.newtonking.com/projects/json-net.aspx)
* Java - [jxs](https://github.com/gonzus/jxs) + [Json-lib](http://json-lib.sourceforge.net/)

## How to use (by C# examples)
Those are working examples - you can copy and run them.

List of examples for other languages is available at the bottom of this document.

### Client

``` C#
using System;

using libUCLA;

namespace UCLA_Client {
    class Client {
        static void Main(string[] args) {
            try {
                UClient client = new ULoader_JSON("config.json").GetClient("output1"); // Create client object, using specified configuration, 
                //client.Start(); // Start client connection explicitly. 
                client.SendData(new byte[] {1,2,3}); // Send some data | also starts connection if client connection was not started

            } catch (UException ex) {
                Console.Write(String.Format("Something went horribly wrong:\n\t{0}\n", ex.Message));
            }

            Console.ReadKey();
        }
    }
}
```

### Server

``` C#
using System;

using libUCLA;

namespace UCLA_Server {
    class Server {
        static void Main(string[] args) {
            try {
                UServer server = new ULoader_JSON("config.json").GetServer("input1"); // Create server object from configuration.

                server.DataReceived += new UReceiveHandler(OnDataReceived); // Before start, you should bind your event handler.
                                                                            // Otherwise you could loose some data.

                //server.Start(); // Explicitly start a server after binding handler.
                                  // Otherwise first call to receive will do it for you.

                server.Run(); // This is test method, which runs in infinite loop.
                              // You should rather use Receive method in a real application.
            } catch (UException ex) {
                Console.Write(String.Format("Something went horribly wrong:\n\t{0}\n", ex.Message));
            }
        }

        private static void OnDataReceived(byte[] buf) { // This method is called whenever server receives a message.
            Console.Write("\n");                         // You should remember that this method must return 
                                                         // as soon as possible for best performance.
            foreach (byte b in buf) {
                Console.Write(String.Format("{0:d}\t", b));
            }
        }
    }
}
```

## Examples for other languages

### `C++`
* [`Client`](https://github.com/mszubart/UCLA/blob/master/cpp/UCLA/UCLA_Client/UCLA_Client.cpp)
* [`Server`](https://github.com/mszubart/UCLA/blob/master/cpp/UCLA/UCLA_Server/UCLA_Server.cpp)

### `C#`
* [`Client`](https://github.com/mszubart/UCLA/blob/master/cs/UCLA/UCLA_Client/Client.cs)
* [`Server`](https://github.com/mszubart/UCLA/blob/master/cs/UCLA/UCLA_Server/Server.cs)

### `Java`
* [`Client`](https://github.com/mszubart/UCLA/blob/master/java/UCLA_Client/src/UCLA_Client/Client.java)
* [`Server`](https://github.com/mszubart/UCLA/blob/master/java/UCLA_Server/src/UCLA_Server/Server.java)