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

You build the libBabySitterCalc.so shared library, TestBabySitter test app suite and BabySitterApp like so:
make all

You run the test app from the top directory like so:
LD_LIBRARY_PATH=./bin ./bin/TestBabySitter

You can also build the library, test app and run the test app suite at the same time like so:
make check

If everything passes you should see test output like so:
Running suite(s): BabySitter
100%: Checks: 1, Failures: 0, Errors: 0

You run the BabySitterApp for inputting the start, end and bedtimes from the top directory like so:
LD_LIBRARY_PATH=./bin ./bin/BabySitterApp

The BabySitterApp will ask you to input the start, end and bedtimes in that order. You can type a 'r' to reset
the app to start over from the beginning. To quit the app type 'q' or hit the return key on an empty line. The
app expects time values between 5:00PM and 4:00AM and will prompt you to re-enter your value if it is invalid or
out of bounds. After all three values are entered it will calculate your expected earnings after which you can
exit or hit 'r' to enter new values.

