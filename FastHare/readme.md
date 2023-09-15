#FastHare 

Compile:
--------------------------------------------------------
make
--------------------------------------------------------
Download an MQLib instance and convert to .net format:
--------------------------------------------------------
wget https://mqlibinstances.s3.amazonaws.com/{instance-name}.zip
unzip {instance-name}.zip
python3 parse.py {instance-name}
--------------------------------------------------------
Convert from QUBO to .net file
--------------------------------------------------------
python3 qubo2ising.py {qubo-file} {net-file}
The program read the QUBO in {qubo-file} and write the Hamiltonian without linear terms to {net-file}
--------------------------------------------------------

How to run:
--------------------------------------------------------
./fasthare <input in net format> <output-file> alpha 

In each iteration, the program computes the similarity score for n*alpha edges (where n is the number of nodes).

The program will write to console in the following format
	{input_file},{n},{m},{n1},{run_time}
The program will output two files 
	{output-file}_compress
		The first line of this file consists of two numbers n1 and m1, where n1 is the number of nodes and m1 is the number of edges in the compressed graph
	{output-file}_flip
	
Example:
./fasthare test.net output 2 0
test.net,10,14,1,4.1e-05
	