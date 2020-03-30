# encryptionChipTest

Code to test writing to and reading from the linear feedback encryption chip we made in Silicon Compilation

The code has to be copied to your own arduino project in order to be executed. chipTrueReader.ino and chipContinuousWriter.ino are the fully debugged
versions of my code. 

The chipReader.ino and chipWriter.ino were the original iterations of the code. They are not true readers and writers because the writer handshakes the acknowledgement output_a signal rather than the reader.
