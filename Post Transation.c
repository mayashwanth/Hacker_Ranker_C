A document is represented as a collection paragraphs, a paragraph is represented as a collection of sentences, a sentence is represented as a collection of words and a word is represented as a collection of lower-case ([a-z]) and upper-case ([A-Z]) English characters.

You will convert a raw text document into its component paragraphs, sentences and words. To test your results, queries will ask you to return a specific paragraph, sentence or word as described below.

Alicia is studying the C programming language at the University of Dunkirk and she represents the words, sentences, paragraphs, and documents using pointers:

A word is described by char * .
A sentence is described by char **. The words in the sentence are separated by one space (" "). The last word does not end with a space(" ").
A paragraph is described by char*** . The sentences in the paragraph are separated by one period (".").
A document is described by char****. The paragraphs in the document are separated by one newline("\n"). The last paragraph does not end with a newline.
For example:

Learning C is fun.
Learning pointers is more fun.It is good to have pointers.

The only sentence in the first paragraph could be represented as:
char** first_sentence_in_first_paragraph = {"Learning", "C", "is", "fun"};
The first paragraph itself could be represented as:
char*** first_paragraph = {{"Learning", "C", "is", "fun"}};
The first sentence in the second paragraph could be represented as:
char** first_sentence_in_second_paragraph = {"Learning", "pointers", "is", "more", "fun"};
The second sentence in the second paragraph could be represented as:
char** second_sentence_in_second_paragraph = {"It", "is", "good", "to", "have", "pointers"};
The second paragraph could be represented as:
char*** second_paragraph = {{"Learning", "pointers", "is", "more", "fun"}, {"It", "is", "good", "to", "have", "pointers"}};
Finally, the document could be represented as:
char**** document = {{{"Learning", "C", "is", "fun"}}, {{"Learning", "pointers", "is", "more", "fun"}, {"It", "is", "good", "to", "have", "pointers"}}};
Alicia has sent a document to her friend Teodora as a string of characters, i.e. represented by char * not .char**** Help her convert the document char**** to  form by completing the following functions:

 char**** get_document(char *test)to return the document represented by char****.
 char*** kth_paragarph(char**** document,int k)to return the kth paragraph.
 char** kthy_sentence_in_mth_paragraph(char****documnet,intk,intm)to return the kth sentence in the mth paragraph.
 char* kth_word_in_mth_sentence_of_nth_pragraph(char****documnet,into return the kth word in the mth sentence of the nth paragraph.

Input Format:

The first line contains the integer paragraph_count.
Each of the next paragrapth_count lines contains a paragraph as a single string.
The next line contains the integer q, the number of queries.
Each of the next q lines or groups of lines contains a query in one of the following formats:

1 The first line contains 1 k:

The next line contains an integer x, the number of sentences in the kth paragraph.
Each of the next x lines contains an integer a[i], the number of words in the ith sentence.
This query corresponds to calling the function kth_paragraph.
2 The first line contains 2 k m:

The next line contains an integer , the number of words in the kth sentence of the mth paragraph.
This query corresponds to calling the function kth_sentence_in_mth paragraph 
3 The only line contains 3 k m n :

 This query corresponds to calling the function kth_sentence_in_mth_paragraph
Constraints

The text which is passed to the  has words separated by a space (" "), sentences separated by a period (".") and paragraphs separated by a newline("\n").
The last word in a sentence does not end with a space.
The last paragraph does not end with a newline.
The words contain only upper-case and lower-case English letters.
1<= number of characters in the entire document <=1000 
1<= number of paragraphs in the entire document <=5
Output Format

Print the paragraph, sentence or the word corresponding to the query to check the logic of your code.

Sample Input 0

2
Learning C is fun.
Learning pointers is more fun.It is good to have pointers.
3
1 2
2
5
6
2 1 1
4
3 1 1 1
Sample Output 0

Learning pointers is more fun.It is good to have pointers.
Learning C is fun
Learning
Explanation 0

The first query corresponds to returning the second paragraph with  sentences of lengths  and  words.
The second query correspond to returning the first sentence of the first paragraph. It contains  words.
The third query corresponds to returning the first word of the first sentence of the first paragraph.

/**************************************************/Code/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
    return strdup(document[n - 1][m - 1][k - 1]);
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) {
    return document[m - 1][k - 1];
}

char*** kth_paragraph(char**** document, int k) {
    return document[k - 1];
}

char**** get_document(char* text) {
    char**** document = NULL;
    char* token;

    // Split text into paragraphs
    token = strtok(text, "\n");
    int paragraph_count = 0;

    while (token != NULL) {
        document = realloc(document, (paragraph_count + 1) * sizeof(char***));
        char*** paragraph = NULL;
        char* paragraph_text = strdup(token);

        // Split paragraph into sentences (using periods followed by spaces as separators)
        char* sentence_token = strtok(paragraph_text, ". ");
        int sentence_count = 0;

        while (sentence_token != NULL) {
            paragraph = realloc(paragraph, (sentence_count + 1) * sizeof(char**));
            char** sentence = NULL;
            char* sentence_text = strdup(sentence_token);

            // Split sentence into words
            char* word_token = strtok(sentence_text, " ");
            int word_count = 0;

            while (word_token != NULL) {
                sentence = realloc(sentence, (word_count + 1) * sizeof(char*));
                sentence[word_count] = strdup(word_token);
                word_token = strtok(NULL, " ");
                word_count++;
            }

            paragraph[sentence_count] = sentence;
            sentence_token = strtok(NULL, ". ");
            sentence_count++;
        }

        document[paragraph_count] = paragraph;
        token = strtok(NULL, "\n");
        paragraph_count++;
    }

    return document;
}

char* get_input_text() {
    int paragraph_count;
    scanf("%d", &paragraph_count);
    getchar();  // Consume newline character

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));

    for (int i = 0; i < paragraph_count; i++) {
        scanf(" %[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen(doc) + 1) * sizeof(char));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count = 0;
    while (sentence[word_count] != NULL) {
        printf("%s", sentence[word_count]);
        word_count++;
        if (sentence[word_count] != NULL)
            printf(" ");
    }
}

void print_paragraph(char*** paragraph) {
    int sentence_count = 0;
    while (paragraph[sentence_count] != NULL) {
        print_sentence(paragraph[sentence_count]);
        printf(".");
        sentence_count++;
    }
}

int main() {
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3) {
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        } else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        } else {
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }

    return 0;
}

