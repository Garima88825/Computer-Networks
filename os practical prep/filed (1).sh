#!/usr/bin/bash
echo -e "\e[0;34mThis program displays the details of the requested file\e[m"
echo -e "\e[1;31mOwnerShip\e[m"
file=$1
echo -e "\e[1;44mOwner Permissions:\e[m" $(ls -lc $1 | awk '{print $1,"\011"}' | cut -b 2-4)
echo -e "\e[1;44mGroup Permissions:\e[m" $(ls -lc $1 | awk '{print $1,"\011"}' | cut -b 5-7)
echo -e "\e[1;44mOther's Permissions:\e[m" $(ls -lc $1 | awk '{print $1,"\011"}' | cut -b 8-10)
echo -e "\n\e[1;31mAccess Time:\e[m $(ls -lc $1 | awk '{print $8}')"
echo -e "\n\e[1;34mThe inode of the file is:\e[m $(ls -li $1 | awk '{print $1}')"
echo -e "\n\e[1;34mThe number of links to file:\e[m  $(ls -l $1 | awk '{print $2}')"
echo -e "\n\e[1;31mThe size of the file is:\e[m $(ls -lh $1 | awk '{print  $2}')"
echo -e "\n\e[1;34mThe size of the file is:\e[m $(ls -lh $1 | awk '{print $5}')"
echo -e "\n\e[1;34mThe owner of the file is:\e[m $(ls -l $1 | awk '{print $3}')"
echo -e "\n\e[1;31mThe file belongs to group:\e[m $(ls -lh $1 | awk '{print $4}')"
echo -e "\n"
