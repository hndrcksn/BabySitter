Babysitter Kata

Background
----------
This kata simulates a babysitter working and getting paid for one night.  The rules are pretty straight forward:

The babysitter 
- starts no earlier than 5:00PM
- leaves no later than 4:00AM
- gets paid $12/hour from start-time to bedtime
- gets paid $8/hour from bedtime to midnight
- gets paid $16/hour from midnight to end of job
- gets paid for full hours (no fractional hours)


Feature:
As a babysitter
In order to get paid for 1 night of work
I want to calculate my nightly charge

Make/Build instructions:
This program was developed on a Linux machine running Ubuntu 14.04.5 LTS (version jessie/sid) on x86_64
hardware, but should work fine on 32bit hardware. It is written for the GNU C compiler suite and uses 
the "check" unit testing framework for C from https://libcheck.github.io/check/ which can be installed 
from the default package installer "apt" like so:
apt install check

You setup the build directories like so:
mkdir obj
mkdir bin

You build the libBabySitterCalc.so shared ibrary like so:
gcc -c -Wall -Werror -fPIC  -std=gnu99 ./src/lib/BabySitterCalc.c -o ./obj/BabySitterCalc.o
gcc -shared -o ./bin/libBabySitterCalc.so ./obj/BabySitterCalc.o

You build the TestBabySitter test app like so:
gcc -L./bin -L/usr/lib/x86_64-linux-gnu/ -Wall -Werror -std=gnu99 ./src/tests/TestBabySitter.c -o ./bin/TestBabySitter -lBabySitterCalc -lcheck -pthread -lrt -lm

You run the test app from the top directory like so:
LD_LIBRARY_PATH=./bin ./bin/TestBabySitter

You should see passed test output like so:
Running suite(s): BabySitter
100%: Checks: 1, Failures: 0, Errors: 0

