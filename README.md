# Socket Server

In this project I will attempt to build a small socket
server from scratch. The aim of the project is to prepare 
me for another bigger project (HTTP Server from scratch).

## Usage
*Last updates: 11/7/2024*

This only works on windows. make sure to run `server.c` file then use telnet to establish a connection:
```bash
$ telnet remotehostname 3490
```
where the `remotehostname` is your device name ([Click here to find it](https://answers.microsoft.com/en-us/windows/forum/all/find-the-name-of-my-computer/12f6a4cc-845d-4163-aae8-ef0223f3104a)).

you should see a hello world message sent then the connection will be lost.
```bash
Hello world!

Connection to host lost.
```

## TODO
 - [x] implement a small server that sends hello world
 - [ ] implement multi-threading to accept and handle multiple connections
 - [ ] implement a client to send messages back to server
 - [ ] implement clients that communicates between each other (chatbox)
 - [ ] Ensure Proper Error handling
 - [ ] Ensure that this program works on both IPv4 and IPv6 (IP Agnostic)

*Last updates: 11/7/2024*

# References
 - [Beej Network Guide](https://beej.us/guide/bgnet/)
 - [Tallyhawk Winsock Windows Examples](https://www.tallyhawk.net/WinsockExamples/)
 - [Microsoft winsock2 documentation](https://learn.microsoft.com/en-us/windows/win32/api/winsock2/)
