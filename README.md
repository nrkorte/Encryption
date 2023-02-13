====================
About:
    This program is capable of running a symmetric block and stream cipher encryption. It also had the ability to 
    decrypt anything encrypted with the same key.

====================
How to Use:
    Run "make" command to create an executable called "PA1"
    PA1 requires 5 program arguments:
        arg1= 'b' in either case for block encryption, or 's' in either case for stream encryption.
        arg2= the input file
        arg3= the desired output file [does not have to exist before running program]
        arg4= the keyfile
        arg5= 'e' in either case for encryption or 'd' in either case for decryption. 

====================
Key:
    The key for this program is contained in the keyfile. This is symmetric encryption so any key will encrypt and
    decrypt. For block encryption the key must be 16 bytes in length [including white space]

====================
Notes:
    If the input file is empty there will not be an error but rather it will encrypt nothing and put it in the output
    file.

====================
Author(s):
    Nicholas Korte [833037164]