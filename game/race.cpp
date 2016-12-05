#include <iostream>
#include <fstream>
#include <iomanip>
#include "vote.h"
#include "race.h" 

using namespace std;



    race::race(){
        office="";
        candidateNames=NULL;
        numOfCandidates=0;
        votes=NULL;
        numOfVotes=0;
    }
    race::race(string officeAA, string *candidateNamesAA,int numOfCandidatesAA){
        office = officeAA;
        numOfCandidates = numOfCandidatesAA;
        candidateNames = new string[numOfCandidates];
        for(int i=0;i<numOfCandidatesAA;i++){
            candidateNames[i]=candidateNamesAA[i];
        }
        int size = 99;
        votes = new vote[size];
        numOfVotes=0;
    }/*
    race::~race(){
        
    }
     */
    void race::singleVote(string voted){
        bool valid=false;
        while (valid==false){
            for (int i=0;i<numOfCandidates;i++){
                if (voted == candidateNames[i]){
                    valid = true;
                    vote temp;
                    temp.castVote(candidateNames[i]);
                    votes[numOfVotes] = temp;
                    numOfVotes++;
                }
            }
            if(valid==false){
            cout<<"Please enter a valid value: ";
            cin>>voted;
            }
        }
    }
    
    void race::results(){
     cout<<"In the race for "<<office<<endl<<"-"<<endl;
     for(int i=0;i<numOfCandidates;i++){
         cout<<candidateNames[i]<<endl;
     }
     cout<<"--"<<endl<<"votes tally"<<endl;
     int voteForCandi = 0;
     for(int i=0;i<numOfCandidates;i++){
         for (int j=0;j<numOfVotes;j++){
             if (candidateNames[i]==votes[j].getVote()){
                 voteForCandi++;
             }
         }
         cout<<candidateNames[i]<<"["<<voteForCandi<<"]"<<endl;
         voteForCandi=0;
     }
    }
    
