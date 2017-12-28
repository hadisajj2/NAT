Outside of the readme, there are two main files:

1. NAT.h
2. NAT.cpp

I wrote the code in visual studio 2017 (hence stdafx.h is included in the header). If you run this 
on visual studio, you need to turn of precomplied headers (you can find instructions here: https://msdn.microsoft.com/en-us/library/1hy7a92h.aspx). I've included
all the required Visual studio files in the git repo.

The main function is located under NAT.cpp. Once you run the program , you will be prompted to enter the NAT file and then the FLOW file.
I have set two sample files in the repo (the ones in the email, NAT.txt and FLOW.txt). The outputs will be written to output.txt 
under ~/NAT/Output.txt

If you need me to give you a linux compatible version, please let me know.


IMPORTANT NOTE ON TIME:
I did not include reading about NAT, writing the Readme and adding files to the git repo 
in my time slot.

A: ASSUMPTIONS

1. ONLY NAT file's first pairs can have a *. E.g.

Valid Entry: *:8080, 192.168.0.1:80
Invalid Entry: 10.0.1.1:8080: *:80

2. There is only one mapping from Flow to NAT. In other words,
a FLOW only has one match in the NAT map.

3. In the NAT flow, if an entry has an asteric, for example *:21,1.2.3.4:12, then there will be
no other entry with *:21 as the first IP:PORT to another IP:PORT (e.g. *:21,1.2.4.5:15 will be invalid

3. The NAT and FLOW file are all proper and well-formed, with no duplicates (as in step 2).
All IPs are of the form W.X.Y.Z where W, X, Y and Z are integers(e.g. 192)
This assumption was set for simplicitiy. 

B: HOW I TESTED MY CODE

To be honest tested for NAT pair with *:port--> pair , ip:*-->pair and pair-->pair.
I didn't have enough time to test for edge cases as I would have ran over 90 minutes.

I also tested against the sample provided.

C: ANY INTERESTING CODING, DESIGN or ALGORITHMIC CHOICES

ALGORITHMIC CHOICES: The first thing that came to my mind when I saw the * and pairs was 
a hashmap (unordered_map). However the challange was to deal with the wildcard *. 

To achieve the needed goal, I placed three maps. 

 M1: One from a non-* pair to a pair
 M2: One from an ip- * (any port) to pair
 M3: One from a * (any ip) - port to pair

For every line in the NAT file (if the line is not empty)
If in the NAT flow, I encountered a non-* pair, I a map from the first pair to the second pair to M1.
If in the NAT flow, the port was an asteric, then I added the IP , pair to M2.
e.g. 10.11.12.13:*,40.100.20.7:3389 --> The I would map 10.11.12.13 to 40.100.20.7:3389

If in the NAT flow, the ip was an asteric, then I added the Port , pair to M3. 
e.g. *:21,1.2.3.4:12, then I would map 21 to 1.2.3.4:12.

To write to the output, the FLOW file (given that there is only one match) was as follows:

For every line (pair) in the FLOW file
 
If there exists an entry of the pair in M1, then write to output Pair in Flow --> What it maps to in M1.
If there exists an entry of the pair's ip in M2, then write to outpout Pair in flow --> what the IP maps to M2.
If there exists an entry of the pair's port in M3, then write to outpout Pair in flow --> what the port maps to M2.

The main benefit of using an unordered_map is that querying can be done in O(1).

SOFTWARE ENGINEERING: Standard class/function definitions. Nothing amazing here.

D: KNOWN LIMITATIONS DUE TO TIME CONSTRAINT (a.k.a what I would've done better), HOW TO MAKE IT BETTER
I tried to solve my limitations through simplyfing the problem (via assumptions). However, give my assumptions, I ran out
of time to try the following:

1. Remove an entry for the maps once it has been written to the output (this needs to be properly tested and looking at edge cases with be a must). 
This approach would allow freeing up space. However, on the flip side, if there is more than one file that needs to be tested against the same NAT file, then
this approach will not work.

2. scaling the problem to very large tables would most likely require some sort of a distributed unordered_map which I am hoping is out of the scope of this challenge.

3. I would say my main technical bottle neck was parsing the pairs (IPs and Ports). I took code from stackoverflow and incorporated into my code. I didn't look at
how efficient they are, hence I would spend more time on this to make it more efficient. 
















