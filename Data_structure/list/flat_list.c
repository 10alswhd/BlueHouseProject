/*
 * flat.c
 *
 *  Created on: Apr 16, 2016
 *      Author: kkim
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

typedef enum {
    STRING,
    LIST
} Type;

typedef struct any {
    void * value;
    Type type;
} Any;

typedef struct Node{
    Any *value;
    struct Node * next;
} Node;


typedef struct List {
    Node *head;
    Node *tail;
} List;

void memory_allocation_error() {
    fprintf(stderr,"memory allocation error");
    exit(-1);
}


void * check_null(void *value) {
    if(!value)
        memory_allocation_error();
    return value;
}

#define new_of(TYPE) (TYPE*) check_null(calloc(1,sizeof(TYPE)))


Any *new_any() {
    return new_of(Any);
}

Node *new_node() {
    return new_of(Node);
}

List *new_list() {
    return new_of(List);
}


Any *anydup(Any *any) {
    Any *new = new_any();
    new->value = any->value;
    new->type = any->type;

    return new;
}

Node *nodedup(Node *node) {
    Node *new = new_node();
    new->value=anydup(node->value);
    return new;
}

Any * any_value(void *value,Type type) {
    Any *new=new_any();
    new->value=value;
    new->type=type;
    return new;
}

void list_insert_node(List *self,Node *node) {
    if (self==NULL || node==NULL)
        return;

    if (self->tail==NULL) {
        assert(self->head==NULL);
        self->head = node;
        self->tail = node;
    } else {
        self->tail->next = node;
        self->tail=node;
    }
}

void list_insert_value(List *self,Any *value) {
    Node *node;
    if(self == NULL || value == NULL)
        return;

    node = new_node();
    node->value = anydup(value);
    list_insert_node(self,node);
}

List *new_list_with(List* val,...) {
    Any *v=NULL;
    va_list va;

    if(val==NULL)
        return val;

    va_start(va,val);
    while((v=va_arg(va, Any *))!=NULL) {
        list_insert_value(val,v);
    }
    va_end(va);

    return val;
}


void print_list(FILE *,List*);

void print_any(FILE *out, Any *any) {

    if(out==NULL || any==NULL)
        return;

    switch (any->type) {
    case STRING:
        fprintf(out,"%s",(char*)any->value);
        break;
    case LIST:
        print_list(out,(List*)any->value);
    }
}

void print_list(FILE *out,List *list) {
    Node *node=NULL;

    if(out==NULL || list==NULL)
        return;

    node=list->head;
    fprintf(out,"[");
    while(node!=NULL) {
        print_any(out,node->value);
        node = node->next;
        if(node!=NULL) {
            fprintf(out,",");
        }
    }
    fprintf(out,"]");
}

#define append list_insert_value

void node_memory_free(Node *node) {
    if (node==NULL)
        return;

    if(node->value) {
        free(node->value);
        node->value=NULL;
    }

    free(node);
}

void list_memory_free(List *list) {
    Node *node = NULL;
    Node *next = NULL;

    if(list==NULL)
        return;

    node = list->head;

    while(node!=NULL) {
        next = node->next;
        node_memory_free(node);
        node = next;
    }

    free(list);
}

#define node_type(NODE)  (NODE->value->type)
#define node_type_is(NODE,TYPE) (NODE->value && node_type(NODE) == TYPE)
#define node_value(NODE) (NODE->value->value)


void flat(List *list,List *output) {
    Node *node = NULL;

    if(list==NULL || output==NULL)
        return;

    node = list->head;

    while(node!=NULL) {
        if (node_type_is(node, LIST)) {
            flat((List*)node_value(node),output);
        } else if (node_type_is(node,STRING)) {
            append(output,anydup(node->value));
        }
        node = node->next;
    }
}

int main(int argc,char *argv[]) {


    List *lista,*listb,*listc,*listd,*data,*flat_list;

    lista = new_list_with(new_list(),any_value("a",STRING));
    listb = new_list_with(new_list(),any_value("b",STRING),any_value(lista,LIST));
    listc = new_list_with(new_list(),any_value("c",STRING),any_value(listb,LIST));
    listd = new_list_with(new_list(),any_value("d",STRING),any_value(listc,LIST));

    data = new_list();
    append(data,any_value(lista,LIST));
    append(data,any_value(listb,LIST));
    append(data,any_value(listc,LIST));
    append(data,any_value(listd,LIST));
    append(data,any_value("e",STRING));

    print_list(stdout,data);
    printf("\n");

    flat_list = new_list();
    flat(data,flat_list);
    print_list(stdout,flat_list);
    printf("\n");

    list_memory_free(data);
    list_memory_free(flat_list);
    list_memory_free(lista);
    list_memory_free(listb);
    list_memory_free(listc);
    list_memory_free(listd);

}
Raw
 flat.clj
(defn my-flatten [v]
  (if(sequential? v)
    (vec (apply concat (map my-flatten v)))
    [v]))
 
 (def lista [ "a" ])
 (def listb [ "b" , lista ])
 (def listc [ "c" , listb ])
 (def listd [ "d" , listc ])
 (def data [ lista, listb, listc, listd, "e" ])
 
(println (my-flatten data))
Raw
 flat.cpp
#include <iostream>
#include <boost/assign.hpp>
#include <string>
#include <typeinfo>
#include <boost/any.hpp>


using boost::any_cast;

typedef boost::any Any;
typedef std::list<Any> List;



std::ostream& print_List(std::ostream& out, List& v) {
  if ( !v.empty() ) {
    out << '[';
    for( List::iterator it=v.begin();it!=v.end();) {
      if ((*it).type()==typeid(List)) {
           List value = any_cast<List>(*it);
           print_List(out,value);
      } else {
          std::string value = any_cast<std::string>(*it);
          out << value;
      }
      it++;
      if(it!=v.end())
         out << ',';

    }
    out << "]";
  }
  return out;
}

std::ostream& operator<< (std::ostream& out,  List& v) {
  return print_List(out,v);
}

void flat(List data, List& output) {
  for(List::iterator it=data.begin();it!=data.end();it++) {
      if ((*it).type()==typeid(List)) {
        List value = any_cast<List>(*it);
        flat(value,output);
      } else {
        std::string value = any_cast<std::string>(*it);
        output.push_back(value);
      }
  }
}

int main(int argc, char *argv[]) {

  List lista = boost::assign::list_of<Any> (std::string("a"));
  List listb = boost::assign::list_of<Any> (std::string("b"))(lista);
  List listc = boost::assign::list_of<Any>(std::string("c"))(listb);
  List listd = boost::assign::list_of<Any>(std::string("d"))(listc);

  List data = boost::assign::list_of<Any>(lista)(listb)(listc)(listd)(std::string("e"));

  std::cout << data << std::endl;

  List output;

  flat(data,output);
  std::cout << output << std::endl;

}
Raw
 flat.go

package main

import (
        "fmt"

)

func flat(list []interface{}) []interface{} {
	var ret []interface{}

	for _,v := range list {
		switch t := v.(type) {
		default:
			ret = append(ret,t)
		case []interface{}:
			for _, e :=range flat(t) {
				ret = append(ret,e)
			}
		}

	}
	return ret
}

func main()  {

        lista := []interface{} {"a"}
	listb := []interface{} {"b",lista}
	listc := []interface{} {"c",listb}
	listd := []interface{} {"d",listc}
        data := []interface{} { lista, listb, listc, listd, "e"}

	fmt.Println(data)
	fmt.Println(flat(data))

}
Raw
 flat.js

lista = ["a"];
listb = ["b", lista];
listc = ["c", listb];
listd = ["d", listc];

data = [ lista, listb, listc, listd, "e" ];

var flatten = function(arr) {
    return arr.reduce(function(output,element){
      return output.concat(Array.isArray(element)?flatten(element):element);
    },[]);
};

console.log(data);
console.log(flatten(data));
Raw
 flat.py


#data = [["a"], ["b",["a"]], ["c",["b",["a"]]], ["d",["c",["b",["a"]]]],"e"]

lista=["a"]
listb=["b",lista]
listc=["c",listb]
listd=["d",listc]
data=[lista,listb,listc,listd,"e"]

print data

def flat(input,output):
    map(lambda x: flat(x,output) if type(x) is list else output.append(x),input)

def flatouput(input,output):
    for elem in input:
        if type(elem) is list:
            flatmap(elem,output)
        else:
            output.append(elem)
            
def flatmap(input):
    ret =[]
    for elem in input:
        ret += flatmap(elem) if type(elem) is list else elem
    return ret

print flatmap(data)
Raw
 flat.rb
lista = ["a"]
listb = ["b", lista]
listc = ["c", listb]
listd = ["d", listc]

data = [ lista, listb, listc, listd, "e" ]

def flat(listdata)
  listdata.inject(Array.new) { |r,e| e.instance_of?(Array) ? r.concat(flat(e)): r << e }
end

p data.flatten
Raw
 TestFlatMap.scala
package org.testbed

/**
  * Created by kkim on 3/28/16.
  */
