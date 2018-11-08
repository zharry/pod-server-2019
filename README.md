# Pod Server 2019

Code base for pod server running on the pod while the hyperloop run is going on.

## Build and Run

This is a `wio` project so install wio (https://github.com/wio/wio)

* Project depends on Boost so following Boost libraries must be installed:
    * system
    * thread
    * coroutine
    * context

```bash
cd pod-server-2019
wio build
wio run
```
## Development

`src/main.cpp` is the entry point of the project and at the moment it contains dummy code to test all the features that are being built. Once a feature is implemented, it can be added to main.cpp. Once all the required features are implemented, pod logic will go in `src/main.cpp`
