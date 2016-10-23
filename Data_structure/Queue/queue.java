package edu.marist.cmpt220l;

import edu.marist.cmpt220l.teams.Team;

/**
 * Created by Steven
 */


public class Queue {
    private Team first;
    private Team last;

    public BracketQueue() {
        this.first = null;
        this.last = null;
    }



    public void enqueue(Team team){
        Team newTeam = new Team(team);
        if (last != null) {
            last.next = newTeam;
        }
            last = newTeam;
    }


    public Team dequeue(){
        if (first != null){
            Team currTeam = first;
            first = first.next;
            return currTeam.value;
        }
    }

    public boolean isEmpty(){
        return first == null;
    }

}