object TestFlatMap {

  def flatMap(in : List[Any] ): List[Any] =
    in.foldLeft(List[Any]())((result,elem) =>
      elem match  {
        case _: List[Any] => result ++ flatMap(elem.asInstanceOf[List[Any]])
        case _ => result :+ elem
      }
    )


  def main(args: Array[String]) {
    val lista = List[Any]("a")
    val listb = List[Any]("b",lista)
    val listc = List[Any]("c",listb)
    val listd = List[Any]("d",listc)
    val data = List[Any](lista,listb,listc,listd,"e")

    println(flatMap(data))

  }

}
Raw
 TestJavaFlatMap.java
package org.testbed;

import java.util.*;
import java.util.function.*;
import java.util.stream.Collector;
import java.util.stream.Collectors;

/**
 * Created by kkim on 3/28/16.
 */
public class TestJavaFlatMap {

    /**
     * Created by kkim on 3/25/16.
     * [['a'], ['b', ['a']], ['c', ['b', ['a']]], ['d', ['c', ['b', ['a']]]], 'e']
     * ['a', 'b', 'a', 'c', 'b', 'a', 'd', 'c', 'b', 'a', 'e']
     *
     */

    public static List flat(List list) {
        List ret = new ArrayList();
        for (Object o : list)
            ret.addAll((o instanceof List)?flat((List)o):Arrays.asList(o));
        return ret;
    }


    public static void main(String[] args) {
        List<Integer> test1 = Arrays.asList(1,2,3);
        List<Integer> test2 = Arrays.asList(4,5);
        List<List<Integer>> test = new ArrayList<>();
        test.add(test1);
        test.add(test2);

        System.out.println(test.stream().flatMap(Collection::stream).collect(Collectors.toList()));
        System.out.println(flat(test));

        List a = Arrays.asList("a");
        List b = Arrays.asList("b",a);
        List c = Arrays.asList("c",b);
        List d = Arrays.asList("d",c);

        List data = Arrays.asList(a,b,c,d,"e");

        System.out.println(data);
        System.out.println(flat(data));

    }
}
