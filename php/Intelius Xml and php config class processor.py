#!/usr/bin/python -tt
# @author Jay Zeng
# @since 8/14/2011
# Utility to dynamically re-construct file 
#
# Input -> output:
# summary_intelius-2011-06-07_m27744-three-headlines-good-news-null.xml -> summary_m27744-three-headlines-good-news-null.xml
# class
# change file name and class name

import re
import os
import commands

# takes a _ delimetered string, convert into camel case
def camelcase(name):
   metachars = ['-', '_', ' '] # dash, underscore, space
   for char in metachars:
      if name.find(char) != -1:  #if string contains any special chars, go ahead to split into string arrays
         names = name.split(char)
         output = ''
         for n in names:
            n = n.capitalize()
            output += n
         return output

   # otherwise capitalize first char
   return name.capitalize()

def list_files():
   files = os.listdir('.')  # return a list of files
   matchedfiles = []
   for file in files:
      if re.search(r'.php$', file):
         matchedfiles.append(file)
   return matchedfiles

def list_xml():
   files = os.listdir('.')  # return a list of files
   matchedfiles = {}
   for file in files:
      if re.search(r'.xml$', file):
         filename = file.replace('_', '').replace('-', '').replace('.xml', '.class.php')
         parts = file.split('_')  # extract test case name
         testcase = camelcase(parts[0]) + camelcase(parts[2].replace('.xml', '').replace('-', ''))
         if filename not in matchedfiles:
            matchedfiles[filename] = testcase
   return matchedfiles

def get_prefix(name):
   prefix = re.search('(\S+)_', name)
   return prefix.group()

def get_content(file):
   fh = open(file, 'rU')
   text = fh.read()
   fh.close() # close existing file handler
   return text

def extract_name(file):
   text = get_content(file)
   classname = re.findall(r'\s(\w+)\sextends', text) # classname is a list
   c = str(classname).strip('[]').strip("'")  # strip off [] and '', converts into a strinog
   return c

def make_newclass(oldclassname, newclassname, text):
   return re.sub(oldclassname, newclassname, text)

def rename_xml():
   files = os.listdir('.')  # return a list of files
   for file in files:
      if re.search(r'.xml$', file):
         names = file.split('_')
         cmd = 'git mv ' + file.rstrip('\n') + ' '+ names[0].rstrip('\n') + '_' + names[2].rstrip('\n')
         print "Executing command: %s" % cmd
         commands.getstatusoutput(cmd)

def main():
   files = list_files()
   xmls = list_xml()

   for f in files:
      for k, v in xmls.items():
         if f == k:
            oldclassname = extract_name(f)
            newclassname = get_prefix(oldclassname) + v

            message = "Writing %s" % f
            content = make_newclass(oldclassname, newclassname, get_content(f))

            fh = open(f, 'w')
            fh.write(content)
            fh.close()
            message += '...done'
            print message
            #print "file: %s; content: %s" % (f, extract_name(f,v))

   # start to rename xml
   rename_xml()

if __name__ == '__main__':
    main()
