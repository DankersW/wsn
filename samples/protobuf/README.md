# Protobuf

Example how to use protobuf to serialize and deseialize a message.

Based on the proto message:

```proto
message SensorData {
    string sensor_id = 1;
    float temperature = 2;
    float humidity = 3;
}
```

## Building & Flashing

```sh
./scripts/build_and_flash.sh -p samples/protobuf -b dongle
```

## Testing/Running

```sh
screen /dev/ttyACM0
```
