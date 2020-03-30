# encryptionChipTest

Code to test writing to and reading from the linear feedback encryption chip we made in Silicon Compilation

The code has to be copied to your own arduino project in order to be executed. chipTrueReader and chipContinuousWriter are the fully debugged
versions of my code. 

The chipReader and chipWriter were the original iterations of the code. They are not true readers and writers because in 
this case, the writer handshakes the acknowledgement output_a signal rather than the reader.
