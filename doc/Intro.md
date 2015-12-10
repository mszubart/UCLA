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

* [Crossroads I/O](https://github.com/crossroads-io/libxs)
* C++ - [cppxs](https://github.com/250bpm/cppxs) + [Jansson](http://www.digip.org/jansson/) + [CMake](http://www.cmake.org/) on Linux
* C# - [crossroads-net](https://github.com/jgoz/crossroads-net) + [Json.NET](http://james.newtonking.com/projects/json-net.aspx)
* Java - [jxs](https://github.com/gonzus/jxs) + [Json-lib](http://json-lib.sourceforge.net/)

## How to use (by C# examples)
Those are working examples - you can copy and run them.

List of examples for other languages is available at the bottom of this document.

### Sender

``` C#
using System;

using libUCLA;

namespace UCLA_Sender {
    class Sender {
        static void Main(string[] args) {
            try {
                USender sender = new ULoader_JSON("config.json").GetSender("output1"); // Create sender object, using specified configuration, 
                //sender.Start(); // Start sender connection explicitly. 
                sender.SendData(new byte[] {1,2,3}); // Send some data | also starts connection if sender connection was not started

            } catch (UException ex) {
                Console.Write(String.Format("Something went horribly wrong:\n\t{0}\n", ex.Message));
            }

            Console.ReadKey();
        }
    }
}
```

### Receiver

``` C#
using System;

using libUCLA;

namespace UCLA_Receiver {
    class Receiver {
        static void Main(string[] args) {
            try {
                UReceiver receiver = new ULoader_JSON("config.json").GetReceiver("input1"); // Create receiver object from configuration.

                receiver.DataReceived += new UReceiveHandler(OnDataReceived); // Before start, you should bind your event handler.
                                                                              // Otherwise you could loose some data.

                //receiver.Start(); // Explicitly start a receiver after binding a handler.
                                    // Otherwise first call to receive will do it for you.

                receiver.Run(); // This is test method, which runs in infinite loop.
                                // You should rather use Receive method in a real application.
            } catch (UException ex) {
                Console.Write(String.Format("Something went horribly wrong:\n\t{0}\n", ex.Message));
            }
        }

        private static void OnDataReceived(byte[] buf) { // This method is called whenever receiver receives a message.
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
* [`Sender`](https://github.com/mszubart/UCLA/blob/master/cpp/UCLA/UCLA_Sender/UCLA_Sender.cpp)
* [`Receiver`](https://github.com/mszubart/UCLA/blob/master/cpp/UCLA/UCLA_Receiver/UCLA_Receiver.cpp)

### `C#`
* [`Sender`](https://github.com/mszubart/UCLA/blob/master/cs/UCLA/UCLA_Sender/Sender.cs)
* [`Receiver`](https://github.com/mszubart/UCLA/blob/master/cs/UCLA/UCLA_Receiver/Receiver.cs)

### `Java`
* [`Sender`](https://github.com/mszubart/UCLA/blob/master/java/UCLA_Sender/src/UCLA_Sender/Sender.java)
* [`Receiver`](https://github.com/mszubart/UCLA/blob/master/java/UCLA_Receiver/src/UCLA_Receiver/Receiver.java)
