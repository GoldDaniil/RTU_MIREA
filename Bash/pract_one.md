<img width="1035" alt="Screenshot 2024-09-08 at 19 06 48" src="https://github.com/user-attachments/assets/f34ea5b4-72a0-4e5b-b6e1-e550e58eb8bc">


grep '^[^#]' /etc/passwd | cut -d ':' -f 1 | sort                                                             


<img width="500" height="470" alt="Screenshot 2024-09-08 at 19 08 56" src="https://github.com/user-attachments/assets/00442559-44a9-410e-bed1-89e0469f9c7a">





<img width="1034" alt="Screenshot 2024-09-08 at 19 12 44" src="https://github.com/user-attachments/assets/c73cda47-a215-4369-b067-02d107eb6be1">

cat /etc/protocols | awk '{print $NF " " $1}' | sort -nr | head -5

<img width="715" alt="Screenshot 2024-09-08 at 19 13 07" src="https://github.com/user-attachments/assets/c6f7bec1-0fca-4b03-a7dc-b7fe6141e850">
