package server;/*
 * Created by jakkra on 2015-02-12.
 */

import commons.Patient;

import java.io.*;

public class Database {
    private static Database db;

    public static void initiate() {
        db = new Database();
    }

    public static Database getInstance() throws Exception {
        if (db != null) {
            return db;
        } else {
            throw new Exception("Must initiate Database first");
        }
    }
    
    public void add(Patient p){
        
    }

    /**
     * @param patientId id of patient to remove
     * @return true if patient was removed (in Database) false otherwise
     */
    public boolean delete(String patientName) throws IOException {
        
        return true;
    }

    /**
     * @param id id of patient to get from database
     * @return Patient object containing fields from the database
     */
    public Patient get(String patientName) throws IOException {
        
        return null;
    }

    public boolean modifyPatient(Patient patient) {
        return true;

    }

    


    //Either a SQL database or just a text file, w/e you like :)
}
