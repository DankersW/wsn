# CoAP message definition

The CoAP message is send inbetween the nodes, and the gateway.

## V1 mesasge set

### Temparature message

Consisting of 2 bytes

|                          | Byte 0            | Byte 1            |
|--------------------------|-------------------|-------------------|
| Temperature message      | Value before coma | Value after comma |
| Sample for 25.71 degrees | 25                | 71                |


**Discover message:** some more bytes


