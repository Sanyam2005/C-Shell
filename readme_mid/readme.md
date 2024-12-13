# Mini project 1(Part 1)
path size 4096
## Spec 1
I used refences for cwd function and how to print the relative and absolute paths

![alt text](<Screenshot from 2024-08-18 00-13-43.png>)
![alt text](<Screenshot from 2024-08-17 17-42-33.png>)

![alt text](<Screenshot from 2024-08-18 00-19-40.png>)
![alt text](<Screenshot from 2024-08-17 17-52-28.png>)
![alt text](<Screenshot from 2024-08-17 17-52-45.png>)

## Spec 2

### I used to understand use of strtok
![alt text](<Screenshot from 2024-08-17 18-02-57.png>)

![alt text](<Screenshot from 2024-08-17 18-16-03.png>)
![alt text](<Screenshot from 2024-08-17 18-16-16.png>)

## Spec 3

![alt text](<Screenshot from 2024-08-18 00-43-08.png>)
![alt text](<Screenshot from 2024-08-18 00-43-28.png>)

![alt text](<Screenshot from 2024-08-18 00-44-42.png>)
![alt text](<Screenshot from 2024-08-18 00-47-26.png>)

## Spec 4

![alt text](<Screenshot from 2024-08-18 00-30-59.png>)
![alt text](<Screenshot from 2024-08-17 22-48-42.png>)

![alt text](<Screenshot from 2024-08-18 00-35-29.png>)
![alt text](<Screenshot from 2024-08-17 22-50-10.png>)
![alt text](<Screenshot from 2024-08-17 22-50-34.png>)

![alt text](<Screenshot from 2024-08-18 00-32-48.png>)
![alt text](<Screenshot from 2024-08-18 00-33-46.png>)
![alt text](<Screenshot from 2024-08-17 23-31-09.png>)

![alt text](<Screenshot from 2024-08-18 00-36-53.png>)

## Spec 5
I have implemented using cicrular buffer implementation
I keep start and end variable and update them so that only 15 elements are stored in array
To ensure storage of log across sessions,i write the values in log.txt and read from the log.txt file when main is executed initially

Assumption : 

most recent command printed at last 

All commands(including errorous are printed in log) except log itself

log.txt stores all previous logs

Note it is having some error handling cases where it print error on invalid format however if someone does log execute on a command having wrong input format as it has a differnet tokenization method it will not detect the error but will run in the same manner as a errenoous command would run when a user would input it.

## Spec 6

For background process we will not add wait in parent so it automatically gives cotrol to terminal
For foreground we add wait in parent
Assumptions:
1. If background process is errorous i will first print pid then error messgage and  then i print "process <pid> exited abmormally
If background process successful i print "process <pid> exited normally
2. If foreground then i print the time taken in next prompt 
Note: in a command like sleep 3;sleep 5 in next prompt i will print <sanyamagrawal@pop-os:~ sleep 3s ; sleep 5s>
If command is sleep 3 ;echo hello ;sleep 5 then in next pompt i print only those which greater than 2 seconds so output is <sanyamagrawal@pop-os:~ sleep 3s ; sleep 5s>

Note - The foreground process is spawned with setpgid() command so that signal could be handled properly. Because of this those processes which need the entire control of terminal do not get the control and then cannot be worked however on closing shell they give signal of SIGHUP (means the process ran but couldnt get control).
For eg, vim will not work

![alt text](<Screenshot from 2024-08-29 23-02-35.png>)
![alt text](<Screenshot from 2024-08-31 13-23-47.png>)
## Spec 7

### In proclore i have used proc/pid/status to get the status file which contains imp details like state and vmsize
I have taken vm size in kilobytes

![alt text](<Screenshot from 2024-08-29 14-20-25.png>)
![alt text](<Screenshot from 2024-08-29 14-20-48.png>)

### For executable path i have used readlink and i have printed the absolute path(as mentioned in doubt doc)

![alt text](<Screenshot from 2024-08-29 14-18-44.png>)


## Spec 8
For seek i have used recursive method, in my search disrectory fn i perform the search algoritm to see and store in results array if any match

results array - relative path

final_results array -absolute path

Then in my seek fn i print the results array
in case of -e flag i check if one directory/file is present and do the specified function

![alt text](<Screenshot from 2024-08-28 16-39-19.png>)
![alt text](<Screenshot from 2024-08-28 16-34-04.png>)
![alt text](<Screenshot from 2024-08-28 16-32-16.png>)
![alt text](<Screenshot from 2024-08-31 17-41-56.png>)
![alt text](<Screenshot from 2024-08-31 17-40-04.png>)
![alt text](<Screenshot from 2024-08-31 17-40-24.png>)

