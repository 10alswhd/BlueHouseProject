package com.your.package;

import com.mongodb.MongoClient;
import java.net.UnknownHostException;
import org.mongodb.morphia.Morphia;

public class MongoDBUtil{

    private static MongoClient mongoClient = null;
    private static Morphia morphia = null;


    public static synchronized MongoClient getMongoClient() throws UnknownHostException{
        if(mongoClient == null){
            mongoClient = new MongoClient("mongo-host", mongo-port );
        }
        return mongoClient;
    }

    public static synchronized Morphia getMorphia() throws UnknownHostException{
        if(morphia == null){
            mongoClient = getMongoClient();
            morphia = new Morphia();
            morphia.mapPackage("com.your.entity/model/domain.package");
        }
        return morphia;
    }


}
