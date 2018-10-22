# Pod Server 2019
Pod Server for 2018-2019 Waterloop Pod

This is a `wio` application.

To build this application:
```bash
make
```

To clean this application:
```bash
make clean
```

Which does these things for us:
   1) Make sure the sub-module(s) are/is properly cloned.
   2) Build the sub-module(s) (uWebSockets , etc..), can be shared libs aswell.
   3) Copy the shared lib(s) (.so) to our main directories 'bin/deps' folder.
   4) Build our server using wio, while linking to the shared binary (.so file) that was copied to the deps folder in (3) and built in (2).

Todo: 
    - Get the wio package to build as an app.
    - Write our own server (tweak according to our needs).
