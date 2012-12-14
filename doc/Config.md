# Unified Communication Layer Alternative
## Structure of configuration file
UCLA configuration file is a JSON text file and contains information needed to successfully connect `Receiver` and `Sender`
You can notice that configuration files for `Receiver` and `Sender` are very similar, so you can use one file for all configuration.
The only difference is that for `Receiver` you have to specify [interface](http://www.crossroads.io/1-0:xs-tcp) and for `Sender` you have to specify host.

* UCLA configuration parser is case sevsitive.
* `Input` and `Output` names follow C language naming conventions.
* [`interface`](http://www.crossroads.io/1-0:xs-tcp) value type is string. This is a name of interface (eg `eth0`) or the the primary IPv4 or IPv6 address assigned to the interface or `*`.
* `host` value type is string. This value accepts IPv4 IP address or a name recognized by DNS.
* `port` value type is string. This value can contain only digits.

## Examples:
### Receiver
For `Receiver`, user defines `inputs` which will listen on specified port and [interface](http://www.crossroads.io/1-0:xs-tcp).
``` JSON
{
    "inputs":{
        "input_name_1":{
            "interface":"*",
            "port":"5555"
        },

        "input_name_2":{
            "interface":"*",
            "port":"4444"
        },
    }
}
```

### Sender
For `Sender`, user defines `outputs` which will send data to specified `port` on `host`.
``` JSON
{
    "outputs":{
        "output_name_1":{
            "host":"192.168.0.12",
            "port":"5555"
        },

        "output_name_2":{
            "host":"192.168.0.12",
            "port":"4444"
        },
    }
}
```

### Mixed
This file contains configuration for both `Receiver` and `Sender`
``` JSON
{
    "outputs":{
        "output_name_1":{
            "host":"192.168.0.12",
            "port":"5555"
        },

        "output_name_2":{
            "host":"192.168.0.12",
            "port":"4444"
        },
    },

    "inputs":{
        "input_name_1":{
            "interface":"*",
            "port":"5555"
        },

        "input_name_2":{
            "interface":"*",
            "port":"4444"
        },
    }
}
```