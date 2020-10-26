/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: yusheng
 *
 * Created on 2020年10月15日, 下午12:12
 */

#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    char letter;
    struct node* next;
}Letter;//link list structor

/* Read a text file into a linked list of characters
 * Manipulate this linked list to perform the steps of the translation,
 */
int main() {
    FILE *myFile = fopen("C:/Users/yushe/OneDrive/Documents/NetBeansProjects/370Assignment2/testing", "r"); 
    Letter *head;
    Letter *current;
    head = NULL;
    if(myFile){
        printf("found file\n");
        char c;
        while(fscanf(myFile,"%c",&c)!= EOF ){
            Letter *node = malloc(sizeof(Letter));//allocates the memory
            node->letter = c;
            node->next =NULL;
            if(head == NULL){
                current = head = node;
            } else {
                current = current->next = node;
            }
        }//while, link list done
    }else{
        printf("didnt find file");
    }
    free(current);
    fclose(myFile);
    translate(head);
    printResult(head);
    free(head);
    return 0;
}//main

/**
 * print translated file
 * @param node head node
 */
void printResult(Letter *node){
    printf("%c",node->letter); //first letter
    while(node->next != NULL){
        node = node->next;
        printf("%c",node->letter);  
    }//go through all node
}//print result

/**
 * translated all file
 * @param node head node
 */
void translate(Letter *node){
    Letter *pointer = node;//save head note
    while(pointer->next != NULL){
        yearOne(pointer);
        pointer = pointer->next;
    }//while loop to translate who file with year 1 method
    pointer = node;
    while(pointer->next != NULL){
        yearTwo(pointer);
        pointer = pointer->next;
    }//while loop to translate who file with year 2 method
    pointer = node;
    while(pointer->next != NULL){
        yearThree(pointer);
        pointer = pointer->next;
    }//while loop to translate who file with year 3 method
    pointer = node;
    while(pointer->next != NULL){
        yearFour(pointer);
        pointer = pointer->next;
    }//while loop to translate who file with year 4 method
    free(pointer);
}//translate


/**
 * Replace all “c” with “s” if followed by the characters “e”, “i” or “y”; otherwise
replace “c” with “k”.
 * @param node head node
 */
void yearOne(Letter *node){
    if(node->letter == 'c'||node->letter == 'C'){
        if(node->next->letter == 'e'||node->next->letter == 'i'||node->next->letter == 'y'
                ||node->next->letter == 'E'||node->next->letter == 'I'||node->next->letter == 'Y'){
            if(node->letter == 'c'){
                node->letter = 's';
            }else{
                node->letter = 'S';
            }    
        }else{
            if(node->letter == 'c'){
                node->letter = 'k';
            }else{
                node->letter = 'K';
            }//else capital K   
        }//if end in c without eiy    
    }//if end in c
}//year one

/**
 * Replace all instances of “ph” with the character f
 * @param node 
 */
void yearTwo(Letter *node){
    if((node->letter == 'p'||node->letter == 'P')&&(node->next->letter == 'h'||node->next->letter == 'H')){
        node->next = node->next->next;
        if(node->letter == 'p'){
            node->letter = 'f';
        }else{
            node->letter = 'F';
        }//change ph to f
    }
}//year two

/**
 * Remove one “e” from the end of words that are more than three characters long, if
they happen to end in “e”.
 * Change all double letters to a single letter (including double spaces). Do not
remove double line spacing (i.e. “\n”).
 * When a word ends in “ed”, change that to just “d”.
 * @param node
 */
void yearThree(Letter *node){
    if(node->next == NULL){
        return;
    }//reaching end, run fail if removed
    Letter *newPointer = node;
    int wordLength = 1;
    if(newPointer->letter == '\n'||newPointer->letter == ' '
            || newPointer->letter == '.'||newPointer->letter == '?'
            ||newPointer->letter == ','){
        newPointer = newPointer->next;//move pointer forward
        if(newPointer->letter == '\n'||newPointer->letter == ' ' == NULL){
            return;//if next node is still not a letter
        }else{
            while(newPointer->next->letter != '\n'&&newPointer->next->letter != ' '
                    &&newPointer->next->letter != '.'&&newPointer->next->letter != '?'
                    &&newPointer->next->letter != ','){
                wordLength++;
                newPointer = newPointer->next;
            }//count length while loop
            if(wordLength > 3){
                if(newPointer->letter == 'e'||newPointer->letter == 'E'){
                    int i = wordLength;
                    while(i > 1){
                        node = node->next;
                        i--;
                    }//move pointer to the last 2nd letter
                    node->next = node->next->next;//delete node 'e'
                }//if end in e
            }//if longer have more than 3 letter
            if(newPointer->letter == 'd'||newPointer->letter == 'D'){
                int i = wordLength;
                while(i > 2){
                        node = node->next;
                        i--;
                    }//move pointer to the last 3rd letter
                if(node->next->letter == 'e'||node->next->letter == 'E'){
                     node->next = node->next->next;
                }//delete node 'e' if end in 'ed'
                free(newPointer);
            }//if end in 'd'
        }//if next node is a letter
    }//if current node is not a letter
    else if(node->letter == node->next->letter
            ||node->letter == node->next->letter +32
            ||node->letter == node->next->letter -32){
        node->next = node->next->next;//delete first letter
    }//if double letter
}//year three

/**
 * Replace all instances of “th” with “z”.
 * Replace all instances of “w” with “v”.
 * Remove the “o” in all instances of “ou”.
 * Remove the “a” in all instances of “ea”.
 * @param node
 */
void yearFour(Letter *node){
    if((node->letter == 't'||node->letter == 'T')&&(node->next->letter == 'h'||node->next->letter == 'H')){
        node->next = node->next->next;
        if(node->letter == 't'){
            node->letter = 'z';
        }else{
            node->letter = 'Z';
        }
    }//Replace all instances of “th” with “z”.
    if(node->letter == 'w'){
        node->letter = 'v';
    }
    if(node->letter == 'W'){
        node->letter = 'V';
    }//Replace all instances of “w” with “v”.
    if((node->next->letter == 'o'||node->next->letter == 'O')
            &&(node->next->next->letter == 'u'||node->next->next->letter == 'U')){
        node->next = node->next->next;
    }//remove o from ou
    if((node->letter == 'e'||node->letter == 'E')&&(node->next->letter == 'a'||node->next->letter == 'A')){
        node->next = node->next->next;
    }//remove a from ea
}//year four