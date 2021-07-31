# Trie
A Trie is a tree-like data structure wherein the nodes of the tree store the entire alphabet, and strings/words can be retrieved by traversing down a branch path of the tree. Each trie has an empty root node, with links (or references) to other nodes — one for each possible alphabetic value.

The shape and the structure of a trie is always a set of linked nodes, connecting back to an empty root node. An important thing to note is that the number of child nodes in a trie depends completely upon the total number of values possible. For example, if we are representing the English alphabet, then the total number of child nodes is directly connected to the total numberof letters possible. In the English alphabet, there are 26 letters, so the total number of child nodes will be 26.

Imagine, however, that we were creating a trie to hold words from the Khmer (Cambodian) alphabet, which is the longest known alphabet with 74 characters. In that case, the root node would contain 74 links to 74 other child nodes.

*The size of a trie is directly correlated to the size of all the possible values that the trie could
represent.*

## Exploration
A trie has an empty root node, which has references to children nodes. If we look at the cross-section of one of these child nodes, we’ll notice that a single node in a trie contains just two things:
- A value, which might be null
- An array of references to child nodes, all of which also might be null

Each node in a trie, including the root node itself, has only these two aspects to it. When a trie representing the English language is created, it consists of a single root node, whose value is usually set to an empty string: "".

That root node will also have an array that contains 26 references, all of which will point to null at first. As the trie grows, those pointers start to get filled up with references to other nodes nodes, which we’ll see an example of pretty soon.

The way that those pointers or references are represented is particularly interesting. We know that each node contains an array of references/links to other nodes. What’s cool about this is that we can use the array’s indexes to find specific references to nodes. For example, our root node will hold an array of indexes 0 through 25, since there are 26 possible slots for the 26 letters of the alphabet. Since the alphabet is in order, we know that the reference to the node that will contain the letter A will live at index 0.

## Insertion
What if we wanted to add a particular word to the list of words represented by this trie? We’d need to do two things in order to make this happen:
- First, we’d need to check that the word pecked doesn’t already exist in this trie.
- Next, if we’ve traversed down the branch where this word ought to live and the words doesn’t exist yet, we’d insert a value into the node’s reference where the word should go.

But how do we actually go about checking if the word exists? And how do we insert the letters into their correct places? This is easier to understand with a small trie as an example, so let’s look at a trie that is empty, and try inserting the word "pie" into it.

We know that we’ll have an empty root node, which will have a value of "", and an array with 26 references in it, all of which will be empty (pointing to null) to start. We’ll work our way through the key, using each letter to build up our trie and add nodes as necessary.

We’ll first look for the pointer for p, since the first letter in our key "pie" is p. Since this trie doesn’t have anything in just yet, the reference at p in our root node will be null. So, we’ll create a new node for p, and the root node now has an array with 25 empty slots, and 1 slot (at index 15) that contains a reference to a node.

Now we have a node at index 15, holding the value for p. But, our string is "pie", so we’re not done yet. We’ll do the same thing for this node: check if there is a null pointer at the next letter of the key: i. Since we encounter another null link for the reference at i, we’ll create another new node. Finally, we’re at the last character of our key: the e in "pie". We create a new node for the array reference to e, and inside of this third node that we’ve created, we’ll set our value: 5.

In the future, if we want to retrieve the value for the key "pie", we’ll traverse down from one array to another, using the indices to go from the nodes p, to i, to e; when we get to the node at the index for e, we’ll stop traversing, and retrieve the value from that node, which will be 5.

## Search
If we search for the key "pie”, we traverse down each node’s array, and look to see if there is a value for the branch path: p-i-e. If it does have a value, we can simply return it. This is sometimes referred to as a search hit, since we were able to find a value for the key. 

