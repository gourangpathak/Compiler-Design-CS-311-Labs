# Importing the library to deal with regular expressions.
import re

# Set of possible keywords in the input provided.
Keywords = ["if", "then", "else", "int", "return"]

# Opening the file on which Lexical Analysis will be done.
inpFile = open("inputFile2.cc", "r")
inpFileString = inpFile.read()

# Ignoring the text with the comments.
comments = re.findall("[/*].*[*/]", inpFileString)
for comment in comments:
    inpFileString = inpFileString.replace(comment, '')

print("\nOutput:")
print("---------------")

# Finding the variable names and categorising them as Keywords, Identifiers accordingly & printing them.
# We used set() to avoid duplicates.
varNames = re.findall("[_a-zA-Z]\w*", inpFileString)
varNames = set(varNames)
for var in varNames:
    if var in Keywords:
        print(var, "\tKeyword")

    else:
        print(var, "\tIdentifier")

# Finding all the integers. We used set() to avoid duplicates.
numValues = set(re.findall("\W\d\d*[.]?\d*", inpFileString))
for num in numValues:
    if (num[0] == '-'):
        print(num, "\tNum")
    else:
        print(num[1:], "\tNum")

# Printing the Symbol Table.
print("\nSymbol table:")
print("---------------")
for var in varNames:
    if var not in Keywords:
        print(var, "\t", "int")

# Closing the input file.
inpFile.close()
