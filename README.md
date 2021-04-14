
## Overview
This is a C++ implementation of WiFi-Connection like altwfc.
This version is still work in progress.

## Roadmap
### QS-Service
```
  [x] Receive packet 0x09 (AVAILABLE)
  [x] Respond packet 0x09 (AVAILBALE)
  [x] Finished
  [ ] Configuration
  [ ] Checking availablitiy
```  
### NA-Service
```
  [ ] Receive /ac
    [ ] Handle login
  TODO
```
  
### Sake
```
  TODO
```

## Notes
### Apache Reverse Proxy
The client sends the **Host** twice in the **HTTP-Header**. Apache does not allow that and your **Proxy wont work**.

To fix this, add the following line to your **httpd.conf**:
```
HttpProtocolOptions Unsafe LenientMethods Allow0.9
```