But what if we search for something that doesn’t exist in our trie? What if we search for the word "pi”, which we haven’t added as a key with a value? Well, we’ll go from the root node to the node at index p, and then we’ll go from the node at p to the node at index i . When we get to this point, we’ll see if the node at the branch path p-i has a value. In this case, it doesn’t have a value; it’s pointing at null. So, we can be sure that the key "pi" doesn’t exist in our trie as a string
with a value. This is often referred to as a search miss, since we could not find a value for the key.

## Deletion
Suppose our trie has both the keys "pie" and "pies", each with their own values. Let’s say we want to remove the key "pies" from our trie.

In order to do this, we’d need to take two steps:
- First, we need to find the node that contains the value for that key, and set its value to null. This means traversing down and finding the last letter of the word "pies”, and then esetting the value of the last node from 12 to null.

- Second, we need to check the node’s references and see if all of its pointers to other nodes are also null. If all of them are empty, that means that there are no other words/branches below this one, and they can all be removed. However, if there are pointers for other nodes that do have values, we don’t want to delete the node that we’ve just set to null.

This last check is particularly important in order to not remove longer strings when we remove substrings of a word. But other than that single check, there’s nothing more to it!

## Spell Checking
Let’s say we have a dictionary of words and then we have some other words which are to be checked in the dictionary for spelling errors. We need to have collection of all words in the dictionary which are very close to the given word. For instance if we are checking a word “ruk” we will have {“truck”,”buck”,”duck”,......}. Therefore, spelling mistake can be corrected by deleting a character from the word or adding a new character in the word or by replacing the character in the word by some appropriate one.

## Implementation
A trie node consists of the following data items:
- Meaning of the word.
- List of synonyms of the word.
- Array of pointers of type trie node of length 26.
- Flag that indicates the completion of the word.

### Operations
- #### void CreateDictionary("..\\trie\\dictionary.txt") 
Requirements: None <br> Result: A trie is created from dictionary.txt. The file is in the following format:

-piper <br>
--someone who plays the bagpipe <br>
bagpiper <br>
musician <br>
player <br>
instrumentalist <br>
-pecked <br>
--(of a bird) strike or bite something with its beak. <br>
strike <br>
beak <br>
pick <br>

The line starting with single dash (-) consists of the word. The line starting with double dash (--) consists of the meaning of the word. Afterwards the lines without any dashes consist of the synonyms until the next word or end of file.

- #### Vector< string> OutputAscending()
Requirements: Trie is not empty <br> Result: Output all the words in ascending order.

- #### Vector< string> OutputDescending()
Requirements: Trie is not empty <br> Result: Output all the words in descending order.

- ####  bool FindWord(key)
Requirements: Trie is not empty. <br> Result: Search for the word with the given key.

- ####  Vector< string> FindSynonyms(key)
Requirements: Trie is not empty. <br> Result: Search for all the synonyms for a given key.

- ####  string FindMeaning(key)
Requirements: Trie is not empty. <br> Result: Search for the meaning of a given word.

- ####  Vector< string> OutputPrefix(prefix)
Requirements: Trie is not empty. <br> Result: Search for all the words with the given prefix.

- ####  Vector< string> OutputSmaller(length)
Requirements: Trie is not empty. <br> Result: Search for all the words smaller than the given length.

- ####  Vector< string> OutputSE(length)
Requirements: Trie is not empty. <br> Result: Search for all the words equal and smaller than the given length.

- ####  Vector< string> OutputGreater(length)
Requirements: Trie is not empty. <br> Result: Search for all the words greater than the given length.

- ####  Vector< string> OutputAnagrams(key)
Requirements: Trie is not empty. <br> Result: Search for all the anagrams for a given word.

- ####  Vector< string> CompleteString(Eword)
Requirements: Trie is not empty. <br> Result: Complete the Eword by check the possible words that can be generated by the Eword.

- ####  Vector< string>SpellChecker(Eword)
Requirements: Trie is not empty. <br> Result: Check the spelling of Eword whether it is correct or not. If its not correct then return the most similar word.

- ####  Vector< string> OutputSuffix(suffix)
Requirements: Trie is not empty. <br> Result: Search for all the words with the given suffix.
