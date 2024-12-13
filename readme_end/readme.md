# Mini project 1(Part 2)

#### GENERAL
Majority of the input is in format of strings of length 4096 chars.

## Spec 9
I have implemented aliases for both commands and functions for functions i have assumed that only the two functions given in doc would be tested but for commands i have done in general

alias or func keyword need to meintioned beofre writing the command or function
## Spec 10
I have assumed that multiple redirection symbols of same kind would not come

I have used dup and dup2 for stdin and stdout to implement redirectionin the end i have restored the stdin and stdout
### References :
![alt text](<Screenshot from 2024-09-12 00-18-40.png>)
 ![alt text](<Screenshot from 2024-09-12 00-18-56.png>)
  ![alt text](<Screenshot from 2024-09-12 00-19-19.png>)
## Spec 11
### Assumptions: 
assume max no of pipes is 256

in case of running in background exited normally would not be shown
Here i am taking that & will not be given in between the pipes like echo hello &|wc my code will give unexpected results in such cases
### References :

![alt text](<Screenshot from 2024-09-07 19-38-15.png>) 
![alt text](<Screenshot from 2024-09-07 19-51-10.png>) 
![alt text](<Screenshot from 2024-09-07 19-51-15.png>)
 ![alt text](<Screenshot from 2024-09-07 19-51-20.png>)

## Spec 12
We combine both pipes and redirection

## Spec 13

### Refernces:
![alt text](<Screenshot from 2024-09-06 19-28-23.png>)
 ![alt text](<Screenshot from 2024-09-06 19-28-34.png>) 
 ![alt text](<Screenshot from 2024-09-06 19-29-11.png>) 

### For checking state i used status file:
![alt text](<Screenshot from 2024-09-07 13-25-02.png>) 
![alt text](<Screenshot from 2024-09-07 13-25-17.png>) 
![alt text](<Screenshot from 2024-09-07 13-25-59.png>)

## Spec 14
I used ping command to send required signal to the command

I also implemented ctrl c ctrl z used signal handler

For ctrl d i checked 'EOF'

![alt text](<Screenshot from 2024-09-07 15-05-37.png>)

### References for ping:
![alt text](<Screenshot from 2024-09-06 19-30-01.png>)
![alt text](<Screenshot from 2024-09-06 19-30-22.png>)
![alt text](<Screenshot from 2024-09-06 19-30-53.png>)
![alt text](<Screenshot from 2024-09-06 19-30-59.png>)

## Spec 15
### Reference used for how to impllement fg command:
![alt text](<Screenshot from 2024-09-07 15-52-20.png>)
 ![alt text](<Screenshot from 2024-09-07 15-52-29.png>) 
 ![alt text](<Screenshot from 2024-09-07 15-52-35.png>)
  ![alt text](<Screenshot from 2024-09-07 15-52-42-1.png>)
## Spec 16
I switch to raw mode for taking input and printing the last pid which is present in status/proc
When we get X i will stop and go back to coked mode
### References :
![alt text](<Screenshot from 2024-09-08 15-28-17.png>)
 ![alt text](<Screenshot from 2024-09-08 15-29-26.png>)
![alt text](<Screenshot from 2024-09-08 15-45-44.png>)
 ![alt text](<Screenshot from 2024-09-08 15-45-56.png>)
## Spec 17
Assumption: invalid command not handled

max size is 8192 of response
### References :
i used reference for checking how to create socket,get request and receive response

![alt text](<Screenshot from 2024-09-11 17-17-39.png>)
 ![alt text](<Screenshot from 2024-09-11 17-17-54.png>) 
 ![alt text](<Screenshot from 2024-09-11 17-18-07.png>) 
 
 used refence to remove html tags

 ![alt text](<Screenshot from 2024-09-11 17-18-37.png>)

 (Redirection function improvement)