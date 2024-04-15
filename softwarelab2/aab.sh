# Question 1
echo -e "\nQuestion 1: Show all the times Edgar Allen Poe's poem 'The Raven' contains the word 'raven'"
echo -e "Answer 1:"
grep -i -n "raven" poem.txt

# Question 2
echo -e "\nQuestion 2: Pick out the blank lines in the file (lines that start and end with nothing in between)"
echo -e "Answer 2:"
grep -E -n '^$' poem.txt

# Question 3
echo -e "\nQuestion 3: Pick out lines with 'rep', 'word', or 'more' (using alternator |)"
echo -e "Answer 3:"
grep -E -n 'rep|word|more' poem.txt

# Question 4
echo -e "\nQuestion 4: Pick out lines with at least two p's followed by any number of letters followed by 'ore'"
echo -e "Answer 4:"
grep -E -n 'p.*p.*ore' poem.txt

# Question 5
echo -e "\nQuestion 5: Pick out lines with 'v', 'z', or 'I' using character classes [ ]"
echo -e "Answer 5:"
grep -E -n '[vzI]' poem.txt

# Question 6
echo -e "\nQuestion 6: Pick out lines that do not start with an uppercase letter"
echo -e "Answer 6:"
grep -E -n '^[^A-Z]' poem.txt

# Question 7
echo -e "\nQuestion 7: Pick out lines that end with a dash -"
echo -e "Answer 7:"
grep -n -- "-$" poem.txt

#Question 8
echo -e "\nUse grep or egrep to pick out all the words that end with ore"
echo -e "Answer 8:"
egrep -o "\b\w*ore\b" poem.txt

#Question 9
echo -e "\nUse grep or egrep to pick out all the words that start with f or F"
echo -e "Answer 9:"
 egrep -o "\bf\w*|\b.*F\w*" poem.txt 

#Question 10
echo -e "\nUse grep or egrep to pick out lines that uses first letter alliteration - starting two
words with the same letter."
echo -e "Answer 10:"
egrep '\b(\w)\w*\s\1\w*\b' poem.txt  